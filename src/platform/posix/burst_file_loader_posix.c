/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <burst/burst_file_loader_posix.h>

#include <clog/clog.h>
#include <stdio.h>
#include <string.h>
#include <tiny-libc/tiny_libc.h>

void burst_file_loader_init(burst_file_loader *self, const char *url)
{
	tc_mem_clear_type(self);
    self->max_count = 64;
    tc_mem_clear_type_array(self->entries, self->max_count);
    self->verboseFlag = 0;
    self->shouldSimulateLoadDelay = 0;
}


void burst_file_loader_destroy(burst_file_loader* self)
{

}

static int load(const char *url, void *user_data, burst_file_loader_callback callback)
{
	static char temp[150];

	strcpy(temp, "data/");
	strcat(temp, url);

    FILE *f = fopen(temp, "rb");
	if (f == 0) {
		CLOG_ERROR("couldn't open file %s %s", url, temp)
	}
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
    uint8_t *contents = malloc(fileSize);
    fread(contents, fileSize, 1, f);
    fclose(f);

//    CLOG_DEBUG("File read done. '%s' octetCount:%ld", temp, fileSize);

    callback(user_data, contents, (int32_t)fileSize);

    tc_memset_octets(contents, 0xfb, fileSize);

    free(contents);

	return 0;
}

static int find_user_data(const burst_file_loader *self, void* user_data)
{
	for (int i=0; i<self->max_count; ++i) 
	{
		const burst_file_entry* entry = &self->entries[i];
		if (entry->user_data == user_data) {
			return i;
		}
	}
	return -1;
}

void burst_file_loader_load(burst_file_loader *self, const char *url, void *user_data, burst_file_loader_callback callback)
{
    if (self->verboseFlag) {
        CLOG_DEBUG("burst: schedule '%s' (%d) %p", url, self->entry_index, user_data);
    }
	int found_index = find_user_data(self, user_data);
	if (found_index != -1) {
		CLOG_ERROR("user data is not unique! '%s' (%p)", url, user_data)
        return;
	}
	burst_file_entry* entry = &self->entries[self->entry_index];
	self->entry_index = (self->entry_index + 1)%self->max_count;
	entry->user_data = user_data;
	entry->url = tc_str_dup(url);
	entry->callback = callback;
}

static int loadOneFile(burst_file_loader *self)
{
    if (self->entry_index == self->read_entry_index) {
        return 0;
    }

    burst_file_entry* entry = &self->entries[self->read_entry_index];

    if (self->verboseFlag) {
        CLOG_DEBUG("burst: reading '%s' (%d) %p", entry->url, self->read_entry_index, entry->user_data);
    }

    self->read_entry_index = (self->read_entry_index + 1) % self->max_count;
    int result = load(entry->url, entry->user_data, entry->callback);

    tc_free((void*)entry->url);
    entry->url = 0;
    entry->callback = 0;
    entry->user_data = 0;
    self->wait = 0;

    if (result < 0) {
        CLOG_ERROR("not working")
        return result;
    }

    return 1;
}

void burst_file_loader_poll(burst_file_loader *self)
{
    if (self->shouldSimulateLoadDelay) {
        self->wait++;
        if (self->wait < 6) {
            return;
        }
    }

    for (size_t i = 0; i < 4; ++i)
    {
        int result = loadOneFile(self);
        if (result < 0) {
            CLOG_ERROR("load error");
        }
        if (result == 0) {
            break;
        }
    }
}

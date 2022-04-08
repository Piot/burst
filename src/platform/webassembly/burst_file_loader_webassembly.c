/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <burst/burst_file_loader_webassembly.h>

#include <mocha/log.h>
#include <tiny-libc/tiny_libc.h>

static void downloadSucceeded(struct emscripten_fetch_t *fetch)
{
	burst_file_loader *self = (burst_file_loader *)fetch->userData;

	uint64_t octet_count = fetch->numBytes;
	const uint8_t *octets = (const uint8_t *)fetch->data;

	//MOCHA_LOG("Download succeeded ! %llu ", octet_count);
	self->callback(self->user_data, octets, (int32_t)octet_count);
}

static void downloadFailed(struct emscripten_fetch_t *fetch)
{
	burst_file_loader *self = (burst_file_loader *)fetch->userData;

	MOCHA_LOG("Download failed ! %p ", (void *)self);
}

void burstFileLoaderInit(burst_file_loader *self, const char *url)
{
	(void)url;

	struct emscripten_fetch_attr_t *attr = &self->attr;

	emscripten_fetch_attr_init(attr);
	tc_strncpy(attr->requestMethod, 20, "GET", 3);
	attr->attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
	attr->onsuccess = downloadSucceeded;
	attr->onerror = downloadFailed;
	attr->userData = self;
}

void burstFileLoaderLoad(burst_file_loader *self, const char *url, void *user_data, burst_file_loader_callback callback)
{
	char temp[150];

	self->callback = callback;
	self->user_data = user_data;

	strcpy(temp, "data/");
	strcat(temp, url);
	MOCHA_LOG("Fetch %s", temp);
	emscripten_fetch(&self->attr, temp);
}

void burstFileLoaderPoll(burst_file_loader *self)
{
	(void)self;

	// Intentionally do nothing. Not needed for webassembly
}

/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_posix_h
#define burst_file_loader_posix_h

#include <burst/burst_file_loader_common.h>

typedef struct burst_file_entry {
    const char *url;
    void *user_data;
    burst_file_loader_callback callback;
} burst_file_entry;

typedef struct burst_file_loader {
    burst_file_entry entries[64];
    int entry_index;
    int read_entry_index;
    int dummy;
    int wait;
    int max_count;
    int verboseFlag;
    int shouldSimulateLoadDelay;
} burst_file_loader;

void burst_file_loader_init(struct burst_file_loader* self, const char* url);
void burst_file_loader_destroy(struct burst_file_loader* self);
void burst_file_loader_load(burst_file_loader* self, const char* url, void* user_data, burst_file_loader_callback callback);
void burst_file_loader_poll(burst_file_loader* self);

#endif

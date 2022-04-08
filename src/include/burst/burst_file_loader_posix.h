/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_posix_h
#define burst_file_loader_posix_h

#include <burst/burst_file_loader_common.h>

typedef struct BurstFileEntry {
    const char *url;
    void *user_data;
    BurstFileLoaderCallback callback;
} BurstFileEntry;

typedef struct BurstFileLoader {
    BurstFileEntry entries[64];
    int entry_index;
    int read_entry_index;
    int dummy;
    int wait;
    int max_count;
    int verboseFlag;
    int shouldSimulateLoadDelay;
} BurstFileLoader;

void burstFileLoaderInit(struct BurstFileLoader* self, const char* url);
void burstFileLoaderDestroy(struct BurstFileLoader* self);
void burstFileLoaderLoad(BurstFileLoader* self, const char* url, void* user_data, BurstFileLoaderCallback callback);
void burstFileLoaderPoll(BurstFileLoader* self);

#endif

/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_ios_h
#define burst_file_loader_ios_h

#include <burst/burst_file_loader_common.h>

typedef struct burst_pending_loading {
	uint8_t* buffer;
	unsigned long count;
	BurstFileLoaderCallback callback;
	void* user_data;
} burst_pending_loading;

extern burst_pending_loading g_burst_pending_loading;

typedef struct BurstFileLoader {
	BurstFileLoaderCallback callback;
	void* user_data;
	const char* root_url;
} BurstFileLoader;

void burstFileLoaderInit(struct BurstFileLoader* self, const char* url);

void burstFileLoaderLoad(BurstFileLoader* self, const char* url, void* user_data, BurstFileLoaderCallback callback);

void burstFileLoaderPoll(BurstFileLoader* self);

#endif

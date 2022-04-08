/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_webassembly_h
#define burst_file_loader_webassembly_h

#include <burst/burst_file_loader_common.h>

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

typedef struct BurstFileLoader {
	struct emscripten_fetch_attr_t attr;
	BurstFileLoaderCallback callback;
	void* user_data;
} BurstFileLoader;

void burstFileLoaderInit(struct BurstFileLoader* self, const char* url);

void burstFileLoaderLoad(BurstFileLoader* self, const char* url, void* user_data, BurstFileLoaderCallback callback);

void burstFileLoaderPoll(BurstFileLoader* self);

#endif

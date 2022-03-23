/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_webassembly_h
#define burst_file_loader_webassembly_h

#include <burst/burst_file_loader_common.h>

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

typedef struct burst_file_loader {
	struct emscripten_fetch_attr_t attr;
	burst_file_loader_callback callback;
	void* user_data;
} burst_file_loader;

void burst_file_loader_init(struct burst_file_loader* self, const char* url);

void burst_file_loader_load(burst_file_loader* self, const char* url, void* user_data, burst_file_loader_callback callback);

void burst_file_loader_poll(burst_file_loader* self);

#endif

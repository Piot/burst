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
	burst_file_loader_callback callback;
	void* user_data;
} burst_pending_loading;

extern burst_pending_loading g_burst_pending_loading;

typedef struct burst_file_loader {
	burst_file_loader_callback callback;
	void* user_data;
	const char* root_url;
} burst_file_loader;

void burst_file_loader_init(struct burst_file_loader* self, const char* url);

void burst_file_loader_load(burst_file_loader* self, const char* url, void* user_data, burst_file_loader_callback callback);

void burst_file_loader_poll(burst_file_loader* self);

#endif

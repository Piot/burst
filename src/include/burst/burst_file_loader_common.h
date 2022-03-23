/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_common_h
#define burst_file_loader_common_h

#include <stdint.h>

struct burst_file_loader;

typedef void (*burst_file_loader_callback)(void* user_data, const uint8_t* octets, int32_t result);
void file_loader_load(struct burst_file_loader* self, const char* url, void* user_data, burst_file_loader_callback callback);

#endif

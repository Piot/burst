/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_common_h
#define burst_file_loader_common_h

#include <stdint.h>

struct BurstFileLoader;

typedef void (*BurstFileLoaderCallback)(void* user_data, const uint8_t* octets, int32_t result);
void burstFileLoaderLoad(struct BurstFileLoader* self, const char* url, void* user_data, BurstFileLoaderCallback callback);

#endif

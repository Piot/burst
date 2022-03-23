/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_h
#define burst_file_loader_h

#include <stdint.h>

#if defined TORNADO_OS_WEBASSEMBLY
#include "burst_file_loader_webassembly.h"
#elif defined TORNADO_OS_IOS
#include "burst_file_loader_ios.h"
#elif defined TORNADO_OS_MACOS || defined TORNADO_OS_LINUX || defined TORNADO_OS_WINDOWS
#include "burst_file_loader_posix.h"
#else 
#error "Unknown platform"
#endif

#endif

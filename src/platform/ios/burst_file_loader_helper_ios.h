/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef burst_file_loader_helper_h
#define burst_file_loader_helper_h

#include <burst/burst_file_loader_common.h>

@interface FileHelper : NSObject
- (void)placeGetRequest:(const char*)action withHandler:(void (^)(NSData* data, NSURLResponse* response, NSError* error))ourBlock;
- (void)loadWithSomething:(const char*)name userdata:(void*)user_data callback:(burst_file_loader_callback)callback;
@end

#endif

/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#import <Foundation/Foundation.h>
#include <clog/clog.h>
#include "burst_file_loader_helper_ios.h"
#include "burst_file_loader_ios.h"



burst_pending_loading g_buffer[128];
size_t g_write_buffer_index = 0;
size_t g_read_buffer_index = 0;

@implementation FileHelper

-(void)placeGetRequest:(const char *)c_url withHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))ourBlock {

	NSString *urlString = [NSString stringWithUTF8String:c_url];

	NSURL *url = [NSURL URLWithString:urlString];
	NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
	request.HTTPMethod = @"GET";
	[[[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:ourBlock] resume];
}

-(void)loadWithSomething:(const char*)name userdata:(void*) user_data callback:(burst_file_loader_callback) callback {
	[self placeGetRequest:name withHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        burst_pending_loading* info = &g_buffer[g_write_buffer_index++];
        g_write_buffer_index %= 128;
		info->user_data = user_data;
		info->buffer = malloc(data.length);
		info->callback = callback;
		[data getBytes:info->buffer length:data.length];
		info->count = data.length;
	}];
}

@end


void burst_file_loader_init(burst_file_loader* self, const char* base_url)
{
	self->root_url = tc_str_dup(base_url);
}

void burst_file_loader_load(burst_file_loader* self, const char* url, void* user_data, burst_file_loader_callback callback)
{
	CLOG_INFO("Loading file '%s'", url);
	FileHelper* helper = [FileHelper alloc];
	char temp[256];
	tc_snprintf(temp, 256, "%s/%s", self->root_url, url);
	[helper loadWithSomething:temp userdata:user_data callback:callback];
}

void burst_file_loader_poll(burst_file_loader* self)
{
    if (g_read_buffer_index != g_write_buffer_index) {
        burst_pending_loading* info = &g_buffer[g_read_buffer_index++];
         g_read_buffer_index %= 128;
        info->callback(info->user_data, info->buffer, info->count);
        free(info->buffer);
        info->buffer = 0;
    }
}

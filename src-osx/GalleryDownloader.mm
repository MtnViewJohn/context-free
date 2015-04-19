// GalleryDownloader.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2013 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#import "GalleryDownloader.h"
#import "CFDGController.h"
#include "variation.h"
#include <errno.h>

@interface GalleryDownloader (internal)
- (void)allDone;
@end

@implementation GalleryDownloader

- (id)initWithDesignID:(int)design controller:(CFDGController*)ctrl
{
    self = [super init];
    if (self) {
        designID = design;
        variation = Variation::random();
        controller = ctrl;
        NSString* urlstring = [NSString stringWithFormat: @"http://www.contextfreeart.org/gallery/data.php?type=cfdg&id=%d", designID];
        NSURL* url = [NSURL URLWithString: urlstring];
        NSURLRequest* req = [NSURLRequest requestWithURL: url];
        galleryConnection = [[NSURLConnection alloc] initWithRequest: req delegate: self];
        if (galleryConnection) {
            receivedData = [[NSMutableData data] retain];
        } else {
            DLerror = [[NSError alloc] initWithDomain: NSPOSIXErrorDomain code: ECONNABORTED userInfo: nil];
            [self allDone];
        }
    }
    return self;
}

- (void)dealloc
{
    [cfdgContents release]; cfdgContents = nil;
    [fileName release];     fileName = nil;
    [DLerror release];      DLerror = nil;
    if (galleryConnection) {
        [galleryConnection cancel];
        [galleryConnection autorelease];    galleryConnection = nil;
    }
    [receivedData release]; receivedData = nil;
    [super dealloc];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    [receivedData setLength: 0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [receivedData appendData: data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    [galleryConnection release];    galleryConnection = nil;
    [receivedData release];         receivedData = nil;
    DLerror = [error retain];
    [self allDone];
}

- (NSURLRequest *)connection:(NSURLConnection *)connection
             willSendRequest:(NSURLRequest *)request
            redirectResponse:(NSURLResponse *)redirectResponse
{
    NSURL* newURL = [request URL];
    NSArray* pathbits = [newURL pathComponents];
    fileName = [pathbits lastObject];
    if (fileName)
        [fileName retain];
    NSString* var = [newURL query];
    if (var) {
        NSRange varLoc = [var rangeOfString: @"variation="];
        if (varLoc.location != NSNotFound) {
            variation = Variation::fromString([[var substringFromIndex: (varLoc.location + varLoc.length)] UTF8String]);
            if (variation == -1)
                variation = 1;
        }
    }
    return request;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    cfdgContents = [receivedData retain];
    [galleryConnection release];    galleryConnection = nil;
    [receivedData release];         receivedData = nil;
    [self allDone];
}
@end

@implementation GalleryDownloader (internal)

- (void)allDone
{
    [controller performSelector: @selector(downloadDone:)
                       onThread: [NSThread mainThread]
                     withObject: self
                  waitUntilDone: NO];
}

@end

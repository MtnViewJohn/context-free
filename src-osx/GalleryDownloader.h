// GalleryDownloader.h
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


#import <Cocoa/Cocoa.h>

@class CFDGController;

@interface GalleryDownloader : NSObject <NSURLConnectionDelegate>
{
@public
    int         designID;
    NSString*   fileName;
    int         variation;
    NSData*     cfdgContents;
    NSError*    DLerror;
    
@private
    NSURLConnection*    galleryConnection;
    NSMutableData*      receivedData;
    CFDGController*     controller;
}

- (id)initWithDesignID:(int)design controller:(CFDGController*)ctrl;

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (NSURLRequest *)connection:(NSURLConnection *)connection
             willSendRequest:(NSURLRequest *)request
            redirectResponse:(NSURLResponse *)redirectResponse;
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
@end

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
#import "CFDGDocument.h"
#include "variation.h"
#include <errno.h>
#include "upload.h"


namespace {
void GalleryError(NSString* info)
{
    NSAlert* fail = [[[NSAlert alloc] init] autorelease];
    [fail setAlertStyle: NSAlertStyleWarning];
    [fail setInformativeText: info];
    [fail setMessageText: @"Context Free Downloader"];
    [fail addButtonWithTitle: @"OK"];
    [fail runModal];
}
}

@implementation GalleryDownloader

- (id)initWithDesignID:(int)design
{
    self = [super init];
    if (self) {
        designID = design;
        variation = Variation::random();
#if 1
        NSString* urlstring = [NSString stringWithFormat: @"https://www.contextfreeart.org/gallery/data.php/%d/info/foo.json", designID];
#else
        NSString* urlstring = [NSString stringWithFormat: @"http://localhost/~john/cfa2/gallery/data.php/%d/info/foo.json", designID];
#endif
        NSURL* url = [NSURL URLWithString: urlstring];
        
        NSURLSessionDataTask* download = [[NSURLSession sharedSession]
                                            dataTaskWithURL: url
                                          completionHandler:^(NSData *data,
                                                              NSURLResponse *response,
                                                              NSError *error)
                                          {
                                              if (data) {
                                                  Upload response(static_cast<const char*>([data bytes]),
                                                                  static_cast<std::size_t>([data length]));
                                                  if (response.mId == 0) {
                                                      DLerror = [[NSError alloc]
                                                                 initWithDomain: NSURLErrorDomain
                                                                           code: NSURLErrorFileDoesNotExist
                                                                       userInfo: nil];
                                                  } else {
                                                      cfdgContents = [[NSData alloc]
                                                                      initWithBytes: response.mPassword.c_str()
                                                                      length: response.mPassword.length()];
                                                      variation = response.mVariation;
                                                      fileName = [[[NSString stringWithUTF8String: response.mFileName.c_str()]
                                                                   lastPathComponent] retain];
                                                  }
                                              } else {
                                                  DLerror = [error retain];
                                              }
                                              [self performSelector: @selector(downloadDone:)
                                                           onThread: [NSThread mainThread]
                                                         withObject: nil
                                                      waitUntilDone: NO];
                                          }];
        [download resume];
        [download retain];
    }
    return self;
}

- (id)initWithUrl:(NSURL*)url
{
    self = [super init];
    if (self) {
        designID = 0;
        variation = Variation::random();
        fileName = [[[url pathComponents] lastObject] retain];
        
        NSURLSessionDataTask* download = [[NSURLSession sharedSession]
                                          dataTaskWithURL: url
                                          completionHandler:^(NSData *data,
                                                              NSURLResponse *response,
                                                              NSError *error)
                                          {
                                              cfdgContents = [data retain];
                                              DLerror = [error retain];
                                              [self performSelector: @selector(downloadDone:)
                                                           onThread: [NSThread mainThread]
                                                         withObject: nil
                                                      waitUntilDone: NO];
                                          }];
        [download resume];
        [download retain];
    }
    return self;
}

- (void)dealloc
{
    [cfdgContents release]; cfdgContents = nil;
    [fileName release];     fileName = nil;
    [DLerror release];      DLerror = nil;
    if (download) {
        if ([download state] == NSURLSessionTaskStateRunning)
            [download cancel];
        [download release];
    }
    [super dealloc];
}

- (void)downloadDone: (id)obj
{
    if (DLerror || !cfdgContents) {
        GalleryError(@"Gallery download failed.");
        return;
    }

    NSString* baseName = [fileName stringByDeletingPathExtension];
    NSString* homeDir = NSHomeDirectory();
    NSString* dlPath = [NSString stringWithFormat: @"%@/Downloads/%@.cfdg", homeDir, baseName];
    int count = 0;
    while ([[NSFileManager defaultManager] fileExistsAtPath: dlPath]) {
        ++count;
        dlPath = [NSString stringWithFormat: @"%@/Downloads/%@ %d.cfdg", homeDir, baseName, count];
    }
    
    if ([cfdgContents writeToFile: dlPath options: NSDataWritingWithoutOverwriting error: nil]) {
        [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL: [NSURL fileURLWithPath: dlPath]
                                                                               display: YES
                                                                     completionHandler:^(NSDocument * _Nullable document,
                                                                                         BOOL documentWasAlreadyOpen,
                                                                                         NSError * _Nullable error)
         {
            if (!document || error) {
                GalleryError(@"Could not open download.");
            } else {
                if ([document isKindOfClass: [CFDGDocument class]]) {
                    CFDGDocument* cfDoc = (CFDGDocument*)document;
                    [cfDoc setVariation: variation];
                    [cfDoc noteStatus: @"Download complete."];
                }
            }
        }];
    } else {
        GalleryError(@"Gallery download failed to save.");
    }

}

@end

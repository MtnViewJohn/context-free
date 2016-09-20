// AVcanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2016 John Horigan - john@glyphic.com
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


#include "AVcanvas.h"
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "BitmapImageHolder.h"

@interface AVimpl : NSObject
{
    BitmapImageHolder                    *_imageData;
    NSError                              *_error;
    AVAssetWriter                        *_assetWriter;
    AVAssetWriterInput                   *_assetInput;
    AVAssetWriterInputPixelBufferAdaptor *_assetInputAdaptor;
    BOOL                                  _isWaitingForInputReady;
    dispatch_semaphore_t                  _writeSemaphore;
    NSInteger                             _frame;
    CMTimeScale                           _frameRate;
}


- (instancetype) initWithName: (NSString*)name
                         data: (BitmapImageHolder*)bits
                    frameRate: (CMTimeScale)fps
                       format: (AVcanvas::VideoFormat)fmt;

- (void) addFrame;
- (void) finishUp;
- (NSError*) error;
@end

@implementation AVimpl
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    if ([keyPath isEqualToString:@"readyForMoreMediaData"]) {
        if (_isWaitingForInputReady && _assetInput.isReadyForMoreMediaData) {
            _isWaitingForInputReady = NO;
            dispatch_semaphore_signal(_writeSemaphore);
        }
    }
}

- (instancetype) initWithName: (NSString*)name
                         data: (BitmapImageHolder*)bits
                    frameRate: (CMTimeScale)fps
                       format: (AVcanvas::VideoFormat)fmt
{
    self = [super init];
    if (!self) return self;
    
    _imageData = [bits retain];
    _frameRate = fps;
    _writeSemaphore = dispatch_semaphore_create(0);

    NSURL* _writeURL = [NSURL fileURLWithPath: name];
    [[NSFileManager defaultManager] removeItemAtPath:[_writeURL path] error:NULL];
    
    auto codec = AVVideoCodecH264;
    if (fmt == AVcanvas::ProRes422) codec = AVVideoCodecAppleProRes422;
    if (fmt == AVcanvas::ProRes4444) codec = AVVideoCodecAppleProRes4444;
    NSDictionary *outputSettings = @{
        AVVideoCodecKey:  codec,
        AVVideoWidthKey:  [NSNumber numberWithInteger: [bits pixelsWide]],
        AVVideoHeightKey: [NSNumber numberWithInteger: [bits pixelsHigh]]
    };

    _assetInput = [[AVAssetWriterInput assetWriterInputWithMediaType: AVMediaTypeVideo
                                                      outputSettings: outputSettings]
                   retain];
    [_assetInput addObserver: self
                  forKeyPath: @"readyForMoreMediaData"
                     options: 0
                     context: NULL];
    
    // Create the asset input adapter
    NSDictionary *bufferAttributes = @{
        (NSString*)kCVPixelBufferPixelFormatTypeKey:    @(kCVPixelFormatType_32BGRA),
        (NSString*)kCVPixelBufferWidthKey:              [NSNumber numberWithInteger: [bits pixelsWide]],
        (NSString*)kCVPixelBufferHeightKey:             [NSNumber numberWithInteger: [bits pixelsHigh]]
    };
    
    _assetInputAdaptor = [[AVAssetWriterInputPixelBufferAdaptor assetWriterInputPixelBufferAdaptorWithAssetWriterInput: _assetInput
                                                                                           sourcePixelBufferAttributes: bufferAttributes]
                          retain];
    
    // Create the asset writer
    _assetWriter = [[AVAssetWriter assetWriterWithURL: _writeURL
                                             fileType: AVFileTypeQuickTimeMovie
                                                error: &_error]
                    retain];
    
    if (_error) {
        [_error retain];    // we will release later
    } else {
        if ([_assetWriter canAddInput: _assetInput]) {
            [_assetWriter addInput:_assetInput];
            [_assetWriter startWriting];
            [_assetWriter startSessionAtSourceTime:kCMTimeZero];
        } else {
            _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:kCVReturnError userInfo:nil];
        }
    }

    return self;
}

- (void) addFrame
{
    if (_error)
        return;
    if ([_assetWriter status] == AVAssetWriterStatusFailed) {
        _error = [[_assetWriter error] retain];
        return;
    }
    
    CVPixelBufferRef pxbuffer = NULL;
    CVReturn status = CVPixelBufferPoolCreatePixelBuffer(NULL, [_assetInputAdaptor pixelBufferPool], &pxbuffer);
    if (status != kCVReturnSuccess || pxbuffer == NULL) {
        _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:status userInfo:nil];
        return;
    }
    
    NSBitmapImageRep* bits = [_imageData getImageRep];
    CGImageRef image = [bits CGImage];
    if (bits == nil || image == nil) {
        _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:kCVReturnError userInfo:nil];
        return;
    }
    
    size_t width =  CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    size_t bytesPerRow = CGImageGetBytesPerRow(image);
    size_t bitsPerComponent = CGImageGetBitsPerComponent(image);
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(image);
    void *pxdata = NULL;
    
    status = CVPixelBufferLockBaseAddress(pxbuffer, 0);
    if (status != kCVReturnSuccess) {
        _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:status userInfo:nil];
        CVPixelBufferRelease(pxbuffer);
        return;
    }
    pxdata = CVPixelBufferGetBaseAddress(pxbuffer);
    
    CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pxdata, width, height,
                                                 bitsPerComponent, bytesPerRow,
                                                 rgbColorSpace, bitmapInfo);
    if (rgbColorSpace == NULL || context == NULL) {
        _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:kCVReturnError userInfo:nil];
        CGColorSpaceRelease(rgbColorSpace);
        CGContextRelease(context);
        CVPixelBufferUnlockBaseAddress(pxbuffer, 0);
        CVPixelBufferRelease(pxbuffer);
        return;
    }

    CGContextDrawImage(context, CGRectMake(0, 0, width,height), image);
    CGColorSpaceRelease(rgbColorSpace);
    CGContextRelease(context);
    CVPixelBufferUnlockBaseAddress(pxbuffer, 0);
    
    if (!_assetInput.isReadyForMoreMediaData) {
        _isWaitingForInputReady = YES;
        dispatch_semaphore_wait(_writeSemaphore, DISPATCH_TIME_FOREVER);
    }
    
    if ([_assetInputAdaptor appendPixelBuffer: pxbuffer
                         withPresentationTime: CMTimeMake(_frame * 100, _frameRate)])
    {
        ++_frame;
    } else {
        _error = [[NSError alloc] initWithDomain: NSCocoaErrorDomain code:kCVReturnError userInfo:nil];
    }
    
    CVPixelBufferRelease(pxbuffer);
}

- (void) finishUp
{
    if (_error == nil) {
        if (!_assetInput.isReadyForMoreMediaData) {
            _isWaitingForInputReady = YES;
            dispatch_semaphore_wait(_writeSemaphore, DISPATCH_TIME_FOREVER);
        }
        
        [_assetInput markAsFinished];
        [_assetWriter finishWritingWithCompletionHandler: ^{}];
    }
    
    CVPixelBufferPoolRelease([_assetInputAdaptor pixelBufferPool]);
    [_assetInput removeObserver: self
                     forKeyPath: @"readyForMoreMediaData"];
    dispatch_release(_writeSemaphore);
}

- (NSError*) error
{
    return _error;
}

- (void)dealloc
{
    [_imageData release];           _imageData = nil;
    [_error release];               _error = nil;
    [_assetInputAdaptor release];   _assetInputAdaptor = nil;
    [_assetInput release];          _assetInput = nil;
    [_assetWriter release];         _assetWriter = nil;
    [super dealloc];
}

@end

AVcanvas::AVcanvas(NSString* name, BitmapImageHolder* bits, int fps, VideoFormat format)
: aggCanvas(AV_Blend), impl([[AVimpl alloc] initWithName: name data: bits
                                               frameRate: static_cast<CMTimeScale>(fps)
                                                  format: format])
{
    if (bits)
        attach([bits bitmapData],
               static_cast<unsigned>([bits pixelsWide]),
               static_cast<unsigned>([bits pixelsHigh]),
               static_cast<int>([bits bytesPerRow]));
    mError = impl == nil || [impl error] != nil;
}

AVcanvas::~AVcanvas()
{
    [impl finishUp];
    [impl release];
}

void
AVcanvas::end()
{
    aggCanvas::end();
    
    [impl addFrame];
    if ([impl error] != nil)
        mError = true;
}


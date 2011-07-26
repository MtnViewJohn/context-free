// BitmapImageHolder.m
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009 John Horigan - john@glyphic.com
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

#import "BitmapImageHolder.h"
#import <Cocoa/Cocoa.h>


@implementation BitmapImageHolder

- (id) initWithBitmapDataPlanes: (unsigned char**)planes
                     pixelsWide: (NSInteger)width
                     pixelsHigh: (NSInteger)height
                  bitsPerSample: (NSInteger)bps
                samplesPerPixel: (NSInteger)spp
                       hasAlpha: (BOOL)alpha
                       isPlanar: (BOOL)isPlanar
                 colorSpaceName: (NSString*)colorSpaceName
                    bytesPerRow: (NSInteger)rowBytes
                   bitsPerPixel: (NSInteger)pixelBits
{
    self = [super init];
    if (!self) return self;
    
    _isPlanar = isPlanar;
    _hasAlpha = alpha;
    if (width < 1 || height < 1 || spp < 1 || spp > 5) return nil;
    _pixelsWide = width;
    _pixelsHigh = height;
    _samplesPerPixel = (unsigned int) spp;
    
    if (bps != 8 && bps != 16) return nil;
    _bitsPerSample = bps;
    
    if (colorSpaceName == nil) return nil;
    if (![colorSpaceName isEqual:NSCalibratedWhiteColorSpace] &&
        ![colorSpaceName isEqual:NSCalibratedBlackColorSpace] &&
        ![colorSpaceName isEqual:NSCalibratedRGBColorSpace] &&
        ![colorSpaceName isEqual:NSDeviceWhiteColorSpace] &&
        ![colorSpaceName isEqual:NSDeviceBlackColorSpace] &&
        ![colorSpaceName isEqual:NSDeviceRGBColorSpace] &&
        ![colorSpaceName isEqual:NSDeviceCMYKColorSpace] &&
        ![colorSpaceName isEqual:NSNamedColorSpace] &&
        ![colorSpaceName isEqual:NSPatternColorSpace] &&
        ![colorSpaceName isEqual:NSCustomColorSpace]) return nil;
    _colorSpace = [colorSpaceName retain];
    
    if (rowBytes == 0) {
        rowBytes = ((isPlanar ? 1 : spp) * bps * width) >> 3;
        rowBytes += ((-rowBytes) & 15);     // pad to 16-byte boundary
    }
    if (rowBytes < 0) return nil;
    _bytesPerRow = (unsigned int)rowBytes;
    
    if (pixelBits == 0)
        pixelBits = isPlanar ? bps : (bps * spp);
    if (pixelBits < 0) return nil;
    _bitsPerPixel = pixelBits;
    
    unsigned int planesExpected = isPlanar ? _samplesPerPixel : 1;
    unsigned int planesProvided = 0;
    
    if (planes) {
        for (unsigned int i = 0 ; i < 5; ++i) {
            if (i < planesExpected)
                _imagePlanes[i] = planes[i];
            else 
                _imagePlanes[i] = NULL;
                
            if (_imagePlanes[i]) ++planesProvided;
        }
        
        if (planesProvided == planesExpected) return self;
        if (planesProvided > 0) return nil;
    }
    
    NSUInteger planeSize = _bytesPerRow * height;
    NSUInteger bitmapsize = (isPlanar ? _samplesPerPixel : 1) * planeSize + 16;
    _imageData = [[NSMutableData dataWithLength:bitmapsize] retain];
    unsigned char* bytes = (unsigned char*)([_imageData mutableBytes]);
    bytes += ((-((long)bytes)) & 15);       // pad to 16-byte boundary
    for (unsigned int i = 0; i < 5; ++i) {
        if (i < planesExpected) {
            _imagePlanes[i] = bytes;
            bytes += planeSize;
        } else {
            _imagePlanes[i] = NULL;
        }
    }
    
    return self;
}

- (void)dealloc
{
    [_imageData release];       _imageData = nil;
    [_colorSpace release];      _colorSpace = nil;
    [super dealloc];
}

- (int) bitsPerPixel { return _bitsPerPixel; }
- (int) samplesPerPixel { return _samplesPerPixel; }
- (BOOL) isPlanar { return _isPlanar; }
- (int) numberOfPlanes { return _isPlanar ? _samplesPerPixel : 1; }
- (int) bytesPerPlane { return _bytesPerRow * _pixelsHigh; }
- (int) bytesPerRow { return _bytesPerRow; }
- (int) bitsPerSample { return _bitsPerSample; }
- (NSString *) colorSpaceName { return _colorSpace; }
- (BOOL) hasAlpha { return _hasAlpha; }
- (int) pixelsHigh { return _pixelsHigh; }
- (int) pixelsWide { return _pixelsWide; }

//
// Getting Image Data 
//
- (unsigned char*) bitmapData { return _imagePlanes[0]; }
- (void) getBitmapDataPlanes: (unsigned char**)data
{
    for (unsigned int i = 0; i < 5; ++i)
        data[i] = _imagePlanes[i];
}


//
// Getting an NSBitmapImageReps
//
- (NSBitmapImageRep*) newImageRep
{
    return [[NSBitmapImageRep alloc]
            initWithBitmapDataPlanes: _imagePlanes
            pixelsWide: _pixelsWide
            pixelsHigh: _pixelsHigh
            bitsPerSample: _bitsPerSample
            samplesPerPixel: _samplesPerPixel
            hasAlpha: _hasAlpha
            isPlanar: _isPlanar
            colorSpaceName: _colorSpace
            bytesPerRow: _bytesPerRow
            bitsPerPixel: _bitsPerPixel
            ];
}

- (NSBitmapImageRep*) getImageRep
{
    return [[[NSBitmapImageRep alloc]
             initWithBitmapDataPlanes: _imagePlanes
                           pixelsWide: _pixelsWide
                           pixelsHigh: _pixelsHigh
                        bitsPerSample: _bitsPerSample
                      samplesPerPixel: _samplesPerPixel
                             hasAlpha: _hasAlpha
                             isPlanar: _isPlanar
                       colorSpaceName: _colorSpace
                          bytesPerRow: _bytesPerRow
                         bitsPerPixel: _bitsPerPixel
             ] autorelease];
}

- (NSBitmapImageRep*) getImageRepCropped: (NSRect)cropRect
{
    unsigned char* planes[5];
    int offset =    (int)cropRect.origin.y * _bytesPerRow + 
                    (int)cropRect.origin.x * (_bitsPerPixel >> 3);
    for (unsigned int i = 0; i < 5; ++i)
        planes[i] = _imagePlanes[i] ? (_imagePlanes[i] + offset) : NULL;
    int width = (int)cropRect.size.width;
    int height = (int)cropRect.size.height;

    return [[[NSBitmapImageRep alloc]
             initWithBitmapDataPlanes: planes
                           pixelsWide: width
                           pixelsHigh: height
                        bitsPerSample: _bitsPerSample
                      samplesPerPixel: _samplesPerPixel
                             hasAlpha: _hasAlpha
                             isPlanar: _isPlanar
                       colorSpaceName: _colorSpace
                          bytesPerRow: _bytesPerRow
                         bitsPerPixel: _bitsPerPixel
             ] autorelease];
}

@end

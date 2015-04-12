// qtCanvas.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2011-2012 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "qtCanvas.h"
#import <QTKit/QTKit.h>
#import <Cocoa/Cocoa.h>
#if !__LP64__
#import <QuickTime/QuickTime.h>
#endif

class qtCanvas::Impl
{
    Impl(NSString* name, BitmapImageHolder* bits, int fps, int qual, bool mpeg4);
    ~Impl();
    
    void addFrame();
    void enterThread();
    void exitThread();
    
    int             mFrameRate;
    NSSize          mSize;
    
#if !__LP64__
    DataHandler     mDataHandler;
#endif
    QTMovie*        mMovie;
    
    NSDictionary*   mDict;
    
    BitmapImageHolder* mImageData;
    
    NSError*        mError;

    friend class qtCanvas;
    friend struct std::default_delete<qtCanvas::Impl>;
};

qtCanvas::Impl::Impl(NSString* name, BitmapImageHolder* bits, int fps, 
                     int qual, bool mpeg4)
: mFrameRate(fps), mDict(nil), mImageData([bits retain]), mError(nil)
{
#if !__LP64__
    mDataHandler = nil;
#endif
    mSize.width  = (CGFloat)[bits pixelsWide];
    mSize.height = (CGFloat)[bits pixelsHigh];
    
    // Check first if the new QuickTime 7.2.1 initToWritableFile: method is available
    if ([[[[QTMovie alloc] init] autorelease] respondsToSelector:@selector(initToWritableFile:error:)] == YES)
    {
        mMovie = [[QTMovie alloc] initToWritableFile: name error: &mError];
        [mError retain];
    } else {
#if !__LP64__
        OSErr   err = -1;
        Handle  dataRef = nil;
        OSType  dataRefType;
        
        // create a file data reference for our movie
        err = QTNewDataReferenceFromFullPathCFString((CFStringRef)name,
                                                     (QTPathStyle)kQTNativeDefaultPathStyle,
                                                     0, &dataRef, &dataRefType);
        
        // create a QuickTime movie from our file data reference
        Movie qtMovie = nil;
        if (err == noErr) {
            CreateMovieStorage(dataRef, dataRefType, 'TVOD', smSystemScript,
                               createMovieFileDeleteCurFile |
                               createMovieFileDontCreateResFile |
                               newMovieActive, &mDataHandler, &qtMovie);
            err = GetMoviesError();
        }
        
        if (err != noErr) {
            DisposeHandle(dataRef);
            mError = [[NSError alloc] initWithDomain: NSOSStatusErrorDomain 
                                                code: (NSInteger)err userInfo: nil];
        } else {
            mMovie = [[QTMovie movieWithQuickTimeMovie:qtMovie disposeWhenDone:YES 
                                                 error: &mError] retain];
            [mError retain];
        }
#else
        mError = [[NSError alloc] initWithDomain: @"" code: (NSInteger)42 userInfo: nil];
#endif
    }
    
    if (mMovie && !mError) {
        [mMovie setAttribute:[NSNumber numberWithBool:YES] forKey:QTMovieEditableAttribute];
        [mMovie detachFromCurrentThread];
        
        long q = codecLosslessQuality;
        switch (qual) {
            case 0:
                q = codecMinQuality; break;
            case 1:
                q = codecLowQuality; break;
            case 2:
                q = codecNormalQuality; break;
            case 3:
                q = codecHighQuality; break;
            default:
                q = codecLosslessQuality; break;
        }
        
        mDict = [[NSDictionary dictionaryWithObjectsAndKeys:mpeg4 ? @"mp4v" : @"rle ",
                    QTAddImageCodecType,
                    [NSNumber numberWithLong: q],
                    QTAddImageCodecQuality,
                    nil] retain];
    }
}

qtCanvas::Impl::~Impl()
{
    [mMovie release]; mMovie = nil;
    [mError release]; mError = nil;
    [mDict release];  mDict = nil;
    [mImageData release];; mImageData = nil;
}

void
qtCanvas::Impl::addFrame()
{
    NSImage* img = [[NSImage alloc] initWithSize: mSize];
    NSBitmapImageRep* rep = [mImageData newImageRep];
    [img addRepresentation: rep];
                             ;
    [mMovie addImage: img forDuration: QTMakeTime(100, mFrameRate) 
      withAttributes: mDict];
    
    [img release];
    [rep release];
}

void
qtCanvas::Impl::enterThread()
{
    [QTMovie enterQTKitOnThread];
    [mMovie attachToCurrentThread];
}

void
qtCanvas::Impl::exitThread()
{
    [mMovie updateMovieFile];
    [mMovie invalidate];
#if !__LP64__
    if (mDataHandler)
        UpdateMovieInStorage([mMovie quickTimeMovie], mDataHandler);
    DisposeMovie([mMovie quickTimeMovie]);
    if (mDataHandler)
        CloseMovieStorage(mDataHandler);
#endif
    [mMovie detachFromCurrentThread];
    [QTMovie exitQTKitOnThread];
}

qtCanvas::qtCanvas(NSString* name, BitmapImageHolder* bits, 
                   int fps, int qual, bool mpeg4)
: aggCanvas(QT_Blend), impl(new Impl(name, bits, fps, qual, mpeg4))
{
    if (bits)
        attach([bits bitmapData], static_cast<unsigned>([bits pixelsWide]),
               static_cast<unsigned>([bits pixelsHigh]),
               static_cast<int>([bits bytesPerRow]));
}

qtCanvas::~qtCanvas() = default;

void
qtCanvas::end()
{
    aggCanvas::end();

    impl->addFrame();
}

NSError*
qtCanvas::getError() const
{
    return impl->mError;
}

void
qtCanvas::enterThread()
{
    impl->enterThread();
}

void
qtCanvas::exitThread()
{
    impl->exitThread();
}

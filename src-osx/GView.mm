// GView.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2013 John Horigan - john@glyphic.com
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

#import "GView.h"
#import "CFDGDocument.h"
#import "VariationFormatter.h"
#import "TopBar.h"
#import "BitmapImageHolder.h"

#include "cfdg.h"
#include "SVGCanvas.h"
#include "ImageCanvas.h"
#include "qtCanvas.h"
#include "tiledCanvas.h"
#include "Rand64.h"
#include <tgmath.h>

// Provide the forward-declarations of new 10.7 SDK symbols so they can be
// called when building with the 10.5 SDK.
#if !defined(MAC_OS_X_VERSION_10_7) || \
MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7

@interface NSWindow (LionSDKDeclarations)
- (void)toggleFullScreen:(id)sender;
@end

enum {
    NSWindowCollectionBehaviorFullScreenPrimary = 1 << 7,
    NSWindowCollectionBehaviorFullScreenAuxiliary = 1 << 8
};

enum {
    NSWindowFullScreenButton = 7
};

enum {
    NSFullScreenWindowMask = 1 << 14
};
#endif  // MAC_OS_X_VERSION_10_7

//#define PROGRESS_ANIMATE_DIRECTLY
//#define USE_SAVE_GRAPHICS_STATE
//#define TIME_AND_LOG_RENDER

#define UPDATE_RATE         (1.0/12.0)
#define PROGRESS_DELAY      12


@interface BitmapAndFormat : BitmapImageHolder {
    aggCanvas::PixelFormat _aggPixFmt;    
}

- (id) initWithAggPixFmt: (aggCanvas::PixelFormat)fmt
              pixelsWide: (NSInteger)width
              pixelsHigh: (NSInteger)height;
- (aggCanvas::PixelFormat) aggPixelFormat;

@end

@implementation BitmapAndFormat

- (id) initWithAggPixFmt: (aggCanvas::PixelFormat)fmt
              pixelsWide: (NSInteger)width
              pixelsHigh: (NSInteger)height
{
    int bps = (fmt & aggCanvas::Has_16bit_Color) + 8;
    
    switch (fmt) {
        case aggCanvas::RGBA8_Blend:
        case aggCanvas::RGBA16_Blend:
            self = [super initWithBitmapDataPlanes: nullptr
                                        pixelsWide: width
                                        pixelsHigh: height
                                     bitsPerSample: bps 
                                   samplesPerPixel: 4
                                          hasAlpha: YES isPlanar: NO
                                    colorSpaceName: NSCalibratedRGBColorSpace
                                       bytesPerRow: 0 bitsPerPixel: 0];
            break;
        case aggCanvas::RGB8_Blend:
        case aggCanvas::RGB16_Blend:
            self = [super initWithBitmapDataPlanes: nullptr
                                        pixelsWide: width
                                        pixelsHigh: height
                                     bitsPerSample: bps 
                                   samplesPerPixel: 3
                                          hasAlpha: NO isPlanar: NO
                                    colorSpaceName: NSCalibratedRGBColorSpace
                                       bytesPerRow: 0 bitsPerPixel: 0];
            break;
        case aggCanvas::Gray8_Blend:
        case aggCanvas::Gray16_Blend:
            self = [super initWithBitmapDataPlanes: nullptr
                                        pixelsWide: width
                                        pixelsHigh: height
                                     bitsPerSample: bps 
                                   samplesPerPixel: 1
                                          hasAlpha: NO isPlanar: NO
                                    colorSpaceName: NSCalibratedWhiteColorSpace
                                       bytesPerRow: 0 bitsPerPixel: 0];
            break;
        default:
            return nil;
    }
    if (!self) return self;

    _aggPixFmt = fmt;

    return self;
}

- (aggCanvas::PixelFormat) aggPixelFormat { return _aggPixFmt; }

@end

@interface GView (internal)

- (void)drawCheckerboardRect:(NSRect)rect;

- (void)buildEngine;
- (void)buildRendererSize:(NSSize)size minimum:(double)minSize;
- (void)buildImageCanvasSize;

- (void)invalidateDrawingImage;
- (void)validateDrawingImage;

- (void)noteProgress;
- (void)requestRenderUpdate;

- (void)showSavePanelTitle:(NSString *)title
        fileType:(NSString *)fileType
        accessoryView:(NSView *)view
        didEndSelector:(SEL)selector;

- (void)saveImagetoFile:(NSURL*)filename;
- (void)saveTileImagetoFile:(NSURL*)filename;
- (void)saveSvgtoFile:(NSURL*)filename;
- (void)saveMovietoFile:(NSURL*)filename;

- (void)deleteRenderer;
+ (void)rendererDeleteThread:(id)arg;
@end


namespace {
    NSURL*    saveImageDirectory = nil;

    NSString* PrefKeyMovieZoom = @"MovieZoom";
    NSString* PrefKeyMovieLength = @"MovieLength";
    NSString* PrefKeyMovieFrameRate = @"MovieFrameRate";
    NSString* PrefKeyMovieFormat = @"MovieFormat";
    NSString* PrefKeyMovieQuality = @"MovieQuality";


    class RenderParameters
    {
    public:
        bool    render;
        bool    periodicUpdate;
        bool    animate;
        bool    animateZoom;
        int     animateFrameCount;

        RenderParameters()
            : render(true), periodicUpdate(true), animate(false)
            { }
    };
        
}


@interface GView (renderThread)
- (void) renderBegin:(RenderParameters*)parameters;
- (void) renderThread:(id)arg;
- (void) renderStopped:(id)arg; // sent by thread
@end


@implementation GView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        mEngine = nullptr;
        mRenderer = nullptr;
        mCanvas = nullptr;
        
        mRenderBitmap = nil;
        mDrawingImage = nil;
        mRestartRenderer = false;
        mUpdateTimer = nil;
        
        mRendering = false;
        mRestartRenderer = false;
        mRendererFinishing = false;
        mRendererStopping = false;
        mLastRenderWasHires = false;
        mCloseOnRenderStopped = false;
        
        mCurrentVariation = 0;
        mIncrementVariationOnRender = false;

        mAnimationCanvas = nullptr;

        mTiled = false;
        
        mFullScreenMenu = nil;
    }
    return self;
}

- (void)awakeFromNib
{
    [mSaveImageAccessory retain];
    [mSaveTileAccessory retain];
    [mSaveAnimationAccessory retain];
    [mDocument retain];
    [self initializeVariation];
    
    NSNumber* one = [NSNumber numberWithInt: 1];
    NSNumber* hundred = [NSNumber numberWithInt: 100];
    NSNumberFormatter* fmt = [mSaveTileWidth formatter];
    [fmt setMinimum: one];
    [fmt setMaximum: hundred];
    fmt = [mSaveTileHeight formatter];
    [fmt setMinimum: one];
    [fmt setMaximum: hundred];
    [mSaveTileWidth setFloatValue: 1.0];
    [mSaveTileHeight setFloatValue: 1.0];
    
    NSWindow* window = [self window];
    if ([window respondsToSelector:@selector(toggleFullScreen:)]) {
        NSWindowCollectionBehavior behavior = [window collectionBehavior];
        behavior |= NSWindowCollectionBehaviorFullScreenPrimary;
        [window setCollectionBehavior:behavior];

        NSButton* fullscreenButton =
            [window standardWindowButton:NSWindowFullScreenButton];
        [fullscreenButton setAction:@selector(enterFullscreen:)];
        [fullscreenButton setTarget:self];
        
        NSMenuItem* winMenu = [[NSApp mainMenu] itemWithTitle: @"Window"];
        mFullScreenMenu = [[winMenu submenu] itemWithTag: (NSInteger)420];
    }
    [window setDelegate: self];
}

- (void)windowDidBecomeMain:(NSNotification *)notification
{
    [self updateFullScreenMenu];
}
- (void)windowDidEnterFullScreen:(NSNotification *)notification
{
    [self updateFullScreenMenu];
}
- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    [self updateFullScreenMenu];
}
- (BOOL)windowShouldClose:(id)sender
{
    if (mRendering && mRenderer) {
        mRenderer->requestStop = true;
        mCloseOnRenderStopped = true;
        return NO;
    }
    return YES;
}

- (void)windowWillClose:(NSNotification *)notification
{
    [self deleteRenderer];
}

- (void)updateFullScreenMenu
{
    NSUInteger masks = [[self window] styleMask];
    if (masks & NSFullScreenWindowMask) {
        [mFullScreenMenu setTitle: @"Exit Full Screen"];
    } else {
        [mFullScreenMenu setTitle: @"Enter Full Screen"];
    }
}

- (void)dealloc
{
    [self deleteRenderer];
    [mDocument release];            mDocument = nil;
    [mDrawingImage release];        mDrawingImage = nil;
    [mRenderBitmap release];        mRenderBitmap = nil;
    [mUpdateTimer release];         mUpdateTimer = nil;
    [mSaveImageAccessory release];  mSaveImageAccessory = nil;
    [mSaveTileAccessory release];  mSaveTileAccessory = nil;
    [mSaveAnimationAccessory release]; mSaveAnimationAccessory = nil;
    
    [super dealloc];
}

- (IBAction)enterFullscreen:(id)sender
{
    [[self window] toggleFullScreen: nil];
}

- (BOOL)isOpaque
{
    return YES;
}

- (void)drawRect:(NSRect)rect
{
    [self validateDrawingImage];
    
    if (!mDrawingImage) {
        [[NSColor whiteColor] set];
        [NSBezierPath fillRect: rect];
        return;
    }
    
    agg::rgba backgroundColor(1.0, 1.0, 1.0, 1.0);
    if (mEngine && mRenderer)
        backgroundColor = mEngine->getBackgroundColor();
    
    if (backgroundColor.opacity() < 1.0) {
        [self drawCheckerboardRect: rect];
    }
    
    [[NSColor colorWithCalibratedRed: backgroundColor.r
                               green: backgroundColor.g
                                blue: backgroundColor.b
                               alpha: backgroundColor.a ] set];
    [NSBezierPath fillRect: rect];
    
    NSGraphicsContext* ctx = [NSGraphicsContext currentContext];
    NSImageInterpolation oldInterp = [ctx imageInterpolation];
    [ctx setImageInterpolation:
        [self inLiveResize]
            ? NSImageInterpolationNone
#if 0
            : NSImageInterpolationHigh
#else
            : NSImageInterpolationDefault
#endif
        ];
    
    NSSize fSize = [self frame].size;
    NSSize rSize = mRenderedRect.size;

    CGFloat scale;
    if (rSize.width <= fSize.width  &&  rSize.height <= fSize.height) {
        // rendered area fits within frame, center it
        scale = 1.0;
    } else {
        CGFloat wScale = fSize.width / rSize.width;
        CGFloat hScale = fSize.height / rSize.height;
        scale = (hScale < wScale) ? hScale : wScale;
    }

    NSRect dRect;

    // center scaled image rectangle
    dRect.size.width = rSize.width * scale;
    dRect.size.height = rSize.height * scale;
    int ox = static_cast<int>(dRect.origin.x = floor((fSize.width - dRect.size.width) * ((CGFloat)0.5)));
    int oy = static_cast<int>(dRect.origin.y = floor((fSize.height - dRect.size.height) * ((CGFloat)0.5)));

    if (mTiled && mRenderer && mRenderer->m_tiledCanvas && scale == 1.0) {
        tileList points = mRenderer->m_tiledCanvas->getTesselation(static_cast<int>(fSize.width), static_cast<int>(fSize.height), ox, oy);
        
        for (agg::point_i& pt: points) {
            NSPoint dPoint = NSMakePoint(pt.x, pt.y);
            
            if (backgroundColor.opacity() < 1.0) {
                NSRect cRect = dRect;
                cRect.origin = dPoint;
                // redraw checkerboard to erase global fill
                [self drawCheckerboardRect: NSIntersectionRect(cRect, rect)];
            }
            
            [mDrawingImage drawAtPoint: dPoint fromRect: NSZeroRect
                             operation: NSCompositeSourceAtop
                              fraction: 1.0];
        }
            
        NSRect boxRect = NSInsetRect(dRect, -0.5, -0.5);
        [[NSColor colorWithDeviceWhite: 0.0 alpha: 0.35 ] set];
        [NSBezierPath strokeRect: boxRect];
        
        boxRect = NSInsetRect(dRect, -1.5, -1.5);
        [[NSColor colorWithDeviceWhite: 1.0 alpha: 0.75 ] set];
        [NSBezierPath strokeRect: boxRect];
    } else {
        if (backgroundColor.opacity() < 1.0) {
            // redraw checkerboard to erase global fill
            [self drawCheckerboardRect: NSIntersectionRect(dRect, rect)];
        }
        
        [mDrawingImage drawInRect: dRect
                         fromRect: NSZeroRect
                        operation: NSCompositeSourceAtop
                         fraction: 1.0];
    }
    
    [ctx setImageInterpolation: oldInterp];
}

- (void)viewDidEndLiveResize
{
    [super viewDidEndLiveResize];
    [self setNeedsDisplay:YES];
}

- (IBAction)toggleRender:(id)sender
{
    if (mRendering)     [self finishRender: sender];
    else                [self startRender: sender];
}

- (IBAction)saveImage:(id)sender
{
    if (mTiled) {
        [self saveTileImage: sender];
    } else {
        [self showSavePanelTitle: NSLocalizedString(@"Save Image", @"")
            fileType: @"png"
            accessoryView: mSaveImageAccessory
            didEndSelector: @selector(saveImagetoFile:)];
    }
}

- (IBAction)saveTileImage:(id)sender
{
    CFDG::frieze_t frz = mEngine->isFrieze();
    switch (frz) {
        case CFDG::no_frieze:
            [mSaveTileWidth setEnabled: YES];
            [mSaveTileHeight setEnabled: YES];
            break;
        case CFDG::frieze_x:
            [mSaveTileHeight setFloatValue: 1.0];
            [mSaveTileWidth setEnabled: YES];
            [mSaveTileHeight setEnabled: NO];
            break;
        case CFDG::frieze_y:
            [mSaveTileWidth setFloatValue: 1.0];
            [mSaveTileWidth setEnabled: NO];
            [mSaveTileHeight setEnabled: YES];
            break;
    }
    
    [self showSavePanelTitle: NSLocalizedString(@"Save Image", @"")
                    fileType: @"png"
               accessoryView: mSaveTileAccessory
              didEndSelector: @selector(saveTileImagetoFile:)];
}

- (IBAction)saveAsSVG:(id)sender
{
    [self showSavePanelTitle: NSLocalizedString(@"Save as SVG", @"")
        fileType: @"svg"
        accessoryView: nil
        didEndSelector: @selector(saveSvgtoFile:)];
}

- (IBAction)saveAsMovie:(id)sender
{
    [self showSavePanelTitle: NSLocalizedString(@"Save as Animation", @"")
        fileType: @"mov"
        accessoryView: mSaveAnimationAccessory
        didEndSelector: @selector(saveMovietoFile:)];
}

- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
{
    SEL action = [anItem action];
    
    if (action == @selector(startRender:))
        return !mRestartRenderer;
    
    if (action == @selector(enterFullscreen:))
        return YES;
        
    if (action == @selector(showHiresRenderSheet:)
    ||  action == @selector(repeatRender:))
        return !mRendering;
            
    if (action == @selector(finishRender:))
        return mRendering && !mRendererFinishing && !mRendererStopping;

    if (action == @selector(stopRender:))
        return mRendering && !mRendererStopping;
    
    if (action == @selector(saveImage:)
    ||  action == @selector(saveAsSVG:)
    ||  action == @selector(saveAsMovie:)
    ||  action == @selector(uploadToGallery:))
        return !mRendering && mRenderBitmap;
            
    return [super validateMenuItem: anItem];
}

- (IBAction) showHiresRenderSheet:(id)sender
{
    [mDocument showHiresRenderSheet: sender];
}

- (void)redisplayImage:(NSValue*)rectObj
{
    mRenderedRect = [rectObj rectValue];
    [self invalidateDrawingImage];
    [self setNeedsDisplay: YES];
}

- (void)noteStats:(NSValue*)value
{
    AbstractSystem::Stats s;
    [value getValue: &s];
    
    NSString *message =
        [NSString localizedStringWithFormat: @"%d shapes",
                s.shapeCount];
    
    if (s.inOutput || s.animating) {
        if (s.fullOutput || s.finalOutput || s.animating) {
            NSString* prefix = s.finalOutput ? @"drawing - " : @"rescaling - ";
            message = [NSLocalizedString(prefix, @"")
                stringByAppendingString: message];
        }
    }
    
    if (s.toDoCount > 0 && !s.finalOutput) {
        message = [message stringByAppendingString:
            [NSString localizedStringWithFormat:
                @" - %d expansions to do", s.toDoCount]];
    }
    else {
        message = [message stringByAppendingString:
            [NSString localizedStringWithFormat:
                @", %d x %d pixels",
                (int)mRenderedRect.size.width,
                (int)mRenderedRect.size.height]];
        if (mTiled) {
            message = [message stringByAppendingString: @", tiled"];
        }
    }
    
#if 0
    if (!s.inOutput) {
        message = [message stringByAppendingString:
            [NSString localizedStringWithFormat:
                @" in %.3f seconds",
                static_cast<double>(s.outputTime) / CLOCKS_PER_SEC]];
    }
#endif
    
    [mStatus setStringValue: message];
    
    if ((s.inOutput && s.fullOutput) || s.showProgress) {
        if (mOutputProgressDelay == PROGRESS_DELAY) {
            [mOutputProgress setHidden: NO];
            [mTopBar relayout];
            mOutputProgressDelay += 1;
        }
        if (mOutputProgressDelay >= PROGRESS_DELAY) {
            double v = 100.0 * s.outputDone / s.outputCount;
            [mOutputProgress setDoubleValue: v];
        }
        else {
            mOutputProgressDelay += 1;
        }
    }
    else {
        if (mOutputProgress > 0) {
            [mOutputProgress setHidden: YES];
            [mTopBar relayout];
            mOutputProgressDelay = 0;
        }
    }
}


-(int)variation
{
    return mCurrentVariation;
}

-(bool)canvasColor256
{
    return mCanvasColor256;
}

-(bool)isTiled
{
    return mTiled;
}

-(int)isFrieze
{
    return (mTiled && mEngine) ? mEngine->isFrieze() : 0;
}

- (NSData*) pngImageDataCropped:(BOOL)cropped multiplier:(NSSize*) mult;
{
    NSBitmapImageRep* bits;
    
    if (mult) {
        NSRect iRect = NSMakeRect(0.0, 0.0, 0.0, 0.0);
        iRect.size = mRenderedRect.size;
        
        NSRect fRect = iRect;
        fRect.size.width *= mult->width;
        fRect.size.height *= mult->height;
        
        tileList points = mRenderer->m_tiledCanvas->getTesselation(static_cast<int>(fRect.size.width),
                                                                   static_cast<int>(fRect.size.height), 0, 0);
        
        NSImage* tileImage = [[NSImage alloc] initWithSize: fRect.size];

        [self validateDrawingImage];
        
        [tileImage lockFocus];
        
        for (agg::point_i& pt: points) {
            [mDrawingImage drawAtPoint: NSMakePoint(pt.x, pt.y)
                              fromRect: NSZeroRect
                             operation: NSCompositeCopy
                              fraction: 1.0];
        }

        bits = [[NSBitmapImageRep alloc]
                    initWithFocusedViewRect: fRect];

        [tileImage unlockFocus];
        [tileImage release];
        [bits autorelease];
    }
    else if (cropped) {
        bits = [mRenderBitmap getImageRepCropped: mRenderedRect];
    }
    else {
        bits = [mRenderBitmap getImageRep];
    }
    
    CGImageRef iref = [bits CGImage];
    if (!iref) return nil;
    
    NSMutableData* mdata = [NSMutableData data];
    CGImageDestinationRef destref = 
        CGImageDestinationCreateWithData((CFMutableDataRef)mdata,
                                         (CFStringRef)@"public.png", 1, nil);
    if (!destref) return nil;
    
    CGImageDestinationAddImage(destref, iref, nullptr);
    CGImageDestinationFinalize(destref);
    CFRelease(destref);
    return mdata;
}

@end








@implementation GView (renderControl)

- (IBAction) repeatRender:(id)sender
{
    if (mLastRenderWasHires) {
        [self updateVariation: YES];
        
        [self startHiresRender: mLastRenderSize
                       minimum: mLastRenderMin];
    } else {
        [self startRender: sender];
    }
}

- (IBAction) startRender:(id)sender
{
    mLastRenderWasHires = false;
    
    if (mRendering) {
        if (!mRestartRenderer) {
            mRestartRenderer = true;
            [self stopRender: sender];
        }
        return;
    }

    [self updateVariation: YES];

    NSSize size = [self frame].size;

    [self buildEngine];
    if (!mEngine) return;
    
    if (mEngine->isTiled()) {
        size.width *= 0.9f;
        size.height *= 0.9f;
    }
    
    [self buildRendererSize: size minimum: 0.3]; 
    if (!mRenderer) return;
    [self buildImageCanvasSize];
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    
    RenderParameters parameters;
    parameters.periodicUpdate = [defaults boolForKey: @"ProgressiveUpdate"];

    [self renderBegin: &parameters];
}

- (IBAction) finishRender:(id)sender
{
    if (mRendererFinishing) {
        [self stopRender: sender];
    }
    if (mRendering  &&  !mRendererFinishing && !mRendererStopping) {
        if (mRenderer)
            mRenderer->requestFinishUp = true;
        
        mRendererFinishing = true;
        [mRenderControl setTitle: NSLocalizedString(@"Stop Now", @"")];
    }
}

- (IBAction) stopRender:(id)sender
{
    if (mRendering && !mRendererStopping) {
        if (mRenderer)
            mRenderer->requestStop = true;

        mRendererStopping = true;
        [mRenderControl setEnabled: NO];
    }
}

- (void) startHiresRender: (NSSize) size
    minimum: (double) minSize
{
    mLastRenderWasHires = true;
    mLastRenderSize = size;
    mLastRenderMin = minSize;
    
    if (mRendering)
        return;

    [self updateVariation: NO];

    [self buildEngine];
    if (!mEngine) return;
    [self buildRendererSize: size minimum: minSize]; 
    if (!mRenderer) return;
    [self buildImageCanvasSize];
    
    RenderParameters parameters;
    parameters.periodicUpdate = false;

    [self renderBegin: &parameters];
}


@end

@implementation GView (renderThread)
- (void) renderBegin:(RenderParameters*)parameters;
{
    [self useVariation];
    
    mRendering = true;
    mRestartRenderer = false;
    mRendererFinishing = false;
    mRendererStopping = false;
    
    [mRenderControl setTitle: NSLocalizedString(@"Stop", @"")];
    
    [mStatus setStringValue: @""];

    [mProgress setHidden: NO];
    [mTopBar relayout];
#ifndef PROGRESS_ANIMATE_DIRECTLY
    [mProgress setUsesThreadedAnimation: YES];
    [mProgress startAnimation: self];
#endif
    mOutputProgressDelay = 0;

    [self display];

    mUpdateTimer =
        [[NSTimer scheduledTimerWithTimeInterval: UPDATE_RATE
            target: self selector: @selector(requestRenderUpdate) userInfo: nil
            repeats: YES] retain];

    // ensure all stays alive while the thread is running
    [[self window] retain];
    [mDocument retain];
    [self retain];
    
    NSValue* v = [NSValue value: parameters
                            withObjCType: @encode(RenderParameters)];
    [NSThread detachNewThreadSelector: @selector(renderThread:)
        toTarget: self
        withObject: v];
}


- (void)renderThread:(id)arg
{
    RenderParameters parameters;
    [arg getValue: &parameters];
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

#ifdef TIME_AND_LOG_RENDER
    NSDate* sTime = [NSDate date];
#endif

    if (mEngine && mRenderer && mCanvas) {
        if (parameters.render) 
            mScale = mRenderer->run(mCanvas, parameters.periodicUpdate);
        else if (parameters.animate) {
            qtCanvas* qt = dynamic_cast<qtCanvas*> (mCanvas);
            assert(qt);
            qt->enterThread();
            mRenderer->animate(mCanvas,
                               parameters.animateFrameCount, 
                               parameters.animateZoom);
            qt->exitThread();
        }
        else {
            mRenderer->draw(mCanvas);
            [mDocument performSelectorOnMainThread: @selector(noteStatus:)
                                        withObject: @"Drawing operation complete"
                                     waitUntilDone: NO];
        }
        
        if (ImageCanvas* ic = dynamic_cast<ImageCanvas*>(mCanvas))
            mCanvasColor256 = ic->colorCount256();
    }
    
#ifdef TIME_AND_LOG_RENDER
    NSLog(@"render took %g seconds", [sTime timeIntervalSinceNow]);
#endif
    
    [self performSelectorOnMainThread: @selector(renderStopped:)
        withObject: self waitUntilDone: NO];

    [pool release];
}


- (void) renderStopped:(id)arg
{
    [mUpdateTimer invalidate];
    [mUpdateTimer release];
    mUpdateTimer = nil;
    
    mRendering = false;
    mRendererFinishing = false;
    mRendererStopping = false;

    delete mCanvas;
    mCanvas = nullptr;
    
#ifndef PROGRESS_ANIMATE_DIRECTLY
    [mProgress stopAnimation: self];
#endif
    [mProgress setHidden: YES];
    [mTopBar relayout];

    [self setNeedsDisplay: YES];

    [mRenderControl setTitle: NSLocalizedString(@"Render", @"")];
    [mRenderControl setEnabled: YES];

    if (mRestartRenderer && !mCloseOnRenderStopped) {
        mRestartRenderer = false;
        [self startRender: self];
    }
    
    // can let everyone go if they really want
    [self release];
    [mDocument release];
    [[self window] release];
    
    if (mCloseOnRenderStopped)
        [[self window] performClose: self];
}

@end


@implementation GView (variationControl)

- (void) initializeVariation
{
    mCurrentVariation = [VariationFormatter randomVariation];
    mIncrementVariationOnRender = false;

    [mVariationStepper setMinValue: [VariationFormatter minVariation]];
    [mVariationStepper setMaxValue: [VariationFormatter maxVariation]];
    [mVariationStepper setIncrement: 1.0];
    
    [mVariationStepper setIntValue: mCurrentVariation];
    [mVariationField setIntValue: mCurrentVariation];
    [self reuseVariation];
}

- (void) updateVariation:(BOOL)incrementIfNeeded
{
    if ([mVariationField currentEditor]) {
        [[self window] makeFirstResponder: nil];
    }
    
    if (incrementIfNeeded && mIncrementVariationOnRender) {
        ++mCurrentVariation;
        if (mCurrentVariation > [VariationFormatter maxVariation])
            mCurrentVariation = [VariationFormatter minVariation];
        [mVariationStepper setIntValue: mCurrentVariation];
        [mVariationField setIntValue: mCurrentVariation];
    }
    [mVariationLabel setStringValue:
        NSLocalizedString(@"this variation:", @"")];
}

- (void) useVariation
{
    mIncrementVariationOnRender = true;
}

- (void) reuseVariation
{
    mIncrementVariationOnRender = false;
    [mVariationLabel setStringValue:
        NSLocalizedString(@"next variation:", @"")];
}

- (void) setVariation:(int)var
{
    mCurrentVariation = var;
    [mVariationStepper setIntValue: mCurrentVariation];
    [mVariationField setIntValue: mCurrentVariation];
    [self reuseVariation];
}

- (IBAction) adjustVariation:(id)sender
{
    if ([mVariationField currentEditor]) {
        int delta = [mVariationStepper intValue] - mCurrentVariation;
        
        [[self window] makeFirstResponder: nil];
        
        mCurrentVariation += delta;
        [mVariationStepper setIntValue: mCurrentVariation];
    }
    else {
        mCurrentVariation = [mVariationStepper intValue];
    }

    [mVariationField setIntValue: mCurrentVariation];
    [self reuseVariation];
}

- (IBAction) editVariation:(id)sender
{
    mCurrentVariation = [mVariationField intValue];
    [mVariationStepper setIntValue: mCurrentVariation];
    [self reuseVariation];
}


@end





@implementation GView (internal)

- (void)drawCheckerboardRect:(NSRect)rect
{
    [[NSColor whiteColor] set];
    [NSBezierPath fillRect: rect];

    if ([self inLiveResize]) return;

    static NSColor* gray = nil;
    if (!gray) {
        gray = [[NSColor colorWithCalibratedWhite: 0.95 alpha: 1.0] retain];
    }
    [gray set];

    static const CGFloat u = 10.0;
 
    NSRect box;
    box.size.width = u;
    box.size.height = u;
    
#if defined(CGFLOAT_IS_DOUBLE) && CGFLOAT_IS_DOUBLE
#define MYfmod fmod
#else
#define MYfmod fmodf
#endif

    for (box.origin.y = floor(NSMinY(rect) / box.size.height) * box.size.height;
        box.origin.y < NSMaxY(rect);
        box.origin.y += box.size.height)
    {
        for (box.origin.x = 
                (floor(NSMinX(rect) / (2.0 * box.size.width)) * 2.0
                + MYfmod(box.origin.y / box.size.height, 2.0))
                * box.size.width;
            box.origin.x < NSMaxX(rect);
            box.origin.x += 2*box.size.width)
        {
            [NSBezierPath fillRect: NSIntersectionRect(box, rect)];
        }
    }
}

- (void)buildEngine
{
    [self deleteRenderer];
    mEngine = [mDocument buildEngine];
    mTiled = false;
}

- (void)buildRendererSize:(NSSize)size minimum:(double)minSize
{
    if (!mEngine) return;
    
    assert(mRenderer == nullptr);
    mRenderer = mEngine->renderer(
        (int)size.width, (int)size.height,
        minSize,
        mCurrentVariation,
        [[NSUserDefaults standardUserDefaults] floatForKey: @"BorderSize"]);
}

- (void)buildImageCanvasSize
{
    if (!mRenderer || !mEngine) return;
    
    BitmapAndFormat* bm = [[BitmapAndFormat alloc] 
                             initWithAggPixFmt: aggCanvas::SuggestPixelFormat(mEngine)
                                    pixelsWide: mRenderer->m_width
                                    pixelsHigh: mRenderer->m_height];
    
    if (!bm) return;
    
    [self invalidateDrawingImage];
    [mRenderBitmap release];
    mRenderBitmap = bm;

    mRenderSize.width = (CGFloat)mRenderer->m_width;
    mRenderSize.height = (CGFloat)mRenderer->m_height;
    mRenderedRect.origin.x = 0.0;
    mRenderedRect.origin.y = 0.0;
    mRenderedRect.size = mRenderSize;

    mCanvas = new ImageCanvas(self, mRenderBitmap, [bm aggPixelFormat]);

    mTiled = mEngine->isTiled() || mEngine->isFrieze() != CFDG::no_frieze;
}


- (void)invalidateDrawingImage
{
    if (mDrawingImage) {        
        [mDrawingImage release];
        mDrawingImage = nil;
    }
}

- (void)validateDrawingImage
{
    if (mDrawingImage || !mRenderBitmap) return;
    
    mDrawingImage = [[NSImage alloc] initWithSize: mRenderedRect.size];
    
    NSBitmapImageRep* bitmap = [mRenderBitmap getImageRepCropped: mRenderedRect];
    
    if (bitmap)
        [mDrawingImage addRepresentation: bitmap];
}

- (void)noteProgress
{
#ifdef PROGRESS_ANIMATE_DIRECTLY
    [mProgress animate: self];
    [mProgress displayIfNeeded];
#endif
}

- (void)requestRenderUpdate
{
    if (mRenderer)
        mRenderer->requestUpdate = true;
}

- (void)showSavePanelTitle:(NSString *)title
        fileType:(NSString *)fileType
        accessoryView:(NSView *)view
        didEndSelector:(SEL)selector
{
    NSSavePanel *sp = [NSSavePanel savePanel];
    [sp setAllowedFileTypes: [NSArray arrayWithObject: fileType]];
    [sp setTitle: title];
    [sp setAccessoryView: view];
    [sp setCanSelectHiddenExtension: YES];
    [sp setExtensionHidden: NO];
    
    if (saveImageDirectory == nil) {
        saveImageDirectory = [[[NSFileManager defaultManager]
                                 URLForDirectory: NSDocumentDirectory
                                        inDomain: NSUserDomainMask
                               appropriateForURL: nil
                                          create: YES
                                           error: NULL] retain];
    }
    
    NSString* name =
        [[[[mDocument fileURL] path]
            stringByDeletingPathExtension] lastPathComponent];
    if ([name length] == 0)
        name = [[self window] title];
        
    if ([[NSUserDefaults standardUserDefaults]
            boolForKey: @"SaveWithVariationCode"])
    {
        NSString* var = [VariationFormatter
                            stringForVariation: mCurrentVariation
                            lowerCase: YES];
        name = [name stringByAppendingFormat: @"-%@", var];
    }
    
    [sp setDirectoryURL: saveImageDirectory];
    [sp setNameFieldStringValue: name];
    [sp beginWithCompletionHandler: ^(NSInteger result) {
        [saveImageDirectory release];
        saveImageDirectory = [[sp directoryURL] retain];
        if (result == NSFileHandlingPanelOKButton) {
            NSURL* file = [sp URL];
            NSInvocation* send
            = [NSInvocation invocationWithMethodSignature:
               [self methodSignatureForSelector: (SEL)selector]];
            
            [send setTarget: self];
            [send setSelector: selector];
            [send setArgument: &file atIndex: 2];
            [send invoke];
        }
    }];
}


- (void)saveImagetoFile:(NSURL*)filename
{
    NSData *pngData =
        [self pngImageDataCropped:
            [[NSUserDefaults standardUserDefaults] boolForKey: @"SaveCropped"]
                       multiplier: nil];
    
    if (pngData) {
        [pngData writeToURL: filename atomically: YES];
    } else {
        [mDocument noteStatus: @"An error occured while writing the PNG file."];
        NSBeep();
    }
}

- (void)saveTileImagetoFile:(NSURL*)filename
{
    NSSize mult = NSMakeSize([mSaveTileWidth floatValue], [mSaveTileHeight floatValue]);
    
    NSData *pngData =
        [self pngImageDataCropped: YES multiplier: &mult];
    
    if (pngData) {
        [pngData writeToURL: filename atomically: YES];
    } else {
        [mDocument noteStatus: @"An error occured while writing the PNG file."];
        NSBeep();
    }
}

- (void)saveSvgtoFile:(NSURL*)filename
{
    mCanvas = new SVGCanvas([[filename path] UTF8String],
        (int)mRenderedRect.size.width, (int)mRenderedRect.size.height,
        false);
    
    if (mCanvas->mError) {
        [mDocument noteStatus: @"An error occured while writing the SVG file."];
        NSBeep();
        delete mCanvas;
        mCanvas = nullptr;
        return;
    }
    
    [mDocument noteStatus: @"Saving to SVG file"];
    
    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;

    [self renderBegin: &parameters];
}


- (void)saveMovietoFile:(NSURL*)filename
{
    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;
    parameters.animate = true;

    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    parameters.animateZoom = [defaults boolForKey: PrefKeyMovieZoom] && !mTiled;
    float movieLength = [defaults floatForKey: PrefKeyMovieLength];
    NSInteger movieFrameRate = [defaults integerForKey: PrefKeyMovieFrameRate];
    bool mpeg4 = (bool)[defaults integerForKey: PrefKeyMovieFormat];
    int qual = (int)[defaults floatForKey: PrefKeyMovieQuality];
    
    parameters.animateFrameCount = static_cast<int>(movieLength * movieFrameRate * 0.01);
    
    NSSize* sz = mTiled ? &mRenderedRect.size : &mRenderSize;
    
    BitmapAndFormat* bits = [BitmapAndFormat alloc];
    [bits initWithAggPixFmt: aggCanvas::RGBA8_Blend
                 pixelsWide: (NSInteger)sz->width
                 pixelsHigh: (NSInteger)sz->height];
    if (!bits) {
        [mDocument noteStatus: @"An error occured while initializing the movie canvas."];
        NSBeep();
        return;
    }
    
    mAnimationCanvas = new qtCanvas([filename path], [bits autorelease],
                                    static_cast<int>(movieFrameRate), qual, mpeg4);
    
    bool movieOK = mAnimationCanvas->getError() == nil;
    if (movieOK) {
        mCanvas = mAnimationCanvas;
        mAnimationCanvas = nullptr;
        
        [self renderBegin: &parameters];
    } else {
        delete mAnimationCanvas;
        mAnimationCanvas = nullptr;
        [mDocument noteStatus: @"An error occured while initializing the movie file."];
        NSBeep();
    }
}

- (void)deleteRenderer
{
    mEngine = nullptr;
    if (mRenderer == nullptr) return;
#ifdef EXTREME_PARAM_DEBUG
    delete mRenderer; mRenderer = nullptr;
#else
    NSValue* r = [NSValue valueWithPointer: (const void*)mRenderer];
    mRenderer = nullptr;
    [NSThread detachNewThreadSelector:@selector(rendererDeleteThread:) toTarget:[GView class] withObject:r];
#endif
}

+ (void)rendererDeleteThread:(id)arg
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSValue* rv = (NSValue*)arg;
    Renderer* r = (Renderer*)[rv pointerValue];
    delete r;

    [pool release];
}

@end

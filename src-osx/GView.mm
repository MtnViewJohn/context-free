// GView.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2008 John Horigan - john@glyphic.com
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

#endif  // MAC_OS_X_VERSION_10_7

//#define PROGRESS_ANIMATE_DIRECTLY
//#define USE_SAVE_GRAPHICS_STATE
//#define TIME_AND_LOG_RENDER

#define UPDATE_RATE         (1.0/12.0)
#define PROGRESS_DELAY      12


struct BitmapAndFormat
{
    BitmapImageHolder*     mBitmap;
    aggCanvas::PixelFormat mFormat;
};

static BitmapAndFormat buildBitmap(int width, int height, CFDG* engine)
{
    BitmapAndFormat ret;
    ret.mBitmap = 0;
    ret.mFormat = aggCanvas::RGBA8_Blend;
    
    if (!engine) return ret;
    
    ret.mFormat = aggCanvas::SuggestPixelFormat(engine);
	ret.mBitmap = [BitmapImageHolder alloc];
    
    switch(ret.mFormat) {
        case aggCanvas::RGBA8_Blend:
        case aggCanvas::RGBA16_Blend:
            [ret.mBitmap
			initWithBitmapDataPlanes: NULL
                          pixelsWide: width
                          pixelsHigh: height
                       bitsPerSample: (ret.mFormat & aggCanvas::Has_16bit_Color) + 8 
                     samplesPerPixel: 4
                            hasAlpha: YES isPlanar: NO
                      colorSpaceName: NSCalibratedRGBColorSpace
                         bytesPerRow: 0 bitsPerPixel: 0];
            break;
        case aggCanvas::RGB8_Blend:
        case aggCanvas::RGB16_Blend:
            [ret.mBitmap
			initWithBitmapDataPlanes: NULL
                          pixelsWide: width
                          pixelsHigh: height
                       bitsPerSample: (ret.mFormat & aggCanvas::Has_16bit_Color) + 8 
                     samplesPerPixel: 3
                            hasAlpha: NO isPlanar: NO
                      colorSpaceName: NSCalibratedRGBColorSpace
                         bytesPerRow: 0 bitsPerPixel: 0];
            break;
        case aggCanvas::Gray8_Blend:
        case aggCanvas::Gray16_Blend:
            [ret.mBitmap
			initWithBitmapDataPlanes: NULL
                          pixelsWide: width
                          pixelsHigh: height
                       bitsPerSample: (ret.mFormat & aggCanvas::Has_16bit_Color) + 8 
                     samplesPerPixel: 1
                            hasAlpha: NO isPlanar: NO
                      colorSpaceName: NSCalibratedWhiteColorSpace
                         bytesPerRow: 0 bitsPerPixel: 0];
            break;
        default:
            break;
    }
    
    [ret.mBitmap autorelease];
    
    return ret;
}



@interface GView (internal)

- (void)drawCheckerboardRect:(NSRect)rect;

- (void)buildEngine;
- (void)buildRendererSize:(NSSize)size minimum:(double)minSize;
- (void)buildImageCanvasSize;

- (void)invalidateDrawingImage;
- (void)validateDrawingImage;

- (void)redisplayImage:(NSValue*)sizeObj;
- (void)noteProgress;
- (void)requestRenderUpdate;

- (void)showSavePanelTitle:(NSString *)title
        fileType:(NSString *)fileType
        accessoryView:(NSView *)view
        didEndSelector:(SEL)selector;

- (void)savePanelDidEnd:(NSSavePanel *)sheet
    returnCode:(int)result contextInfo:(void *)ctx;

- (void)saveImage:(bool)save toFile:(NSString*)filename;
- (void)saveTileImage:(bool)save toFile:(NSString*)filename;
- (void)saveSvg:(bool)save toFile:(NSString*)filename;
- (void)saveMovie:(bool)save toFile:(NSString*)filename;

@end


namespace {
    NSString* saveImageDirectory = nil;

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
		bool	animateZoom;
		int		animateFrameCount;
		
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
        mEngine = 0;
        mRenderer = 0;
        mCanvas = 0;
        
		mRenderBitmap = nil;
        mDrawingImage = nil;
        mRestartRenderer = false;
        mUpdateTimer = nil;
        
        mRendering = false;
        mRestartRenderer = false;
        mRendererFinishing = false;
        mRendererStopping = false;
        mLastRenderWasHires = false;
        
        mCurrentVariation = 0;
        mIncrementVariationOnRender = false;
		
		mAnimationCanvas = 0;
		
		mTiled = false;
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
    
    NSWindow* window = [self window];
    if ([window respondsToSelector:@selector(toggleFullScreen:)]) {
        NSWindowCollectionBehavior behavior = [window collectionBehavior];
        behavior |= NSWindowCollectionBehaviorFullScreenPrimary;
        [window setCollectionBehavior:behavior];

        NSButton* fullscreenButton =
            [window standardWindowButton:NSWindowFullScreenButton];
        [fullscreenButton setAction:@selector(enterFullscreen:)];
        [fullscreenButton setTarget:self];
    }
}

- (void)dealloc
{
    delete mRenderer;               mRenderer = 0;
    delete mEngine;                 mEngine = 0;
    [mDocument release];            mDocument = nil;
    [mDrawingImage release];        mDrawingImage = nil;
	[mRenderBitmap release];		mRenderBitmap = nil;
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
        backgroundColor = mEngine->getBackgroundColor(mRenderer);
    
	if (backgroundColor.opacity() < 1.0) {
		[self drawCheckerboardRect: rect];
	}

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
	NSSize iSize = mRenderSize;
	
	float scale;
	if (rSize.width <= fSize.width  &&  rSize.height <= fSize.height) {
		// rendered area fits within frame, center it
		scale = 1.0f;
	}
	else {
		float wScale = fSize.width / rSize.width;
		float hScale = fSize.height / rSize.height;
		scale = (hScale < wScale) ? hScale : wScale;
	}
	
	NSRect dRect;

	// center scaled image rectangle
	dRect.size.width = iSize.width * scale;
	dRect.size.height = iSize.height * scale;
	float ox = dRect.origin.x = floorf((fSize.width - dRect.size.width) / 2.0f);
	float oy = dRect.origin.y = floorf((fSize.height - dRect.size.height) / 2.0f);

    if (mTiled && scale == 1.0f) {
        tileList points = 
            mRenderer->m_tiledCanvas->getTesselation(fSize.width, fSize.height, ox, oy);
        
        for (tileList::iterator pt = points.begin(); 
             pt != points.end(); ++pt) {
            NSPoint dPoint;
            dPoint.x = (float)pt->x;
            dPoint.y = (float)pt->y;

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
        [[NSColor colorWithDeviceRed: backgroundColor.r
                               green: backgroundColor.g
                                blue: backgroundColor.b
                               alpha: backgroundColor.a ] set];
        [NSBezierPath fillRect: rect];
        
        if (backgroundColor.opacity() < 1.0) {
            [NSBezierPath clipRect: dRect];
            [self drawCheckerboardRect: NSIntersectionRect(dRect, rect)];
        }
        
        [mDrawingImage drawInRect: dRect fromRect: NSZeroRect
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
            didEndSelector: @selector(saveImage:toFile:)];
    }
}

- (IBAction)saveTileImage:(id)sender
{
    BOOL tilable = [self isRect];
    [mSaveTileOptions selectCellWithTag:0];
    [[mSaveTileOptions cellWithTag:1] setEnabled: tilable];
    [self showSavePanelTitle: NSLocalizedString(@"Save Image", @"")
                    fileType: @"png"
               accessoryView: mSaveTileAccessory
              didEndSelector: @selector(saveTileImage:toFile:)];
}

- (IBAction)saveAsSVG:(id)sender
{
    [self showSavePanelTitle: NSLocalizedString(@"Save as SVG", @"")
        fileType: @"svg"
        accessoryView: nil
        didEndSelector: @selector(saveSvg:toFile:)];
}

- (IBAction)saveAsMovie:(id)sender
{
    [self showSavePanelTitle: NSLocalizedString(@"Save as Animation", @"")
        fileType: @"mov"
        accessoryView: mSaveAnimationAccessory
        didEndSelector: @selector(saveMovie:toFile:)];
}

- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
{
    SEL action = [anItem action];
    
    if (action == @selector(startRender:))
        return !mRestartRenderer;
        
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
    
    if (s.toDoCount > 0) {
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
            message = [message stringByAppendingString:
                [self isRect] ? 
                         @", tiled rectangular" : @", tiled"];
        }
    }
    
#if 0
    if (!s.inOutput) {
        message = [message stringByAppendingString:
            [NSString localizedStringWithFormat:
                @" in %.3f seconds",
                (double)s.outputTime / CLOCKS_PER_SEC]];
    }
#endif
    
    [mStatus setStringValue: message];
    
    if (s.inOutput  &&  s.fullOutput) {
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

-(bool)isRect
{
    int x, y;
	return mTiled && mRenderer->m_tiledCanvas->isRectangular(&x, &y) && 
        (x > 1 || y > 1);
}

- (NSData*) pngImageDataCropped:(BOOL)cropped rectangular:(BOOL) rect;
{
    NSBitmapImageRep* bits;
    
    if (mTiled) {
        agg::point_i factor(1, 1);                      // unit tile by default
        if (rect) mRenderer->m_tiledCanvas->isRectangular(&factor.x, &factor.y);
        
        NSRect iRect = NSMakeRect(0.0, 0.0, 0.0, 0.0);
        iRect.size = mRenderSize;
        
        NSRect fRect = iRect;
        fRect.size.width *= factor.x;
        fRect.size.height *= factor.y;
        
        tileList points = 
            mRenderer->m_tiledCanvas->getTesselation(fRect.size.width,
                                                     fRect.size.height, 0, 0);
        
        NSImage* tileImage = [[NSImage alloc] initWithSize: fRect.size];

        [self validateDrawingImage];
        
        [tileImage lockFocus];
        
        for (tileList::iterator pt = points.begin(); 
             pt != points.end(); ++pt)
        {
            NSPoint dPoint;
            dPoint.x = (float)pt->x;
            dPoint.y = (float)pt->y;
            [mDrawingImage drawAtPoint: dPoint fromRect: NSZeroRect
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
            
    NSData *pngData =
        [bits representationUsingType: NSPNGFileType properties: nil];
	
	return pngData;
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
        else
            mRenderer->draw(mCanvas);
        
        ImageCanvas* ic = dynamic_cast<ImageCanvas*>(mCanvas);
        if (ic) 
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
    mCanvas = 0;
    
#ifndef PROGRESS_ANIMATE_DIRECTLY
    [mProgress stopAnimation: self];
#endif
    [mProgress setHidden: YES];
    [mTopBar relayout];

    [self setNeedsDisplay: YES];

    [mRenderControl setTitle: NSLocalizedString(@"Render", @"")];
    [mRenderControl setEnabled: YES];

    if (mRestartRenderer) {
        mRestartRenderer = false;
        [self startRender: self];
    }
    
    // can let everyone go if they really want
    [self release];
    [mDocument release];
    [[self window] release];
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
	
	static const float u = 10.0;
	 
	NSRect box;
	box.size.width = u;
	box.size.height = u;
	
	for (box.origin.y = floor(NSMinY(rect) / box.size.height) * box.size.height;
		box.origin.y < NSMaxY(rect);
		box.origin.y += box.size.height)
	{
		for (box.origin.x = 
				(floor(NSMinX(rect) / (2.0 * box.size.width)) * 2.0
				 + fmodf(box.origin.y / box.size.height, 2.0))
				 * box.size.width;
			box.origin.x < NSMaxX(rect);
			box.origin.x += 2*box.size.width)
		{
			[NSBezierPath fillRect: box];
		}
	}
}

- (void)buildEngine
{
    delete mRenderer;
    mRenderer = 0;
    delete mEngine;
    mEngine = [mDocument buildEngine];
}

- (void)buildRendererSize:(NSSize)size minimum:(double)minSize
{
    if (!mEngine) return;
    
    delete mRenderer;
    mRenderer = mEngine->renderer(
        (int)size.width, (int)size.height,
        minSize,
        mCurrentVariation,
		[[NSUserDefaults standardUserDefaults] floatForKey: @"BorderSize"]);
}

- (void)buildImageCanvasSize
{
    if (!mRenderer) return;
    
    [self invalidateDrawingImage];
    [mRenderBitmap release];
    
    BitmapAndFormat baf = buildBitmap(mRenderer->m_width, mRenderer->m_height,
                                     mEngine);
    
    mRenderBitmap = [baf.mBitmap retain];

    if (!mRenderBitmap) return;
    
    mRenderSize.width = (float)mRenderer->m_width;
    mRenderSize.height = (float)mRenderer->m_height;
    mRenderedRect.origin.x = 0.0;
    mRenderedRect.origin.y = 0.0;
    mRenderedRect.size = mRenderSize;

    mCanvas = new ImageCanvas(self, mRenderBitmap, baf.mFormat);

    mTiled = mEngine->isTiled();

    mRenderer->draw(mCanvas);
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
    
	mDrawingImage = [[NSImage alloc] initWithSize: mRenderSize];
    [mDrawingImage setScalesWhenResized: TRUE];
    [mDrawingImage setDataRetained: TRUE];
    
    NSBitmapImageRep* bitmap = [mRenderBitmap getImageRep];
    
    if (bitmap)
        [mDrawingImage addRepresentation: bitmap];
}

- (void)redisplayImage:(NSValue*)rectObj
{
    mRenderedRect = [rectObj rectValue];
    [self invalidateDrawingImage];
    [self display];
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
    [sp setRequiredFileType: fileType];
    [sp setTitle: title];
    [sp setAccessoryView: view];
    [sp setCanSelectHiddenExtension: YES];
    
    if (saveImageDirectory == nil) {
        saveImageDirectory = [NSHomeDirectory() retain];
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
    
    [sp beginSheetForDirectory: saveImageDirectory
        file: name
        modalForWindow: [self window]
        modalDelegate: self
        didEndSelector: @selector(savePanelDidEnd:returnCode:contextInfo:)
        contextInfo: (void*)selector]; 
}


- (void)savePanelDidEnd:(NSSavePanel *)sheet
    returnCode:(int)result contextInfo:(void *)ctx
{
    [saveImageDirectory release];
    saveImageDirectory = [[sheet directory] retain];

	bool doSave =
		result == NSOKButton
		&& [sheet makeFirstResponder: nil];
	NSString* filename = [sheet filename];

	NSInvocation* send
		= [NSInvocation invocationWithMethodSignature:
			[self methodSignatureForSelector: (SEL)ctx]];
	
	[send setTarget: self];
	[send setSelector: (SEL)ctx];
	[send setArgument: &doSave atIndex: 2];
	[send setArgument: &filename atIndex: 3];
	[send invoke];
}


- (void)saveImage:(bool)save toFile:(NSString*)filename
{
    if (!save) return;

	NSData *pngData =
		[self pngImageDataCropped:
			[[NSUserDefaults standardUserDefaults] boolForKey: @"SaveCropped"]
                      rectangular: NO];

    [pngData writeToFile: filename atomically: YES];
}

- (void)saveTileImage:(bool)save toFile:(NSString*)filename
{
    if (!save) return;
    
	NSData *pngData =
		[self pngImageDataCropped: NO rectangular: 
            [mSaveTileOptions selectedTag] == 1];
    
    [pngData writeToFile: filename atomically: YES];
}

- (void)saveSvg:(bool)save toFile:(NSString*)filename
{
    if (!save || mRendering) return;

    mCanvas = new SVGCanvas([filename UTF8String],
        (int)mRenderedRect.size.width, (int)mRenderedRect.size.height,
        false);
    
    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;

    [self renderBegin: &parameters];
}


- (void)saveMovie:(bool)save toFile:(NSString*)filename
{
    if (!save || mRendering)
	{
        return;
	}

    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;
    parameters.animate = true;

    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
	parameters.animateZoom = [defaults boolForKey: PrefKeyMovieZoom] && !mTiled;
    float movieLength = [defaults floatForKey: PrefKeyMovieLength];
    int movieFrameRate = [defaults integerForKey: PrefKeyMovieFrameRate];
    bool mpeg4 = (bool)[defaults integerForKey: PrefKeyMovieFormat];
    int qual = (int)[defaults floatForKey: PrefKeyMovieQuality];
    
    parameters.animateFrameCount = movieLength * movieFrameRate * 0.01;
    
    BitmapImageHolder* bits = [BitmapImageHolder alloc];
    [bits initWithBitmapDataPlanes: NULL
                        pixelsWide: mRenderer->m_width
                        pixelsHigh: mRenderer->m_height
                     bitsPerSample: 8
                   samplesPerPixel: 4
                          hasAlpha: YES isPlanar: NO
                    colorSpaceName: NSCalibratedRGBColorSpace
                       bytesPerRow: 0 bitsPerPixel: 0];
    
    
    mAnimationCanvas = new qtCanvas(filename, [bits autorelease],
                                    movieFrameRate, qual, mpeg4);
    
    bool movieOK = mAnimationCanvas->getError() == nil;
    if (movieOK) {
        mCanvas = mAnimationCanvas;
        mAnimationCanvas = 0;
        
        [self renderBegin: &parameters];
    } else {
        delete mAnimationCanvas;
        mAnimationCanvas = 0;
        [mStatus setStringValue: @"An error occured while initializing the movie file."];
    }
}



@end

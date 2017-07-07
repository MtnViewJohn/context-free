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
#include "AVcanvas.h"
#include "tiledCanvas.h"
#include "Rand64.h"
#include <tgmath.h>
#include <tempfile.h>

using cfdg_ptr = std::shared_ptr<CFDG>;
using renderer_ptr = std::unique_ptr<Renderer>;
using canvas_ptr = std::unique_ptr<Canvas>;
using tempfile_ptr = std::unique_ptr<TempFile>;


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
        case aggCanvas::AV_Blend:
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

@interface GView () {
cfdg_ptr     mEngine;
renderer_ptr mRenderer;
canvas_ptr   mCanvas;
tempfile_ptr mMovieFile;
BitmapAndFormat*  mRenderBitmap;  // this bitmap must never be drawn
}
@end

@interface GView (internal)

- (void)drawCheckerboardRect:(NSRect)rect;

- (void)buildEngine;
- (void)buildRendererSize:(NSSize)size minimum:(double)minSize;
- (void)buildImageCanvasSize;

- (void)invalidateDrawingImage;
- (bool)validateDrawingImage;

- (void)noteProgress;
- (void)requestRenderUpdate;

- (void)setupPlayer:(NSURL*)movie;
- (void)tearDownPlayer;
- (void)stopLoadingAnimationAndHandleError:(NSError *)error;

- (bool)setupTimeSlider:(AVPlayerItem*)playerItem;
- (void)setUpPlaybackOfAsset:(AVURLAsset *)asset withKeys:(NSArray *)keys;

- (void)showSavePanelTitle:(NSString *)title
                  fileType:(NSArray *)fileType
             accessoryView:(NSView *)view
            didEndSelector:(SEL)selector;

- (void)saveImagetoFile:(NSURL*)filename;
- (void)saveTileImagetoFile:(NSURL*)filename;
- (void)saveSvgtoFile:(NSURL*)filename;
- (void)saveMovietoFile:(NSURL*)filename;

- (void)deleteRenderer;
+ (void)rendererDeleteThread:(id)arg;
@end

NSString* PrefKeyMovieZoom = @"MovieZoom";
NSString* PrefKeyMovieLength = @"MovieLength";
NSString* PrefKeyMovieFrameRate = @"MovieFrameRate";
NSString* PrefKeyMovieFormat = @"MovieFormat";

namespace {
    NSURL*      saveImageDirectory = nil;
    void*       ItemStatusContext = &ItemStatusContext;
    void*       LayerStatusContext = &LayerStatusContext;
    void*       ItemDurationContext = &ItemDurationContext;
    NSImage*    PlayNormalImage = nil;
    NSImage*    PlayPressImage = nil;
    NSImage*    PauseNormalImage = nil;
    NSImage*    PausePressImage = nil;

    class RenderParameters
    {
    public:
        bool    render;
        bool    periodicUpdate;
        bool    animate;
        bool    animateZoom;
        int     animateFrameCount;
        int     animateFrame;

        RenderParameters()
            : render(true), periodicUpdate(true), animate(false)
            { }
    };
    
    NSArray*    ActionStrings = @[@"Stop", @"Render", @"Animate", @"Frame"];
}


@interface GView (renderThread)
- (void) renderBegin:(RenderParameters*)parameters;
- (void) renderThread:(id)arg;
- (void) renderStopped:(id)arg; // sent by thread
@end


@implementation GView

+ (void)initialize {
    if (self == [GView self]) {
        PlayNormalImage =   [[NSImage imageNamed:@"RemotePlay_norm.tif.icns"] retain];
        PlayPressImage =    [[NSImage imageNamed:@"RemotePlay_press.tif.icns"] retain];
        PauseNormalImage =  [[NSImage imageNamed:@"RemotePause_norm.tif.icns"] retain];
        PausePressImage =   [[NSImage imageNamed:@"RemotePause_press.tif.icns"] retain];
    }
}

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
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

        mTiled = false;
        
        mFullScreenMenu = nil;
    }
    return self;
}

- (void)awakeFromNib
{
    [super awakeFromNib];
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
    mCurrentAction = ActionType::RenderAction;
    mLastAnimateFrame = 1.0;
    self.wantsLayer = YES;
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
    [self tearDownPlayer];
    if (mRendering && mRenderer) {
        mRenderer->requestStop = true;
        mCloseOnRenderStopped = true;
        return NO;
    }
    return YES;
}

- (void)windowWillClose:(NSNotification *)notification
{
    [self tearDownPlayer];
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
    [self tearDownPlayer];
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

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
                        change:(NSDictionary *)change context:(void *)context
{
    if (context == ItemDurationContext) {
        AVPlayerItem* playerItem = (AVPlayerItem*)object;
        dispatch_async(dispatch_get_main_queue(),
                       ^{
                           [self setupTimeSlider: playerItem];
                       });
        return;
    }
    if (context == ItemStatusContext) {
        AVPlayerItem* playerItem = (AVPlayerItem*)object;
        dispatch_async(dispatch_get_main_queue(),
                       ^{
                           AVPlayerItemStatus stat = [playerItem status];
                           if (stat == AVPlayerItemStatusReadyToPlay &&
                               [mMoviePlayerLayer isReadyForDisplay])
                           {
                               [mMovieControls setHidden: NO];
                               [mStatus setHidden: YES];
                           }
                           if (stat == AVPlayerItemStatusFailed) {
                               [self stopLoadingAnimationAndHandleError: [playerItem error]];
                           }
                       });
        return;
    }
    if (context == LayerStatusContext) {
        AVPlayerLayer* playerLayer = (AVPlayerLayer*)object;
        dispatch_async(dispatch_get_main_queue(),
                       ^{
                           AVPlayerItemStatus stat = [[[playerLayer player] currentItem] status];
                           if (stat == AVPlayerItemStatusReadyToPlay &&
                               [playerLayer isReadyForDisplay])
                           {
                               [mMovieControls setHidden: NO];
                               [mStatus setHidden: YES];
                           }
                       });
        return;
    }

    [super observeValueForKeyPath:keyPath ofObject:object
                           change:change context:context];
}

- (IBAction) toggleMovieStartStop:(id)sender
{
    if ([mMoviePlayer rate] == 0.0f) {
        if (mAtEndofMovie)
            [mMoviePlayer seekToTime: kCMTimeZero];
        [mMoviePlayer play];
        mAtEndofMovie = false;
        mStartStopButton.image = PauseNormalImage;
        mStartStopButton.alternateImage = PausePressImage;
    } else {
        [mMoviePlayer pause];
        mStartStopButton.image = PlayNormalImage;
        mStartStopButton.alternateImage = PlayPressImage;
    }
}

- (IBAction) movieRewind:(id)sender
{
    [mMoviePlayer seekToTime: kCMTimeZero];
    mAtEndofMovie = false;
}

- (IBAction) movieTimeChange:(id)sender
{
    auto scale = mMoviePlayer.currentItem.duration.timescale;
    double time = [mTimeSlider doubleValue];
    CMTime t = CMTimeMakeWithSeconds(time, scale);
    [mMoviePlayer seekToTime:t toleranceBefore:kCMTimeZero toleranceAfter:kCMTimeZero];
}

- (void)drawRect:(NSRect)rect
{
    if (mMoviePlayer || ![self validateDrawingImage]) {
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
        tileList points = mRenderer->m_tiledCanvas->getTessellation(static_cast<int>(fSize.width), static_cast<int>(fSize.height), ox, oy);
        
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
    if ([mActionControl selectedSegment] == 1) {
        [[mActionSelect cell] performClickWithFrame:[sender frame]
                                             inView:[sender superview]];
        return;
    }
    
    if (mRendering) {
        [self finishRender: sender];
    } else {
        float frame = 0.0;
        switch (mCurrentAction) {
            case RenderAction:
                [self startRender: sender];
                break;
                
            case AnimateFrameAction:
                frame = mLastAnimateFrame;
            case AnimateAction: {
                NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
                float movieWidth = [defaults floatForKey: PrefKeyMovieWidth];
                float movieHeight = [defaults floatForKey: PrefKeyMovieHeight];
                double movieMinSize = [defaults doubleForKey: PrefKeyMinumumSize];
                [self startAnimation: NSMakeSize(movieWidth, movieHeight)
                             minimum: movieMinSize
                               frame: frame];
                break;
            }
            case StopAction:
                break;
        }
    }
}

- (IBAction)selectAction:(id)sender
{
    NSInteger newAction = [mActionSelect selectedTag];
    mCurrentAction = (ActionType)newAction;
    [mActionControl setLabel: ActionStrings[newAction]
                  forSegment: 0];
}

- (IBAction)saveOutput:(id)sender
{
    if (mMovieFile) {
        if (!mMovieFile->written()) {
            [mDocument noteStatus: @"Movie file is already saved."];
            NSBeep();
            return;
        }
        [self showSavePanelTitle: NSLocalizedString(@"Save as Animation", @"")
                        fileType: @[@"mov"]
                   accessoryView: nil
                  didEndSelector: @selector(saveMovietoFile:)];
    } else if (mTiled) {
        [self saveTileImage: sender];
    } else {
        [self showSavePanelTitle: NSLocalizedString(@"Save Image", @"")
                        fileType: @[@"png"]
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
                    fileType: @[@"png"]
               accessoryView: mSaveTileAccessory
              didEndSelector: @selector(saveTileImagetoFile:)];
}

- (IBAction)saveAsSVG:(id)sender
{
    [self showSavePanelTitle: NSLocalizedString(@"Save as SVG", @"")
                    fileType: @[@"svg"]
               accessoryView: nil
              didEndSelector: @selector(saveSvgtoFile:)];
}

- (BOOL)validateMenuItem:(NSMenuItem *)anItem
{
    SEL action = [anItem action];
    
    if (action == @selector(startRender:))
        return !mRestartRenderer;
    
    if (action == @selector(enterFullscreen:))
        return YES;
        
    if (action == @selector(showHiresRenderSheet:)
    ||  action == @selector(repeatRender:)
    ||  action == @selector(showAnimateSheet:))
        return !mRendering;
            
    if (action == @selector(finishRender:))
        return mRendering && !mRendererFinishing && !mRendererStopping;

    if (action == @selector(stopRender:))
        return mRendering && !mRendererStopping;
    
    if (action == @selector(saveAsSVG:)
    ||  action == @selector(uploadToGallery:))
        return !mRendering && mRenderBitmap;
    
    if (action == @selector(saveOutput:))
        return !mRendering && (mRenderBitmap || mMovieFile);
            
    return [super validateMenuItem: anItem];
}

- (IBAction) showHiresRenderSheet:(id)sender
{
    [mDocument showHiresRenderSheet: sender];
}

- (IBAction) showAnimationSheet:(id)sender
{
    [mDocument showAnimateSheet: sender];
}

- (IBAction)showAnimationFrameSheet:(id)sender
{
    [mDocument showAnimateFrameSheet: sender];
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
        if (![mOutputProgress isHidden]) {
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

- (NSData*) pngImageDataCropped:(BOOL)cropped multiplier:(NSSize*) mult
{
    NSBitmapImageRep* bits;
    
    if (mult && (mult->width != 1.0 || mult->height != 1.0)) {
        int  width = static_cast<int>(mRenderedRect.size.width  * mult->width);
        int height = static_cast<int>(mRenderedRect.size.height * mult->height);
        
        auto fmt = [mRenderBitmap aggPixelFormat];
        
        BitmapAndFormat* png_bm = [[BitmapAndFormat alloc]
                                 initWithAggPixFmt: fmt
                                        pixelsWide: width
                                        pixelsHigh: height];
        if (!png_bm) return nil;
        [png_bm autorelease];
        
        auto pngCanvas = std::make_unique<ImageCanvas>(self, png_bm, fmt);
        auto srcCanvas = std::make_unique<ImageCanvas>(self, mRenderBitmap, fmt);
        if (!srcCanvas || !pngCanvas) return nil;

        tileList points = mRenderer->m_tiledCanvas->getTessellation(width, height, 0, 0);
        
        for (agg::point_i& pt: points)
            pngCanvas->draw(*srcCanvas, pt.x, pt.y);
        
        bits = [png_bm getImageRep];
    }
    else if (cropped && !mult) {
        bits = [mRenderBitmap getImageRepCropped: mRenderedRect];
    }
    else {
        bits = [mRenderBitmap getImageRep];
    }
    
    CGImageRef iref = [bits CGImage];
    if (!iref) return nil;
    
    NSMutableData* mdata = [NSMutableData data];
    CGImageDestinationRef destref = 
        CGImageDestinationCreateWithData((CFMutableDataRef)mdata, kUTTypePNG, 1, nil);
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
    mCurrentAction = ActionType::RenderAction;
    mLastRenderWasHires = false;
    [self tearDownPlayer];
    
    if (mRendering) {
        if (!mRestartRenderer) {
            mRestartRenderer = true;
            [self stopRender: sender];
        }
        return;
    }
    
    mMovieFile.reset();

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
        [mActionControl setLabel: NSLocalizedString(@"Stop Now", @"") forSegment: 0];
    }
}

- (IBAction) stopRender:(id)sender
{
    if (mRendering && !mRendererStopping) {
        if (mRenderer)
            mRenderer->requestStop = true;

        mRendererStopping = true;
        [mActionControl setEnabled: NO];
    }
}

- (void) startHiresRender: (NSSize) size
    minimum: (double) minSize
{
    mLastRenderWasHires = true;
    mLastRenderSize = size;
    mLastRenderMin = minSize;
    mCurrentAction = ActionType::RenderAction;
    [self tearDownPlayer];
    
    if (mRendering)
        return;
    
    mMovieFile.reset();

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

- (void) startAnimation: (NSSize) size
                minimum: (double) minSize
                  frame: (float) fr
{
    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;
    parameters.animate = true;
    parameters.animateFrame = static_cast<int>(fr);
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float movieLength = [defaults floatForKey: PrefKeyMovieLength];
    NSInteger movieFrameRate = [defaults integerForKey: PrefKeyMovieFrameRate];
    auto fmt = AVcanvas::H264;
    switch ([defaults integerForKey: PrefKeyMovieFormat]) {
        case 2:
            fmt = AVcanvas::ProRes422;
            break;
        case 3:
            fmt = AVcanvas::ProRes4444;
            break;
        default:
            break;
    }
    
    parameters.animateFrameCount = static_cast<int>(movieLength * movieFrameRate * 0.01);
    
    [self buildEngine];
    if (!mEngine) return;
    [self buildRendererSize: size minimum: minSize];
    if (!mRenderer) return;
    parameters.animateZoom = [defaults boolForKey: PrefKeyMovieZoom] && !mTiled;

    auto width = mRenderer->m_width;
    auto height = mRenderer->m_height;
    if (width & 7)
        width = (width + 8) & (~7);
    if (height & 7)
        height = (height + 8) & (~7);
    mRenderSize.width = (CGFloat)width;
    mRenderSize.height = (CGFloat)height;
    mRenderedRect.origin.x = 0.0;
    mRenderedRect.origin.y = 0.0;
    mRenderedRect.size = mRenderSize;
    
    if (!NSEqualSizes(size, mRenderSize))
        [mDocument noteStatus: [NSString stringWithFormat:@"Size reduced to %dx%d",
                                width, height]];
    if (width != mRenderer->m_width || height != mRenderer->m_height)
        [mDocument noteStatus: [NSString stringWithFormat:@"TiledCanvas desired size was %dx%d",
                                mRenderer->m_width, mRenderer->m_height]];

    if (parameters.animateFrame == 0) {
        mCurrentAction = ActionType::AnimateAction;

        BitmapAndFormat* bits = [BitmapAndFormat alloc];
        [bits initWithAggPixFmt: aggCanvas::AV_Blend
                     pixelsWide: (NSInteger)width
                     pixelsHigh: (NSInteger)height];
        if (!bits) {
            [mDocument noteStatus: @"An error occured while initializing the movie canvas."];
            NSBeep();
            return;
        }
        
        [self tearDownPlayer];
        mMovieFile = std::make_unique<TempFile>([mDocument system], AbstractSystem::MovieTemp, 0);
        auto stream = mMovieFile->forWrite();
        delete stream;  // close the temp file, we need its name
        NSString* path = [NSString stringWithUTF8String: mMovieFile->name().c_str()];
        
        mCanvas = std::make_unique<AVcanvas>(path, [bits autorelease],
                                             static_cast<int>(movieFrameRate), fmt);
        
        if (!mCanvas->mError) {
            [self renderBegin: &parameters];
        } else {
            mCanvas.reset();
            [mDocument noteStatus: @"An error occured while initializing the movie file."];
            NSBeep();
        }
    } else {
        mLastAnimateFrame = fr;
        mCurrentAction = ActionType::AnimateFrameAction;
        mMovieFile.reset();
        [self buildImageCanvasSize];
        [self renderBegin: &parameters];
    }
}

@end

@implementation GView (renderThread)
- (void) renderBegin:(RenderParameters*)parameters
{
    [self useVariation];
    
    mRendering = true;
    mRestartRenderer = false;
    mRendererFinishing = false;
    mRendererStopping = false;
    
    [mActionControl setLabel: NSLocalizedString(@"Stop", @"") forSegment: 0];
    
    [mStatus setStringValue: @""];

    [mProgress setHidden: NO];
    [mMovieControls setHidden: YES];
    [mStatus setHidden: NO];
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
            mScale = mRenderer->run(mCanvas.get(), parameters.periodicUpdate);
        else if (parameters.animate) {
            assert(parameters.animateFrame  > 0 || dynamic_cast<AVcanvas*>(mCanvas.get()));
            assert(parameters.animateFrame == 0 || dynamic_cast<ImageCanvas*>(mCanvas.get()));
            mRenderer->animate(mCanvas.get(),
                               parameters.animateFrameCount,
                               parameters.animateFrame,
                               parameters.animateZoom);
            if (mCanvas->mError)
                NSBeep();
        }
        else {
            mRenderer->draw(mCanvas.get());
            [mDocument performSelectorOnMainThread: @selector(noteStatus:)
                                        withObject: @"Drawing operation complete"
                                     waitUntilDone: NO];
        }
        
        if (ImageCanvas* ic = dynamic_cast<ImageCanvas*>(mCanvas.get()))
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

    mCanvas.reset();
    
#ifndef PROGRESS_ANIMATE_DIRECTLY
    [mProgress stopAnimation: self];
#endif
    [mProgress setHidden: YES];
    [mTopBar relayout];

    [self setNeedsDisplay: YES];

    [mActionControl setLabel: ActionStrings[mCurrentAction] forSegment: 0];
    [mActionControl setEnabled: YES];

    if (mRestartRenderer && !mCloseOnRenderStopped) {
        mRestartRenderer = false;
        [self startRender: self];
    }
    
    if (mMovieFile && mMovieFile->written()) {
        NSString* tempPath = [NSString stringWithUTF8String: mMovieFile->name().c_str()];
        NSURL* tempURL = [NSURL fileURLWithPath: tempPath];
        [self performSelector:@selector(setupPlayer:) withObject:tempURL afterDelay:0.5];
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
    mTiled = mEngine && (mEngine->isTiled() || mEngine->isFrieze() != CFDG::no_frieze);
}

- (void)buildRendererSize:(NSSize)size minimum:(double)minSize
{
    if (!mEngine) return;
    
    assert(!mRenderer);
    mRenderer.reset(mEngine->renderer(mEngine,
        (int)size.width, (int)size.height,
        minSize,
        mCurrentVariation,
        [[NSUserDefaults standardUserDefaults] floatForKey: @"BorderSize"]));
    if (!mRenderer)
        mEngine.reset();
}

- (void)buildImageCanvasSize
{
    if (!mRenderer || !mEngine) return;
    
    BitmapAndFormat* bm = [[BitmapAndFormat alloc] 
                             initWithAggPixFmt: aggCanvas::SuggestPixelFormat(mEngine.get())
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

    mCanvas = std::make_unique<ImageCanvas>(self, mRenderBitmap, [bm aggPixelFormat]);
}


- (void)invalidateDrawingImage
{
    if (mDrawingImage) {        
        [mDrawingImage release];
        mDrawingImage = nil;
    }
}

- (bool)validateDrawingImage
{
    if (mDrawingImage || !mRenderBitmap) return mDrawingImage != nil;
    
    mDrawingImage = [[NSImage alloc] initWithSize: mRenderedRect.size];
    
    NSBitmapImageRep* bitmap = [mRenderBitmap getImageRepCropped: mRenderedRect];
    
    if (bitmap)
        [mDrawingImage addRepresentation: bitmap];
    
    return mDrawingImage != nil;
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

- (void)setupPlayer:(NSURL*)movie
{
    if (!mMoviePlayer) {
        mMoviePlayer = [[AVPlayer alloc] init];
        mTimeObserverToken = [mMoviePlayer addPeriodicTimeObserverForInterval: CMTimeMake(1, 10)
                                                                        queue: dispatch_get_main_queue()
                                                                   usingBlock: ^(CMTime time) {
                                                                       if ([[mMoviePlayer currentItem] status] == AVPlayerItemStatusReadyToPlay) {
                                                                           double now = CMTimeGetSeconds([mMoviePlayer currentTime]);
                                                                           mTimeSlider.doubleValue = now;
                                                                           mCurrentTime.doubleValue = now;
                                                                           [mTimeSlider setEnabled: YES];
                                                                       } else {
                                                                           [mTimeSlider setEnabled: NO];
                                                                       }
                                                                   }];
        mEndMovieToken = nil;
    }
    
    if (!mMoviePlayerLayer) {
        AVPlayerLayer *newPlayerLayer = [AVPlayerLayer playerLayerWithPlayer: mMoviePlayer];
        newPlayerLayer.frame = self.layer.bounds;
        newPlayerLayer.autoresizingMask = kCALayerWidthSizable | kCALayerHeightSizable;
        [self.layer addSublayer:newPlayerLayer];
        mMoviePlayerLayer = [newPlayerLayer retain];
        [mMoviePlayerLayer addObserver:self forKeyPath:@"readyForDisplay" options:0 context:LayerStatusContext];
        
    }
    
    // Create an asset with our URL, asychronously load its tracks and whether it's playable or protected.
    // When that loading is complete, configure a player to play the asset.
    AVURLAsset *asset = [[AVURLAsset alloc] initWithURL: movie options: nil];
    NSArray *assetKeysToLoadAndTest = @[@"playable", @"hasProtectedContent", @"tracks", @"duration"];
    [asset loadValuesAsynchronouslyForKeys:assetKeysToLoadAndTest completionHandler:^(void) {
        // The asset invokes its completion handler on an arbitrary queue when loading is complete.
        // Because we want to access our AVPlayer in our ensuing set-up, we must dispatch our handler to the main queue.
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            [self setUpPlaybackOfAsset:asset withKeys:assetKeysToLoadAndTest];
        });
    }];
}

- (void)tearDownPlayer
{
    if (!mMoviePlayer) return;
    [mMoviePlayer pause];
    
    if (mMoviePlayerLayer) {
        [mMoviePlayerLayer setPlayer:nil];
        [mMoviePlayerLayer removeFromSuperlayer];
        [mMoviePlayerLayer removeObserver:self forKeyPath:@"readyForDisplay" context:LayerStatusContext];
        [mMoviePlayerLayer release]; mMoviePlayerLayer = nil;
    }
    
    if (mTimeObserverToken)
        [mMoviePlayer removeTimeObserver: mTimeObserverToken];
    if (mEndMovieToken)
        [[NSNotificationCenter defaultCenter] removeObserver: mEndMovieToken];
    mEndMovieToken = nil;
    mTimeObserverToken = nil;
    
    AVPlayerItem* playerItem = [mMoviePlayer currentItem];
    if (playerItem) {
        [playerItem removeObserver:self forKeyPath:@"duration" context:ItemDurationContext];
        [playerItem removeObserver:self forKeyPath:@"status" context:ItemStatusContext];
    }
    
    [mMoviePlayer replaceCurrentItemWithPlayerItem: nil];
    
    [mMoviePlayer release]; mMoviePlayer = nil;
    
    [mMovieControls setHidden: YES];
    [mStatus setHidden: NO];
}

- (void)setUpPlaybackOfAsset:(AVURLAsset *)asset withKeys:(NSArray *)keys
{
    [asset autorelease];
    
    // This method is called when the AVAsset for our URL has completing the loading of the values of the specified array of keys.
    // We set up playback of the asset here.
    AVPlayerItem* playerItem = nil;
    
    // First test whether the values of each of the keys we need have been successfully loaded.
    for (NSString *key in keys) {
        NSError *error = nil;
        
        if ([asset statusOfValueForKey:key error:&error] == AVKeyValueStatusFailed) {
            // We can fail here even though the movie media is OK. Try a different
            // method for loading the item and hope for the best.
            playerItem = [AVPlayerItem playerItemWithURL: [asset URL]];
            if ([playerItem status] == AVPlayerItemStatusFailed) {
                [self stopLoadingAnimationAndHandleError: [playerItem error]];
                return;
            }
            [playerItem addObserver:self forKeyPath:@"duration" options:0 context:ItemDurationContext];
            break;
        }
    }
    
    if (!playerItem) {      // Only test if the keys all loaded the first time
        if (![asset isPlayable] || [asset hasProtectedContent] ||
            [[asset tracksWithMediaType:AVMediaTypeVideo] count] == 0)
        {
            [mDocument noteStatus: @"Cannot play movie."];
            return;
        }
    }
    
    // We can play this asset.
    // Create a new AVPlayerItem and make it our player's current item.
    if (!playerItem) {
        playerItem = [AVPlayerItem playerItemWithAsset:asset];
        [playerItem addObserver:self forKeyPath:@"duration" options:0 context:ItemDurationContext];
    }
    
    if (mEndMovieToken) {
        [[NSNotificationCenter defaultCenter] removeObserver: mEndMovieToken];
        mEndMovieToken = nil;
    }
    
    AVPlayerItem* oldPlayerItem = [mMoviePlayer currentItem];
    if (oldPlayerItem) {
        [oldPlayerItem removeObserver:self forKeyPath:@"duration" context:ItemDurationContext];
        [oldPlayerItem removeObserver:self forKeyPath:@"status" context:ItemStatusContext];
    }
    

    
    if (playerItem) {
        [self setupTimeSlider: playerItem];
        
        [playerItem addObserver:self forKeyPath:@"status" options:0 context:ItemStatusContext];
        
        // Subscribe to the AVPlayerItem's DidPlayToEndTime notification.
        mEndMovieToken = [[NSNotificationCenter defaultCenter] addObserverForName:AVPlayerItemDidPlayToEndTimeNotification
                                                                           object:playerItem
                                                                            queue:[NSOperationQueue mainQueue]
                                                                       usingBlock:^(NSNotification *note) {
                                                                           mAtEndofMovie = true;
                                                                           mStartStopButton.image = PlayNormalImage;
                                                                           mStartStopButton.alternateImage = PlayPressImage;
                                                                       }
                          ];
    }
    [mMoviePlayer replaceCurrentItemWithPlayerItem:playerItem];
    mMoviePlayer.actionAtItemEnd = AVPlayerActionAtItemEndPause;
    
    mAtEndofMovie = false;
}

- (bool)setupTimeSlider:(AVPlayerItem*)playerItem
{
    CMTime lengthTime = [playerItem duration];
    double length = CMTimeGetSeconds(lengthTime);
    if (isfinite(length)) {
        mTimeSlider.maxValue = length;
        mTimeLabel.doubleValue = length;
        mTimeSlider.doubleValue = 0.0;
        mStartStopButton.image = PlayNormalImage;
        mStartStopButton.alternateImage = PlayPressImage;
        return true;
    }
    return false;
}

- (void)stopLoadingAnimationAndHandleError:(NSError *)error
{
    if (error) {
        [mDocument noteStatus: [error localizedDescription]];
        NSString* fail = [error localizedFailureReason];
        if (fail)
            [mDocument noteStatus: fail];
    }
    NSBeep();
}

- (void)showSavePanelTitle:(NSString *)title
        fileType:(NSArray *)fileTypes
        accessoryView:(NSView *)view
        didEndSelector:(SEL)selector
{
    NSSavePanel *sp = [NSSavePanel savePanel];
    [sp setAllowedFileTypes: fileTypes];
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
        [self pngImageDataCropped: NO multiplier: &mult];
    
    if (pngData) {
        [pngData writeToURL: filename atomically: YES];
    } else {
        [mDocument noteStatus: @"An error occured while writing the PNG file."];
        NSBeep();
    }
}

- (void)saveSvgtoFile:(NSURL*)filename
{
    mCanvas = std::make_unique<SVGCanvas>(
        [[filename path] UTF8String],
        (int)mRenderedRect.size.width, (int)mRenderedRect.size.height,
        false
    );
    
    if (mCanvas->mError) {
        [mDocument noteStatus: @"An error occured while writing the SVG file."];
        NSBeep();
        mCanvas.reset();
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
    if (!mMovieFile) {
        [mDocument noteStatus: @"There is no movie to save."];
        NSBeep();
        return;
    }
    if (!mMovieFile->written()) {
        [mDocument noteStatus: @"Movie file is already saved."];
        NSBeep();
        return;
    }
    
    NSError* fileErr = nil;
    [self tearDownPlayer];   // disconnect player from temp file
    NSString* tempPath = [NSString stringWithUTF8String: mMovieFile->name().c_str()];
    NSURL* tempURL = [NSURL fileURLWithPath: tempPath];
    if ([[NSFileManager defaultManager] moveItemAtURL:tempURL
                                                toURL:filename
                                                error:&fileErr])
    {
        mMovieFile->release();
    } else {
        [mDocument noteStatus: @"Movie save failed."];
        NSBeep();
    }
}

- (void)deleteRenderer
{
    mEngine.reset();
    mMovieFile.reset();
    mCanvas.reset();
    if (!mRenderer) return;
#ifdef EXTREME_PARAM_DEBUG
    mRenderer.reset();
#else
    NSValue* r = [NSValue valueWithPointer: (const void*)mRenderer.get()];
    mRenderer.release();
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

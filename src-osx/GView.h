// GView.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2012 John Horigan - john@glyphic.com
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

#import <Cocoa/Cocoa.h>
#import "KFSplitView.h"

@class CFDGDocument;
@class TopBar;
@class BitmapImageHolder;

class CFDG;
class Canvas;
class Renderer;
class qtCanvas;

@interface GView : NSView<NSWindowDelegate> {
    CFDG*       mEngine;
    Renderer*   mRenderer;
    Canvas*     mCanvas;
    
    NSSize              mRenderSize;    // size we asked to render to
    NSRect              mRenderedRect;  // area that was actually rendered
    BitmapImageHolder*  mRenderBitmap;  // this bitmap must never be drawn

    NSImage*            mDrawingImage;

    NSTimer*    mUpdateTimer;
    int         mOutputProgressDelay;
    
    bool mRendering;
    bool mRestartRenderer;
    bool mRendererFinishing;
    bool mRendererStopping;
    bool mLastRenderWasHires;
    bool mCloseOnRenderStopped;
    
    NSSize mLastRenderSize;
    double mLastRenderMin;
    
    bool mCanvasColor256;

    IBOutlet CFDGDocument*          mDocument;

    IBOutlet TopBar*                mTopBar;
    IBOutlet NSButton*              mRenderControl;
    IBOutlet NSTextField*           mStatus;
    IBOutlet NSProgressIndicator*   mProgress;
    IBOutlet NSProgressIndicator*   mOutputProgress;
    
    int     mCurrentVariation;
    bool    mIncrementVariationOnRender;
    
    IBOutlet NSTextField*           mVariationLabel;
    IBOutlet NSTextField*           mVariationField;
    IBOutlet NSStepper*             mVariationStepper;
    
    IBOutlet NSView*                mSaveImageAccessory;
    IBOutlet NSView*                mSaveTileAccessory;
    IBOutlet NSTextField*           mSaveTileWidth;
    IBOutlet NSTextField*           mSaveTileHeight;
    IBOutlet NSView*                mSaveAnimationAccessory;
    
    NSMenuItem*    mFullScreenMenu;
    
    qtCanvas*      mAnimationCanvas;

    bool    mTiled;
    double  mScale;
}

- (id)initWithFrame:(NSRect)frame;

- (IBAction)toggleRender:(id)sender;
- (IBAction)saveImage:(id)sender;
- (IBAction)saveTileImage:(id)sender;
- (IBAction)saveAsSVG:(id)sender;
- (IBAction)saveAsMovie:(id)sender;
- (BOOL)validateMenuItem:(NSMenuItem *)anItem;
- (IBAction)enterFullscreen:(id)sender;
- (void)updateFullScreenMenu;

- (IBAction) showHiresRenderSheet:(id)sender;

- (void)noteStats:(NSValue*)v;
- (void)redisplayImage:(NSValue*)sizeObj;

- (int) variation;
- (bool) canvasColor256;
- (bool) isTiled;
- (int) isFrieze;
- (NSData*) pngImageDataCropped:(BOOL)cropped multiplier:(NSSize*) mult;

@end

@interface GView (renderControl)
- (IBAction) startRender:(id)sender;
- (IBAction) finishRender:(id)sender;
- (IBAction) stopRender:(id)sender;
- (IBAction) repeatRender:(id)sender;
- (void) startHiresRender: (NSSize) size minimum: (double) minSize;
@end

@interface GView (variationControl)
- (void) initializeVariation;
- (void) updateVariation:(BOOL)incrementIfNeeded;
- (void) useVariation;
- (void) reuseVariation;
- (void) setVariation:(int)var;
- (IBAction) adjustVariation:(id)sender;    // sent by stepper
- (IBAction) editVariation:(id)sender;      // sent by text field
@end

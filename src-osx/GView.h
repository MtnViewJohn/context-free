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
#import <AVFoundation/AVFoundation.h>
#import "../src-scintilla/cocoa/ScintillaView.h"
#import "../src-scintilla/cocoa/InfoBar.h"
#include <memory>

extern NSString* PrefKeyMovieZoom;
extern NSString* PrefKeyMovieLength;
extern NSString* PrefKeyMovieFrameRate;
extern NSString* PrefKeyMovieFormat;
extern NSString* PrefKeyMovieWidth;
extern NSString* PrefKeyMovieHeight;
extern NSString* PrefKeyHiresWidth;
extern NSString* PrefKeyHiresHeight;
extern NSString* PrefKeyMinumumSize;
extern NSString* prefKeyEditorFontFamily;
extern NSString* prefKeyEditorFontSize;

@class CFDGDocument;
@class TopBar;

typedef NS_ENUM(NSInteger, ActionType) {
    StopAction          = 0,
    RenderAction        = 1,
    AnimateAction       = 2,
    AnimateFrameAction  = 3,
    Render2SizeAction   = 4
};

typedef NS_ENUM(NSInteger, FindReplaceShowEnum) {
    ShowNeither         = 0,
    ShowFind            = 1,
    ShowFindReplace     = 2
};

long MakeColor(id v);

@interface GView : NSView<NSWindowDelegate, ScintillaNotificationProtocol> {
    NSSize              mRenderSize;    // size we asked to render to
    NSRect              mRenderedRect;  // area that was actually rendered

    NSImage*            mDrawingImage;

    NSTimer*    mUpdateTimer;
    int         mOutputProgressDelay;
    
    AVPlayer*       mMoviePlayer;
    AVPlayerLayer*  mMoviePlayerLayer;
    id              mTimeObserverToken;
    bool            mAtEndofMovie;
    id              mEndMovieToken;
    BOOL            mLoop;
    double          mFrameRate;
    
    bool mRendering;
    bool mRestartRenderer;
    bool mRendererFinishing;
    bool mRendererStopping;
    bool mCloseOnRenderStopped;
    
    float  mLastAnimateFrame;
    
    bool mCanvasColor256;

    IBOutlet CFDGDocument*          mDocument;

    IBOutlet TopBar*                mTopBar;
    IBOutlet NSSegmentedControl*    mActionControl;
    IBOutlet NSPopUpButton*         mActionSelect;
    IBOutlet NSTextField*           mStatus;
    IBOutlet NSProgressIndicator*   mProgress;
    IBOutlet NSProgressIndicator*   mOutputProgress;
    
    IBOutlet NSTextField*           mFindText;
    IBOutlet NSTextField*           mReplaceText;
    NSInteger                       mFindTextVersion;
    IBOutlet NSSegmentedControl*    mFindButtons;
    IBOutlet NSSegmentedControl*    mReplaceButtons;
    IBOutlet NSButton*              mFindOptionsButton;

    int     mCurrentVariation;
    bool    mIncrementVariationOnRender;
    ActionType mCurrentAction;
    
    IBOutlet NSTextField*           mVariationLabel;
    IBOutlet NSTextField*           mVariationField;
    IBOutlet NSStepper*             mVariationStepper;
    IBOutlet NSTextField*           mFrameLabel;
    IBOutlet NSTextField*           mFrameField;
    IBOutlet NSStepper*             mFrameStepper;
    IBOutlet NSTextField*           mRenderWidth;
    IBOutlet NSTextField*           mRenderHeight;
    IBOutlet NSTextField*           mRenderX;

    IBOutlet NSBox*                 mMovieControls;
    IBOutlet NSButton*              mStartStopButton;
    IBOutlet NSButton*              mRewindButton;
    IBOutlet NSSlider*              mTimeSlider;
    IBOutlet NSTextField*           mTimeLabel;
    IBOutlet NSTextField*           mCurrentTime;
    
    IBOutlet NSView*                mSaveImageAccessory;
    IBOutlet NSView*                mSaveTileAccessory;
    IBOutlet NSTextField*           mSaveTileWidth;
    IBOutlet NSTextField*           mSaveTileHeight;
    IBOutlet NSView*                mSaveAnimationAccessory;
    
    IBOutlet NSBox*                 mEditorBox;
    ScintillaView*                  mEditor;
    IBOutlet NSImageView*           mRewindView;
    
    bool    mTiled;
    double  mScale;
    
    bool mSuspendNotifications;
}

- (id)initWithFrame:(NSRect)frame;
- (void)showFindReplace:(FindReplaceShowEnum) e;
- (IBAction)findAction:(id)sender;
- (IBAction)findOptions:(id)sender;

- (IBAction)toggleRender:(id)sender;
- (IBAction)selectAction:(id)sender;
- (IBAction)saveOutput:(id)sender;
- (IBAction)saveTileImage:(id)sender;
- (IBAction)saveAsSVG:(id)sender;
- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)anItem;

- (IBAction) showHiresRenderSheet:(id)sender;
- (IBAction) showAnimationSheet:(id)sender;
- (IBAction) showAnimationFrameSheet:(id)sender;

- (IBAction) toggleMovieStartStop:(id)sender;
- (IBAction) movieRewind:(id)sender;
- (IBAction) movieTimeChange:(id)sender;

- (void)noteStats:(NSValue*)v;
- (void)redisplayImage:(NSValue*)sizeObj;

- (int) variation;
- (bool) canvasColor256;
- (bool) isTiled;
- (int) isFrieze;
- (NSData*) pngImageDataCropped:(BOOL)cropped multiplier:(NSSize*) mult;

- (void)controlTextDidChange:(NSNotification *)notification;
- (void)notification:(SCNotification *)notification;
- (void)suspendNotifications:(BOOL)suspend;
- (void)updateStyling;
@end

@interface GView (renderControl)
- (IBAction) startRender:(id)sender;
- (IBAction) finishRender:(id)sender;
- (IBAction) stopRender:(id)sender;
- (void) startHiresRender;
- (void) startAnimation:(float) frame;
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

@interface GView (frameControl)
- (void) initializeFrame;
- (int) checkFrame:(int)frame;
- (void) setAnimationFrame:(float)frame;
- (float) animationFrame;
- (IBAction) adjustFrame:(id)sender;        // sent by stepper & text field
@end


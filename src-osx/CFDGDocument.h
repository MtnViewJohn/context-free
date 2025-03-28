// CFDGDocument.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2008-2011 John Horigan - john@glyphic.com
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
#import "../src-scintilla/cocoa/ScintillaView.h"
#include "cfdg.h"

@class GalleryUploader;
@class GalleryDownloader;
@class GView;
@class CfdgErrorWrapper;

@interface CFDGDocument : NSDocument {
    AbstractSystem*         mSystem;
    NSData*                 mContent;
    
    ScintillaView*          mEditor;
    IBOutlet NSTextView*    mStatusText;
    
    IBOutlet NSTextField*   mAnimationFrame;
    IBOutlet NSTextField*   mFrameLabel;
    IBOutlet NSTextField*   mTimeLabel;
    IBOutlet NSPopUpButton* mAnimationCodec;
    IBOutlet NSTextField*   mCodecLabel;
    
    IBOutlet GView*         mGView;
    IBOutlet NSPanel*       mHiresSheet;
    IBOutlet NSPanel*       mAnimateSheet;
    IBOutlet NSTextField*   mSheetLabel;
    
    IBOutlet NSSplitView*   mGViewSplit;
    IBOutlet NSSplitView*   mEditorSplit;
    
    GalleryUploader*        mUploader;

    NSString*               mDisplayName;
    
    BOOL                    mIsExample;
}

- (IBAction) startRender:(id)sender;
- (IBAction) finishRender:(id)sender;
- (IBAction) stopRender:(id)sender;
- (IBAction) saveAsSVG:(id)sender;
- (IBAction) uploadToGallery:(id)sender;
- (IBAction) insertUnicode:(id)sender;
- (IBAction)shiftLeftRight:(id)sender;

- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)anItem;

- (IBAction) showHiresRenderSheet:(id)sender;
- (IBAction) startHiresRender:(id)sender;
- (IBAction) cancelHiresRender:(id)sender;
- (IBAction) showAnimateSheet:(id)sender;
- (IBAction) showAnimateFrameSheet:(id)sender;
- (IBAction) startAnimation:(id)sender;
- (IBAction) cancelAnimation:(id)sender;
- (IBAction) closeAll:(id)sender;

- (cfdg_ptr)buildEngine;
- (AbstractSystem*)system;

- (BOOL)isExample;
- (void)makeExample;

- (void)setEditor:(ScintillaView*)editor;
- (void)showContent;
- (NSData*)getContent;
- (void)updateFont:(NSString*)name size:(float)sz;
- (void)updateStyling;
- (void)textDidChange:(NSNotification *)notification;
- (void)setDirty:(BOOL)dirty;
- (void)tabWidthDidChange:(NSInteger)tab;

- (void)noteStatus:(NSString*)s;
- (void)noteCatastrophicError:(NSString*)s;
- (void)noteStats:(NSValue*)v;
- (void) setVariation:(int)var;
- (void)noteError:(CfdgErrorWrapper*)e;
- (void)highlightChars:(CfdgErrorWrapper*)link;

+ (NSString*)documentType;
+ (BOOL)autosavesInPlace;
+ (NSArray*) checkForTempFiles;

@end

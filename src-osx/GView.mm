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
#import "CFDGController.h"

#include "cfdg.h"
#include "SVGCanvas.h"
#include "ImageCanvas.h"
#include "AVcanvas.h"
#include "tiledCanvas.h"
#include "Rand64.h"
#include <cmath>
#include "tempfile.h"
#include <algorithm>
#include <cstring>
#include "CFscintilla.h"

using cfdg_ptr = std::shared_ptr<CFDG>;
using renderer_ptr = std::unique_ptr<Renderer>;
using canvas_ptr = std::unique_ptr<Canvas>;
using tempfile_ptr = std::unique_ptr<TempFile>;


//#define PROGRESS_ANIMATE_DIRECTLY
//#define USE_SAVE_GRAPHICS_STATE
//#define TIME_AND_LOG_RENDER

#define UPDATE_RATE         (1.0/12.0)
#define PROGRESS_DELAY      12

extern NSInteger CurrentTabWidth;

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

typedef NS_ENUM(signed char, FindResult) {
    FindResultNotFound,
    FindResultFound,
    FindResultFoundWrapped
};

typedef NS_ENUM(NSInteger, FindType) {
    FindContains = 1,
    FindWholeWord = 2,
    FindStartsWith = 3
};



- (void)setupEditor;
- (FindResult) findAndHighlightText: (NSString *) searchText
                          matchCase: (BOOL) matchCase
                           findType: (FindType) findType
                           scrollTo: (BOOL) scrollTo
                               wrap: (BOOL) wrap
                          backwards: (BOOL) backwards;
- (int) findAndReplaceText: (NSString *) searchText
                    byText: (NSString *) newText
                 matchCase: (BOOL) matchCase
                  findType: (FindType) findType
                     doAll: (BOOL) doAll
               inSelection: (BOOL) inSelection;
- (BOOL)findNext:(BOOL)reversed;
- (void)replaceNext;
- (void)replaceAll:(BOOL)inSelection;
- (void)checkAutoC;

- (void)drawCheckerboardRect:(NSRect)rect;

- (void) setMovieImagesPlay:(BOOL)play;

- (void)buildEngine;
- (void)buildRendererSize:(NSSize)size minimum:(double)minSize;
- (void)buildImageCanvasSize;

- (void)invalidateDrawingImage;
- (bool)validateDrawingImage;

- (void)noteProgress;
- (void)requestRenderUpdate;
- (void)setCurrentAction:(ActionType)newAction;

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
    NSImage*    RewindNormalImage = nil;
    NSImage*    RewindPressImage = nil;
    NSImage*    MagnifyingGlassLight = nil;
    NSImage*    MagnifyingGlassDark = nil;
    
    NSString* PrefKeyEditorDefaultBold = @"EditorDefaultBold";
    NSString* PrefKeyEditorCommentsBold = @"EditorCommentsBold";
    NSString* PrefKeyEditorSymbolsBold = @"EditorSymbolsBold";
    NSString* PrefKeyEditorIdentifiersBold = @"EditorIdentifiersBold";
    NSString* PrefKeyEditorKeywordsBold = @"EditorKeywordsBold";
    NSString* PrefKeyEditorBuiltinsBold = @"EditorBuiltinsBold";
    NSString* PrefKeyEditorStringsBold = @"EditorStringsBold";
    NSString* PrefKeyEditorNumbersBold = @"EditorNumbersBold";
    NSString* PrefKeyEditorDefaultItalic = @"EditorDefaultItalic";
    NSString* PrefKeyEditorCommentsItalic = @"EditorCommentsItalic";
    NSString* PrefKeyEditorSymbolsItalic = @"EditorSymbolsItalic";
    NSString* PrefKeyEditorIdentifiersItalic = @"EditorIdentifiersItalic";
    NSString* PrefKeyEditorKeywordsItalic = @"EditorKeywordsItalic";
    NSString* PrefKeyEditorBuiltinsItalic = @"EditorBuiltinsItalic";
    NSString* PrefKeyEditorStringsItalic = @"EditorStringsItalic";
    NSString* PrefKeyEditorNumbersItalic = @"EditorNumbersItalic";
    NSString* PrefKeyEditorDefaultColor = @"EditorDefaultColor";
    NSString* PrefKeyEditorCommentsColor = @"EditorCommentsColor";
    NSString* PrefKeyEditorSymbolsColor = @"EditorSymbolsColor";
    NSString* PrefKeyEditorIdentifiersColor = @"EditorIdentifiersColor";
    NSString* PrefKeyEditorKeywordsColor = @"EditorKeywordsColor";
    NSString* PrefKeyEditorBuiltinsColor = @"EditorBuiltinsColor";
    NSString* PrefKeyEditorStringsColor = @"EditorStringsColor";
    NSString* PrefKeyEditorNumbersColor = @"EditorNumbersColor";
    NSString* PrefKeyEditorDefaultDarkColor = @"EditorDefaultDarkColor";
    NSString* PrefKeyEditorCommentsDarkColor = @"EditorCommentsDarkColor";
    NSString* PrefKeyEditorSymbolsDarkColor = @"EditorSymbolsDarkColor";
    NSString* PrefKeyEditorIdentifiersDarkColor = @"EditorIdentifiersDarkColor";
    NSString* PrefKeyEditorKeywordsDarkColor = @"EditorKeywordsDarkColor";
    NSString* PrefKeyEditorBuiltinsDarkColor = @"EditorBuiltinsDarkColor";
    NSString* PrefKeyEditorStringsDarkColor = @"EditorStringsDarkColor";
    NSString* PrefKeyEditorNumbersDarkColor = @"EditorNumbersDarkColor";

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
    
    NSArray*    ActionStrings = nil;
    
    NSDictionary<NSString*, NSString*>* ColorNames = nil;
}


@interface GView (renderThread)
- (void) renderBegin:(RenderParameters*)parameters;
- (void) renderThread:(id)arg;
- (void) renderStopped:(id)arg; // sent by thread
@end


@implementation GView {
    bool mMatchCase;
    FindType mFindType;
    bool mWrapSearch;
    NSInteger mLastCaretPos;
}

+ (void)initialize {
    if (self == [GView self]) {
        PlayNormalImage =   [[NSImage imageNamed:@"RemotePlay_norm.tif.icns"] retain];
        PlayPressImage =    [[NSImage imageNamed:@"RemotePlay_press.tif.icns"] retain];
        PauseNormalImage =  [[NSImage imageNamed:@"RemotePause_norm.tif.icns"] retain];
        PausePressImage =   [[NSImage imageNamed:@"RemotePause_press.tif.icns"] retain];
        RewindNormalImage =  [[NSImage imageNamed:@"rewind.norm.icns"] retain];
        RewindPressImage =   [[NSImage imageNamed:@"rewind.press.icns"] retain];
        MagnifyingGlassLight = [[NSImage imageNamed:@"magnifying-glass.icns"] retain];
        MagnifyingGlassDark = [[NSImage imageNamed:@"magnifying-glass-white.icns"] retain];
        std::sort(CFscintilla::AutoComplete.begin(), CFscintilla::AutoComplete.end(), CFscintilla::AutoCmp());
        ColorNames = [[NSDictionary alloc] initWithObjectsAndKeys:
                        @"aliceblue", @"#f0f8ff",
                        @"antiquewhite", @"#faebd7",
                        @"aqua", @"#00ffff",
                        @"aquamarine", @"#7fffd4",
                        @"azure", @"#f0ffff",
                        @"beige", @"#f5f5dc",
                        @"bisque", @"#ffe4c4",
                        @"black", @"#000000",
                        @"blanchedalmond", @"#ffebcd",
                        @"blue", @"#0000ff",
                        @"blueviolet", @"#8a2be2",
                        @"brown", @"#a52a2a",
                        @"burlywood", @"#deb887",
                        @"cadetblue", @"#5f9ea0",
                        @"chartreuse", @"#7fff00",
                        @"chocolate", @"#d2691e",
                        @"coral", @"#ff7f50",
                        @"cornflowerblue", @"#6495ed",
                        @"cornsilk", @"#fff8dc",
                        @"crimson", @"#dc143c",
                        @"cyan", @"#00ffff",
                        @"darkblue", @"#00008b",
                        @"darkcyan", @"#008b8b",
                        @"darkgoldenrod", @"#b8860b",
                        @"darkgray", @"#a9a9a9",
                        @"darkgrey", @"#a9a9a9",
                        @"darkgreen", @"#006400",
                        @"darkkhaki", @"#bdb76b",
                        @"darkmagenta", @"#8b008b",
                        @"darkolivegreen", @"#556b2f",
                        @"darkorange", @"#ff8c00",
                        @"darkorchid", @"#9932cc",
                        @"darkred", @"#8b0000",
                        @"darksalmon", @"#e9967a",
                        @"darkseagreen", @"#8fbc8f",
                        @"darkslateblue", @"#483d8b",
                        @"darkslategray", @"#2f4f4f",
                        @"darkslategrey", @"#2f4f4f",
                        @"darkturquoise", @"#00ced1",
                        @"darkviolet", @"#9400d3",
                        @"deeppink", @"#ff1493",
                        @"deepskyblue", @"#00bfff",
                        @"dimgray", @"#696969",
                        @"dimgrey", @"#696969",
                        @"dodgerblue", @"#1e90ff",
                        @"firebrick", @"#b22222",
                        @"floralwhite", @"#fffaf0",
                        @"forestgreen", @"#228b22",
                        @"fuchsia", @"#ff00ff",
                        @"gainsboro", @"#dcdcdc",
                        @"ghostwhite", @"#f8f8ff",
                        @"gold", @"#ffd700",
                        @"goldenrod", @"#daa520",
                        @"gray", @"#808080",
                        @"grey", @"#808080",
                        @"green", @"#008000",
                        @"greenyellow", @"#adff2f",
                        @"honeydew", @"#f0fff0",
                        @"hotpink", @"#ff69b4",
                        @"indianred", @"#cd5c5c",
                        @"indigo", @"#4b0082",
                        @"ivory", @"#fffff0",
                        @"khaki", @"#f0e68c",
                        @"lavender", @"#e6e6fa",
                        @"lavenderblush", @"#fff0f5",
                        @"lawngreen", @"#7cfc00",
                        @"lemonchiffon", @"#fffacd",
                        @"lightblue", @"#add8e6",
                        @"lightcoral", @"#f08080",
                        @"lightcyan", @"#e0ffff",
                        @"lightgoldenrodyellow", @"#fafad2",
                        @"lightgray", @"#d3d3d3",
                        @"lightgrey", @"#d3d3d3",
                        @"lightgreen", @"#90ee90",
                        @"lightpink", @"#ffb6c1",
                        @"lightsalmon", @"#ffa07a",
                        @"lightseagreen", @"#20b2aa",
                        @"lightskyblue", @"#87cefa",
                        @"lightslategray", @"#778899",
                        @"lightslategrey", @"#778899",
                        @"lightsteelblue", @"#b0c4de",
                        @"lightyellow", @"#ffffe0",
                        @"lime", @"#00ff00",
                        @"limegreen", @"#32cd32",
                        @"linen", @"#faf0e6",
                        @"magenta", @"#ff00ff",
                        @"maroon", @"#800000",
                        @"mediumaquamarine", @"#66cdaa",
                        @"mediumblue", @"#0000cd",
                        @"mediumorchid", @"#ba55d3",
                        @"mediumpurple", @"#9370db",
                        @"mediumseagreen", @"#3cb371",
                        @"mediumslateblue", @"#7b68ee",
                        @"mediumspringgreen", @"#00fa9a",
                        @"mediumturquoise", @"#48d1cc",
                        @"mediumvioletred", @"#c71585",
                        @"midnightblue", @"#191970",
                        @"mintcream", @"#f5fffa",
                        @"mistyrose", @"#ffe4e1",
                        @"moccasin", @"#ffe4b5",
                        @"navajowhite", @"#ffdead",
                        @"navy", @"#000080",
                        @"oldlace", @"#fdf5e6",
                        @"olive", @"#808000",
                        @"olivedrab", @"#6b8e23",
                        @"orange", @"#ffa500",
                        @"orangered", @"#ff4500",
                        @"orchid", @"#da70d6",
                        @"palegoldenrod", @"#eee8aa",
                        @"palegreen", @"#98fb98",
                        @"paleturquoise", @"#afeeee",
                        @"palevioletred", @"#db7093",
                        @"papayawhip", @"#ffefd5",
                        @"peachpuff", @"#ffdab9",
                        @"peru", @"#cd853f",
                        @"pink", @"#ffc0cb",
                        @"plum", @"#dda0dd",
                        @"powderblue", @"#b0e0e6",
                        @"purple", @"#800080",
                        @"rebeccapurple", @"#663399",
                        @"red", @"#ff0000",
                        @"rosybrown", @"#bc8f8f",
                        @"royalblue", @"#4169e1",
                        @"saddlebrown", @"#8b4513",
                        @"salmon", @"#fa8072",
                        @"sandybrown", @"#f4a460",
                        @"seagreen", @"#2e8b57",
                        @"seashell", @"#fff5ee",
                        @"sienna", @"#a0522d",
                        @"silver", @"#c0c0c0",
                        @"skyblue", @"#87ceeb",
                        @"slateblue", @"#6a5acd",
                        @"slategray", @"#708090",
                        @"slategrey", @"#708090",
                        @"snow", @"#fffafa",
                        @"springgreen", @"#00ff7f",
                        @"steelblue", @"#4682b4",
                        @"tan", @"#d2b48c",
                        @"teal", @"#008080",
                        @"thistle", @"#d8bfd8",
                        @"tomato", @"#ff6347",
                        @"turquoise", @"#40e0d0",
                        @"violet", @"#ee82ee",
                        @"wheat", @"#f5deb3",
                        @"white", @"#ffffff",
                        @"whitesmoke", @"#f5f5f5",
                        @"yellow", @"#ffff00",
                        @"yellowgreen", @"#9acd32",
                        nil];
        ActionStrings = [[NSArray alloc] initWithObjects: @"Stop", @"Render", @"Animate", @"Frame", @"Sized", nil];
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
        mCloseOnRenderStopped = false;
        
        mCurrentVariation = 0;
        mIncrementVariationOnRender = false;

        mTiled = false;
        
        mFullScreenMenu = nil;
        
        mFindTextVersion = NSIntegerMin;
        mMatchCase = true;
        mFindType = FindContains;
        mWrapSearch = true;
        mSuspendNotifications = false;
        mLastCaretPos = -1;
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
    [self initializeFrame];
    [self setCurrentAction: ActionType::RenderAction];
    
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
    self.wantsLayer = YES;
    
    NSRect newFrame = mEditorBox.frame;
    //newFrame.size.width -= 2 * newFrame.origin.x;
    //newFrame.size.height -= 3 * newFrame.origin.y + 55;
    
    mEditor = [[[ScintillaView alloc] initWithFrame: newFrame] autorelease];
    [mDocument setEditor: mEditor];
    
    [mEditorBox.contentView addSubview: mEditor];
    [mEditor setAutoresizesSubviews: YES];
    [mEditor setAutoresizingMask: NSViewWidthSizable | NSViewHeightSizable];
    [mEditor setDelegate: self];
    // I have no idea why this can't be called directly
    [[NSOperationQueue mainQueue] addOperationWithBlock: ^{
        [window makeFirstResponder:[mEditor content]];
    }];
    NSView* superview = [mRewindView superview];
    [self setupEditor];

    [mRewindView setAlphaValue:0.0];        // Put search wrap symbol on top
    [mRewindView removeFromSuperview];      // but have it be invisible (for now)
    [superview addSubview:mRewindView];
}

- (void)showFindReplace:(FindReplaceShowEnum) e
{
    NSRect newFrame = mEditorBox.frame;
    switch (e) {
        case ShowFind:
            newFrame.size.height -= 29;
            break;
        case ShowFindReplace:
            newFrame.size.height -= 55;
            break;
        default:
            break;
    }
    [mEditor setFrame: newFrame];
}

- (IBAction) findAction:(id)sender
{
    NSInteger tag = [sender tag];
    if ([sender isKindOfClass: [NSSegmentedControl class]]) {
        NSSegmentedControl* ctrl = (NSSegmentedControl*)sender;
        NSInteger seg = [ctrl selectedSegment];
        tag = [[ctrl cell] tagForSegment:seg];
    }
    switch (tag) {
        case 0: {   // Jump to selection
            [mEditor setGeneralProperty: SCI_SCROLLCARET value: 0];
            break;
        }
        case NSTextFinderActionShowFindInterface:
            [self showFindReplace: ShowFind];
            break;
        case NSTextFinderActionNextMatch:
            [self findNext:NO];
            break;
        case NSTextFinderActionPreviousMatch:
            [self findNext:YES];
            break;
        case NSTextFinderActionReplaceAll:
            [self replaceAll: NO];
            break;
        case NSTextFinderActionReplaceAllInSelection:
            [self replaceAll: YES];
            break;
        case NSTextFinderActionReplaceAndFind:
            [self replaceNext];
            break;
        case NSTextFinderActionSetSearchString: {
            BOOL canFind = [[mEditor selectedString] length] > 0;
            [mFindButtons setEnabled: canFind];
            [mReplaceButtons setEnabled: canFind];
            [mFindText setStringValue: [mEditor selectedString]];
            NSPasteboard* pBoard = [NSPasteboard pasteboardWithName:NSFindPboard];
            mFindTextVersion = [pBoard declareTypes:[NSArray arrayWithObject:NSStringPboardType] owner:nil];
            [pBoard setString:[mEditor selectedString] forType:NSStringPboardType];
            break;
        }
        case NSTextFinderActionShowReplaceInterface:
            [self showFindReplace: ShowFindReplace];
            break;
        case NSTextFinderActionHideFindInterface:
        case NSTextFinderActionHideReplaceInterface:
            [[self window] makeFirstResponder:[mEditor content]];
            [self showFindReplace: ShowNeither];
            break;
        default:
            break;
    }
}

- (void)findOptions:(id)sender
{
    switch (NSInteger t = [sender tag]) {
        case 0:
            mMatchCase = !mMatchCase;
            break;
        case 1:
        case 2:
        case 3:
            mFindType = (FindType)t;
            break;
        case 4:
            mWrapSearch = !mWrapSearch;
            break;
        default:
            break;
    }
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
    [self showFindReplace: ShowNeither];
    [[self window] makeFirstResponder:nil];
    [self tearDownPlayer];
    [self deleteRenderer];
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
    NSPasteboard* pBoard = [NSPasteboard pasteboardWithName:NSFindPboard];
    NSInteger version = [pBoard changeCount];
    if (version != mFindTextVersion) {
        NSString* find = [pBoard stringForType:NSPasteboardTypeString];
        mFindTextVersion = version;
        if (find)
            [mFindText setStringValue: find];
    }
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
        [self setMovieImagesPlay: YES];
    } else {
        [mMoviePlayer pause];
        [self setMovieImagesPlay: NO];
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
    int ox = static_cast<int>(dRect.origin.x = std::floor((fSize.width - dRect.size.width) * ((CGFloat)0.5)));
    int oy = static_cast<int>(dRect.origin.y = std::floor((fSize.height - dRect.size.height) * ((CGFloat)0.5)));

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

- (void)viewDidChangeEffectiveAppearance
{
    [self updateStyling];
    [self setMovieImagesPlay: mMoviePlayer && mMoviePlayer.rate > 0.0f];
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
            case Render2SizeAction:
                [self updateVariation: YES];
                [self startHiresRender];
                break;
                
            case AnimateFrameAction:
                [self updateVariation: YES];
                frame = mLastAnimateFrame;
            case AnimateAction: {
                [self startAnimation: frame];
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
    [self setCurrentAction: (ActionType)newAction];
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

- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)anItem
{
    SEL action = [anItem action];
    NSInteger tag = [anItem tag];
    static NSTextFinderAction findtags[5] = {
        NSTextFinderActionNextMatch,
        NSTextFinderActionPreviousMatch,
        NSTextFinderActionReplaceAll,
        NSTextFinderActionReplaceAllInSelection,
        NSTextFinderActionReplaceAndFind
    };
    
    if (action == @selector(startRender:) || action == @selector(toggleRender:))
        return !mRestartRenderer;
    
    if (action == @selector(enterFullscreen:))
        return YES;
        
    if (action == @selector(showHiresRenderSheet:)
        ||  action == @selector(showAnimateSheet:)
        ||  action == @selector(showAnimateFrameSheet:))
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
    
    if (action == @selector(findAction:) && std::find(findtags, findtags+5, tag) != findtags+5)
        return [[mFindText stringValue] length] > 0;
    
    if (action == @selector(findOptions:)) {
        NSMenuItem* menu = (NSMenuItem*)anItem;
        switch (tag) {
            case 0:
                menu.state = mMatchCase ? NSOnState : NSOffState;
                break;
            case 1:
            case 2:
            case 3:
                menu.state = mFindType == tag;
                break;
            case 4:
                menu.state = mWrapSearch ? NSOnState : NSOffState;
                break;
            default:
                break;
        }
    }
            
    return YES;
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
        CGImageDestinationCreateWithData((CFMutableDataRef)mdata, kUTTypePNG, 1, nil);
    if (!destref) return nil;
    
    CGImageDestinationAddImage(destref, iref, nullptr);
    CGImageDestinationFinalize(destref);
    CFRelease(destref);
    return mdata;
}


- (void)controlTextDidChange:(NSNotification *)notification
{
    NSTextField *textField = [notification object];
    if (textField == mRenderWidth || textField == mRenderHeight)
        [self reuseVariation];
    if (textField == mFrameField)
        [self adjustFrame: textField];  // which calls reuseVariation
    if (textField == mFindText) {
        BOOL canFind = [[mFindText stringValue] length] > 0;
        [mFindButtons setEnabled: canFind];
        [mReplaceButtons setEnabled: canFind];
        NSPasteboard* pBoard = [NSPasteboard pasteboardWithName:NSFindPboard];
        mFindTextVersion = [pBoard declareTypes:[NSArray arrayWithObject:NSStringPboardType] owner:nil];
        [pBoard setString:[mFindText stringValue] forType:NSStringPboardType];
    }
}

- (void)suspendNotifications:(BOOL)suspend
{
    mSuspendNotifications = suspend;
}

- (void)notification:(SCNotification *)notification
{
    if (mSuspendNotifications) return;
    switch (notification->nmhdr.code) {
        case SCN_CHARADDED: {
            
            if (notification->ch == '}') {                  // auto unindent
                long pos = [mEditor getGeneralProperty:SCI_GETCURRENTPOS];
                long lineno = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION
                                                parameter:pos];
                long indentPos = [mEditor getGeneralProperty:SCI_GETLINEINDENTPOSITION
                                                   parameter:lineno];
                if (indentPos + 1 == pos) {     // '}' is in initial white space
                    long indent = [mEditor getGeneralProperty:SCI_GETLINEINDENTATION
                                                    parameter:lineno];
                    if (indent >= CurrentTabWidth)
                        [mEditor setGeneralProperty:SCI_SETLINEINDENTATION
                                          parameter:lineno
                                              value:indent - CurrentTabWidth];
                    else
                        [mEditor setGeneralProperty:SCI_SETLINEINDENTATION
                                          parameter:lineno
                                              value:0];
                }
                return;
            }
            
            // auto-completion
            [self checkAutoC];
            break;
        }
        case SCN_MODIFIED:
            if (notification->modificationType & (SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT)) {
                [[NSNotificationCenter defaultCenter] postNotificationName: NSTextDidChangeNotification object: mEditor];
                [mDocument textDidChange:nil];
            }
            if (notification->modificationType & SC_MOD_INSERTCHECK && notification->text) {
                if (std::strcmp(notification->text, "\n") == 0 ||
                    std::strcmp(notification->text, "\r") == 0 ||
                    std::strcmp(notification->text, "\r\n") == 0)
                {      // auto indent
                    long lineno = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION parameter:notification->position];
                    auto line = std::string([mEditor getGeneralProperty:SCI_LINELENGTH parameter: lineno], ' ');
                    [mEditor setReferenceProperty:SCI_GETLINE parameter:lineno value:(void*)line.data()];
                    long indent = [mEditor getGeneralProperty:SCI_GETLINEINDENTATION parameter:lineno];
                    bool white = true;
                    for (char c: line) {
                        if (c == '{')
                            indent += CurrentTabWidth;
                        if (c == '}' && !white)
                            indent -= CurrentTabWidth;
                        if (!isspace((unsigned char)c))
                            white = false;
                    }
                    if (indent > 0) {
                        auto nextline = std::string(notification->text);
                        nextline.append(indent, ' ');
                        [mEditor setReferenceProperty:SCI_CHANGEINSERTION
                                            parameter:nextline.length()
                                                value:(const void*)nextline.data()];
                    }
                }
            }
            if (notification->modificationType & (SC_PERFORMED_REDO | SC_PERFORMED_UNDO) &&
                [mEditor getGeneralProperty:SCI_AUTOCACTIVE])
                [self checkAutoC];
            break;
        case SCN_AUTOCCHARDELETED:
            [self checkAutoC];
            break;
        case SCN_SAVEPOINTLEFT:
            [mDocument setDirty:YES];
            break;
        case SCN_SAVEPOINTREACHED:
            [mDocument setDirty:NO];
            break;
        case SCN_FOCUSOUT:
            [[NSNotificationCenter defaultCenter] postNotificationName: NSTextDidEndEditingNotification object: mEditor];
            break;
        case SCN_UPDATEUI: {
            // brace highlighting
            long caretPos = [mEditor getGeneralProperty:SCI_GETCURRENTPOS];
            if (caretPos == mLastCaretPos) break;
            mLastCaretPos = caretPos;
            long bracePos1 = -1;
            long bracePos2 = -1;
            if (caretPos > 0 && std::strchr("[]{}()",
                                            (char)[mEditor getGeneralProperty:SCI_GETCHARAT
                                                                    parameter:caretPos - 1]))
            {
                bracePos1 = caretPos - 1;
            } else if (std::strchr("[]{}()",
                                   (char)[mEditor getGeneralProperty:SCI_GETCHARAT
                                                           parameter:caretPos]))
            {
                bracePos1 = caretPos;
            }
            if (bracePos1 >= 0) {
                bracePos2 = [mEditor getGeneralProperty:SCI_BRACEMATCH
                                              parameter:bracePos1];
                if (bracePos2 == INVALID_POSITION)
                    [mEditor getGeneralProperty:SCI_BRACEBADLIGHT
                                      parameter:bracePos1];
                else
                    [mEditor getGeneralProperty:SCI_BRACEHIGHLIGHT
                                      parameter:bracePos1
                                          extra:bracePos2];
            } else {
                [mEditor getGeneralProperty:SCI_BRACEHIGHLIGHT
                                  parameter:INVALID_POSITION
                                      extra:INVALID_POSITION];
            }
            break;
        }
        case SCN_STYLENEEDED: {
            auto startpos = [mEditor getGeneralProperty:SCI_GETENDSTYLED];
            auto startline = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION parameter:startpos];
            startpos = [mEditor getGeneralProperty:SCI_POSITIONFROMLINE parameter:startline];
            long endpos = notification->position;
            auto endline = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION parameter:endpos];
            CFscintilla::Style state = CFscintilla::StyleDefault;
            if (startline > 0 && static_cast<CFscintilla::Style>
                ([mEditor getGeneralProperty:SCI_GETSTYLEAT
                                   parameter:(startpos-1)]) == CFscintilla::StyleComment)
                state = CFscintilla::StyleComment;
            std::vector<char> text, styles;
            [mEditor setGeneralProperty:SCI_STARTSTYLING parameter:startpos value:0];
            for (auto i = startline; i <= endline; ++i) {
                auto length = [mEditor getGeneralProperty:SCI_LINELENGTH parameter:i];
                if (static_cast<long>(text.size()) < length + 1)
                    text.resize(length + 1);
                if (static_cast<long>(styles.size()) < length)
                    styles.resize(length);
                [mEditor setReferenceProperty:SCI_GETLINE parameter:i value:text.data()];
                text[length] = '\0';
                state = CFscintilla::StyleLine(length, text.data(), styles.data(), state);
                [mEditor setReferenceProperty:SCI_SETSTYLINGEX parameter:length value:styles.data()];
            }
            break;
        }
        default:
            break;
    }
}

long MakeColor(id v)
{
    if ([v isKindOfClass:[NSString class]]) {
        NSString* fromHTML = (NSString*)v;
        if (NSString* cvalue = [ColorNames objectForKey:[fromHTML lowercaseString]])
            fromHTML = cvalue;
        if ((fromHTML.length == 4 || fromHTML.length == 7) && [fromHTML characterAtIndex: 0] == '#') {
            bool longVersion = fromHTML.length > 6;
            int index = 1;
            
            char value[3] = {0, 0, 0};
            value[0] = static_cast<char>([fromHTML characterAtIndex: index++]);
            if (longVersion)
                value[1] = static_cast<char>([fromHTML characterAtIndex: index++]);
            else
                value[1] = value[0];
            
            unsigned rawRed;
            [[NSScanner scannerWithString: @(value)] scanHexInt: &rawRed];
            
            value[0] = static_cast<char>([fromHTML characterAtIndex: index++]);
            if (longVersion)
                value[1] = static_cast<char>([fromHTML characterAtIndex: index++]);
            else
                value[1] = value[0];
            
            unsigned rawGreen;
            [[NSScanner scannerWithString: @(value)] scanHexInt: &rawGreen];
            
            value[0] = static_cast<char>([fromHTML characterAtIndex: index++]);
            if (longVersion)
                value[1] = static_cast<char>([fromHTML characterAtIndex: index++]);
            else
                value[1] = value[0];
            
            unsigned rawBlue;
            [[NSScanner scannerWithString: @(value)] scanHexInt: &rawBlue];
            
            long color = (rawBlue << 16) + (rawGreen << 8) + rawRed;
            return color;
        } else {
            return -1;
        }
    }
    if ([v isKindOfClass:[NSColor class]]) {
        NSColor* value = (NSColor*)v;
        if (value.colorSpaceName != NSDeviceRGBColorSpace)
            value = [value colorUsingColorSpaceName: NSDeviceRGBColorSpace];
        long red = static_cast<long>(value.redComponent * 255);
        long green = static_cast<long>(value.greenComponent * 255);
        long blue = static_cast<long>(value.blueComponent * 255);
        
        long color = (blue << 16) + (green << 8) + red;
        return color;
    }
    return -1;
}

- (void)updateStyling
{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    NSString* fontName = [defaults stringForKey: prefKeyEditorFontName];
    float fontSize = [defaults floatForKey: prefKeyEditorFontSize];
    NSFont* font = [NSFont fontWithName:fontName size:fontSize];
    if (!font) {
        fontName = @"Courier";
        fontSize = 12.0;
        font = [NSFont fontWithName:fontName size:fontSize];
        [defaults setObject:fontName forKey:prefKeyEditorFontName];
        [defaults setFloat:fontSize forKey:prefKeyEditorFontSize];
    }

    // Colors and styles for various syntactic elements. First the default style.
    [mEditor setStringProperty: SCI_STYLESETFONT parameter: STYLE_DEFAULT value: fontName];
    long sz = static_cast<long>(fontSize * 100.0f);
    [mEditor setGeneralProperty: SCI_STYLESETSIZEFRACTIONAL parameter: STYLE_DEFAULT value: sz];
    
    NSApplication* me = [NSApplication sharedApplication];
    NSAppearance* saved = nil;
    bool darkMode = false;
#ifndef __MAC_10_14
    NSString* NSAppearanceNameDarkAqua = @"foo";
#endif
    if (@available(macOS 10_14, *)) {
        saved = [NSAppearance currentAppearance];
        NSAppearance* next = [me effectiveAppearance];
        [NSAppearance setCurrentAppearance: next];
        darkMode = [[next bestMatchFromAppearancesWithNames:
                     @[NSAppearanceNameAqua, NSAppearanceNameDarkAqua]]
                        isEqualToString:NSAppearanceNameDarkAqua];
    }

    [mEditor setColorProperty: SCI_STYLESETFORE parameter: STYLE_DEFAULT value: [NSColor textColor]];
    [mEditor setColorProperty: SCI_STYLESETBACK parameter: STYLE_DEFAULT value: [NSColor textBackgroundColor]];
    [mEditor setGeneralProperty: SCI_STYLECLEARALL parameter: 0 value: 0];

    [mEditor setColorProperty:SCI_STYLESETFORE parameter:STYLE_LINENUMBER value:[NSColor textColor]];
    [mEditor setColorProperty:SCI_STYLESETBACK parameter:STYLE_LINENUMBER value:[NSColor gridColor]];
    [mEditor setColorProperty:SCI_SETSELFORE parameter:1 value:[NSColor selectedTextColor]];
    [mEditor setColorProperty:SCI_SETSELBACK parameter:1 value:[NSColor selectedTextBackgroundColor]];
    [mEditor message:SCI_SETCARETFORE wParam:MakeColor([NSColor textColor])];

    if (saved)
        [NSAppearance setCurrentAppearance: saved];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleDefault
                          value:[defaults boolForKey:PrefKeyEditorDefaultBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleDefault
                          value:[defaults boolForKey:PrefKeyEditorDefaultItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleComment
                          value:[defaults boolForKey:PrefKeyEditorCommentsBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleComment
                          value:[defaults boolForKey:PrefKeyEditorCommentsItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleSymbol
                          value:[defaults boolForKey:PrefKeyEditorSymbolsBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleSymbol
                          value:[defaults boolForKey:PrefKeyEditorSymbolsItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleIdentifier
                          value:[defaults boolForKey:PrefKeyEditorIdentifiersBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleIdentifier
                          value:[defaults boolForKey:PrefKeyEditorIdentifiersItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleKeywords
                          value:[defaults boolForKey:PrefKeyEditorKeywordsBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleKeywords
                          value:[defaults boolForKey:PrefKeyEditorKeywordsItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleBuiltins
                          value:[defaults boolForKey:PrefKeyEditorBuiltinsBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleBuiltins
                          value:[defaults boolForKey:PrefKeyEditorBuiltinsItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleString
                          value:[defaults boolForKey:PrefKeyEditorStringsBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleString
                          value:[defaults boolForKey:PrefKeyEditorStringsItalic]];
    
    [mEditor setGeneralProperty:SCI_STYLESETBOLD
                      parameter:CFscintilla::StyleNumber
                          value:[defaults boolForKey:PrefKeyEditorNumbersBold]];
    [mEditor setGeneralProperty:SCI_STYLESETITALIC
                      parameter:CFscintilla::StyleNumber
                          value:[defaults boolForKey:PrefKeyEditorNumbersItalic]];
    
    if (darkMode) {
        mFindOptionsButton.image = MagnifyingGlassDark;
        [mEditor setColorProperty:SCI_STYLESETBACK parameter:STYLE_LINENUMBER fromHTML:@"#363636"];
        [mEditor setColorProperty:SCI_STYLESETFORE parameter:STYLE_BRACELIGHT fromHTML:@"#fff"];
        [mEditor setColorProperty:SCI_STYLESETBACK parameter:STYLE_BRACELIGHT fromHTML:@"#7a7a85"];
        [mEditor setColorProperty:SCI_STYLESETFORE parameter:STYLE_BRACEBAD   fromHTML:@"#ff6969"];
        [mEditor setGeneralProperty:SCI_STYLESETBOLD parameter:STYLE_BRACEBAD value: 1];
        
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleDefault
                              value: MakeColor([defaults stringForKey:PrefKeyEditorDefaultDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleComment
                              value: MakeColor([defaults stringForKey:PrefKeyEditorCommentsDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleSymbol
                              value: MakeColor([defaults stringForKey:PrefKeyEditorSymbolsDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleIdentifier
                              value: MakeColor([defaults stringForKey:PrefKeyEditorIdentifiersDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleKeywords
                              value: MakeColor([defaults stringForKey:PrefKeyEditorKeywordsDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleBuiltins
                              value: MakeColor([defaults stringForKey:PrefKeyEditorBuiltinsDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleString
                              value: MakeColor([defaults stringForKey:PrefKeyEditorStringsDarkColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleNumber
                              value: MakeColor([defaults stringForKey:PrefKeyEditorNumbersDarkColor])];
    } else {
        mFindOptionsButton.image = MagnifyingGlassLight;
        [mEditor setColorProperty:SCI_STYLESETFORE parameter:STYLE_BRACELIGHT fromHTML:@"#8a2be2"];
        [mEditor setColorProperty:SCI_STYLESETBACK parameter:STYLE_BRACELIGHT fromHTML:@"#e6e6fa"];
        [mEditor setColorProperty:SCI_STYLESETFORE parameter:STYLE_BRACEBAD   fromHTML:@"#ff0000"];
        [mEditor setGeneralProperty: SCI_STYLESETBOLD parameter:STYLE_BRACEBAD value: 1];
        
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleDefault
                              value: MakeColor([defaults stringForKey:PrefKeyEditorDefaultColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleComment
                              value: MakeColor([defaults stringForKey:PrefKeyEditorCommentsColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleSymbol
                              value: MakeColor([defaults stringForKey:PrefKeyEditorSymbolsColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleIdentifier
                              value: MakeColor([defaults stringForKey:PrefKeyEditorIdentifiersColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleKeywords
                              value: MakeColor([defaults stringForKey:PrefKeyEditorKeywordsColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleBuiltins
                              value: MakeColor([defaults stringForKey:PrefKeyEditorBuiltinsColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleString
                              value: MakeColor([defaults stringForKey:PrefKeyEditorStringsColor])];
        [mEditor setGeneralProperty: SCI_STYLESETFORE
                          parameter: CFscintilla::StyleNumber
                              value: MakeColor([defaults stringForKey:PrefKeyEditorNumbersColor])];
    }

    NSSize size = [@"8888" sizeWithAttributes: @{NSFontAttributeName: font}];
    [mEditor setGeneralProperty: SCI_SETMARGINWIDTHN parameter: 0 value: static_cast<long>(size.width + 10.9)];
}


@end








@implementation GView (renderControl)

- (IBAction) startRender:(id)sender
{
    [self setCurrentAction: ActionType::RenderAction];
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

- (void) startHiresRender
{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float hiresWidth = [defaults floatForKey: PrefKeyHiresWidth];
    float hiresHeight = [defaults floatForKey: PrefKeyHiresHeight];
    double minSize = [defaults doubleForKey: PrefKeyMinumumSize];
    NSSize size = NSMakeSize(hiresWidth, hiresHeight);
    
    [self setCurrentAction: ActionType::Render2SizeAction];
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

- (void) startAnimation: (float) frame
{
    RenderParameters parameters;
    parameters.render = false;
    parameters.periodicUpdate = false;
    parameters.animate = true;
    parameters.animateFrame = static_cast<int>(frame);
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float movieWidth = [defaults floatForKey: PrefKeyMovieWidth];
    float movieHeight = [defaults floatForKey: PrefKeyMovieHeight];
    NSSize size = NSMakeSize(movieWidth, movieHeight);
    double minSize = [defaults doubleForKey: PrefKeyMinumumSize];
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
    
    if ((int)movieWidth & 7) {
        NSString* message =     parameters.animateFrame ?
                                @"Cannot create animation movie frame" :
                                @"Cannot create animation movie";
        NSAlert* nonono = [[[NSAlert alloc] init] autorelease];
        [nonono setAlertStyle: NSAlertStyleWarning];
        [nonono setMessageText: message];
        [nonono setInformativeText: @"Rendered width must be a multiple of 8 pixels"];
        [nonono addButtonWithTitle: @"OK"];
        [nonono beginSheetModalForWindow: [self window]
                           modalDelegate:nil
                          didEndSelector:nil
                             contextInfo:nil];
        return;
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
        [self setCurrentAction: ActionType::AnimateAction];

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
        stream.reset();  // close the temp file, we need its name
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
        [self setAnimationFrame: frame];
        [self setCurrentAction: ActionType::AnimateFrameAction];
        [self tearDownPlayer];
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


@implementation GView (frameControl)

- (void)initializeFrame
{
    mLastAnimateFrame = 1.0;
    [mFrameField setIntValue: 1];
    [mFrameStepper setIntValue: 1];
}

- (int)checkFrame:(int)frame
{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float movieLength = [defaults floatForKey: PrefKeyMovieLength];
    NSInteger movieFrameRate = [defaults integerForKey: PrefKeyMovieFrameRate];
    float animateFrameCount = movieLength * movieFrameRate * 0.01f;
    if (frame < 1) return 1;
    if (frame > animateFrameCount) return (int)animateFrameCount;
    return frame;
}

- (void)setAnimationFrame:(float)frame
{
    mLastAnimateFrame = frame;
    int f = static_cast<int>(frame);
    [mFrameStepper setIntValue: f];
    [mFrameField setIntValue: f];
}

- (float)animationFrame
{
    return mLastAnimateFrame;
}

- (IBAction)adjustFrame:(id)sender
{
    [self reuseVariation];
    int f1 = [sender intValue];
    int f2 = [self checkFrame: f1];
    if (f1 != f2)
        NSBeep();
    [mFrameField setIntValue: f2];
    [mFrameStepper setIntValue: f2];
    mLastAnimateFrame = f2;
}

@end


@implementation GView (internal)

- (void)setupEditor
{
    [mEditor setGeneralProperty: SCI_SETLEXER parameter: SCLEX_CONTAINER value: 0];
    [mEditor setGeneralProperty: SCI_SETMARGINTYPEN parameter: 0 value: SC_MARGIN_NUMBER];
    [mEditor setGeneralProperty: SCI_SETMARGINWIDTHN parameter: 1 value: 0];

    [self updateStyling];
    
    InfoBar* infoBar = [[[InfoBar alloc] initWithFrame: NSMakeRect(0, 0, 400, 0)] autorelease];
    [infoBar setDisplay: IBShowStatusText | IBShowCaretPosition];
    [mEditor setInfoBar: infoBar top: NO];
    [mEditor setStatusText: @"Operation complete"];
    [mEditor setGeneralProperty:SCI_SETSEARCHFLAGS value:SCFIND_MATCHCASE];
    [mEditor setGeneralProperty:SCI_SETUSETABS value:0];
    [mEditor setGeneralProperty:SCI_SETTABWIDTH value:CurrentTabWidth];
    [mEditor setGeneralProperty:SCI_SETINDENT value:0];
    [mEditor setGeneralProperty:SCI_SETTABINDENTS value:1];
    [mEditor setGeneralProperty:SCI_SETBACKSPACEUNINDENTS value:1];
    [mEditor setGeneralProperty:SCI_SETINDENTATIONGUIDES value:SC_IV_LOOKBOTH];
    
    [mEditor setGeneralProperty:SCI_AUTOCSETIGNORECASE value:1];
    [mEditor setReferenceProperty:SCI_AUTOCSTOPS parameter:0 value:"[]{}<>,1234567890()/*+-|=!&^ \t.\r\n"];
    [mEditor setReferenceProperty:SCI_SETWORDCHARS parameter:0 value:"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:"];
}

/**
 * Searches and marks the first occurrence of the given text and optionally scrolls it into view.
 *
 * @result FindResultFound if something was found, FindResultFoundWrapped is the
 * editor wrapped beforer finding the text, FindResultNotFound otherwise.
 */
- (FindResult) findAndHighlightText: (NSString *) searchText
                          matchCase: (BOOL) matchCase
                           findType: (FindType) findType
                           scrollTo: (BOOL) scrollTo
                               wrap: (BOOL) wrap
                          backwards: (BOOL) backwards {
    int searchFlags= 0;
    if (matchCase)
        searchFlags |= SCFIND_MATCHCASE;
    if (findType == FindWholeWord)
        searchFlags |= SCFIND_WHOLEWORD;
    if (findType == FindStartsWith)
        searchFlags |= SCFIND_WORDSTART;

    long selectionStart = [mEditor getGeneralProperty: SCI_GETSELECTIONSTART parameter: 0];
    long selectionEnd = [mEditor getGeneralProperty: SCI_GETSELECTIONEND parameter: 0];
    
    // Sets the start point for the coming search to the beginning of the current selection.
    // For forward searches we have therefore to set the selection start to the current selection end
    // for proper incremental search. This does not harm as we either get a new selection if something
    // is found or the previous selection is restored.
    if (!backwards)
        [mEditor getGeneralProperty: SCI_SETSELECTIONSTART parameter: selectionEnd];
    [mEditor setGeneralProperty: SCI_SEARCHANCHOR value: 0];
    sptr_t result;
    const char *textToSearch = searchText.UTF8String;
    bool didWrap = false;
    
    // The following call will also set the selection if something was found.
    if (backwards) {
        result = [ScintillaView directCall: mEditor
                                   message: SCI_SEARCHPREV
                                    wParam: searchFlags
                                    lParam: (sptr_t) textToSearch];
        if (result < 0 && wrap) {
            // Try again from the end of the document if nothing could be found so far and
            // wrapped search is set.
            [mEditor getGeneralProperty: SCI_SETSELECTIONSTART parameter: [mEditor getGeneralProperty: SCI_GETTEXTLENGTH parameter: 0]];
            [mEditor setGeneralProperty: SCI_SEARCHANCHOR value: 0];
            result = [ScintillaView directCall: mEditor
                                       message: SCI_SEARCHNEXT
                                        wParam: searchFlags
                                        lParam: (sptr_t) textToSearch];
            didWrap = true;
        }
    } else {
        result = [ScintillaView directCall: mEditor
                                   message: SCI_SEARCHNEXT
                                    wParam: searchFlags
                                    lParam: (sptr_t) textToSearch];
        if (result < 0 && wrap) {
            // Try again from the start of the document if nothing could be found so far and
            // wrapped search is set.
            [mEditor getGeneralProperty: SCI_SETSELECTIONSTART parameter: 0];
            [mEditor setGeneralProperty: SCI_SEARCHANCHOR value: 0];
            result = [ScintillaView directCall: mEditor
                                       message: SCI_SEARCHNEXT
                                        wParam: searchFlags
                                        lParam: (sptr_t) textToSearch];
            didWrap = true;
        }
    }
    
    if (result >= 0) {
        if (scrollTo)
            [mEditor setGeneralProperty: SCI_SCROLLCARET value: 0];
    } else {
        // Restore the former selection if we did not find anything.
        [mEditor setGeneralProperty: SCI_SETSELECTIONSTART value: selectionStart];
        [mEditor setGeneralProperty: SCI_SETSELECTIONEND value: selectionEnd];
    }
    return (result < 0) ? FindResultNotFound : (didWrap ? FindResultFoundWrapped
                                                : FindResultFound);
}



/**
 * Searches the given text and replaces
 *
 * @result Number of entries replaced, 0 if none.
 */
- (int) findAndReplaceText: (NSString *) searchText
                    byText: (NSString *) newText
                 matchCase: (BOOL) matchCase
                  findType: (FindType) findType
                     doAll: (BOOL) doAll
               inSelection: (BOOL) inSelection {
    // The current position is where we start searching for single occurrences. Otherwise we start at
    // the beginning of the document.
    long startPosition;
    if (doAll && !inSelection)
        startPosition = 0; // Start at the beginning of the text if we replace all occurrences.
    else
        // For a single replacement we start at the current caret position.
        startPosition = [mEditor getGeneralProperty: SCI_GETCURRENTPOS];
    long endPosition;
    if (doAll && inSelection)
        endPosition = [mEditor getGeneralProperty: SCI_GETANCHOR];
    else
        endPosition = [mEditor getGeneralProperty: SCI_GETTEXTLENGTH];
    
    if (doAll && endPosition < startPosition)
        std::swap(startPosition, endPosition);
    if (doAll && endPosition == startPosition)
        return 0;

    int searchFlags= 0;
    if (matchCase)
        searchFlags |= SCFIND_MATCHCASE;
    if (findType == FindWholeWord)
        searchFlags |= SCFIND_WHOLEWORD;
    if (findType == FindStartsWith)
        searchFlags |= SCFIND_WORDSTART;
    [mEditor setGeneralProperty: SCI_SETSEARCHFLAGS value: searchFlags];
    [mEditor setGeneralProperty: SCI_SETTARGETSTART value: startPosition];
    [mEditor setGeneralProperty: SCI_SETTARGETEND value: endPosition];
    
    const char *textToSearch = searchText.UTF8String;
    long sourceLength = std::strlen(textToSearch); // Length in bytes.
    const char *replacement = newText.UTF8String;
    long targetLength = std::strlen(replacement);  // Length in bytes.
    sptr_t result;
    
    int replaceCount = 0;
    if (doAll) {
        bool replaced = false;
        while (true) {
            result = [ScintillaView directCall: mEditor
                                       message: SCI_SEARCHINTARGET
                                        wParam: sourceLength
                                        lParam: (sptr_t) textToSearch];
            if (result < 0)
                break;

            if (!replaced)
                [ScintillaView directCall: mEditor
                                  message: SCI_BEGINUNDOACTION
                                   wParam: 0
                                   lParam: 0];
            replaced = true;
            
            replaceCount++;
            [ScintillaView directCall: mEditor
                              message: SCI_REPLACETARGET
                               wParam: targetLength
                               lParam: (sptr_t) replacement];
            
            if (inSelection)
                endPosition += targetLength - sourceLength;
            else
                endPosition = [mEditor getGeneralProperty: SCI_GETTEXTLENGTH];

            // The replacement changes the target range to the replaced text. Continue after that till the end.
            // The text length might be changed by the replacement so make sure the target end is the actual
            // text end.
            [mEditor setGeneralProperty: SCI_SETTARGETSTART value: [mEditor getGeneralProperty: SCI_GETTARGETEND]];
            [mEditor setGeneralProperty: SCI_SETTARGETEND value: endPosition];
        }
        if (replaced)
            [ScintillaView directCall: mEditor
                              message: SCI_ENDUNDOACTION
                               wParam: 0
                               lParam: 0];
    } else {
        result = [ScintillaView directCall: mEditor
                                   message: SCI_SEARCHINTARGET
                                    wParam: sourceLength
                                    lParam: (sptr_t) textToSearch];
        replaceCount = (result < 0) ? 0 : 1;
        
        if (replaceCount > 0) {
            [ScintillaView directCall: mEditor
                              message: SCI_REPLACETARGET
                               wParam: targetLength
                               lParam: (sptr_t) replacement];
            
            // For a single replace we set the new selection to the replaced text.
            [mEditor setGeneralProperty: SCI_SETSELECTIONSTART value: [mEditor getGeneralProperty: SCI_GETTARGETSTART]];
            [mEditor setGeneralProperty: SCI_SETSELECTIONEND value: [mEditor getGeneralProperty: SCI_GETTARGETEND]];
        }
    }
    
    return replaceCount;
}


- (BOOL)findNext:(BOOL)reversed
{
    NSString* text = [mFindText stringValue];
    if ([text length] == 0) {
        [mEditor setStatusText:@"No search text set"];
        NSBeep();
        return NO;
    }
    
    auto found = [self findAndHighlightText:text
                                  matchCase:mMatchCase
                                   findType:mFindType
                                   scrollTo:YES
                                       wrap:mWrapSearch
                                  backwards:reversed];
    
    switch (found) {
        case FindResultNotFound:
            [mEditor setStatusText: @"Text not found"];
            NSBeep();
            break;
        case FindResultFound:
            [mEditor setStatusText: @""];
            break;
        case FindResultFoundWrapped: {
            auto anime = [mRewindView animator];    // 0.25sec animation
            [anime setAlphaValue:1.0];
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 500 * NSEC_PER_MSEC), dispatch_get_main_queue(), ^{
                [anime setAlphaValue:0.0];
            });
            if (reversed)
                [mEditor setStatusText: @"The search wrapped to the end"];
            else
                [mEditor setStatusText: @"The search wrapped to the start"];
            break;
        }
    }
    
    return found != FindResultNotFound;
}


- (void)replaceNext
{
    NSString* text = [mFindText stringValue];
    NSString* replaceText = [mReplaceText stringValue];
    if ([text length] == 0) {
        [mEditor setStatusText:@"No search text set"];
        NSBeep();
        return;
    }
    
    int cnt = [self findAndReplaceText:text
                                byText:replaceText
                             matchCase:mMatchCase
                              findType:mFindType
                                 doAll:NO
                           inSelection:NO];
    if (cnt == 0) {
        [mEditor setStatusText: @"Text not found"];
        NSBeep();
        return;
    }
    [mEditor setStatusText: @"Replaced"];

    [self findNext:NO];
}

- (void)replaceAll: (BOOL)inSelection
{
    NSString* text = [mFindText stringValue];
    NSString* replaceText = [mReplaceText stringValue];
    if ([text length] == 0) {
        [mEditor setStatusText:@"No search text set"];
        NSBeep();
        return;
    }
    
    bool canUndo = [mEditor getGeneralProperty:SCI_CANUNDO];
    int cnt = [self findAndReplaceText:text
                                byText:replaceText
                             matchCase:mMatchCase
                              findType:mFindType
                                 doAll:YES
                           inSelection:inSelection];
    canUndo = [mEditor getGeneralProperty:SCI_CANUNDO];

    switch (cnt) {
        case 0:
            [mEditor setStatusText: @"Text not found"];
            NSBeep();
            break;
        case 1:
            [mEditor setStatusText:@"1 replacement"];
            break;
        default:
            [mEditor setStatusText: [NSString stringWithFormat:@"%d replacements", cnt]];
    }
}

- (void)checkAutoC
{
    long pos = [mEditor getGeneralProperty:SCI_GETCURRENTPOS];
    long wordPos = [mEditor getGeneralProperty:SCI_WORDSTARTPOSITION
                                     parameter:pos
                                         extra:1];
    long len = pos - wordPos;
    if (len > 1) {
        std::string list; list.reserve(1500);
        std::string word(len, ' ');
        Sci_TextRange r{{wordPos, pos}, word.data()};
        [mEditor getGeneralProperty:SCI_GETTEXTRANGE
                                ref:(const void*)(&r)];
        auto iter = std::lower_bound(CFscintilla::AutoComplete.begin(),
                                     CFscintilla::AutoComplete.end(),
                                     word.c_str(), CFscintilla::AutoCmp());
        while (iter != CFscintilla::AutoComplete.end() &&
               strncasecmp(*iter, word.c_str(), len) == 0)
        {
            if (!list.empty()) list.append(1, ' ');
            list.append(*iter);
            ++iter;
        }
        if (!list.empty()) {
            [mEditor setReferenceProperty:SCI_AUTOCSHOW
                                parameter:len
                                    value:list.c_str()];
            return;
        }
    }
    if ([mEditor getGeneralProperty:SCI_AUTOCACTIVE])
        [mEditor setGeneralProperty:SCI_AUTOCCANCEL value:0];
}

- (void) setMovieImagesPlay:(BOOL)play
{
    bool dark = false;
#ifndef __MAC_10_14
    NSString* NSAppearanceNameDarkAqua = @"foo";
#endif
    if (@available(macOS 10_14, *)) {
        NSAppearance* next = [[NSApplication sharedApplication] effectiveAppearance];
        dark = [[next bestMatchFromAppearancesWithNames:
                 @[NSAppearanceNameAqua, NSAppearanceNameDarkAqua]]
                isEqualToString:NSAppearanceNameDarkAqua];
    }

    if (play) {
        mStartStopButton.image = dark ? PausePressImage : PauseNormalImage;
        mStartStopButton.alternateImage = dark ? PauseNormalImage : PausePressImage;
    } else {
        mStartStopButton.image = dark ? PlayPressImage : PlayNormalImage;
        mStartStopButton.alternateImage = dark ? PlayPressImage : PlayNormalImage;
    }
    mRewindButton.image = dark ? RewindPressImage : RewindNormalImage;
    mRewindButton.alternateImage = dark ? RewindNormalImage : RewindPressImage;
}

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
    
    for (box.origin.y = std::floor(NSMinY(rect) / box.size.height) * box.size.height;
        box.origin.y < NSMaxY(rect);
        box.origin.y += box.size.height)
    {
        for (box.origin.x = 
                (std::floor(NSMinX(rect) / (2.0 * box.size.width)) * 2.0
                 + std::fmod(box.origin.y / box.size.height, 2.0))
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
    mRenderer = mEngine->renderer(mEngine,
        (int)size.width, (int)size.height,
        minSize,
        mCurrentVariation,
        [[NSUserDefaults standardUserDefaults] floatForKey: @"BorderSize"]);
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

- (void)setCurrentAction:(ActionType)newAction
{
    bool notframe = newAction != ActionType::AnimateFrameAction;
    bool notHires = newAction != ActionType::Render2SizeAction;
    [mFrameLabel setHidden: (notframe && notHires)];
    [mFrameField setHidden: notframe];
    [mFrameStepper setHidden: notframe];
    [mRenderWidth setHidden: notHires];
    [mRenderHeight setHidden: notHires];
    [mRenderX setHidden: notHires];
    [mFrameLabel setStringValue: (notframe ? @"Size:" : @"Frame:")];
    mCurrentAction = newAction;
    [mActionControl setLabel: ActionStrings[newAction]
                  forSegment: 0];
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
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    mCurrentTime.doubleValue = [defaults floatForKey: PrefKeyMovieLength];
    NSCell *cell = [[[NSCell alloc]initTextCell: [mCurrentTime stringValue]] autorelease];
    CGFloat sz = [cell cellSize].width + 20.0;
    NSRect rect = [mCurrentTime frame];
    rect.origin.x -= (sz - rect.size.width) / 2.0;
    rect.size.width = sz;
    [mCurrentTime setFrame: rect];
    mCurrentTime.doubleValue = 0.0;
    
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
                                                                           [self setMovieImagesPlay: NO];
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
        [self setMovieImagesPlay: NO];
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

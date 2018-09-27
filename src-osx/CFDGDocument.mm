// CFDGDocument.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2008-2013 John Horigan - john@glyphic.com
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

#import "CFDGDocument.h"
#import "GView.h"
#import "GalleryUploader.h"

#include <fstream>
#include <sstream>

#include "cfdg.h"
#include "posixSystem.h"
#include "location.hh"

#include "variation.h"

@interface CfdgErrorWrapper : NSObject
{
@private
    yy::location mLocation;
    NSString* mMessage;
    NSString* mFile;
}

-(id)initWithError: (const CfdgError*) err;
-(NSString*)message;
-(NSString*)path;
-(yy::location*)location;

@end


NSString* PrefKeyMovieWidth = @"MovieWidth";
NSString* PrefKeyMovieHeight = @"MovieHeight";
NSString* PrefKeyMinumumSize = @"HiresMinimumSize";
NSString* PrefKeyHiresWidth = @"HiresWidth";
NSString* PrefKeyHiresHeight = @"HiresHeight";

extern NSInteger CurrentTabWidth;

namespace {
    
    class CocoaSystem : public PosixSystem
    {
    public:
        CocoaSystem(CFDGDocument* doc) : mDoc(doc) { }
        
        void message(const char* fmt, ...) override;
        void syntaxError(const CfdgError& err) override;
        void catastrophicError(const char* what) override;
        
        istr_ptr openFileForRead(const std::string& path) override;
        const FileChar* tempFileDirectory() override;
        std::string relativeFilePath(const std::string& base, const std::string& rel) override;
        
        void stats(const Stats& s) override;
        
        void orphan() override;
        
    private:
        CFDGDocument* mDoc;
        
        CFDGDocument* findDocFor(const std::string& path);
    };
    
    CFDGDocument*
    CocoaSystem::findDocFor(const std::string& path)
    {
        if (path.empty())
            return mDoc;

        NSString* pathStr =
            [NSString stringWithUTF8String: path.c_str() ];
        
        NSURL* pathURL = [NSURL fileURLWithPath: pathStr];
            
        return [[NSDocumentController sharedDocumentController]
                    documentForURL: pathURL];
    }
    
    
    void
    CocoaSystem::message(const char* fmt, ...)
    {
        if (!mDoc) return;
        char buf[256];
        {
            va_list args;
            va_start(args, fmt);
            vsnprintf(buf, sizeof(buf), fmt, args);
            buf[sizeof(buf)-1] = '\0';
            va_end(args);
        }
        
        [mDoc performSelectorOnMainThread: @selector(noteStatus:)
            withObject: [NSString stringWithUTF8String: buf]
            waitUntilDone: NO];
    }

    void
    CocoaSystem::stats(const Stats& s)
    {
        if (!mDoc) return;
        NSValue* value = [NSValue value: &s withObjCType: @encode(Stats)];
        
        [mDoc performSelectorOnMainThread: @selector(noteStats:)
            withObject: value waitUntilDone: NO];
    }
    
    
    void 
    CocoaSystem::syntaxError(const CfdgError& err)
    {
        if (!mDoc) return;
        
        CfdgErrorWrapper* objcerr = [[[CfdgErrorWrapper alloc] initWithError: &err]
                                     autorelease];
        
        [mDoc performSelectorOnMainThread: @selector(noteError:)
                               withObject: objcerr
                            waitUntilDone: NO];
    }
            
    void
    CocoaSystem::catastrophicError(const char* what)
    {
        [mDoc performSelectorOnMainThread: @selector(noteCatastrophicError:)
                               withObject: [NSString stringWithUTF8String: what]
                            waitUntilDone: YES];
    }
    
    AbstractSystem::istr_ptr
    CocoaSystem::openFileForRead(const std::string& path)
    {
        CFDGDocument* doc = findDocFor(path);
                
        if (doc) {
            NSData* data = [doc getContent];
            std::string s{reinterpret_cast<const char*>([data bytes]), [data length]};
            return std::make_unique<std::istringstream>(s);
        }

        return std::make_unique<std::ifstream>(path.c_str(), std::ios::in);
    }
    
    const AbstractSystem::FileChar*
    CocoaSystem::tempFileDirectory()
    {
        return [NSTemporaryDirectory() UTF8String];
    }
    
    std::string
    CocoaSystem::relativeFilePath(const std::string& base, const std::string& rel)
    {
        NSString* baseStr =
            [NSString stringWithUTF8String: base.c_str()];
        NSString* relStr =
            [NSString stringWithUTF8String: rel.c_str()];
        
        NSString* newStr =
            [[baseStr stringByDeletingLastPathComponent]
                stringByAppendingPathComponent: relStr];
        
        NSString* exStr = cfdgVersion == 2 ? [[relStr stringByDeletingPathExtension] stringByAppendingString:@"_v2.cfdg"]
                                           : relStr;

        NSFileManager* fm = [NSFileManager defaultManager];
        NSString* libStr =[[[[NSBundle mainBundle] resourcePath]
                            stringByAppendingPathComponent: @"Examples"]
                           stringByAppendingPathComponent: exStr];
        if ([fm fileExistsAtPath: libStr])
            newStr = libStr;
        
        return std::string([newStr UTF8String]);
    }
    
    void
    CocoaSystem::orphan()
    { mDoc = nil; }
};

@implementation CfdgErrorWrapper

-(id)initWithError: (const CfdgError*) err 
{
    self = [super init];
    if (self) {
        mLocation = err->where;
        mMessage = [[NSString stringWithUTF8String: err->what()] retain];
        if (mLocation.begin.filename && mLocation.begin.filename->length()) {
            mFile = [[NSString stringWithUTF8String: mLocation.begin.filename->c_str()] retain];
            mLocation.begin.filename = mLocation.end.filename = nullptr;
        }
    }
    return self;
}

- (void)dealloc
{
    [mMessage release];     mMessage = nil;
    [mFile release];        mFile = nil; mLocation.begin.filename = mLocation.end.filename = nullptr;
    [super dealloc];
}

-(NSString*)message
{
    return mMessage;
}

-(NSString*)path
{
    return mFile;
}
    
-(yy::location*)location
{
    return &mLocation;
}

@end



NSString* CFDGDocumentType = @"ContextFree Design Grammar";

@implementation CFDGDocument

+ (NSString*) documentType
{
    return CFDGDocumentType;
}

+ (BOOL)autosavesInPlace
{
    return NO;
}

+ (NSArray*) checkForTempFiles
{
    NSMutableArray* files = nil;
    
    CocoaSystem sys(nil);
    auto temps = sys.findTempFiles();
    if (!temps.empty())
        files = [NSMutableArray arrayWithCapacity: temps.size()];

    for (auto&& temp: temps)
        [files addObject: [NSString stringWithUTF8String: temp.c_str()]];
    
    return files;
}

- (id)init
{
    self = [super init];
    if (self) {
        mSystem = new CocoaSystem(self);
        mContent = nil;
        mUploader = nil;
        mDisplayName = nil;
        mEditor = nil;
    }
    return self;
}

- (void)dealloc
{
    //delete mSystem;     mSystem = 0;
    mSystem->orphan();                      // leave system orphaned on the heap
    [mContent release]; mContent = nil;
    [mUploader release]; mUploader = nil;
    [mEditor release]; mEditor = nil;
    [super dealloc];
}

- (NSString *)windowNibName {
    return @"CFDGDocument";
}

- (void)showWindows
{
    [super showWindows];

    if ([[mEditor string] length] == 0)
        return;
        
    BOOL render = [[NSUserDefaults standardUserDefaults]
                        boolForKey: @"RenderOnDocumentOpen"];
    if (render)
        [self startRender: self];
}

- (void)close
{
    mGView = nil;
    [self stopRender: self];
    [super close];
}

- (cfdg_ptr)buildEngine
{
    [[[mStatusText textStorage] mutableString] setString: @""];
    
    const char* fileName = [[[self fileURL] path] UTF8String];
    if (!fileName) fileName = "";
    
    static NSLock* parseLock = [[NSLock alloc] init];
    
    cfdg_ptr result;
    if ([parseLock lockBeforeDate: [NSDate dateWithTimeIntervalSinceNow: 2.0]]) {
        result = CFDG::ParseFile(fileName, mSystem, [mGView variation]);
        [parseLock unlock];
    }
    return result;
}

- (AbstractSystem*)system
{
    return mSystem;
}

- (void)noteStatus:(NSString*)s
{
    if (mStatusText != nil) {
        [[[mStatusText textStorage] mutableString] appendString: s];
        [[[mStatusText textStorage] mutableString] appendString: @"\n"];
        // scroll to the end
        NSRange range = NSMakeRange ([[mStatusText string] length], 0);
        [mStatusText scrollRangeToVisible: range];
    }
}

- (void)noteStats:(NSValue*)v
{
    if (mGView != nil) {
        [mGView noteStats: v];
    }
}

- (void) setVariation:(int)var
{
    if (mGView)
        [mGView setVariation: var];
}

- (void)noteCatastrophicError:(NSString*)s
{
    (void)NSRunAlertPanel(@"A major error has occured", @"Error: %@", nil, nil, nil, s);
}

- (void)noteError:(CfdgErrorWrapper*)e
{
    NSMutableAttributedString* msg = [[[NSMutableAttributedString alloc] 
                                       initWithString: @"Parse error - "] 
                                      autorelease];
    NSUInteger start = [msg length];
    [[msg mutableString] appendString: [e message]];
    [[msg mutableString] appendString: @"\n"];
    
    if (mStatusText != nil) {
        NSString* errorPath = [e path];
        
        [msg beginEditing];
        NSURL* myURL = [self fileURL];
        if ((errorPath == nil && myURL == nil) ||
            ([[myURL path] isEqual: errorPath]))
        {
            NSRange r = NSMakeRange(start, [msg length] - (start + 1));
            
            [msg addAttribute: NSLinkAttributeName value: e range: r];
            
            // make the text appear in blue
            [msg addAttribute: NSForegroundColorAttributeName value: [NSColor blueColor] range: r];
            
            // next make the text appear with an underline
            [msg addAttribute:
             NSUnderlineStyleAttributeName value:[NSNumber numberWithInt: NSSingleUnderlineStyle] 
                        range:r];
        }
        [msg endEditing];
        
        [[mStatusText textStorage] appendAttributedString: msg];
        // scroll to the end
        NSRange range = NSMakeRange ([[mStatusText string] length], 0);
        [mStatusText scrollRangeToVisible: range];
    }
}

- (void)highlightChars:(CfdgErrorWrapper*)link
{
    yy::location* errLoc = [link location];
    auto b = [mEditor getGeneralProperty:SCI_POSITIONFROMLINE parameter:(errLoc->begin.line - 1)] +
             errLoc->begin.column;
    auto e = [mEditor getGeneralProperty:SCI_POSITIONFROMLINE parameter:(errLoc->end.line - 1)] +
             errLoc->end.column;
    [mEditor setGeneralProperty:SCI_SETSEL parameter:b value:e];
    [[mGView window] makeFirstResponder: [mEditor content]];
}

- (void)updateFont:(NSString*)name size:(float)sz
{
    // Colors and styles for various syntactic elements. First the default style.
    long isz = static_cast<long>(sz * 100.0f);
    [mEditor setStringProperty: SCI_STYLESETFONT parameter: STYLE_DEFAULT value: name];
    [mEditor setGeneralProperty: SCI_STYLESETSIZEFRACTIONAL parameter: STYLE_DEFAULT value: isz];
    for (int i = SCE_C_DEFAULT; i <= SCE_C_ESCAPESEQUENCE; ++i) {
        [mEditor setStringProperty: SCI_STYLESETFONT parameter: i value: name];
        [mEditor setGeneralProperty: SCI_STYLESETSIZEFRACTIONAL parameter: i value: isz];
    }
}

- (void)tabWidthDidChange:(NSInteger)tab
{
    [mEditor setGeneralProperty:SCI_SETTABWIDTH value:tab];
}

- (NSData *)dataOfType:(NSString *)type error:(NSError * _Nullable *)outError
{
    if (![type isEqualToString: CFDGDocumentType]) {
        *outError = [NSError errorWithDomain:NSOSStatusErrorDomain
                                        code:unimpErr
                                    userInfo:NULL];
        return nil;
    }

    return [self getContent];
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)type error:(NSError * _Nullable *)outError
{
    if (![type isEqualToString: CFDGDocumentType]) {
        *outError = [NSError errorWithDomain:NSOSStatusErrorDomain
                                        code:unimpErr
                                    userInfo:NULL];
        return NO;
    }

    [mContent release];
    mContent = [data retain];
    [self showContent];
    [self setDirty:NO];

    return YES;
}

-(void)saveDocument:sender
{
    [self saveDocumentWithDelegate:self
                   didSaveSelector:@selector(didSaveDocument:didSave:contextInfo:)
                       contextInfo:NULL];
}

-(void)saveDocumentAs:sender
{
    [self runModalSavePanelForSaveOperation:NSSaveAsOperation
                                   delegate:self
                            didSaveSelector:@selector(didSaveDocument:didSave:contextInfo:)
                                contextInfo:NULL];
}

- (void)didSaveDocument:(NSDocument *)doc didSave:(BOOL)didSave contextInfo:(void  *)contextInfo
{
    if (didSave)
        [mEditor getGeneralProperty:SCI_SETSAVEPOINT];
}

- (void)windowControllerDidLoadNib:(NSWindowController *)windowController
{
    [self showContent];
    [self setDirty:NO];
    [mStatusText setEditable: NO];
    mGViewSplit.autosaveName = @"CFDG view splitter";
    mEditorSplit.autosaveName = @"CFDG editor splitter";
}

- (BOOL)textView:(NSTextView *)aTextView clickedOnLink:(id)link atIndex:(NSUInteger)charIndex
{
    [self highlightChars: (CfdgErrorWrapper*) link];
    return YES;
}

- (IBAction)toggleRenderView:(id)sender
{
}

- (IBAction) closeAll:(id)sender
{
    [[NSDocumentController sharedDocumentController] 
        closeAllDocumentsWithDelegate: nil 
                  didCloseAllSelector: @selector(toggleRenderView:) 
                          contextInfo: (void*)0];
}

- (IBAction) enterFullscreen:(id)sender { [mGView enterFullscreen: sender]; }
- (IBAction) startRender:(id)sender { [mGView startRender: sender]; }
- (IBAction) finishRender:(id)sender{ [mGView finishRender: sender]; }
- (IBAction) stopRender:(id)sender  { [mGView stopRender: sender]; }
- (IBAction) saveAsSVG:(id)sender   { [mGView saveAsSVG: sender]; }

- (IBAction) insertUnicode:(id)sender
{
    NSMenuItem* menu = (NSMenuItem*)sender;
    unichar codePoint = (unichar)([menu tag]);
    if (codePoint) {
        NSString* unistring = [NSString stringWithCharacters:&codePoint length:1];
        [mEditor insertText: unistring];
    } else {
        [mEditor insertText: [menu title]];
    }
}

- (IBAction)shiftLeftRight:(id)sender
{
    NSInteger delta = [sender tag] * CurrentTabWidth;
    bool didChange = false;
    long start = [mEditor getGeneralProperty:SCI_GETANCHOR];
    long end = [mEditor getGeneralProperty:SCI_GETCURRENTPOS];
    start = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION parameter:start];
    end = [mEditor getGeneralProperty:SCI_LINEFROMPOSITION parameter:end];
    if (end < start) {
        long t = start; start = end; end = t;
    }
    for (; start <= end; ++start) {
        long i = [mEditor getGeneralProperty:SCI_GETLINEINDENTATION parameter:start];
        long i2 = i + delta;
        if (i2 < 0) i2 = 0;
        if (i != i2) {
            if (!didChange)
                [mEditor getGeneralProperty:SCI_BEGINUNDOACTION];
            didChange = true;
            [mEditor setGeneralProperty:SCI_SETLINEINDENTATION parameter:start value:i2];
        }
    }
    if (didChange)
        [mEditor getGeneralProperty:SCI_ENDUNDOACTION];
}


- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)anItem
{
    SEL action = [anItem action];
    
    if (action == @selector(enterFullscreen:))
        return YES;
   
    if (action == @selector(startRender:)
    ||  action == @selector(finishRender:)
    ||  action == @selector(stopRender:)
    ||  action == @selector(saveAsSVG:)
    ||  action == @selector(showHiresRenderSheet:)
    ||  action == @selector(showAnimationFrameSheet:)
    ||  action == @selector(showAnimationSheet:)
    ||  action == @selector(uploadToGallery:))
    {
        return [mGView validateUserInterfaceItem: anItem];
    }
    
    return [super validateUserInterfaceItem: anItem];
}

- (IBAction) showHiresRenderSheet:(id)sender
{
    [NSApp beginSheet: mHiresSheet
        modalForWindow: [(NSWindowController*)[[self windowControllers] lastObject] window]
        modalDelegate: nil didEndSelector: nil contextInfo: nil];
}

- (IBAction) startHiresRender:(id)sender
{
    if (![mHiresSheet makeFirstResponder: nil])
    return;

    [mGView startHiresRender];
    [self cancelHiresRender:sender];
}

- (IBAction) cancelHiresRender:(id)sender
{
    [NSApp endSheet: mHiresSheet];
    [mHiresSheet orderOut: sender];
}

- (IBAction) showAnimateSheet:(id)sender
{
    [mSheetLabel setStringValue: @"Start Animation"];
    [mFrameLabel setHidden: YES];
    [mAnimationFrame setHidden: YES];
    [mCodecLabel setHidden: NO];
    [mAnimationCodec setHidden: NO];
    [NSApp beginSheet: mAnimateSheet
       modalForWindow: [(NSWindowController*)[[self windowControllers] lastObject] window]
        modalDelegate: nil didEndSelector: nil contextInfo: nil];
}

- (IBAction) showAnimateFrameSheet:(id)sender
{
    [mSheetLabel setStringValue: @"Animate a Frame"];
    [mFrameLabel setHidden: NO];
    [mAnimationFrame setHidden: NO];
    [mCodecLabel setHidden: YES];
    [mAnimationCodec setHidden: YES];
    [mAnimationFrame setIntValue: static_cast<int>([mGView animationFrame])];
    [NSApp beginSheet: mAnimateSheet
       modalForWindow: [(NSWindowController*)[[self windowControllers] lastObject] window]
        modalDelegate: nil didEndSelector: nil contextInfo: nil];
}

- (IBAction) startAnimation:(id)sender
{
    if (![mAnimateSheet makeFirstResponder: nil])
        return;
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float movieWidth = [defaults floatForKey: PrefKeyMovieWidth];
    float movieFrame =  1.0;
    NSString* message = nil;
    NSString* problem = nil;
    if (![mAnimationFrame isHidden]) {
        // If animating a frame then check if frame is legal
        float intpart;
        float movieLength = [defaults floatForKey: PrefKeyMovieLength];
        NSInteger movieFrameRate = [defaults integerForKey: PrefKeyMovieFrameRate];
        float animateFrameCount = movieLength * movieFrameRate * 0.01f;
        movieFrame = [mAnimationFrame floatValue];
        if (movieFrame < 1.0 || modff(movieFrame, &intpart) != 0.0)
            problem = @"Frame must be a positive integer";
        if (movieFrame > animateFrameCount)
            problem = @"Specified frame is after the end of the movie";
        message = @"Cannot create animation movie frame";
    } else {
        message = @"Cannot create animation movie";
    }
    
    if ((int)movieWidth & 7) {
        if (problem)
            problem = [NSString stringWithFormat: @"%@, also the rendered width must be a multiple of 8 pixels", problem];
        else
            problem = @"Rendered width must be a multiple of 8 pixels";
    }
    
    if (problem) {
        NSAlert* nonono = [[[NSAlert alloc] init] autorelease];
        [nonono setAlertStyle: NSAlertStyleWarning];
        [nonono setMessageText: message];
        [nonono setInformativeText: problem];
        [nonono addButtonWithTitle: @"OK"];
        [nonono beginSheetModalForWindow: mAnimateSheet
                           modalDelegate:nil
                          didEndSelector:nil
                             contextInfo:nil];
        return;
    }

    
    [mGView startAnimation: movieFrame];
    [self cancelAnimation:sender];
}

- (IBAction) cancelAnimation:(id)sender
{
    [NSApp endSheet: mAnimateSheet];
    [mAnimateSheet orderOut: sender];
}

- (IBAction) uploadToGallery:(id)sender
{
    if (!mUploader) {
        mUploader= [[GalleryUploader alloc]
                    initForDocument: self andView: mGView];
    }
    [mUploader show: self];
}

- (void)setEditor:(ScintillaView*)editor
{
    [mEditor release];
    mEditor = [editor retain];
}

- (void)showContent
{
    if (mEditor) {
        [mGView suspendNotifications:YES];
        if (mContent) {
            NSMutableData* m = [mContent mutableCopy];
            ++m.length;     // Add null termination
            [mEditor setReferenceProperty:SCI_SETTEXT parameter:0 value:(const void*)[m bytes]];
            --m.length;     // restore
        } else {
            [mEditor getGeneralProperty:SCI_CLEARALL];
        }
        [mGView suspendNotifications:NO];
        [mEditor setGeneralProperty:SCI_EMPTYUNDOBUFFER value:0];
        [mEditor setGeneralProperty:SCI_GOTOPOS value:0];
    }
}

- (NSData*)getContent
{
    if (mContent) return mContent;

    long length = [mEditor getGeneralProperty:SCI_GETLENGTH];
    
    if (length == 0) {
        mContent = [[NSData data] retain];
    } else {
        try {
            NSMutableData* data = [NSMutableData dataWithLength: length + 1];
            [mEditor setReferenceProperty:SCI_GETTEXT
                                parameter:length + 1
                                    value:(void*)[data mutableBytes]];
            --data.length;                      // chop off terminal '\0'
            mContent = [data retain];
        } catch (...) {
            mContent = [[NSData data] retain];
        }
    }

    return mContent;
}


- (void)readFromExample:(NSString*)path
{
    [self readDesign: [[path lastPathComponent] stringByDeletingPathExtension]
            cfdgText: [NSData dataWithContentsOfFile: path]];
}

- (void)readDesign:(NSString*)name cfdgText:(NSData*)cfdg
{
    [self readFromData: cfdg ofType: CFDGDocumentType error: nil];
    
    if (name) {
        [mDisplayName release];
        mDisplayName = [name retain];
    }
}

- (NSString*)displayName
{
    if (mDisplayName) return mDisplayName;
    return [super displayName];
}

- (void)setFileURL:(NSURL *)absoluteURL
{
    [mDisplayName release];
    mDisplayName = nil;
    [super setFileURL: absoluteURL];
}


- (void)textDidChange:(NSNotification *)notification
{
    [self stopRender: self];
    [mGView reuseVariation];
    [mContent release]; mContent = nil;
}

- (void)setDirty:(BOOL)dirty
{
    NSString* title = [self displayName];
    if (dirty)
        title = [title stringByAppendingString:@" — Edited"];
    for (NSWindowController* ctrl in [self windowControllers]) {
        [ctrl setDocumentEdited:dirty];
        [[ctrl window] setDocumentEdited:dirty];
        [[ctrl window] setTitle: title];
    }
}

- (BOOL)isDocumentEdited {
    if (mEditor)
        return [mEditor getGeneralProperty:SCI_GETMODIFY];
    else
        return NO;
}

- (void)canCloseDocumentWithDelegate:(id)delegate shouldCloseSelector:(SEL)shouldCloseSelector contextInfo:(void *)contextInfo
{
    BOOL OKToClose = YES;
    if ([self isDocumentEdited]) {
        NSString* fileName = [[self fileURL] lastPathComponent];
        if (fileName == nil)
            fileName = [self displayName];
        NSInteger result = NSRunAlertPanel([[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"],
                                     @"The %@ file has changed. \n\nDo you want to save the changes?",
                                     @"Yes", @"No", @"Cancel",
                                     fileName);
        switch (result) {
            case NSAlertDefaultReturn:
                [self saveDocumentWithDelegate:delegate
                               didSaveSelector:shouldCloseSelector
                                   contextInfo:contextInfo];
                return;
            case NSAlertAlternateReturn:
                break;  // OKToClose = YES;
            default:
                OKToClose = NO;
                break;
        }
    }
    if ([delegate respondsToSelector:shouldCloseSelector]) {
        void (*delegateMethod)(id, SEL, id, BOOL, void *);
        delegateMethod = (void (*)(id, SEL, id, BOOL, void *))[delegate methodForSelector:shouldCloseSelector];
        delegateMethod(delegate, shouldCloseSelector, self, OKToClose, contextInfo);
    }

}

@end


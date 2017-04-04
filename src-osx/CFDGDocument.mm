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


namespace {
    using namespace std;
    
    NSString* PrefKeyMovieWidth = @"MovieWidth";
    NSString* PrefKeyMovieHeight = @"MovieHeight";
    NSString* PrefKeyHiresWidth = @"HiresWidth";
    NSString* PrefKeyHiresHeight = @"HiresHeight";
    NSString* PrefKeyMinumumSize = @"HiresMinimumSize";
    
    class CocoaSystem : public PosixSystem
    {
    public:
        CocoaSystem(CFDGDocument* doc) : mDoc(doc) { }
        
        void message(const char* fmt, ...) override;
        void syntaxError(const CfdgError& err) override;
        void catastrophicError(const char* what) override;
        
        istream* openFileForRead(const string& path) override;
        const char* tempFileDirectory() override;
        string relativeFilePath(const string& base, const string& rel) override;
        
        void stats(const Stats& s) override;
        
        void orphan() override;
        
    private:
        CFDGDocument* mDoc;
        
        CFDGDocument* findDocFor(const string& path);
    };
    
    CFDGDocument*
    CocoaSystem::findDocFor(const string& path)
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
    
    istream*
    CocoaSystem::openFileForRead(const string& path)
    {
        CFDGDocument* doc = findDocFor(path);
                
        if (doc) {
            NSData* data = [doc getContent];
            basic_stringstream<char>* s = new stringstream;
            s->write(reinterpret_cast<const char*>([data bytes]), [data length]);
            s->seekp(0, ios::beg);
            return s;
        }

        return new ifstream(path.c_str(), ios::in);
    }
    
    const char*
    CocoaSystem::tempFileDirectory()
    {
        return [NSTemporaryDirectory() UTF8String];
    }
    
    string
    CocoaSystem::relativeFilePath(const string& base, const string& rel)
    {
        NSString* baseStr =
            [NSString stringWithUTF8String: base.c_str()];
        NSString* relStr =
            [NSString stringWithUTF8String: rel.c_str()];
        
        NSString* newStr =
            [[baseStr stringByDeletingLastPathComponent]
                stringByAppendingPathComponent: relStr];
        
        NSFileManager* fm = [NSFileManager defaultManager];
        if (![fm fileExistsAtPath: newStr]) {
            NSString* libStr =
                [[[[NSBundle mainBundle] resourcePath]
                    stringByAppendingPathComponent: @"Examples"]
                        stringByAppendingPathComponent: relStr];
            if ([fm fileExistsAtPath: libStr])
                newStr = libStr;
        }

        return string([newStr UTF8String]);
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
    return YES;
}

+ (NSArray*) checkForTempFiles
{
    NSMutableArray* files = nil;
    
    CocoaSystem sys(nil);
    std::vector<std::string> temps = sys.findTempFiles();
    if (!temps.empty())
        files = [NSMutableArray arrayWithCapacity: temps.size()];

    for (string& temp: temps)
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
    }
    return self;
}

- (void)dealloc
{
    //delete mSystem;     mSystem = 0;
    mSystem->orphan();                      // leave system orphaned on the heap
    [mContent release]; mContent = nil;
    [mUploader release]; mUploader = nil;
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
    mStatus = nil;
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
    if (mStatus != nil) {
        [mStatus setStringValue: s];
        [mStatus setToolTip: s];
    }
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
    
    if (mStatus != nil) {
        [mStatus setStringValue: [msg mutableString]];
        [mStatus setToolTip: [msg mutableString]];
    }
    
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
    NSString* text = [mEditor string];
    
    NSRange lineRange;
    unsigned int lineCount;
    NSUInteger endOfLine;
    NSUInteger start;
    NSUInteger end;
    
    lineRange.location = 0;
    lineRange.length = 0;
    lineCount = 1;          // lineRange(0,0) is the start of line 1!
    
    while (lineCount < errLoc->begin.line) {
        // find start of next line
        [text getLineStart: nil end: &endOfLine contentsEnd: nil
                  forRange: lineRange];
        lineRange.location = endOfLine;
        lineCount += 1;
    }
    start = lineRange.location + errLoc->begin.column;
    
    while (lineCount < errLoc->end.line) {
        // find start of next line
        [text getLineStart: nil end: &endOfLine contentsEnd: nil
                  forRange: lineRange];
        lineRange.location = endOfLine;
        lineCount += 1;
    }
    end = lineRange.location + errLoc->end.column;
    
    lineRange.location = start;
    lineRange.length = end - start;
    
    [mEditor setSelectedRange: lineRange];
    [mEditor scrollRangeToVisible: lineRange];
    [[mGView window] makeFirstResponder: mEditor];
}

- (NSData *)dataRepresentationOfType:(NSString *)type {
    NSAssert([type isEqualToString: CFDGDocumentType], @"Unknown type");

    return [self getContent];
}

- (BOOL)loadDataRepresentation:(NSData *)data ofType:(NSString *)type
{
    NSAssert([type isEqualToString: CFDGDocumentType], @"Unknown type");

    mContent = [data retain];
    [self showContent];
    
    return YES;
}

- (void)windowControllerDidLoadNib:(NSWindowController *)windowController
{
    [self showContent];
    [mStatusText setEditable: NO];
    [mEditor setAutomaticDashSubstitutionEnabled:NO];
    [mEditor setAutomaticDataDetectionEnabled:NO];
    [mEditor setAutomaticLinkDetectionEnabled:NO];
    [mEditor setAutomaticSpellingCorrectionEnabled:NO];
    [mEditor setAutomaticTextReplacementEnabled:NO];
    [mEditor setAutomaticQuoteSubstitutionEnabled:NO];
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
- (IBAction) repeatRender:(id)sender{ [mGView repeatRender: sender]; }
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


- (BOOL)validateMenuItem:(NSMenuItem *)anItem
{
    SEL action = [anItem action];
    
    if (action == @selector(enterFullscreen:))
        return YES;
   
    if (action == @selector(startRender:)
    ||  action == @selector(repeatRender:)
    ||  action == @selector(finishRender:)
    ||  action == @selector(stopRender:)
    ||  action == @selector(saveAsSVG:)
    ||  action == @selector(showHiresRenderSheet:)
    ||  action == @selector(showAnimationFrameSheet:)
    ||  action == @selector(showAnimationSheet:)
    ||  action == @selector(uploadToGallery:))
    {
        return [mGView validateMenuItem: anItem];
    }
    
    return [super validateMenuItem: anItem];
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

    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    float hiresWidth = [defaults floatForKey: PrefKeyHiresWidth];
    float hiresHeight = [defaults floatForKey: PrefKeyHiresHeight];
    double hiresMinSize = [defaults doubleForKey: PrefKeyMinumumSize];

    [mGView startHiresRender: NSMakeSize(hiresWidth, hiresHeight)
                minimum: hiresMinSize];
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
    float movieHeight = [defaults floatForKey: PrefKeyMovieHeight];
    double movieMinSize = [defaults doubleForKey: PrefKeyMinumumSize];
    float movieFrame =  0.0;
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
                       completionHandler: ^(NSModalResponse returnCode){}];
        return;
    }

    
    [mGView startAnimation: NSMakeSize(movieWidth, movieHeight)
                   minimum: movieMinSize
                     frame: movieFrame];
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

- (void)showContent
{
    if (mEditor) {
        NSString* s = [[NSString alloc]
                        initWithData: mContent encoding: NSUTF8StringEncoding];
        [mEditor setString: s];
        [s release];
    }
}

- (NSData*)getContent
{
    [mContent release];
    
    mContent = [[[mEditor string]
                    dataUsingEncoding: NSUTF8StringEncoding] retain];
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


// Delegate methods from the editor
- (void) textDidChange: (NSNotification *) notification
{
    [self stopRender: self];
    [mGView reuseVariation];
}

@end


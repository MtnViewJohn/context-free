// CFDGController.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005 Mark Lentczner - markl@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#import "CFDGController.h"
#import "CFDGDocument.h"
#import "GalleryDownloader.h"
#import "GalleryUploader.h"
#include "SystemConfiguration/SCNetwork.h"
#include <SystemConfiguration/SCNetworkReachability.h>
#include "cfdg.h"
#include "GView.h"

@interface CFDGController (setup)
+ (void)setupURLs;
+ (void)setupExamples;
+ (void)setupDefaults;
+ (void)migrateCredentials;

- (void)buildExamplesMenu;
- (void)buildHelpMenu;
@end

@interface CFDGController (internal)
- (void)openExampleFromPath:(NSString*)path;
- (void)updateFontDisplay:(NSFont*)font;
@end

@interface CFDGController (update)
- (void)checkForUpdateInBackground;
- (void)checkForUpdate:(BOOL)inBackground;
- (void)updateThread:(id)arg;
- (void)getUpdateInfo;
- (void)gotUpdateInfo:(id)arg;
@end

// Provide the forward-declarations of new 10.7 SDK symbols so they can be
// called when building with the 10.5 SDK.
#if !defined(MAC_OS_X_VERSION_10_7) || \
MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7

enum {
    NSApplicationPresentationFullScreen = 1 << 10
};

#endif  // MAC_OS_X_VERSION_10_7

NSString* prefKeyEditorFontFamily = @"EditorFontFamily";
NSString* prefKeyEditorFontSize = @"EditorFontSize";

NSInteger CurrentTabWidth;

namespace {
    NSArray* urls = nil;
    NSArray* examples = nil;
    
    NSString* PrefKeyLaunchAction = @"LaunchAction";
    enum LaunchAction {
        LaunchActionWelcome     = 2,
        LaunchActionUntitled    = 1,
        LaunchActionNone        = 0
    };

    // Preferences keys
    static NSString* prefKeyCheckUpdateWeekly   = @"CheckUpdatesWeekly";
    static NSString* prefKeyCheckUpdateLast     = @"CheckUpdatesLastTime";
    static NSString* prefKeyTabWidth            = @"TabWidth";

    // Update location
    static NSString* updateURL
        = @"https://www.contextfreeart.org/ContextFreeMacOSXVersion.xml";
    static const char* updateServer
        = "www.ozonehouse.com";
        
    // Update dictionary keys (fetched from server)
    static NSString* updateKeyVersion = @"CFBundleVersion";
    static NSString* updateKeyShortVersion = @"CFBundleShortVersionString";
    static NSString* updateKeyDownloadURL = @"DownloadURL";
    static NSString* updateKeyWebSiteURL = @"WebSiteURL";

    static const NSTimeInterval updateCheckingInterval = 7*24*60*60;
        // one week in seconds
    
    static NSString* prefKeyUserName = @"UserName";
    static NSString* prefKeyPassword = @"UserPassword";


    void addFileMenuItems(NSArray* filePaths, NSMenu* menu,
        CFDGController* target, SEL selector)
    {
        NSUInteger n = [filePaths count];
        for (NSUInteger i = 0; i < n; ++i) {
            NSString* path = [filePaths objectAtIndex: i];
            NSString* title = [[path lastPathComponent]
                                stringByDeletingPathExtension];
            if ([title hasSuffix:@"_v2"]) continue;
            
            NSMenuItem* item = [menu addItemWithTitle: title
                                    action: selector
                                    keyEquivalent: @""];
            
            [item setTarget: target];
            [item setTag: i];
        }
    }

    void openFileMenuItem(NSArray* filePaths, id sender, CFDGController* target)
    {
        if (![sender respondsToSelector: @selector(tag)])
            return;
        
        NSInteger index = [sender tag];
        if (index < 0 || index >= static_cast<int>([filePaths count]))
            return;
            
        id path = [filePaths objectAtIndex: index];
        [target openExampleFromPath: path];
    }
}



@implementation CFDGController

+ (void)initialize
{
    [CFDGController setupURLs];
    [CFDGController setupExamples];
    [CFDGController setupDefaults];
    [CFDGController migrateCredentials];
}

- (void)awakeFromNib
{
    mUpdateInfo = nil;
    [self buildExamplesMenu];
    [self buildHelpMenu];
    [self updateFontDisplay: [mFontDisplay font]];
    [self darkModeEnabled];         // make sure OSXversion is set
    if (OSXversion < 7) {
        [mFullScreenMenu setHidden: YES];
        [mFullScreenMenu setEnabled: NO];
    } else {
        [mFullScreenMenu setHidden: NO];
        [mFullScreenMenu setEnabled: YES];
        NSApplicationPresentationOptions opts = [NSApp presentationOptions];
        if (opts & NSApplicationPresentationFullScreen) {
            [mFullScreenMenu setTitle: @"Exit Full Screen"];
        }
    }
}

static NSInteger OSXversion = 0;

- (BOOL)darkModeEnabled
{
    if (OSXversion == 0) {
        NSString* versionString = [[NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"] objectForKey:@"ProductVersion"];
        NSArray* versions = [versionString componentsSeparatedByString:@"."];
        NSUInteger count = [versions count];
        if (count > 1 && [[versions objectAtIndex:0] integerValue] == 10)
            OSXversion = [[versions objectAtIndex:1] integerValue];
    }
    return OSXversion >= 14;
}

- (IBAction)gotoURL:(id)sender
{
    if (![sender respondsToSelector: @selector(tag)])
        return;
    
    NSInteger index = [sender tag];
    if (index < 0 || index >= static_cast<int>([urls count]))
        return;
        
    NSURL* url = [NSURL URLWithString: [urls objectAtIndex: index]];
    
    [[NSWorkspace sharedWorkspace] openURL: url];
}

- (IBAction)openExample:(id)sender
{
    openFileMenuItem(examples, sender, self);
}

- (IBAction)checkForUpdateNow:(id)sender
{
    [self checkForUpdate: NO];
}

- (IBAction)setEditorFont:(id)sender
{
    NSFontManager* fontWindow = [NSFontManager sharedFontManager];
    [fontWindow orderFrontFontPanel: self];
}

- (IBAction)changeTabWidth:(id)sender
{
    NSInteger tag = [sender selectedTag];
    [[NSUserDefaults standardUserDefaults] setInteger:tag forKey:prefKeyTabWidth];
    CurrentTabWidth = tag;
    for (NSDocument* nsdoc in [[NSDocumentController sharedDocumentController] documents])
        if ([nsdoc isKindOfClass:[CFDGDocument class]]) {
            CFDGDocument* cfdoc = (CFDGDocument*)nsdoc;
            [cfdoc tabWidthDidChange:tag];
        }
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
    NSInteger tab = [[NSUserDefaults standardUserDefaults] integerForKey:prefKeyTabWidth];
    if (tab < 2 || tab > 8) tab = 2;
    [mTabWidth selectItemWithTag:tab];
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    // Make the color fields validate and write out their data
    NSWindow* window = (NSWindow*)sender;
    [window makeFirstResponder:window];
    
    if (auto fontPanel = [[NSFontManager sharedFontManager] fontPanel: NO])
        [fontPanel orderOut: self];
    
    return YES;
}

- (void)changeFont:(id)sender
{
    NSFont* oldFont = [mFontDisplay font];
    NSFont* newFont = [sender convertFont: oldFont];
    NSString* name = [newFont familyName];
    float size = static_cast<float>([newFont pointSize]);
    [[NSUserDefaults standardUserDefaults] setObject: name 
                                              forKey: prefKeyEditorFontFamily];
    [[NSUserDefaults standardUserDefaults] setFloat: size 
                                             forKey: prefKeyEditorFontSize];

    [self updateFontDisplay: newFont];
    // No font pref binding, so the existing windows have to be updated
    for (NSDocument* nsdoc in [[NSDocumentController sharedDocumentController] documents])
        if ([nsdoc isKindOfClass:[CFDGDocument class]]) {
            CFDGDocument* cfdoc = (CFDGDocument*)nsdoc;
            [cfdoc updateStyling];
        }
}

- (IBAction)changeStyle:(id)sender
{
    // Bad field data causes restore to default (which is stored in the field tag)
    if ([sender isKindOfClass:[NSTextField class]]) {
        NSTextField* field = sender;
        if (MakeColor(field.stringValue) < 0) {
            field.stringValue = [NSString stringWithFormat:@"#%06lX", [field tag]];
        }
    }
    // No style binding, so the existing windows have to be updated
    for (NSDocument* nsdoc in [[NSDocumentController sharedDocumentController] documents])
        if ([nsdoc isKindOfClass:[CFDGDocument class]]) {
            CFDGDocument* cfdoc = (CFDGDocument*)nsdoc;
            [cfdoc updateStyling];
        }
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [NSApp setServicesProvider: self];
    [self checkForUpdateInBackground];
    NSArray* tempFiles = [CFDGDocument checkForTempFiles];
    if (tempFiles) {
        NSAlert* askDelete = [[[NSAlert alloc] init] autorelease];
        [askDelete setMessageText: @"Old temporary files found"];
        [askDelete setAlertStyle: NSAlertStyleWarning];
        [askDelete addButtonWithTitle: @"Delete"];
        [askDelete addButtonWithTitle: @"Do Not Delete"];
        
        NSInteger button = [askDelete runModal];
        if (button == NSAlertFirstButtonReturn) {
            for (NSString* file in tempFiles) {
                [[NSFileManager defaultManager] removeItemAtPath: file error: nil];
            }
        }
    }
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    Renderer::AbortEverything = true;
    return NSTerminateNow;
}

- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender
{
    LaunchAction l = (LaunchAction)[[NSUserDefaults standardUserDefaults]
                                        integerForKey: PrefKeyLaunchAction];
    
    switch (l) {
        case LaunchActionNone:
            return NO;
            
        case LaunchActionUntitled:
        case LaunchActionWelcome:
        default:
            return YES;
    }
}

- (BOOL)applicationOpenUntitledFile:(NSApplication *)theApplication
{
    LaunchAction l = (LaunchAction)[[NSUserDefaults standardUserDefaults]
                                        integerForKey: PrefKeyLaunchAction];
    
    switch (l) {
        case LaunchActionNone:
            return YES;
            
        case LaunchActionWelcome: {
            NSString* welcomePath
                = [[NSBundle mainBundle] 
                    pathForResource: @"welcome" ofType: @"cfdg"
                        inDirectory: @"Examples"];
            [self openExampleFromPath: welcomePath];
            return YES;
        }

        case LaunchActionUntitled:
        default:
            return NO;
    }
}

-(void)displayGalleryCfdg:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error {
    if (NSAppKitVersionNumber < NSAppKitVersionNumber10_9)
        return;
    
    NSError* err = nil;
    CFDGDocument* doc = nil;

    NSString* pboardString = [pboard stringForType:NSPasteboardTypeString];
    NSURL* pboardURL = [NSURL URLWithString: pboardString];
    if (pboardURL == nil) {
        // cfdg text drop
        doc = [[NSDocumentController sharedDocumentController]
               openUntitledDocumentAndDisplay: NO error: nil];
        
        if (doc) {
            [doc readFromData: [pboardString dataUsingEncoding: NSUTF8StringEncoding]
                       ofType: [CFDGDocument documentType]
                        error: &err];
            [doc makeWindowControllers];
            [doc showWindows];
        } else {
            NSBeep();
        }
        return;
    }

    // File drop
    if ([[pboardURL scheme] isEqualToString: @"file"]) {
        [[NSWorkspace sharedWorkspace] openURL: pboardURL];
        return;
    }
    
    if ((![[pboardURL scheme] isEqualToString: @"http"] &&
         ![[pboardURL scheme] isEqualToString: @"https"]) ||
        (![[pboardURL host] isEqualToString: @"www.contextfreeart.org"] &&
         ![[pboardURL host] isEqualToString: @"contextfreeart.org"]) ||
        ![[pboardURL pathComponents][1] isEqualToString: @"gallery"])
    {
        NSBeep();
        return;
    }
    
    // CFA gallery URL drop
    NSString* query = [pboardURL query];
    NSString* frag = [pboardURL fragment];
    NSString* idStr = nil;
    NSRange idLoc = [query rangeOfString: @"id="];
    if (idLoc.location != NSNotFound)
        idStr = query;
    else if ((idLoc = [frag rangeOfString: @"#design/"]).location != NSNotFound)
        idStr = frag;
    
    if (idLoc.location != NSNotFound && idStr != nil) {
        int designID = [[idStr substringFromIndex: (idLoc.location + idLoc.length)] intValue];
        [[GalleryDownloader alloc] initWithDesignID: designID];
    } else if ([[pboardURL pathExtension] isEqualToString: @"cfdg"]) {
        [[GalleryDownloader alloc] initWithUrl: pboardURL];
    }

    if (doc) {
        [doc makeWindowControllers];
        [doc showWindows];
        [doc noteStatus: @"Downloading from the gallery…"];
    } else {
        NSBeep();
    }
}
@end

@implementation CFDGController (setup)

+ (void)setupURLs
{
    NSString* helpMenuPath
        = [[NSBundle mainBundle]
                pathForResource:@"HelpMenu"
                ofType:@"plist"];

    urls = [[NSArray arrayWithContentsOfFile: helpMenuPath] retain];
}

+ (void)setupExamples
{
    examples = [[[[NSBundle mainBundle] pathsForResourcesOfType: @"cfdg"
                                                    inDirectory: @"Examples"]
                 sortedArrayUsingSelector:@selector(localizedCaseInsensitiveCompare:)]
                retain];
}

+ (void)setupDefaults
{
    NSString* userDefaultsValuesPath
        = [[NSBundle mainBundle]
                pathForResource:@"UserDefaults"
                ofType:@"plist"];

    NSDictionary* userDefaultsValuesDict
        = [NSDictionary dictionaryWithContentsOfFile: userDefaultsValuesPath];
    
    [[NSUserDefaults standardUserDefaults]
        registerDefaults: userDefaultsValuesDict];

    [[NSUserDefaultsController sharedUserDefaultsController]
        setInitialValues: userDefaultsValuesDict];

    CurrentTabWidth = [[NSUserDefaults standardUserDefaults] integerForKey:prefKeyTabWidth];
}

+ (void)migrateCredentials
{
    NSString* name = [[NSUserDefaults standardUserDefaults] stringForKey: prefKeyUserName];
    NSString* password = [[NSUserDefaults standardUserDefaults] stringForKey: prefKeyPassword];
    
    // Move plain-text password into the keychain
    if (password) {
        if (name)
            [GalleryUploader savePassword: password forUser: name];
        [[NSUserDefaults standardUserDefaults] removeObjectForKey: prefKeyPassword];
    }
}

- (void)buildExamplesMenu
{
    addFileMenuItems(examples, mExampleMenu, self, @selector(openExample:));
}

- (void)buildHelpMenu
{
    NSUInteger n = [urls count];
    for (NSUInteger i = 0; i < n; i += 2) {
        NSString* title = [urls objectAtIndex: i];
        
        if ([title length] == 0) {
            [mHelpMenu addItem: [NSMenuItem separatorItem]];
        }
        else {
            NSMenuItem* item = [mHelpMenu addItemWithTitle: title
                                    action: @selector(gotoURL:)
                                    keyEquivalent: @""];
            [item setTarget: self];
            [item setTag: i+1];
        }
    }
}


@end

@implementation CFDGController (internal)
- (void)openExampleFromPath:(NSString*)path
{
    [ [NSDocumentController sharedDocumentController]
              openDocumentWithContentsOfURL: [NSURL fileURLWithPath: path] display: YES
                completionHandler: ^(NSDocument* document, BOOL documentWasAlreadyOpen, NSError* error)
    {
        if (document && !error && [document isKindOfClass: [CFDGDocument class]]) {
            CFDGDocument* cfDoc = (CFDGDocument*)document;
            [cfDoc makeExample];
        } else {
            NSBeep();
        }
    }];
}

- (void)updateFontDisplay:(NSFont*)font
{
    double size = static_cast<double>([font pointSize]);
    NSString* name;
    
    if (fabs(size - floor(size + 0.5)) >= 0.05) {
        name = [NSString stringWithFormat: @"%@ %.1f", [font displayName], size];
    } else {
        name = [NSString stringWithFormat: @"%@ %d", [font displayName], (int)size];
    }
    
    [mFontDisplay setStringValue: name];
}
@end

@implementation CFDGController (update)


- (void)checkForUpdateInBackground
{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    
    if (![defaults boolForKey: prefKeyCheckUpdateWeekly]) return;

    NSString* lastUpdateCheckString =
        [defaults stringForKey: prefKeyCheckUpdateLast];
    if (lastUpdateCheckString) {
        NSDate* lastUpdateCheck =
        [[[NSDate alloc] initWithTimeIntervalSinceReferenceDate: [lastUpdateCheckString doubleValue]] autorelease];
        NSTimeInterval sinceLastCheck = - [lastUpdateCheck timeIntervalSinceNow];

        if (sinceLastCheck < updateCheckingInterval)
            return;
    }
    
    [self checkForUpdate: YES];
}

- (void)checkForUpdate:(BOOL)inBackground
{
    [mUpdateInfo release];
    mUpdateInfo = nil;
    
    bool networkUp = false;
    SCNetworkConnectionFlags flags;
    SCNetworkReachabilityRef target = SCNetworkReachabilityCreateWithName(NULL, updateServer);
    if (SCNetworkReachabilityGetFlags(target, &flags)) {
        networkUp =
                !(flags & kSCNetworkFlagsConnectionRequired)
             &&  (flags & kSCNetworkFlagsReachable);
        // See "Technical Note TN1145 Living in a Dynamic TCP/IP Environment
        // http://developer.apple.com/technotes/tn/tn1145.html
    }
    CFRelease(target);
    if (!networkUp) {
        if (!inBackground) {
            [self gotUpdateInfo: self]; // Hack: non-nil means not in background
        }
        return;
    }
    
    if (inBackground) {
        [NSThread detachNewThreadSelector: @selector(updateThread:)
            toTarget: self
            withObject: nil];
    }
    else {
        [self getUpdateInfo];
        [self gotUpdateInfo: self]; // Hack: non-nil means not in background
    }
}

- (void)updateThread:(id)arg
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    [self getUpdateInfo];
    
    [self performSelectorOnMainThread: @selector(gotUpdateInfo:)
        withObject: nil     // Hack: nil means in background
        waitUntilDone: NO];

    [pool release];
}

- (void)getUpdateInfo
{
    mUpdateInfo =
        [[NSDictionary dictionaryWithContentsOfURL:
                [NSURL URLWithString: updateURL]] retain];
}

- (void)gotUpdateInfo:(id)arg
{
    if (!mUpdateInfo) {
        if (arg) { // Hack: non-nil arg means checking in the foreground
            NSAlert* alert = [[[NSAlert alloc] init] autorelease];
            [alert setMessageText:
                NSLocalizedString(@"Could not check for an update.", @"")];
            [alert setInformativeText:
                NSLocalizedString(@"Either the network is down or the update server could not be reached.", @"")];
            [alert addButtonWithTitle: NSLocalizedString(@"OK", @"")];
            [alert runModal];
        }
        return;
    }


    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];

    [defaults
     setObject: [NSString stringWithFormat:@"%f", [[NSDate date] timeIntervalSinceReferenceDate]]
        forKey: prefKeyCheckUpdateLast];
    [defaults synchronize];
    
    NSDictionary* bundleInfo =
        [[NSBundle bundleForClass: [self class]] infoDictionary];
    int thisVersion =
        [[bundleInfo objectForKey: updateKeyVersion] intValue];
        
    int updateVersion =
        [[mUpdateInfo objectForKey: updateKeyVersion] intValue];

    if (thisVersion >= updateVersion) {
        if (arg) { // Hack: non-nil arg means checking in the foreground
            NSAlert* alert = [[[NSAlert alloc] init] autorelease];
            [alert setMessageText:
                NSLocalizedString(@"Your version of Context Free is up to date.", @"")];
            [alert setInformativeText:
                [NSString stringWithFormat:
                    NSLocalizedString(@"You are running version %@ (v%d).", @""),
                        [bundleInfo objectForKey: updateKeyShortVersion],
                        thisVersion]];
            [alert setAlertStyle: NSAlertStyleInformational];
            [alert addButtonWithTitle: NSLocalizedString(@"OK", @"")];
            [alert runModal];
        }
        return;
    }

    NSAlert* alert = [[[NSAlert alloc] init] autorelease];
    [alert setMessageText:
        NSLocalizedString(@"There is a new version of Context Free available.", @"")];
    [alert setInformativeText:
        [NSString stringWithFormat:
            NSLocalizedString(@"You are running version %@ (v%d).  Version %@ (v%d) is now available.", @""),
            [bundleInfo objectForKey: updateKeyShortVersion], thisVersion,
            [mUpdateInfo objectForKey: updateKeyShortVersion], updateVersion]];
    [alert setAlertStyle: NSAlertStyleInformational];
    [alert addButtonWithTitle: NSLocalizedString(@"Download now", @"")];
    [alert addButtonWithTitle: NSLocalizedString(@"Go to website", @"")];
    [alert addButtonWithTitle: NSLocalizedString(@"Remind me later", @"")];
    
    switch ([alert runModal]) {
        case NSAlertFirstButtonReturn:
            [[NSWorkspace sharedWorkspace] openURL:
                [NSURL URLWithString:
                    [mUpdateInfo objectForKey: updateKeyDownloadURL]]];
            break;
        case NSAlertSecondButtonReturn:
            [[NSWorkspace sharedWorkspace] openURL:
                [NSURL URLWithString:
                    [mUpdateInfo objectForKey: updateKeyWebSiteURL]]];
            break;
    };
}

@end


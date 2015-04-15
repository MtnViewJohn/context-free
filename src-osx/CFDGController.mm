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
#include "SystemConfiguration/SCNetwork.h"
#include <SystemConfiguration/SCNetworkReachability.h>
#include "cfdg.h"

@interface CFDGController (setup)
+ (void)setupURLs;
+ (void)setupExamples;
+ (void)setupDefaults;

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

    // Update location
    static NSString* updateURL
        = @"http://www.ozonehouse.com/ContextFree/ContextFreeMacOSXVersion.xml";
    static const char* updateServer
        = "www.ozonehouse.com";
        
    // Update dictionary keys (fetched from server)
    static NSString* updateKeyVersion = @"CFBundleVersion";
    static NSString* updateKeyShortVersion = @"CFBundleShortVersionString";
    static NSString* updateKeyDownloadURL = @"DownloadURL";
    static NSString* updateKeyWebSiteURL = @"WebSiteURL";

    static const NSTimeInterval updateCheckingInterval = 7*24*60*60;
        // one week in seconds
    
    static NSString* prefKeyEditorFontName = @"EditorFontName";
    static NSString* prefKeyEditorFontSize = @"EditorFontSize";


    void addFileMenuItems(NSArray* filePaths, NSMenu* menu,
        CFDGController* target, SEL selector)
    {
        NSUInteger n = [filePaths count];
        for (NSUInteger i = 0; i < n; ++i) {
            NSString* path = [filePaths objectAtIndex: i];
            NSString* title = [[path lastPathComponent]
                                stringByDeletingPathExtension];
            
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
}

- (void)awakeFromNib
{
    mUpdateInfo = nil;
    [self buildExamplesMenu];
    [self buildHelpMenu];
    [self updateFontDisplay: [mFontDisplay font]];
    SInt32 vers;
    if (Gestalt(gestaltSystemVersionMinor, &vers) != noErr || vers < 7) {
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
    [fontWindow setDelegate: self];
    [fontWindow orderFrontFontPanel: self];
}

- (void)changeFont:(id)sender
{
    NSFont* oldFont = [mFontDisplay font];
    NSFont* newFont = [sender convertFont: oldFont];
    NSString* name = [newFont fontName];
    float size = static_cast<float>([newFont pointSize]);
    [[NSUserDefaults standardUserDefaults] setObject: name 
                                              forKey: prefKeyEditorFontName];
    [[NSUserDefaults standardUserDefaults] setFloat: size 
                                             forKey: prefKeyEditorFontSize];

    [self updateFontDisplay: newFont];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [NSApp setServicesProvider: self];
    [self checkForUpdateInBackground];
    NSArray* tempFiles = [CFDGDocument checkForTempFiles];
    if (tempFiles) {
        NSInteger button = NSRunAlertPanel(@"Old temporary files found", @"",
                                           @"Delete", @"Leave", nil);
        if (button == NSAlertDefaultReturn) {
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
    NSString * pboardString = [pboard stringForType:NSStringPboardType];
    
    if ([pboardString hasPrefix: @"file://"]) {
        [[NSWorkspace sharedWorkspace] openURL: [NSURL URLWithString: pboardString]];
    } else if ([pboardString hasPrefix: @"http://www.contextfreeart.org/gallery/"]) {
        NSRange idLoc = [pboardString rangeOfString: @"id="];
        if (idLoc.location != NSNotFound) {
            int designID = [[pboardString substringFromIndex: (idLoc.location + idLoc.length)] intValue];
            [[GalleryDownloader alloc] initWithDesignID: designID controller: self];
        }
    } else {
        NSError* err = nil;
        id doc = [[NSDocumentController sharedDocumentController]
                  openUntitledDocumentOfType: [CFDGDocument documentType]
                  display: NO];
        [doc readFromData: [pboardString dataUsingEncoding: NSUTF8StringEncoding] ofType: [CFDGDocument documentType] error: &err];
        [doc showWindows];
    }
}

- (void)downloadDone:(GalleryDownloader*)downloader
{
    if (!downloader || !downloader->cfdgContents || downloader->DLerror)
        return;
    
    id doc = [[NSDocumentController sharedDocumentController]
              openUntitledDocumentOfType: [CFDGDocument documentType]
              display: NO];
    
    [doc readDesign: downloader->fileName
           cfdgText: downloader->cfdgContents];
    [doc showWindows];
    [doc setVariation: downloader->variation];
    [downloader release];
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
    examples = [[[NSBundle mainBundle] pathsForResourcesOfType: @"cfdg"
        inDirectory: @"Examples"] retain];
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
    id doc = [[NSDocumentController sharedDocumentController]
                openUntitledDocumentOfType: [CFDGDocument documentType]
                display: NO];

    [doc readFromExample: path];
    [doc showWindows];
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
            [NSDate dateWithString: lastUpdateCheckString];
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
        setObject: [[NSDate date] description]
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
            [alert setAlertStyle: NSInformationalAlertStyle];
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
    [alert setAlertStyle: NSInformationalAlertStyle];
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


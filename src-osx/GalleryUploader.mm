// GalleryUploader.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
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

#import "GalleryUploader.h"
#import "CFDGDocument.h"
#import "GView.h"
#import "VariationFormatter.h"
#import <WebKit/WebFrame.h>
#import <WebKit/DOMCore.h>
#include <Security/Security.h>

#include <string>
#include <sstream>

#include "upload.h"

namespace {

    std::string asString(NSString* ns)
    {
        NSData* d = [ns dataUsingEncoding: NSUTF8StringEncoding];
        std::string s(reinterpret_cast<const char*>([d bytes]), [d length]);
        return s;
    }

    NSString* asNSString(const std::string& s)
    {
        return [NSString stringWithUTF8String: s.c_str()];
    }
    
    static NSString* ccURI   = @"CreativeCommonsLicenseURI";
    static NSString* ccName  = @"CreativeCommonsLicenseName";
    static NSString* ccImage = @"CreativeCommonsLicenseImage";
    
    static NSString* galDomain = @"www.contextfreeart.org";
    static NSString* galPath = @"/gallery/";

#if 1
    static NSString* uploadUrl =
        @"https://www.contextfreeart.org/gallery/upload.php";

    static NSString* displayUrl =
        @"https://www.contextfreeart.org/gallery/view.php?id=%d";
    
    static NSString* tagsUrl =
        @"https://www.contextfreeart.org/gallery/tags.php?t=tags";
#else
    static NSString* uploadUrl =
        @"http://localhost/~john/cfa2/gallery/upload.php";
    
    static NSString* displayUrl =
        //@"http://localhost:8000/main.html#design/%d";
        @"http://localhost/~john/cfa2/gallery/view.php?id=%d";
    
    static NSString* tagsUrl =
        @"http://localhost/~john/cfa2/gallery/tags.php?t=tags";
#endif
    
    SecKeychainItemRef getGalleryKeychainItem(NSString* name)
    {
        SecKeychainItemRef itemRef = nil;
        if (SecKeychainFindInternetPassword(NULL,
                                            (UInt32)[galDomain length],
                                            [galDomain UTF8String],
                                            0,
                                            NULL,
                                            (UInt32)[name length],
                                            [name UTF8String],
                                            (UInt32)[galPath length],
                                            [galPath UTF8String],
                                            0,
                                            kSecProtocolTypeHTTPS,
                                            kSecAuthenticationTypeHTMLForm,
                                            0,
                                            NULL,
                                            &itemRef
                                            ) == errSecSuccess)
        {
            return itemRef;
        }
        return nil;
    }
}



@implementation GalleryUploader

+ (NSString*) copyPassword:(NSString *)forUser
{
    NSString* ret = NULL;
    
    if (SecKeychainItemRef itemRef = getGalleryKeychainItem(forUser)) {
        SecKeychainAttribute     attr;
        SecKeychainAttributeList attrList;
        UInt32                   length;
        void                     *outData;
        
        // To set the account name attribute
        attr.tag = kSecAccountItemAttr;
        attr.length = 0;
        attr.data = NULL;
        attrList.count = 1;
        attrList.attr = &attr;
        
        
        if (SecKeychainItemCopyContent(itemRef, NULL, &attrList, &length, &outData) == noErr) {
            ret = [[NSString alloc] initWithBytes:outData
                                           length:length
                                         encoding:NSUTF8StringEncoding];
            SecKeychainItemFreeContent(&attrList, outData);
        }
        CFRelease(itemRef);
    }
    return ret;
}

+ (void) savePassword:(NSString*)password forUser:(NSString*)user
{
    SecKeychainItemRef itemRef;

    if (!password || !user) return;
    
    if (SecKeychainItemRef itemRef = getGalleryKeychainItem(user)) {
        // Try to update password of existing keychain item
        SecKeychainAttribute     attr;
        SecKeychainAttributeList attrList;
        
        // To set the account name attribute
        attr.tag = kSecAccountItemAttr;
        attr.length = (UInt32)[user length];
        attr.data = (void*)[user UTF8String];
        attrList.count = 1;
        attrList.attr = &attr;
        
        if (SecKeychainItemModifyContent(itemRef, &attrList, (UInt32)[password length],
                                         (void *)[password UTF8String]) == noErr)
        {
            return;         // success, we're done
        }
        // failure, make a new item
    }
    
    if (OSStatus s = SecKeychainAddInternetPassword(NULL,
                                                   (UInt32)[galDomain length],
                                                   [galDomain UTF8String],
                                                   0,
                                                   NULL,
                                                   (UInt32)[user length],
                                                   [user UTF8String],
                                                   (UInt32)[galPath length],
                                                   [galPath UTF8String],
                                                   0,
                                                   kSecProtocolTypeHTTPS,
                                                   kSecAuthenticationTypeHTMLForm,
                                                   (UInt32)[password length],
                                                   [password UTF8String],
                                                   &itemRef
                                                   ) != noErr)
    {
        CFStringRef msg = SecCopyErrorMessageString(s, NULL);
        NSLog(@"Error saving password: %@", (NSString*)msg);
        CFRelease(msg);
    }
}

- (id)initForDocument:(CFDGDocument*)document andView:(GView*)view
{
    self = [self initWithWindowNibName: @"GalleryUploader"];
    if (!self) return self;

    mDocument = document;
    mView = view;
    mStatus = 0;
    
        // no need to retain - the document is retaining us!

    [self loadWindow];
    [mFormView retain];
    [mProgressView retain];
    [mDoneView retain];
    return self;
}

- (void) dealloc {
    [mDoneView release];
    [mProgressView release];
    [mFormView release];
    if (mTagsTask) {
        if ([mTagsTask state] == NSURLSessionTaskStateRunning)
            [mTagsTask cancel];
        [mTagsTask release];
    }
    if (mUploadTask) {
        if ([mUploadTask state] == NSURLSessionTaskStateRunning)
            [mUploadTask cancel];
        [mUploadTask release];
    }
    [mOrigPassword release];
    [mOrigName release];
    [mTags release];
    [super dealloc];
}


- (NSData*)requestBody
{
    Upload upload;

    upload.mUserName    = asString([mUserNameField stringValue]);
    upload.mPassword    = asString([mPasswordField stringValue]);
    upload.mTitle       = asString([mTitleField stringValue]);
    upload.mNotes       = asString([mNotesView string]);
    upload.mTags        = asString([[mTagsView objectValue] componentsJoinedByString: @" "]);
    upload.mFileName    = asString([mFileField stringValue]) + ".cfdg";
    upload.mVariation   = [mView variation];
    upload.mTiled       = 0;
    if ([mTiled state] == NSOnState) {
        upload.mTiled = [mView isFrieze];
        if ([mView isTiled] && !upload.mTiled)
            upload.mTiled = 3;
    }
    upload.mCompression = (Upload::Compression)
                    [[mCompressionMatrix selectedCell] tag];
    upload.mccLicenseURI    = asString(mDefccURI);
    upload.mccLicenseName   = asString(mDefccName);
    upload.mccLicenseImage  = asString(mDefccImage);
    
    BOOL crop = upload.mTiled || 
            [[NSUserDefaults standardUserDefaults] boolForKey: @"SaveCropped"];
    
    NSSize mult = NSMakeSize([mSaveTileWidth floatValue], [mSaveTileHeight floatValue]);
    
    NSData* textData    = [mDocument getContent];
    NSData* imageData   = [mView pngImageDataCropped: crop
                                          multiplier: [mView isTiled] ? &mult : nil];
    
    if (!imageData) return nil;

    upload.mText        = reinterpret_cast<const char*>([textData bytes]);
    upload.mTextLen     = [textData length];
    upload.mImage       = reinterpret_cast<const char*>([imageData bytes]);
    upload.mImageLen    = [imageData length];
    
    std::ostringstream design;
    upload.generatePayload(design);

    return [NSData dataWithBytes: design.str().data()
                    length: design.str().length()];
}

- (void)setView:(NSView*)view
{
    if (view == mProgressView)
        [mProgressBar startAnimation: nil];
    else
        [mProgressBar stopAnimation: nil];
    
    NSRect contentFrame = [mContentView frame];

    NSSize oldContentSize = contentFrame.size;
    NSSize newContentSize = [view frame].size;
    NSSize deltaSize;
    deltaSize.width = newContentSize.width - oldContentSize.width;
    deltaSize.height = newContentSize.height - oldContentSize.height;

    NSView* container = [mContentView superview];
    [mContentView removeFromSuperview];
    contentFrame.size = newContentSize;
    [view setFrame: contentFrame];
    [container addSubview: view];
    mContentView = view;

    NSWindow* window = [self window];
    NSRect f = [window frame];
    f.origin.x -= deltaSize.width / 2.0;
    f.origin.y -= deltaSize.height;
    f.size.width += deltaSize.width;
    f.size.height += deltaSize.height;

    [window setFrame: f display: YES animate: YES];
}


- (IBAction)retry:(id)sender
{
    if (mSuccessId) {
        NSString* where = [NSString stringWithFormat: displayUrl, mSuccessId];
        [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString: where]];
        [self cancel: sender];
    } else {
        [self setView: mFormView];
    }
}

- (IBAction)show:(id)sender
{
    [self setView: mFormView];
    
    NSMutableURLRequest* request =
    [NSMutableURLRequest requestWithURL: [NSURL URLWithString: tagsUrl]
                            cachePolicy: NSURLRequestReloadIgnoringCacheData
                        timeoutInterval: 120.0
     ];
    [request setHTTPMethod: @"GET"];
    [request setValue: @"application/json"
        forHTTPHeaderField: @"Content-Type"];
    
    mTagsTask = [[NSURLSession sharedSession] dataTaskWithRequest: request
                                                completionHandler:^(NSData *data,
                                                                    NSURLResponse *response,
                                                                    NSError *error)
                    {
                        if (data) {
                            auto tags = Upload::AllTags(static_cast<const char*>([data bytes]),
                                                        static_cast<std::size_t>([data length]));
                            NSMutableArray<NSString*>* tagset = [NSMutableArray arrayWithCapacity: tags.size()];
                            for (auto&& tag: tags)
                                [tagset addObject: [NSString stringWithUTF8String:tag.c_str()]];
                            [tagset sortUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
                            dispatch_async(dispatch_get_main_queue(), ^{mTags = [tagset retain];});
                        }
                    }];
    [mTagsTask retain];
    [mTagsTask resume];
        
    mOrigName = [[NSString alloc] initWithString: [mUserNameField stringValue]];
    mOrigPassword = [GalleryUploader copyPassword: mOrigName];
    if (mOrigPassword)
        [mPasswordField setStringValue: mOrigPassword];
    

    if ([[mTitleField stringValue] length] == 0) {
        NSString* name = [mDocument displayName];
        name = name.stringByDeletingPathExtension;
        name = name.capitalizedString;
        [mTitleField setStringValue: name];
    }

    if ([[mFileField stringValue] length] == 0) {
        NSString* file = [[mDocument fileURL] path];
        if (file) {
            file = [[file stringByDeletingPathExtension] lastPathComponent];
        } else {
            file = [mDocument displayName];
        }
        [mFileField setStringValue: file];
    }

    [mVariationField setIntValue: [mView variation]];
    
    int bestCompression = [mView canvasColor256] ? 
        Upload::CompressPNG8 : Upload::CompressJPEG;
    [mCompressionMatrix selectCellWithTag: bestCompression];

    bool tiled = [mView isTiled];
    [mTiled setEnabled: tiled];
    [mCropCheck setEnabled: !tiled];
    [mSaveTileWidth setHidden: !tiled];
    [mSaveTileHeight setHidden: !tiled];
    [mWidthLabel setHidden: !tiled];
    [mHeightLabel setHidden: !tiled];
    [mMultLabel setHidden: !tiled];
    [mTiled setState: (tiled ? NSOnState : NSOffState)];
    
    if (tiled) {
        CFDG::frieze_t frz = (CFDG::frieze_t)[mView isFrieze];
        [mSaveTileWidth setEnabled: frz != CFDG::frieze_y];
        [mSaveTileHeight setEnabled: frz != CFDG::frieze_x];

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
    }
    
    [self updateCCInfo: YES];
    
    [NSApp beginSheet: [self window]
        modalForWindow: [mView window]
        modalDelegate: nil didEndSelector: nil contextInfo: nil];
}


- (void)updateCCInfo:(BOOL)reset
{
    if (reset) {
        mDefccURI = [[NSUserDefaults standardUserDefaults] stringForKey: ccURI];
        mDefccName = [[NSUserDefaults standardUserDefaults] stringForKey: ccName];
        mDefccImage = [[NSUserDefaults standardUserDefaults] stringForKey: ccImage];
    }
    
    if (!mDefccURI || !mDefccName || !mDefccImage || [mDefccURI length] == 0 || 
        [mDefccName length] == 0 || [mDefccImage length] == 0) 
    {
        mDefccURI = @"";
        mDefccName = @"no license chosen";
        mDefccImage = @"";
    }

    bool isSeeded = [mDefccURI length] > 0;
    
    [mLicenseName setStringValue: mDefccName];
    
    if (isSeeded) {
        NSURL* iconURL = [NSURL URLWithString: mDefccImage];
        NSImage* icon = [[[NSImage alloc] initWithContentsOfURL: iconURL] autorelease];
        [mLicenseImage setImage: icon];
        [mLicenseImage setEnabled: YES];
    } else {
        [mLicenseImage setImage: nil];
        [mLicenseImage setEnabled: NO];
    }
}

- (IBAction)goToCreateAccount:(id)sender
{
    NSURL* url = [NSURL URLWithString: 
        @"https://www.contextfreeart.org/phpbb/ucp.php?mode=register"];
    
    [[NSWorkspace sharedWorkspace] openURL: url];
}

- (IBAction)changeLicense:(id)sender
{
    NSPopUpButton* ccmenu = (NSPopUpButton*)sender;
    NSInteger tag = [ccmenu selectedTag];
    switch (tag) {
        case 0:
            [self updateCCInfo: YES];
            return;
        case 1:
            mDefccURI = @"https://creativecommons.org/publicdomain/zero/1.0/";
            mDefccName = @"CC0 1.0 Universal (CC0 1.0) Public Domain Dedication";
            mDefccImage = @"https://licensebuttons.net/p/zero/1.0/88x31.png";
            break;
        case 2:
            mDefccURI = @"https://creativecommons.org/licenses/by/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution 4.0 International";
            break;
        case 3:
            mDefccURI = @"https://creativecommons.org/licenses/by-sa/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by-sa/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution-ShareAlike 4.0 International";
            break;
        case 4:
            mDefccURI = @"https://creativecommons.org/licenses/by-nd/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by-nd/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution-NoDerivatives 4.0 International";
            break;
        case 5:
            mDefccURI = @"https://creativecommons.org/licenses/by-nc/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by-nc/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution-NonCommercial 4.0 International";
            break;
        case 6:
            mDefccURI = @"https://creativecommons.org/licenses/by-nc-sa/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International";
            break;
        case 7:
            mDefccURI = @"https://creativecommons.org/licenses/by-nc-nd/4.0/";
            mDefccImage = @"https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png";
            mDefccName = @"Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International";
            break;
        default:
            mDefccURI = @"";
            mDefccName = @"no license chosen";
            mDefccImage = @"";
            break;
    }
    [self updateCCInfo: NO];
}

- (IBAction)licenseDetails:(id)sender
{
    NSURL* url = [NSURL URLWithString: mDefccURI];
    
    [[NSWorkspace sharedWorkspace] openURL: url];
}

- (IBAction)upload:(id)sender
{
    if (![[mPasswordField stringValue] isEqualToString: mOrigPassword] ||
        ![[mUserNameField stringValue] isEqualToString: mOrigName])
    {
        [GalleryUploader savePassword: [mPasswordField stringValue]
                              forUser: [mUserNameField stringValue]];
    }
    
    NSData* body = [self requestBody];
    if (!body) {
        [mMessage setString: @"Failed to generate PNG image to upload."];
        [self setView: mDoneView];
        return;
    }
    
    NSMutableURLRequest* request =
        [NSMutableURLRequest requestWithURL: [NSURL URLWithString: uploadUrl]
                                cachePolicy: NSURLRequestReloadIgnoringCacheData
                            timeoutInterval: 120.0
        ];
    [request setHTTPMethod: @"POST"];
    [request setValue: asNSString(Upload::generateContentType())
                forHTTPHeaderField: @"Content-Type"];
    
    mUploadTask = [[NSURLSession sharedSession] uploadTaskWithRequest: request
                                                             fromData: body
                                                    completionHandler:^(NSData *data,
                                                                        NSURLResponse *response,
                                                                        NSError *error)
    {
        NSString* newmsg = nil;
        BOOL retry = NO;
        unsigned design = 0;
        NSAttributedString *theParsedHTML = nil;
        if (error) {
            newmsg = [error localizedDescription];
        } else {
            NSInteger status = 0;
            if ([response isKindOfClass:[NSHTTPURLResponse class]] ) {
                status = [(NSHTTPURLResponse *)response statusCode];
            }
            
            switch (status) {
                case 0:
                    newmsg = @"Upload completed without a status code (?!?!?!).";
                    break;
                case 200: {
                    Upload response(static_cast<const char*>([data bytes]),
                                    static_cast<std::size_t>([data length]));
                    design = response.mId;
                    if (design) {
                        newmsg =  @"Upload completed successfully.";
                        retry = YES;
                        mSuccessId = design;
                    } else {
                        newmsg = @"The gallery indicates that the upload succeeded but did not return a design number.";
                    }
                    break;
                }
                case 409:
                case 401:
                case 400:
                case 404:
                case 500:
                    retry = YES;
                default: {
                    // Take the raw HTML data and then initialize an NSMutableAttributed
                    // string with HTML code
                    theParsedHTML = [[NSAttributedString alloc] initWithHTML:data
                                                          documentAttributes: nil];
                    
                    // Make a copy of retry with __block storage. We don't want to make retry
                    // a __block variable because this block is going to end up on the
                    // heap.
                    __block BOOL stopped = retry;
                    // This UUID will only be found in the response body if the upload
                    // failed. Give the user another chance if failure occured.
                    [data enumerateByteRangesUsingBlock: ^(const void *bytes, NSRange byteRange, BOOL *stop)
                        {
                            if (byteRange.length && strnstr(static_cast<const char*>(bytes),
                                                            "AFD8D2F0-B6EB-4569-9D89-954604507F3B",
                                                            byteRange.length))
                            {
                                stopped = YES;
                                *stop = YES;
                            }
                        }];
                    retry = stopped;
                    mSuccessId = 0;
                    break;
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (theParsedHTML) {
                [[mMessage textStorage] setAttributedString:theParsedHTML];
                [mMessage setBackgroundColor:[NSColor whiteColor]];
                [theParsedHTML release];
            } else if (newmsg) {
                [mMessage setString: newmsg];
            }
            [mRetryButton setEnabled: retry];
            if (retry && design)
                [mRetryButton setTitle: @"See Design"];
            else
                [mRetryButton setTitle: @"Try Again"];
            [self setView: mDoneView];
        });
    }];
    [mUploadTask retain];
    [mUploadTask resume];

    [mRetryButton setEnabled:NO];
    [self setView: mProgressView];
}


- (IBAction)cancel:(id)sender
{
    NSWindow* window = [self window];
    [NSApp endSheet: window];
    [window orderOut: sender];
}

- (NSArray<NSString*>*)tokenField:(NSTokenField *)tokenField
          completionsForSubstring:(NSString *)substring
                     indexOfToken:(NSInteger)tokenIndex
              indexOfSelectedItem:(NSInteger *)selectedIndex
{
    NSInteger start = -1;
    for (NSUInteger i = 0; i < [mTags count]; ++i)
        if ([mTags[i] hasPrefix: substring]) {
            start = i;
            break;
        }
    if (start == -1)
        return nil;
    NSUInteger count = 1;
    for (NSUInteger i = start + 1; i < [mTags count]; ++i)
        if ([mTags[i] hasPrefix: substring])
            ++count;
        else
            break;
    return [mTags subarrayWithRange: NSMakeRange(start, count)];
}


@end

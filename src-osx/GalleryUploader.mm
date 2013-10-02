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
#import <WebKit/WebPolicyDelegate.h>
#import <WebKit/DOMCore.h>

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
}



@implementation GalleryUploader

- (id)initForDocument:(CFDGDocument*)document andView:(GView*)view;
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
    [mLicenseView retain];
    return self;
}

- (void) dealloc {
    [mLicenseView release];
    [mDoneView release];
    [mProgressView release];
    [mFormView release];
    [mConnection release];
    [mResponseBody release];
    [super dealloc];
}


- (NSData*)requestBody
{
    Upload upload;

    upload.mUserName    = asString([mUserNameField stringValue]);
    upload.mPassword    = asString([mPasswordField stringValue]);
    upload.mTitle       = asString([mTitleField stringValue]);
    upload.mNotes       = asString([mNotesView string]);
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

    std::ostringstream payloadStream;
    upload.generatePayload(payloadStream);
    std::string payloadString = payloadStream.str();

    return [NSData dataWithBytes: payloadString.data()
                    length: payloadString.length()];
}

- (void)setView:(NSView*)view
{
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

- (void)allDone:(NSString*)message
{
    [mConnection release];      mConnection = nil;

    if (message) mStatus = -1;
    
    [mRetryButton setEnabled:NO];
    switch (mStatus) {
        case -1:
            [mMessage setString: message];
            break;
        case 0:
            [mMessage setString: @"Upload completed without a status code (?!?!?!)."];
            break;
        case 409:
            [mRetryButton setEnabled:YES];
        case 200: {
            NSAttributedString *theParsedHTML;

            // Take the raw HTML data and then initialize an NSMutableAttributed
            // string with HTML code
            theParsedHTML = [[NSAttributedString alloc] initWithHTML:mResponseBody 
                        documentAttributes: nil];
            
            NSUInteger responseLength = [mResponseBody length];
            char* rawHTML = reinterpret_cast<char*>([mResponseBody mutableBytes]);
            
            // This UUID will only be found in the response body if the upload
            // failed. Give the user another chance if failure occured.
            if (responseLength && strnstr(rawHTML, "AFD8D2F0-B6EB-4569-9D89-954604507F3B", 
                                          responseLength)) 
            {
                [mRetryButton setEnabled:YES];
            }
            
            // no parsing or fetching error.. so lets display it
            
            if (theParsedHTML) {
                [[mMessage textStorage] setAttributedString:theParsedHTML];
                [theParsedHTML release];
            }
            break;
        }
        case 404:
            [mMessage setString: @"Upload service is offline."];
            break;
        default:
            [mMessage setString: [NSString localizedStringWithFormat:
                @"Failed with unexpected status code: %ld, %@", static_cast<long>(mStatus),
                [NSHTTPURLResponse localizedStringForStatusCode: mStatus]]];
            break;
    }
    [mResponseBody release];    mResponseBody = nil;
    [self setView: mDoneView];
}

- (IBAction)retry:(id)sender
{
    [self setView: mFormView];
}

- (IBAction)show:(id)sender
{
    [self setView: mFormView];

    if ([[mTitleField stringValue] length] == 0) {
        [mTitleField setStringValue: [mDocument displayName]];
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
    
    [self updateCCInfo];
    
    [NSApp beginSheet: [self window]
        modalForWindow: [mView window]
        modalDelegate: nil didEndSelector: nil contextInfo: nil];
}


- (void)updateCCInfo
{
    mDefccURI = [[NSUserDefaults standardUserDefaults] stringForKey: ccURI];
    mDefccName = [[NSUserDefaults standardUserDefaults] stringForKey: ccName];
    mDefccImage = [[NSUserDefaults standardUserDefaults] stringForKey: ccImage];
    
    if (!mDefccURI || !mDefccName || !mDefccImage || [mDefccURI length] == 0 || 
        [mDefccName length] == 0 || [mDefccImage length] == 0) 
    {
        mDefccURI = @"";
        mDefccName = @"no license chosen";
        mDefccImage = @"";
    }
    
    bool isSeeded = [mDefccURI length] > 0;
    NSError* err = nil;
    NSString* htmlPath = [[NSBundle mainBundle] pathForResource: @"widgetform" 
                                                         ofType: @"html"];
    //NSString* theHtml = [NSString stringWithContentsOfFile: htmlPath];
    NSString* theHtml = [NSString stringWithContentsOfFile: htmlPath 
                                                  encoding: NSUTF8StringEncoding 
                                                     error: &err];
    NSString* seededHtml = [NSString stringWithFormat: theHtml, 
                            mDefccURI,
                            isSeeded ? @"" : @"&want_a_license=no_license_by_default"];
    
    [mLicenseName setStringValue: mDefccName];
    
    [[mCreativeCommonsWidget mainFrame] loadHTMLString: seededHtml
                                               baseURL: [NSURL fileURLWithPath: htmlPath]];
    [mCreativeCommonsWidget setPolicyDelegate: self];
    
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
        @"http://www.contextfreeart.org/phpbb/profile.php?mode=register"];
    
    [[NSWorkspace sharedWorkspace] openURL: url];
}

- (IBAction)changeLicense:(id)sender
{
    [self setView: mLicenseView];
}

- (IBAction)updateLicense:(id)sender
{
    mDefccURI = @"";
    mDefccName = @"";
    mDefccImage = @"";
    
    DOMDocument* dom = [[mCreativeCommonsWidget mainFrame] DOMDocument];
    
    if (dom) {
        DOMElement* licenseURIElem = [dom getElementById: @"cc_js_result_uri"];
        DOMElement* licenseNameElem = [dom getElementById: @"cc_js_result_name"];
        DOMElement* licenseImageElem = [dom getElementById: @"cc_js_result_img"];
        
        if (licenseNameElem && licenseImageElem && licenseURIElem) {
            mDefccURI = [licenseURIElem getAttribute: @"value"];
            mDefccName = [licenseNameElem getAttribute: @"value"];
            mDefccImage = [licenseImageElem getAttribute: @"value"];
        }
    }
    
    [[NSUserDefaults standardUserDefaults] setObject: mDefccURI forKey: ccURI];
    [[NSUserDefaults standardUserDefaults] setObject: mDefccName forKey: ccName];
    [[NSUserDefaults standardUserDefaults] setObject: mDefccImage forKey: ccImage];
    
    [self updateCCInfo];
    
    [self setView: mFormView];
}

- (IBAction)noChangeLicense:(id)sender
{
    [self setView: mFormView];
}

- (IBAction)licenseDetails:(id)sender
{
    NSURL* url = [NSURL URLWithString: mDefccURI];
    
    [[NSWorkspace sharedWorkspace] openURL: url];
}

- (void)webView:(WebView *)sender decidePolicyForNavigationAction:(NSDictionary *)actionInformation
        request:(NSURLRequest *)request frame:(WebFrame *)frame 
decisionListener:(id)listener 
{
    int navigationType = [[actionInformation objectForKey:WebActionNavigationTypeKey] intValue];
    if (navigationType == WebNavigationTypeLinkClicked) {    
        [listener ignore];
        [[NSWorkspace sharedWorkspace] openURL: [request URL]];
    } else {
        [listener use];
    }
}

- (IBAction)upload:(id)sender
{
    NSData* body = [self requestBody];
    if (!body) {
        [mMessage setString: @"Failed to generate PNG image to upload."];
        [self setView: mDoneView];
        return;
    }
    
    NSMutableURLRequest* request =
        [NSMutableURLRequest requestWithURL:
                [NSURL URLWithString: @"http://www.contextfreeart.org/gallery/upload.php"]
                //[NSURL URLWithString: @"http://aluminium.local/~john/cfa2/gallery/upload.php"]
            cachePolicy: NSURLRequestReloadIgnoringCacheData
            timeoutInterval: 120.0
        ];
    [request setHTTPMethod: @"POST"];
    [request setValue: asNSString(Upload::generateContentType())
                forHTTPHeaderField: @"Content-Type"];
    [request setHTTPBody: body];

    mResponseBody = [[NSMutableData data] retain];

    mConnection = [NSURLConnection alloc];
    [mConnection initWithRequest: request delegate: self];
    if (!mConnection) {
        [self cancel: sender];
    }

    [mRetryButton setEnabled:NO];
    [self setView: mProgressView];
}


-(void)connection:(NSURLConnection *)c didReceiveResponse:(NSURLResponse *)response
{
    [mResponseBody setLength: 0];
    
    if ([response isKindOfClass:[NSHTTPURLResponse class]] ) {
        mStatus = [(NSHTTPURLResponse *)response statusCode];
    }
}

- (void)connection:(NSURLConnection *)c didReceiveData:(NSData *)data
{
    [mResponseBody appendData: data];
}

-(void)connectionDidFinishLoading:(NSURLConnection *)c
{
    [self performSelector:@selector( allDone: )
               withObject:0
               afterDelay:0.0];
}

- (void)connection:(NSURLConnection *)c didFailWithError:(NSError *)error
{
    [self allDone: [error localizedDescription]];
}




- (IBAction)cancel:(id)sender
{
    if (mConnection) {
        [mConnection cancel];
    }

    [mConnection release];      mConnection = nil;
    [mResponseBody release];    mResponseBody = nil;

    NSWindow* window = [self window];
    [NSApp endSheet: window];
    [window orderOut: sender];
}

@end

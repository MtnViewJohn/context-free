// GalleryUploader.h
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

#import <Cocoa/Cocoa.h>
#import <WebKit/WebView.h>

@class CFDGDocument;
@class GView;

@interface GalleryUploader : NSWindowController {
    CFDGDocument*               mDocument;
    GView*                      mView;
    NSInteger                   mStatus;

    IBOutlet NSView*    mContentView;

    IBOutlet NSView*    mLicenseView;
    IBOutlet WebView*       mCreativeCommonsWidget;
    
    IBOutlet NSView*    mFormView;
    IBOutlet NSTextField*      mUserNameField;
    IBOutlet NSTextField*      mPasswordField;
    IBOutlet NSTextField*      mTitleField;
    IBOutlet NSTextView*       mNotesView;
    IBOutlet NSTextField*      mFileField;
    IBOutlet NSTextField*      mVariationField;
    IBOutlet NSMatrix*         mCompressionMatrix;
    IBOutlet NSButton*         mTiled;
    IBOutlet NSTextField*      mLicenseName;
    IBOutlet NSButton*         mLicenseImage;
    IBOutlet NSTextField*      mSaveTileWidth;
    IBOutlet NSTextField*      mSaveTileHeight;
    IBOutlet NSButton*         mCropCheck;
    IBOutlet NSTextField*      mWidthLabel;
    IBOutlet NSTextField*      mHeightLabel;
    IBOutlet NSTextField*      mMultLabel;

    IBOutlet NSView*           mProgressView;
    IBOutlet NSProgressIndicator* mProgressBar;

    IBOutlet NSView*           mDoneView;
    IBOutlet NSTextView*       mMessage;
    IBOutlet NSButton*         mRetryButton;

    NSURLConnection*           mConnection;
    NSMutableData*             mResponseBody;
    
    NSString* mDefccURI;
    NSString* mDefccName;
    NSString* mDefccImage;
}

- (id)initForDocument:(CFDGDocument*)document andView:(GView*)view;

- (IBAction)show:(id)sender;

- (IBAction)goToCreateAccount:(id)sender;
- (IBAction)changeLicense:(id)sender;
- (IBAction)updateLicense:(id)sender;
- (IBAction)noChangeLicense:(id)sender;
- (IBAction)licenseDetails:(id)sender;
- (IBAction)upload:(id)sender;

- (IBAction)cancel:(id)sender;
- (IBAction)retry:(id)sender;

- (void)webView:(WebView *)sender decidePolicyForNavigationAction:(NSDictionary *)actionInformation
        request:(NSURLRequest *)request frame:(WebFrame *)frame 
decisionListener:(id)listener;

- (void) updateCCInfo;

@end

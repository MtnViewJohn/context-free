// ImageCanvas.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2009-2013 John Horigan - john@glyphic.com
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

#import "ImageCanvas.h"

#import <Cocoa/Cocoa.h>

#import "GView.h"
#import "BitmapImageHolder.h"

#include "makeCFfilename.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace {
std::string dummy;
}

ImageCanvas::ImageCanvas(GView* view, BitmapImageHolder* bitmap,
        PixelFormat format)
    : aggCanvas(format), mView(view), mOutputName(dummy)
{
    attach([bitmap bitmapData], static_cast<unsigned>([bitmap pixelsWide]),
           static_cast<unsigned>([bitmap pixelsHigh]),
           static_cast<int>([bitmap bytesPerRow]));
    assert([bitmap bitsPerPixel] == BytesPerPixel.at(format) * 8);
}

ImageCanvas::ImageCanvas(const std::string& name, BitmapImageHolder* bitmap, aggCanvas::PixelFormat pixfmt,
         int _fps, VideoFormat format, int frames, int loops, AbstractSystem& sys)
    : aggCanvas(pixfmt), mOutputName(name), mImageData([bitmap retain]),
      fps(_fps), mOutFormat(format), mFrameCount(frames), mLoopCount(loops)
{
    attach([mImageData bitmapData], static_cast<unsigned>([mImageData pixelsWide]),
           static_cast<unsigned>([mImageData pixelsHigh]),
           static_cast<int>([mImageData bytesPerRow]));
    assert([mImageData bitsPerPixel] == BytesPerPixel.at(pixfmt) * 8);
    
    NSURL* ffUrl = [[NSBundle mainBundle] URLForAuxiliaryExecutable: @"ffmpeg"];
    ffmpegBinary = [ffUrl fileSystemRepresentation];

    mTempFiles.reserve(frames);
    mTempDirectory = sys.tempDirectoryForWrite("cfdg-temp-frames-");
    if (mTempDirectory.empty()) {
        mError = true;
        sys.message("*** Cannot create temporary directory for animation frames.");
    }
    mTemplate = mTempDirectory + "/%f.png";
}

ImageCanvas::~ImageCanvas()
{
    [mImageData release];   mImageData = nil;
    for (auto&& file: mTempFiles) {
        remove(file.c_str());
    }
    if (!mTempDirectory.empty())
        rmdir(mTempDirectory.c_str());
}

void
ImageCanvas::start(bool clear,  const agg::rgba& background,
    int width, int height)
{
    aggCanvas::start(clear, background, width, height);
}

void
ImageCanvas::end()
{
    aggCanvas::end();

    if (mView) {
        [mView performSelectorOnMainThread: @selector(redisplayImage:)
                                withObject: [NSValue valueWithRect:
                                             NSMakeRect(cropX(), cropY(), cropWidth(), cropHeight())]
                             waitUntilDone: NO];
    }
    
    if (mFrameCount) {
        std::string name = makeCFfilename(mTemplate.c_str(), mCurrentFrame++,
                                          123456, 1);
        NSString* nameNS = [NSString stringWithUTF8String: name.c_str()];
        NSURL* nameUrl = [NSURL fileURLWithPath: nameNS];
        
        NSBitmapImageRep* bits = [mImageData getImageRep];
        CGImageRef iref = [bits CGImage];
        if (!iref) return;
        
        NSMutableData* mdata = [NSMutableData data];
        CGImageDestinationRef destref =
            CGImageDestinationCreateWithData((CFMutableDataRef)mdata, kUTTypePNG, 1, nil);
        if (!destref) return;
        
        CGImageDestinationAddImage(destref, iref, nullptr);
        CGImageDestinationFinalize(destref);
        CFRelease(destref);
        if (mdata) {
            [mdata writeToURL: nameUrl atomically: YES];
            mTempFiles.push_back(std::move(name));
        }
    }

}

bool
ImageCanvas::completeMovie()
{
    std::string cmdline;
    const char* fmt = nullptr;
    
    switch (mOutFormat) {
        case GIF: {
            if (mLoopCount == 1)
                mLoopCount = -1;
            if (mLoopCount > 1)
                --mLoopCount;
            
            fmt = "'%s' -hide_banner -framerate %.2f -i '%s/%%06d.png' -v warning "
                  "-vf 'split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse' "
                  "-loop %d -y '%s'";
            auto sz = std::snprintf(nullptr, 0, fmt, ffmpegBinary.c_str(), fps * 0.01,
                                    mTempDirectory.c_str(), mLoopCount, mOutputName.c_str());
            std::vector<char> buf(sz + 1);
            std::snprintf(buf.data(), sz + 1, fmt, ffmpegBinary.c_str(), fps * 0.01,
                          mTempDirectory.c_str(), mLoopCount, mOutputName.c_str());
            cmdline = buf.data();
            break;
        }
        case H264:
            fmt = "'%s' -hide_banner -framerate %.2f -i '%s/%%06d.png' -v warning "
                  "-c:v libx264 -preset slow -crf 20.0 -pix_fmt yuv420p -y '%s'";
            break;
        case ProRes422:
            fmt = "'%s' -hide_banner -framerate %.2f -i '%s/%%06d.png' -v warning "
                  "-c:v prores_ks -profile:v 2 -vendor apl0 -pix_fmt yuv422p10le -y '%s'";
            break;
        case ProRes4444:
            fmt = "'%s' -hide_banner -framerate %.2f -i '%s/%%06d.png' -v warning "
                  "-c:v prores_ks -profile:v 4 -vendor apl0 -pix_fmt yuva444p10le -y '%s'";
    }
    if (fmt && cmdline.empty()) {
        auto sz = std::snprintf(nullptr, 0, fmt, ffmpegBinary.c_str(), fps * 0.01,
                                mTempDirectory.c_str(), mOutputName.c_str());
        std::vector<char> buf(sz + 1);
        std::snprintf(buf.data(), sz + 1, fmt, ffmpegBinary.c_str(), fps * 0.01,
                      mTempDirectory.c_str(), mOutputName.c_str());
        cmdline = buf.data();
    }

    fs::path outfile_p(mOutputName);
    
    if (std::system(cmdline.c_str()) || !fs::exists(outfile_p)) {
        mError = true;
        return false;
    }
    return true;
}

// pngCanvas.h
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2012 John Horigan - john@glyphic.com
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

#include "abstractPngCanvas.h"
#include <string>
#include <vector>
#include "cfdg.h"

class pngCanvas : public abstractPngCanvas
{
public:
    enum OutputFormat { PNGfile = 0, SVGfile = 1, MOVfile = 2, BMPfile = 3, JSONfile = 5, GIFfile = 4 };
    enum QTcodec { H264 = 0, ProRes = 1, GIF = 2 };
    pngCanvas(const char* outfilename, bool quiet, int width, int height,
              PixelFormat pixfmt, bool crop, int frameCount, int variation,
              bool wallpaper, Renderer *r, int mx, int my, bool tmp,
              AbstractSystem& sys)
    : abstractPngCanvas(outfilename, quiet, width, height, pixfmt, crop,
                        frameCount, variation, wallpaper, r, mx, my),
      mOrigName(outfilename),
      usetmpfile(tmp),
      mSystem(sys)
    {
        if (tmp && frameCount) {
            mTempFiles.reserve(frameCount);
            mTempDirectory = sys.tempDirectoryForWrite("cfdg-temp-GIFframes-");
            if (mTempDirectory.empty()) {
                mError = true;
                std::cerr << "*** Cannot create temporary directory for GIF frames." << std::endl;
            }
        }
    }
    ~pngCanvas();

    std::string mTempDirectory;
    std::vector<std::string> mTempFiles;

    static std::string wcstomsb(const std::wstring& wstr);
    static std::wstring mbstowcs(const std::string& str);

    virtual bool completeMovie(int fps, int loops, OutputFormat fmt, QTcodec codec, bool alpha);
    static bool ffAvailable();
protected:
    virtual void output(const char * outfilename, int frame = -1) override;
    virtual FILE* makeTemp(int frame);
    std::string mOrigName;
private:
	bool usetmpfile;
protected:
    AbstractSystem& mSystem;
};


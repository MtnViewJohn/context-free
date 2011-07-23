// WinPngCanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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
//

#include "cfdg.h"
#include "aggCanvas.h"
#include "tiledCanvas.h"

class pngCanvas : public aggCanvas
{
public:
  pngCanvas(const char* outfilename, bool quiet, int width, int height, 
            aggCanvas::PixelFormat pixfmt, bool crop, int frameCount,
            int variation);
  ~pngCanvas();

  void output(const char * outfilename, int frame = -1);

  void start(bool clear, const agg::rgba& bk, int width, int height);
  void end();

  tiledCanvas* mTiledCanvas;
private:
  unsigned char* mData;
  static int CanvasCount;

  const char* mOutputFileName;
  int mStride;
  int mFrameCount;
  int mCurrentFrame;

  aggCanvas::PixelFormat mPixelFormat;
  agg::rgba mBackground;

  bool mCrop;
  bool mQuiet;
  int  mVariation;
};


#pragma once
// WinPngCanvas.h
// Context Free
// ---------------------
// Copyright (C) 2026 John Horigan - john@glyphic.com
//

#include "pngCanvas.h"

class WinPngCanvas : public pngCanvas
{
public:
    WinPngCanvas(const char* outfilename, bool quiet, int width, int height,
        PixelFormat pixfmt, bool crop, int frameCount, int variation,
        bool wallpaper, Renderer* r, int mx, int my, bool tmp,
        AbstractSystem& sys)
        : pngCanvas(outfilename, quiet, width, height, pixfmt, crop, frameCount,
            variation, wallpaper, r, mx, my, tmp, sys)
    {}
    virtual bool completeMovie(int fps, int loops, OutputFormat fmt, QTcodec codec, bool alpha) override;
    static bool ffAvailable();
protected:
    virtual FILE* makeTemp(int frame) override;
};


#pragma once
#include "pngCanvas.h"

class WinCanvas;

class WinJpegCanvas : public pngCanvas
{
public:
    WinJpegCanvas(const char* name, WinCanvas* canvas, bool crop, int variation, Renderer* r, int mx, int my, AbstractSystem& sys);
    virtual ~WinJpegCanvas();
    virtual void end() override;
    virtual void output(const char* outfilename, int frame = -1) override;
    int ActualWidth() const;
    int ActualHeight() const;
    int ActualOffset() const;
protected:
    WinCanvas* m_Canvas;
    enum class Encoder { libpng, gdiplus };
    Encoder mEncoder;
};


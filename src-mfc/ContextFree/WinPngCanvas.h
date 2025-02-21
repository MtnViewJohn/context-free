#pragma once
#include "pngCanvas.h"

class WinCanvas;

class WinPngCanvas : public pngCanvas
{
public:
    WinPngCanvas(const char* name, WinCanvas* canvas, bool crop, int variation, Renderer* r, int mx, int my);
    virtual ~WinPngCanvas();
    virtual void end() override;
    virtual void output(const char* outfilename, int frame = -1) override;
protected:
    WinCanvas* m_Canvas;
};


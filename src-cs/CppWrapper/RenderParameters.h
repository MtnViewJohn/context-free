#pragma once

namespace CppWrapper {
    public value class RenderParameters
    {
    public:
        enum class RenderActions { Render, Animate, SaveSVG };
        RenderActions action;
        bool    periodicUpdate;
        bool	animateZoom;
        bool    suppressDisplay;
        int		animateFrameCount;
        int     width;
        int     height;
        double  minimumSize;
        double  borderSize;
        int     animateWidth;
        int     animateHeight;
        int     length;
        double  frameRate;
        int     frame;
        bool    animateFrame;
        int     codec;
        bool    preview;
        bool    loop;
    };
}

#pragma once

class RenderParameters
{
public:
    RenderParameters();
    void Load();
    void Save();

    enum class RenderActions { Render, Animate, SaveSVG };
    enum class Codecs { H264 = 0, ProRes = 1 };

    RenderActions action = RenderActions::Render;
    bool    periodicUpdate = true;
    bool	animateZoom = false;
    bool    suppressDisplay = false;
    int		animateFrameCount = 150;
    int     width = 1000;
    int     height = 1000;
    double  minimumSize = 0.3;
    double  borderSize = 2.0;
    int     animateWidth = 640;
    int     animateHeight = 480;
    int     length = 10;
    int     frameRate = 15;
    int     frame = 1;
    bool    animateFrame = false;
    Codecs  codec = Codecs::H264;
    bool    preview = false;
    bool    loop = false;
};


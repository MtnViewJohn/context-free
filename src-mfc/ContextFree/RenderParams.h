#pragma once

class RenderParameters
{
public:
    RenderParameters();
    static void Load();
    static void Save();
    static void Modify(int& param, int v);
    static void Modify(bool& param, bool v);

    enum class RenderActions { Render, Animate, SaveSVG };
    enum class Codecs { H264 = 0, ProRes = 1 };

    RenderActions action = RenderActions::Render;
    int     width = 1000;
    int     height = 1000;
    int     variation = 1;
    bool    animateFrame = false;
    bool    renderSize = false;
    static bool     PeriodicUpdate;
    static bool	    AnimateZoom;
    static bool     SuppressDisplay;
    static int		AnimateFrameCount;
    static double   MinimumSize;
    static double   BorderSize;
    static int      RenderWidth;
    static int      RenderHeight;
    static int      AnimateWidth;
    static int      AnimateHeight;
    static int      MovieLength;
    static int      MovieFrameRate;
    static int      MovieFrame;
    static Codecs   Codec;
};


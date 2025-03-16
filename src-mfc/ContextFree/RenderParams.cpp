#include "pch.h"
#include "RenderParams.h"
#include <cwchar>
#include "variation.h"
#include "Animate.h"

namespace {
    double GetDouble(const CString& str, double def)
    {
        wchar_t* endp = nullptr;
        double v = std::wcstod(str, &endp);

        if (endp == (LPCTSTR)str || v == HUGE_VAL)
            return def;

        return v;
    }

    CString GetString(double v)
    {
        CString str;
        str.Format(_T("%g"), v);
        return str;
    }
};

bool     RenderParameters::PeriodicUpdate = true;
bool     RenderParameters::AnimateZoom = false;
bool     RenderParameters::SuppressDisplay = false;
int      RenderParameters::AnimateFrameCount = 150;
double   RenderParameters::MinimumSize = 0.3;
double   RenderParameters::BorderSize = 2.0;
int      RenderParameters::RenderWidth = 640;
int      RenderParameters::RenderHeight = 480;
int      RenderParameters::AnimateWidth = 640;
int      RenderParameters::AnimateHeight = 480;
int      RenderParameters::MovieLength = 10;
int      RenderParameters::MovieFrameRate = 15;
int      RenderParameters::MovieFrame = 1;
RenderParameters::Codecs   RenderParameters::Codec = RenderParameters::Codecs::H264;

RenderParameters::RenderParameters()
{
    static bool Loaded = false;
    if (!Loaded) {
        Load();
        Loaded = true;
    }
    variation = Variation::random();
}

void RenderParameters::Load()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    PeriodicUpdate = pApp->GetProfileIntW(pszKey, _T("ProgressiveRender"), 1) != 0;
    AnimateZoom = pApp->GetProfileIntW(pszKey, _T("AnimateZoom"), 0) != 0;
    SuppressDisplay = pApp->GetProfileIntW(pszKey, _T("SuppressDisplay"), 0) != 0;
    RenderWidth = pApp->GetProfileIntW(pszKey, _T("RenderWidth"), 1000);
    RenderHeight = pApp->GetProfileIntW(pszKey, _T("RenderHeight"), 1000);
    MinimumSize = GetDouble(pApp->GetProfileStringW(pszKey, _T("MinimumSize"), _T("0.3")), 0.3);
    BorderSize = GetDouble(pApp->GetProfileStringW(pszKey, _T("BorderWidth"), _T("2")), 2.0);
    AnimateWidth = pApp->GetProfileIntW(pszKey, _T("AnimateWidth"), 640);
    AnimateHeight = pApp->GetProfileIntW(pszKey, _T("AnimateHeight"), 480);
    MovieLength = pApp->GetProfileIntW(pszKey, _T("AnimateLength"), 10);
    MovieFrameRate = pApp->GetProfileIntW(pszKey, _T("AnimateFrameRate"), 15);
    MovieFrame = pApp->GetProfileIntW(pszKey, _T("AnimateFrame"), 1);
    Codec = (Codecs)pApp->GetProfileIntW(pszKey, _T("AnimateCodec"), 0);
    AnimateFrameCount = MovieLength * MovieFrameRate;

    RenderWidth = std::clamp(RenderWidth, 8, 32768);
    RenderHeight = std::clamp(RenderHeight, 8, 32768);
    MinimumSize = std::clamp(MinimumSize, 0.0, 10.0);
    BorderSize = std::clamp(BorderSize, -1.0, 2.0);
    AnimateWidth = std::clamp(AnimateWidth, 8, 32768);
    AnimateHeight = std::clamp(AnimateHeight, 8, 32768);
    if (std::find(Animate::Rates.begin(), Animate::Rates.end(), MovieFrameRate) == Animate::Rates.end())
        MovieFrameRate = 15;
    MovieFrame = std::clamp(MovieFrame, 1, AnimateFrameCount);
    Codec = (Codecs)std::clamp((int)Codec, 0, 1);
}

void RenderParameters::Save()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileInt(pszKey, _T("ProgressiveRender"), PeriodicUpdate);
    pApp->WriteProfileInt(pszKey, _T("AnimateZoom"), AnimateZoom);
    pApp->WriteProfileInt(pszKey, _T("SuppressDisplay"), SuppressDisplay);
    pApp->WriteProfileInt(pszKey, _T("RenderWidth"), RenderWidth);
    pApp->WriteProfileInt(pszKey, _T("RenderHeight"), RenderHeight);
    pApp->WriteProfileStringW(pszKey, _T("MinimumSize"), GetString(MinimumSize));
    pApp->WriteProfileStringW(pszKey, _T("BorderWidth"), GetString(BorderSize));
    pApp->WriteProfileInt(pszKey, _T("AnimateWidth"), AnimateWidth);
    pApp->WriteProfileInt(pszKey, _T("AnimateHeight"), AnimateHeight);
    pApp->WriteProfileInt(pszKey, _T("AnimateLength"), MovieLength);
    pApp->WriteProfileInt(pszKey, _T("AnimateFrameRate"), MovieFrameRate);
    pApp->WriteProfileInt(pszKey, _T("AnimateFrame"), MovieFrame);
    pApp->WriteProfileInt(pszKey, _T("AnimateCodec"), (int)Codec);
}

// Capture a write to a parameter and flush it to the registry if the value
// actually changes
void RenderParameters::Modify(int& param, int v)
{
    if (param != v) {
        param = v;
        Save();
    }
}
void RenderParameters::Modify(bool& param, bool v)
{
    if (param != v) {
        param = v;
        Save();
    }
}

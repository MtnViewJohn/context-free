#include "pch.h"
#include "RenderParams.h"
#include <cwchar>

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

RenderParameters::RenderParameters()
{
    Load();
}

void RenderParameters::Load()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Render");

    periodicUpdate = pApp->GetProfileIntW(pszKey, _T("ProgressiveRender"), 1) != 0;
    animateZoom = pApp->GetProfileIntW(pszKey, _T("AnimateZoom"), 0) != 0;
    suppressDisplay = pApp->GetProfileIntW(pszKey, _T("SuppressDisplay"), 0) != 0;
    width = pApp->GetProfileIntW(pszKey, _T("RenderWidth"), 1000);
    height = pApp->GetProfileIntW(pszKey, _T("RenderHeight"), 1000);
    minimumSize = GetDouble(pApp->GetProfileStringW(pszKey, _T("MinimumSize"), _T("0.3")), 0.3);
    borderSize = GetDouble(pApp->GetProfileStringW(pszKey, _T("BorderWidth"), _T("2")), 2.0);
    animateWidth = pApp->GetProfileIntW(pszKey, _T("AnimateWidth"), 640);
    animateHeight = pApp->GetProfileIntW(pszKey, _T("AnimateHeight"), 480);
    length = pApp->GetProfileIntW(pszKey, _T("AnimateLength"), 10);
    frameRate = pApp->GetProfileIntW(pszKey, _T("AnimateFrameRate"), 15);
    frame = pApp->GetProfileIntW(pszKey, _T("AnimateFrame"), 1);
    codec = (Codecs)pApp->GetProfileIntW(pszKey, _T("AnimateCodec"), 0);
    loop = pApp->GetProfileIntW(pszKey, _T("AnimatePreviewLoop"), 0) != 0;
    preview = pApp->GetProfileIntW(pszKey, _T("AnimatePreview"), 0) != 0;
    animateFrameCount = length * frameRate;
}

void RenderParameters::Save()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Render");

    pApp->WriteProfileInt(pszKey, _T("ProgressiveRender"), periodicUpdate);
    pApp->WriteProfileInt(pszKey, _T("AnimateZoom"), animateZoom);
    pApp->WriteProfileInt(pszKey, _T("SuppressDisplay"), suppressDisplay);
    pApp->WriteProfileInt(pszKey, _T("RenderWidth"), width);
    pApp->WriteProfileInt(pszKey, _T("RenderHeight"), height);
    pApp->WriteProfileStringW(pszKey, _T("MinimumSize"), GetString(minimumSize));
    pApp->WriteProfileStringW(pszKey, _T("BorderWidth"), GetString(borderSize));
    pApp->WriteProfileInt(pszKey, _T("AnimateWidth"), animateWidth);
    pApp->WriteProfileInt(pszKey, _T("AnimateHeight"), animateHeight);
    pApp->WriteProfileInt(pszKey, _T("AnimateLength"), length);
    pApp->WriteProfileInt(pszKey, _T("AnimateFrameRate"), frameRate);
    pApp->WriteProfileInt(pszKey, _T("AnimateFrame"), frame);
    pApp->WriteProfileInt(pszKey, _T("AnimateCodec"), (int)codec);
    pApp->WriteProfileInt(pszKey, _T("AnimatePreviewLoop"), loop);
    pApp->WriteProfileInt(pszKey, _T("AnimatePreview"), preview);
}

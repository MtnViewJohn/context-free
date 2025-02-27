#include "pch.h"
#include "Settings.h"

Settings::LaunchActions Settings::AtLaunch = Settings::LaunchActions::Welcome;
bool Settings::RenderOnOpen = true;

Settings::Settings()
{
    static bool Loaded = false;
    if (!Loaded) {
        Load();
        Loaded = true;
    }
}

void Settings::Load()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    AtLaunch = (LaunchActions)pApp->GetProfileIntW(pszKey, _T("LaunchAction"), (int)LaunchActions::Welcome);
    RenderOnOpen = pApp->GetProfileIntW(pszKey, _T("RenderOnOpen"), 1) != 0;

    RenderParameters::Load();
    EditorParams::Load();
}

void Settings::Save(bool justme)
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileInt(pszKey, _T("LaunchAction"), (int)AtLaunch);
    pApp->WriteProfileInt(pszKey, _T("RenderOnOpen"), RenderOnOpen);

    if (!justme) {
        RenderParameters::Save();
        EditorParams::Save();
    }
}

// Capture a write to a parameter and flush it to the registry if the value
// actually changes
void Settings::Modify(int& param, int v)
{
    if (param != v) {
        param = v;
        Save(true);
    }
}
void Settings::Modify(bool& param, bool v)
{
    if (param != v) {
        param = v;
        Save(true);
    }
}


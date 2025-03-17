#include "pch.h"
#include "Settings.h"

Settings::LaunchActions Settings::AtLaunch = Settings::LaunchActions::Welcome;
bool Settings::RenderOnOpen = true;
int Settings::EditorWidth = 30;
int Settings::WindowWidth = 0;
int Settings::WindowHeight = 0;

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
    EditorWidth = pApp->GetProfileIntW(pszKey, _T("EditorWidth"), 30);
    WindowWidth = pApp->GetProfileIntW(pszKey, _T("WindowWidth"), 0);
    WindowHeight = pApp->GetProfileIntW(pszKey, _T("WindowHeight"), 0);

    AtLaunch = (LaunchActions)std::clamp((int)AtLaunch, 0, 2);
    EditorWidth = std::clamp(EditorWidth, 15, 85);
    if (WindowWidth != 0 && WindowWidth != INT_MAX)
        WindowWidth = std::clamp(WindowWidth, 300, GetSystemMetrics(SM_CXMAXIMIZED));
    if (WindowHeight != 0 && WindowHeight != INT_MAX)
        WindowHeight = std::clamp(WindowHeight, 300, GetSystemMetrics(SM_CYMAXIMIZED));

    RenderParameters::Load();
    EditorParams::Load();
}

void Settings::Save(bool justme)
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileInt(pszKey, _T("LaunchAction"), (int)AtLaunch);
    pApp->WriteProfileInt(pszKey, _T("RenderOnOpen"), RenderOnOpen);
    pApp->WriteProfileInt(pszKey, _T("EditorWidth"), EditorWidth);
    pApp->WriteProfileInt(pszKey, _T("WindowWidth"), WindowWidth);
    pApp->WriteProfileInt(pszKey, _T("WindowHeight"), WindowHeight);

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


#include "pch.h"
#include "EditorParams.h"
#include <string>

int EditorParams::FontSize = 10;
CString EditorParams::FontName = _T("Courier New");
int EditorParams::TabWidth = 4;

EditorParams::EditorParams()
{
    static bool Loaded = false;
    if (!Loaded) {
        Load();
        Loaded = true;
    }
}

void EditorParams::Load()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    FontSize = pApp->GetProfileIntW(pszKey, _T("FontSize"), 10);
    FontName = pApp->GetProfileStringW(pszKey, _T("FontName"), _T("Courier New"));
    TabWidth = pApp->GetProfileIntW(pszKey, _T("TabWidth"), 4);
}

void EditorParams::Save()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileInt(pszKey, _T("FontSize"), FontSize);
    pApp->WriteProfileStringW(pszKey, _T("FontName"), FontName);
    pApp->WriteProfileInt(pszKey, _T("TabWidth"), TabWidth);
}

bool EditorParams::SetFont(CString name, CString& fname, int& fsize)
{
    std::wstring wname((LPCTSTR)name);
    auto div = wname.find_last_of(L' ');

    if (div != std::wstring::npos) {
        wchar_t* end = nullptr;
        int maybeSize = std::wcstol(wname.c_str() + div + 1, &end, 10);
        if (maybeSize > 0 && end && *end == L'\0') {
            fsize = maybeSize;
            wname[div] = L'\0';
            fname = wname.c_str();
            return true;
        }
    }
    return false;
}

CString EditorParams::GetFont(CString& fname, int& fsize)
{
    CString name;
    name.Format(_T("%s %d"), (LPCTSTR)fname, fsize);
    return name;
}


#include "pch.h"
#include "EditorParams.h"
#include <string>

namespace {
    int CALLBACK EnumFontFamProc(CONST LOGFONTW*, CONST TEXTMETRICW*, DWORD, LPARAM lParam)
    {
        int* count = reinterpret_cast<int*>(lParam);
        ++(*count);
        return *count;
    }
}

int EditorParams::FontSize = 10;
CString EditorParams::FontName = _T("Courier New");
int EditorParams::TabWidth = 4;

bool EditorParams::DefaultBold = false;
bool EditorParams::DefaultItalic = false;
bool EditorParams::CommentBold = false;
bool EditorParams::CommentItalic = true;
bool EditorParams::SymbolBold = false;
bool EditorParams::SymbolItalic = false;
bool EditorParams::IdentBold = false;
bool EditorParams::IdentItalic = false;
bool EditorParams::KeywordBold = true;
bool EditorParams::KeywordItalic = false;
bool EditorParams::BuiltinBold = true;
bool EditorParams::BuiltinItalic = false;
bool EditorParams::FileBold = false;
bool EditorParams::FileItalic = false;
bool EditorParams::NumberBold = false;
bool EditorParams::NumberItalic = false;
COLORREF EditorParams::DefaultColor = 0x0;
COLORREF EditorParams::CommentColor = 0x0097BF7;
COLORREF EditorParams::SymbolColor = 0x0101010;
COLORREF EditorParams::IdentColor = 0x000567F;
COLORREF EditorParams::KeywordColor = 0x056007F;
COLORREF EditorParams::BuiltinColor = 0x0007F00;
COLORREF EditorParams::FileColor = 0x0FFAA3E;
COLORREF EditorParams::NumberColor = 0x07F7F00;

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

    DefaultBold   = pApp->GetProfileIntW(pszKey, _T("DefaultBold"), 0);
    DefaultItalic = pApp->GetProfileIntW(pszKey, _T("DefaultItalic"), 0);
    CommentBold   = pApp->GetProfileIntW(pszKey, _T("CommentBold"), 0);
    CommentItalic = pApp->GetProfileIntW(pszKey, _T("CommentItalic"), 1);
    SymbolBold   = pApp->GetProfileIntW(pszKey, _T("SymbolBold"), 0);
    SymbolItalic = pApp->GetProfileIntW(pszKey, _T("SymbolItalic"), 0);
    IdentBold   = pApp->GetProfileIntW(pszKey, _T("IdentBold"), 0);
    IdentItalic = pApp->GetProfileIntW(pszKey, _T("IdentItalic"), 0);
    KeywordBold   = pApp->GetProfileIntW(pszKey, _T("KeywordBold"), 1);
    KeywordItalic = pApp->GetProfileIntW(pszKey, _T("KeywordItalic"), 0);
    BuiltinBold   = pApp->GetProfileIntW(pszKey, _T("BuiltinBold"), 1);
    BuiltinItalic = pApp->GetProfileIntW(pszKey, _T("BuiltinItalic"), 0);
    FileBold   = pApp->GetProfileIntW(pszKey, _T("FileBold"), 0);
    FileItalic = pApp->GetProfileIntW(pszKey, _T("FileItalic"), 0);
    NumberBold   = pApp->GetProfileIntW(pszKey, _T("NumberBold"), 0);
    NumberItalic = pApp->GetProfileIntW(pszKey, _T("NumberItalic"), 0);

    DefaultColor = pApp->GetProfileIntW(pszKey, _T("DefaultColor"), 0x0);
    CommentColor = pApp->GetProfileIntW(pszKey, _T("CommentColor"), 0x0097BF7);
    SymbolColor = pApp->GetProfileIntW(pszKey, _T("SymbolColor"), 0x0101010);
    IdentColor = pApp->GetProfileIntW(pszKey, _T("IdentColor"), 0x000567F);
    KeywordColor = pApp->GetProfileIntW(pszKey, _T("KeywordColor"), 0x056007F);
    BuiltinColor = pApp->GetProfileIntW(pszKey, _T("BuiltinColor"), 0x0007F00);
    FileColor = pApp->GetProfileIntW(pszKey, _T("FileColor"), 0x0FFAA3E);
    NumberColor = pApp->GetProfileIntW(pszKey, _T("NumberColor"), 0x07F7F00);

    FontSize = std::clamp(FontSize, 6, 30);

    if (FontName.GetLength() < 3 || FontName.GetLength() > 31)
        FontName = L"Courier New";
    LOGFONT logFont = { 0 };
    logFont.lfCharSet = SC_CHARSET_DEFAULT;
    ::wcsncpy_s(logFont.lfFaceName, (LPCTSTR)FontName, 32);
    int fontCount = 0;
    if (::EnumFontFamilies(::GetDC(NULL), (LPCTSTR)FontName, &EnumFontFamProc, (LPARAM)(&fontCount)) == 0)
        FontName = L"Courier New";

    TabWidth = std::clamp(TabWidth, 1, 8);

    DefaultColor &= 0xFFFFFF;
    CommentColor &= 0xFFFFFF;
    SymbolColor &= 0xFFFFFF;
    IdentColor &= 0xFFFFFF;
    KeywordColor &= 0xFFFFFF;
    BuiltinColor &= 0xFFFFFF;
    FileColor &= 0xFFFFFF;
    NumberColor &= 0xFFFFFF;
}

void EditorParams::Save()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileInt(pszKey, _T("FontSize"), FontSize);
    pApp->WriteProfileStringW(pszKey, _T("FontName"), FontName);
    pApp->WriteProfileInt(pszKey, _T("TabWidth"), TabWidth);

    pApp->WriteProfileInt(pszKey, _T("DefaultBold"), DefaultBold);
    pApp->WriteProfileInt(pszKey, _T("DefaultItalic"), DefaultItalic);
    pApp->WriteProfileInt(pszKey, _T("CommentBold"), CommentBold);
    pApp->WriteProfileInt(pszKey, _T("CommentItalic"), CommentItalic);
    pApp->WriteProfileInt(pszKey, _T("SymbolBold"), SymbolBold);
    pApp->WriteProfileInt(pszKey, _T("SymbolItalic"), SymbolItalic);
    pApp->WriteProfileInt(pszKey, _T("IdentBold"), IdentBold);
    pApp->WriteProfileInt(pszKey, _T("IdentItalic"), IdentItalic);
    pApp->WriteProfileInt(pszKey, _T("KeywordBold"), KeywordBold);
    pApp->WriteProfileInt(pszKey, _T("KeywordItalic"), KeywordItalic);
    pApp->WriteProfileInt(pszKey, _T("BuiltinBold"), BuiltinBold);
    pApp->WriteProfileInt(pszKey, _T("BuiltinItalic"), BuiltinItalic);
    pApp->WriteProfileInt(pszKey, _T("FileBold"), FileBold);
    pApp->WriteProfileInt(pszKey, _T("FileItalic"), FileItalic);
    pApp->WriteProfileInt(pszKey, _T("NumberBold"), NumberBold);
    pApp->WriteProfileInt(pszKey, _T("NumberItalic"), NumberItalic);

    pApp->WriteProfileInt(pszKey, _T("DefaultColor"), DefaultColor);
    pApp->WriteProfileInt(pszKey, _T("CommentColor"), CommentColor);
    pApp->WriteProfileInt(pszKey, _T("SymbolColor"), SymbolColor);
    pApp->WriteProfileInt(pszKey, _T("IdentColor"), IdentColor);
    pApp->WriteProfileInt(pszKey, _T("KeywordColor"), KeywordColor);
    pApp->WriteProfileInt(pszKey, _T("BuiltinColor"), BuiltinColor);
    pApp->WriteProfileInt(pszKey, _T("FileColor"), FileColor);
    pApp->WriteProfileInt(pszKey, _T("NumberColor"), NumberColor);
}

bool EditorParams::SetFont(CString name, CString& fname, int& fsize)
{
    auto div = name.ReverseFind(L' ');

    if (div != -1) {
        wchar_t* wname = name.LockBuffer();
        wchar_t* end = nullptr;
        int maybeSize = std::wcstol(wname + div + 1, &end, 10);
        name.UnlockBuffer();
        if (maybeSize > 0 && end && *end == L'\0') {
            fsize = maybeSize;
            fname = name.Mid(0, div);
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


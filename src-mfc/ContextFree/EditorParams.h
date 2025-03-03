#pragma once

class EditorParams
{
public:
    EditorParams();
    static void Load();
    static void Save();

    static int FontSize;
    static CString FontName;
    static int TabWidth;
    static bool SetFont(CString name, CString& fname = FontName, int& fsize = FontSize);
    static CString GetFont(CString& fname = FontName, int& fsize = FontSize);
};


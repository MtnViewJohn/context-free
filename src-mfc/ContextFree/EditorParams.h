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

    static bool DefaultBold;
    static bool DefaultItalic;
    static bool CommentBold;
    static bool CommentItalic;
    static bool SymbolBold;
    static bool SymbolItalic;
    static bool IdentBold;
    static bool IdentItalic;
    static bool KeywordBold;
    static bool KeywordItalic;
    static bool BuiltinBold;
    static bool BuiltinItalic;
    static bool FileBold;
    static bool FileItalic;
    static bool NumberBold;
    static bool NumberItalic;
    static COLORREF DefaultColor;
    static COLORREF CommentColor;
    static COLORREF SymbolColor;
    static COLORREF IdentColor;
    static COLORREF KeywordColor;
    static COLORREF BuiltinColor;
    static COLORREF FileColor;
    static COLORREF NumberColor;
};


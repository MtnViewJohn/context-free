// PrefsPageEditor.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "PrefsPageEditor.h"
#include "EditorParams.h"
#include <vector>
#include "CFFontDialog.h"

// PrefsPageEditor dialog

IMPLEMENT_DYNAMIC(PrefsPageEditor, CPropertyPage)

PrefsPageEditor::PrefsPageEditor()
	: CPropertyPage(IDD_PREFS_EDITOR)
	, m_CRefMap{
		{IDC_DEFAULT_COLOR, &m_cDefaultColor},
		{IDC_COMMENT_COLOR, &m_cCommentColor},
		{IDC_SYMBOL_COLOR, &m_cSymbolColor},
		{IDC_IDENT_COLOR, &m_cIdentColor},
		{IDC_KEYWORD_COLOR, &m_cKeywordColor},
		{IDC_BUILTIN_COLOR, &m_cBuiltinColor},
		{IDC_FILE_COLOR, &m_cFileColor},
		{IDC_NUMBER_COLOR, &m_cNumberColor}
	}
	, m_CBtnMap{
		{IDC_DEFAULT_COLOR, &m_ctrlDefaultColor},
		{IDC_COMMENT_COLOR, &m_ctrlCommentColor},
		{IDC_SYMBOL_COLOR, &m_ctrlSymbolColor},
		{IDC_IDENT_COLOR, &m_ctrlIdentColor},
		{IDC_KEYWORD_COLOR, &m_ctrlKeywordColor},
		{IDC_BUILTIN_COLOR, &m_ctrlBuiltinColor},
		{IDC_FILE_COLOR, &m_ctrlFileColor},
		{IDC_NUMBER_COLOR, &m_ctrlNumberColor}
	}
	, m_bBoldMap{
		{IDC_DEFAULT_COLOR, &m_bDefaultBold},
		{IDC_COMMENT_COLOR, &m_bCommentBold},
		{IDC_SYMBOL_COLOR, &m_bSymbolBold},
		{IDC_IDENT_COLOR, &m_bIdentBold},
		{IDC_KEYWORD_COLOR, &m_bKeywordBold},
		{IDC_BUILTIN_COLOR, &m_bBuiltinBold},
		{IDC_FILE_COLOR, &m_bFileBold},
		{IDC_NUMBER_COLOR, &m_bNumberBold}
	}
	, m_bItalicMap{
		{IDC_DEFAULT_COLOR, &m_bDefaultItalic},
		{IDC_COMMENT_COLOR, &m_bCommentItalic},
		{IDC_SYMBOL_COLOR, &m_bSymbolItalic},
		{IDC_IDENT_COLOR, &m_bIdentItalic},
		{IDC_KEYWORD_COLOR, &m_bKeywordItalic},
		{IDC_BUILTIN_COLOR, &m_bBuiltinItalic},
		{IDC_FILE_COLOR, &m_bFileItalic},
		{IDC_NUMBER_COLOR, &m_bNumberItalic}
	}
	, m_CPickerMap{
		{IDC_RED_PICKER, &m_ctrlRedPicker},
		{IDC_GREEN_PICKER, &m_ctrlGreenPicker},
		{IDC_BLUE_PICKER, &m_ctrlBluePicker}
	}
	, m_iCurrentColor(IDC_DEFAULT_COLOR)
	, m_sFontName(EditorParams::GetFont())
	, m_iTabWidth(EditorParams::TabWidth)
	, m_bDefaultBold(EditorParams::DefaultBold)
	, m_bDefaultItalic(EditorParams::DefaultItalic)
	, m_bCommentBold(EditorParams::CommentBold)
	, m_bCommentItalic(EditorParams::CommentItalic)
	, m_bSymbolBold(EditorParams::SymbolBold)
	, m_bSymbolItalic(EditorParams::SymbolItalic)
	, m_bIdentBold(EditorParams::IdentBold)
	, m_bIdentItalic(EditorParams::IdentItalic)
	, m_bKeywordBold(EditorParams::KeywordBold)
	, m_bKeywordItalic(EditorParams::KeywordItalic)
	, m_bBuiltinBold(EditorParams::BuiltinBold)
	, m_bBuiltinItalic(EditorParams::BuiltinItalic)
	, m_bFileBold(EditorParams::FileBold)
	, m_bFileItalic(EditorParams::FileItalic)
	, m_bNumberBold(EditorParams::NumberBold)
	, m_bNumberItalic(EditorParams::NumberItalic)
	, m_cDefaultColor(EditorParams::DefaultColor)
	, m_cCommentColor(EditorParams::CommentColor)
	, m_cSymbolColor(EditorParams::SymbolColor)
	, m_cIdentColor(EditorParams::IdentColor)
	, m_cKeywordColor(EditorParams::KeywordColor)
	, m_cBuiltinColor(EditorParams::BuiltinColor)
	, m_cFileColor(EditorParams::FileColor)
	, m_cNumberColor(EditorParams::NumberColor)
	, m_sRGBtext(_T(""))
{
	BOOL succ = m_Font.CreatePointFont(EditorParams::FontSize * 10, (LPCTSTR)EditorParams::FontName);
}

PrefsPageEditor::~PrefsPageEditor()
{
}

void PrefsPageEditor::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FONTNAME, m_sFontName);
	DDX_Control(pDX, IDC_FONTNAME, m_ctrlFontName);
	DDX_Control(pDX, IDC_TABSPIN, m_ctrlTabSpin);
	DDX_Check(pDX, IDC_DEFAULT_BOLD, m_bDefaultBold);
	DDX_Check(pDX, IDC_DEFAULT_ITALIC, m_bDefaultItalic);
	DDX_Check(pDX, IDC_COMMENT_BOLD, m_bCommentBold);
	DDX_Check(pDX, IDC_COMMENT_ITALIC, m_bCommentItalic);
	DDX_Check(pDX, IDC_SYMBOL_BOLD, m_bSymbolBold);
	DDX_Check(pDX, IDC_SYMBOL_ITALIC, m_bSymbolItalic);
	DDX_Check(pDX, IDC_IDENT_BOLD, m_bIdentBold);
	DDX_Check(pDX, IDC_IDENT_ITALIC, m_bIdentItalic);
	DDX_Check(pDX, IDC_KEYWORD_BOLD, m_bKeywordBold);
	DDX_Check(pDX, IDC_KEYWORD_ITALIC, m_bKeywordItalic);
	DDX_Check(pDX, IDC_BUILTIN_BOLD, m_bBuiltinBold);
	DDX_Check(pDX, IDC_BUILTIN_ITALIC, m_bBuiltinItalic);
	DDX_Check(pDX, IDC_FILE_BOLD, m_bFileBold);
	DDX_Check(pDX, IDC_FILE_ITALIC, m_bFileItalic);
	DDX_Check(pDX, IDC_NUMBER_BOLD, m_bNumberBold);
	DDX_Check(pDX, IDC_NUMBER_ITALIC, m_bNumberItalic);
	DDX_Control(pDX, IDC_DEFAULT_COLOR, m_ctrlDefaultColor);
	DDX_Control(pDX, IDC_COMMENT_COLOR, m_ctrlCommentColor);
	DDX_Control(pDX, IDC_SYMBOL_COLOR, m_ctrlSymbolColor);
	DDX_Control(pDX, IDC_IDENT_COLOR, m_ctrlIdentColor);
	DDX_Control(pDX, IDC_KEYWORD_COLOR, m_ctrlKeywordColor);
	DDX_Control(pDX, IDC_BUILTIN_COLOR, m_ctrlBuiltinColor);
	DDX_Control(pDX, IDC_FILE_COLOR, m_ctrlFileColor);
	DDX_Control(pDX, IDC_NUMBER_COLOR, m_ctrlNumberColor);
	DDX_Control(pDX, IDC_COLOR_PICKER, m_ctrlColorPicker);
	DDX_Control(pDX, IDC_LUM_PICKER, m_ctrlLumPicker);
	DDX_Control(pDX, IDC_RED_PICKER, m_ctrlRedPicker);
	DDX_Control(pDX, IDC_GREEN_PICKER, m_ctrlGreenPicker);
	DDX_Control(pDX, IDC_BLUE_PICKER, m_ctrlBluePicker);
	DDX_Text(pDX, IDC_RGB_TEXT, m_sRGBtext);
}


BEGIN_MESSAGE_MAP(PrefsPageEditor, CPropertyPage)
	ON_BN_CLICKED(IDC_FONTCHANGE, &PrefsPageEditor::OnClickedFontchange)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TABSPIN, &PrefsPageEditor::OnTabWidthUD)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_DEFAULT_COLOR, IDC_NUMBER_COLOR, &PrefsPageEditor::OnColorBtn)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_DEFAULT_BOLD, IDC_NUMBER_ITALIC, &PrefsPageEditor::OnTypeBtn)
	ON_BN_CLICKED(IDC_COLOR_PICKER, &PrefsPageEditor::OnClickedColorPicker)
	ON_BN_CLICKED(IDC_LUM_PICKER, &PrefsPageEditor::OnClickedLumPicker)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RED_PICKER, IDC_BLUE_PICKER, &PrefsPageEditor::OnClickedRGBPicker)
	ON_MESSAGE(WM_CTLCOLORSTATIC, &PrefsPageEditor::OnStaticCtl)
END_MESSAGE_MAP()


// PrefsPageEditor message handlers

void PrefsPageEditor::OnOK()
{
	EditorParams::SetFont(m_sFontName);
	EditorParams::TabWidth = m_iTabWidth;
	EditorParams::DefaultBold = m_bDefaultBold;
	EditorParams::DefaultItalic = m_bDefaultItalic;
	EditorParams::CommentBold = m_bCommentBold;
	EditorParams::CommentItalic = m_bCommentItalic;
	EditorParams::SymbolBold = m_bSymbolBold;
	EditorParams::SymbolItalic = m_bSymbolItalic;
	EditorParams::IdentBold = m_bIdentBold;
	EditorParams::IdentItalic = m_bIdentItalic;
	EditorParams::KeywordBold = m_bKeywordBold;
	EditorParams::KeywordItalic = m_bKeywordItalic;
	EditorParams::BuiltinBold = m_bBuiltinBold;
	EditorParams::BuiltinItalic = m_bBuiltinItalic;
	EditorParams::FileBold = m_bFileBold;
	EditorParams::FileItalic = m_bFileItalic;
	EditorParams::NumberBold = m_bNumberBold;
	EditorParams::NumberItalic = m_bNumberItalic;
	EditorParams::DefaultColor = m_cDefaultColor;
	EditorParams::CommentColor = m_cCommentColor;
	EditorParams::SymbolColor = m_cSymbolColor;
	EditorParams::IdentColor = m_cIdentColor;
	EditorParams::KeywordColor = m_cKeywordColor;
	EditorParams::BuiltinColor = m_cBuiltinColor;
	EditorParams::FileColor = m_cFileColor;
	EditorParams::NumberColor = m_cNumberColor;
	EditorParams::Save();

	CPropertyPage::OnOK();
}

void PrefsPageEditor::OnClickedFontchange()
{
	CString fname = _T("Courier New");
	int fsize = 10;
	if (!EditorParams::SetFont(m_sFontName, fname, fsize) || fname.GetLength() > 31) {
		MessageBeep(MB_ICONEXCLAMATION);
		MessageBoxW(_T("Cannot parse font name, using default."), NULL, MB_ICONEXCLAMATION);
	}

	LOGFONT logFont = { 0 };
	CClientDC dc(this);
	logFont.lfHeight = -((dc.GetDeviceCaps(LOGPIXELSY) * fsize) / 72);
	logFont.lfWeight = FW_NORMAL;
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	::wcsncpy_s(logFont.lfFaceName, (LPCTSTR)fname, 32);
	CFFontDialog fDlg(&logFont, CF_FIXEDPITCHONLY | CF_INITTOLOGFONTSTRUCT |
							   CF_SCREENFONTS | CF_NOSCRIPTSEL | CF_NOSTYLESEL);

	if (fDlg.DoModal() == IDOK) {
		fname = fDlg.GetFaceName();
		fsize = (fDlg.GetSize() + 5) / 10;
		m_sFontName = EditorParams::GetFont(fname, fsize);
		m_Font.Detach();
		logFont.lfWeight = *m_bBoldMap[m_iCurrentColor] ? FW_BOLD : FW_NORMAL;
		logFont.lfItalic = *m_bItalicMap[m_iCurrentColor];
		m_Font.CreateFontIndirectW(&logFont);
		m_ctrlFontName.SetFont(&m_Font);
		UpdateData(FALSE);
		m_FontChanged = true;
	}
}

void PrefsPageEditor::UpdateFont()
{
	CString fname = _T("Courier New");
	int fsize = 10;
	if (!EditorParams::SetFont(m_sFontName, fname, fsize) || fname.GetLength() > 31)
		return;
	LOGFONT logFont = { 0 };
	logFont.lfHeight = fsize * 10;
	logFont.lfWeight = *m_bBoldMap[m_iCurrentColor] ? FW_BOLD : FW_NORMAL;
	logFont.lfItalic = *m_bItalicMap[m_iCurrentColor];
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
	::wcsncpy_s(logFont.lfFaceName, (LPCTSTR)fname, 32);
	m_Font.Detach();
	m_Font.CreatePointFontIndirect(&logFont);
	m_ctrlFontName.SetFont(&m_Font);
}

BOOL PrefsPageEditor::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_ctrlFontName.SetFont(&m_Font);

	m_ctrlTabSpin.SetRange(1, 1000);
	m_ctrlTabSpin.SetPos(500);

	SetDlgItemInt(IDC_TABWIDTH, m_iTabWidth, 0);

	for (UINT id = IDC_DEFAULT_COLOR; id <= IDC_NUMBER_COLOR; ++id)
		UpdateColor(*m_CRefMap[id], id);

	m_ctrlColorPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::PICKER);
	m_ctrlLumPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::LUMINANCE);
	m_ctrlRedPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::RED);
	m_ctrlGreenPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::GREEN);
	m_ctrlBluePicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::BLUE);
	m_CBtnMap[m_iCurrentColor]->SetCheck(BST_CHECKED);
	OnColorBtn(m_iCurrentColor);

	// Create system palette:
	CClientDC dc(this);

	int nColors = 256; // Use 256 first entries
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
	LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = (USHORT)nColors;

	::GetSystemPaletteEntries(dc.GetSafeHdc(), 0, nColors, pLP->palPalEntry);

	m_Palette.CreatePalette(pLP);

	delete[] pLP;

	m_ctrlColorPicker.SetPalette(&m_Palette);
	m_ctrlLumPicker.SetPalette(&m_Palette);
	m_ctrlRedPicker.SetPalette(&m_Palette);
	m_ctrlGreenPicker.SetPalette(&m_Palette);
	m_ctrlBluePicker.SetPalette(&m_Palette);

	return TRUE;
}

void PrefsPageEditor::OnTabWidthUD(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMUPDOWN pUpDown = (LPNMUPDOWN)pNotifyStruct;
	if (pUpDown->iDelta > 0 && m_iTabWidth < 8) {
		++m_iTabWidth;
		SetDlgItemInt(IDC_TABWIDTH, m_iTabWidth, 0);
	}
	if (pUpDown->iDelta < 0 && m_iTabWidth > 1) {
		--m_iTabWidth;
		SetDlgItemInt(IDC_TABWIDTH, m_iTabWidth, 0);
	}
}

void PrefsPageEditor::OnColorBtn(UINT id)
{
	ASSERT(m_CBtnMap.contains(id) && m_CRefMap.contains(id));
	m_CBtnMap[m_iCurrentColor]->SetWindowTextW(_T(""));
	m_CBtnMap[id]->SetWindowTextW(_T("◯"));
	bool updateFont = *m_bBoldMap[m_iCurrentColor] != *m_bBoldMap[id] ||
					  *m_bItalicMap[m_iCurrentColor] != *m_bItalicMap[id];
	m_iCurrentColor = id;
	COLORREF col = *m_CRefMap[id];
	m_ctrlColorPicker.SetColor(col);
	m_ctrlLumPicker.SetColor(col);
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	UpdateRGBText(col);
	if (updateFont)
		UpdateFont();
}

void PrefsPageEditor::OnTypeBtn(UINT id)
{
	UpdateData(TRUE);
	if (id - IDC_DEFAULT_BOLD   == m_iCurrentColor - IDC_DEFAULT_COLOR ||
		id - IDC_DEFAULT_ITALIC == m_iCurrentColor - IDC_DEFAULT_COLOR)
	{
		UpdateFont();
	}
}

void PrefsPageEditor::OnClickedColorPicker()
{
	COLORREF col = m_ctrlColorPicker.GetColor();
	m_ctrlLumPicker.SetColor(col);
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	UpdateColor(col, m_iCurrentColor);
}

void PrefsPageEditor::OnClickedLumPicker()
{
	m_ctrlColorPicker.SetLuminance(m_ctrlLumPicker.GetLuminance());
	COLORREF col = m_ctrlLumPicker.GetColor();
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	UpdateColor(col, m_iCurrentColor);
}

void PrefsPageEditor::OnClickedRGBPicker(UINT id)
{
	COLORREF col = m_CPickerMap[id]->GetColor();
	m_ctrlColorPicker.SetColor(col);
	m_ctrlLumPicker.SetColor(col);
	if (id != IDC_RED_PICKER  )
		m_ctrlRedPicker.SetColor(col);
	if (id != IDC_GREEN_PICKER)
		m_ctrlGreenPicker.SetColor(col);
	if (id != IDC_BLUE_PICKER )
		m_ctrlBluePicker.SetColor(col);
	UpdateColor(col, m_iCurrentColor);
	UpdateRGBText(col);
}

void PrefsPageEditor::UpdateColor(COLORREF col, UINT id)
{
	*m_CRefMap[id] = col;
	m_CBtnMap[id]->SetFaceColor(col);
	COLORREF altColor = UpdateRGBText(col);
	m_CBtnMap[id]->SetTextColor(altColor);
}

COLORREF PrefsPageEditor::UpdateRGBText(COLORREF col)
{
	DWORD lightness = GetRValue(col) * 77 + GetGValue(col) * 150 + GetBValue(col) * 29;
	m_sRGBtext.Format(_T("Red=%d Green=%d Blue=%d (0x%x,0x%x,0x%x)"),
		GetRValue(col), GetGValue(col), GetBValue(col),
		GetRValue(col), GetGValue(col), GetBValue(col));
	UpdateData(FALSE);
	m_TextColor = col;
	m_BackColor = lightness >= 32768 ? 0 : 0xffffff;
	m_ctrlFontName.Invalidate();
	return m_BackColor;
}

LRESULT PrefsPageEditor::OnStaticCtl(WPARAM wParam, LPARAM lParam)
{
	if ((HWND)lParam == m_ctrlFontName.GetSafeHwnd()) {
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, m_TextColor);
		SetBkColor(hdcStatic, 0xffffff);
		return (LRESULT)((HBRUSH)(COLOR_WINDOW + 1));
	}
	return LRESULT();
}

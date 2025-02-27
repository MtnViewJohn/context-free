// PrefsPageEditor.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "PrefsPageEditor.h"
#include "EditorParams.h"
#include <vector>

// PrefsPageEditor dialog

IMPLEMENT_DYNAMIC(PrefsPageEditor, CPropertyPage)

PrefsPageEditor::PrefsPageEditor()
	: CPropertyPage(IDD_PREFS_EDITOR),
	m_sFontName(EditorParams::GetFont())
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
}


BEGIN_MESSAGE_MAP(PrefsPageEditor, CPropertyPage)
	ON_BN_CLICKED(IDC_FONTCHANGE, &PrefsPageEditor::OnClickedFontchange)
END_MESSAGE_MAP()


// PrefsPageEditor message handlers

void PrefsPageEditor::OnOK()
{
	EditorParams::SetFont(m_sFontName);
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
	CFontDialog fDlg(&logFont, CF_FIXEDPITCHONLY | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS);

	if (fDlg.DoModal() == IDOK) {
		fname = fDlg.GetFaceName();
		fsize = (fDlg.GetSize() + 5) / 10;
		m_sFontName = EditorParams::GetFont(fname, fsize);
		m_Font.Detach();
		m_Font.CreateFontIndirectW(&logFont);
		m_ctrlFontName.SetFont(&m_Font);
		UpdateData(FALSE);
		m_FontChanged = true;
	}
}

BOOL PrefsPageEditor::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_ctrlFontName.SetFont(&m_Font);

	return TRUE;
}

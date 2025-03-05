#pragma once
#include "afxdialogex.h"
#include <map>
#include "myafxcolorpickerctrl.h"

// PrefsPageEditor dialog

class PrefsPageEditor : public CPropertyPage
{
	DECLARE_DYNAMIC(PrefsPageEditor)

public:
	PrefsPageEditor();
	virtual ~PrefsPageEditor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PREFS_EDITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTabWidthUD(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnColorBtn(UINT id);
	afx_msg void OnTypeBtn(UINT id);

	std::map<UINT, COLORREF*> m_CRefMap;
	std::map<UINT, CMFCButton*> m_CBtnMap;
	std::map<UINT, BOOL*> m_bBoldMap;
	std::map<UINT, BOOL*> m_bItalicMap;
	std::map<UINT, myCMFCColorPickerCtrl*> m_CPickerMap;
	UINT m_iCurrentColor;
	COLORREF m_TextColor;
	COLORREF m_BackColor;
	void UpdateColor(COLORREF col, UINT id);
	COLORREF UpdateRGBText(COLORREF col);
	void UpdateFont();

	DECLARE_MESSAGE_MAP()
public:
	CString m_sFontName;
	virtual void OnOK();
	afx_msg void OnClickedFontchange();
	CEdit m_ctrlFontName;
	CFont m_Font;
	virtual BOOL OnInitDialog();
	bool m_FontChanged = false;
	bool m_StyleChanged = false;
	CSpinButtonCtrl m_ctrlTabSpin;
	int m_iTabWidth;
	BOOL m_bDefaultBold;
	BOOL m_bDefaultItalic;
	BOOL m_bCommentBold;
	BOOL m_bCommentItalic;
	BOOL m_bSymbolBold;
	BOOL m_bSymbolItalic;
	BOOL m_bIdentBold;
	BOOL m_bIdentItalic;
	BOOL m_bKeywordBold;
	BOOL m_bKeywordItalic;
	BOOL m_bBuiltinBold;
	BOOL m_bBuiltinItalic;
	BOOL m_bFileBold;
	BOOL m_bFileItalic;
	BOOL m_bNumberBold;
	BOOL m_bNumberItalic;
	CMFCButton m_ctrlDefaultColor;
	CMFCButton m_ctrlCommentColor;
	CMFCButton m_ctrlSymbolColor;
	CMFCButton m_ctrlIdentColor;
	CMFCButton m_ctrlKeywordColor;
	CMFCButton m_ctrlBuiltinColor;
	CMFCButton m_ctrlFileColor;
	CMFCButton m_ctrlNumberColor;
	COLORREF m_cDefaultColor;
	COLORREF m_cCommentColor;
	COLORREF m_cSymbolColor;
	COLORREF m_cIdentColor;
	COLORREF m_cKeywordColor;
	COLORREF m_cBuiltinColor;
	COLORREF m_cFileColor;
	COLORREF m_cNumberColor;
	myCMFCColorPickerCtrl  m_ctrlColorPicker;
	myCMFCColorPickerCtrl m_ctrlLumPicker;
	CPalette m_Palette;
	afx_msg void OnClickedColorPicker();
	afx_msg void OnClickedLumPicker();
	afx_msg void OnClickedRGBPicker(UINT id);
	myCMFCColorPickerCtrl m_ctrlRedPicker;
	myCMFCColorPickerCtrl m_ctrlGreenPicker;
	myCMFCColorPickerCtrl m_ctrlBluePicker;
	CString m_sRGBtext;
	afx_msg LRESULT OnStaticCtl(WPARAM wParam, LPARAM lParam);
};

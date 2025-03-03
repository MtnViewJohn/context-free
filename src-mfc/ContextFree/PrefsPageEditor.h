#pragma once
#include "afxdialogex.h"


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

	DECLARE_MESSAGE_MAP()
public:
	CString m_sFontName;
	virtual void OnOK();
	afx_msg void OnClickedFontchange();
	CEdit m_ctrlFontName;
	CFont m_Font;
	virtual BOOL OnInitDialog();
	bool m_FontChanged = false;
	CSpinButtonCtrl m_ctrlTabSpin;
	int m_iTabWidth;
};

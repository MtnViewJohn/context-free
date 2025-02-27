#pragma once
#include "afxdialogex.h"


// PrefsPageGeneral dialog

class PrefsPageGeneral : public CPropertyPage
{
	DECLARE_DYNAMIC(PrefsPageGeneral)

public:
	PrefsPageGeneral();
	virtual ~PrefsPageGeneral();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PREF_GENERAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_ctrlBorderSize;
	BOOL m_bOpenRender;
	BOOL m_bProgressive;
	int m_iAtLaunch;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

#pragma once
#include "afxdialogex.h"
#include "RenderParams.h"
#include <string>

// RenderSize dialog

class RenderSize : public CDialog
{
	DECLARE_DYNAMIC(RenderSize)

public:
	RenderSize(RenderParameters& p,  CWnd* pParent = nullptr);   // standard constructor
	virtual ~RenderSize();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RenderSize };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlWidth;
	CEdit m_ctrlHeight;
	CEdit m_ctrlMinSize;
	CSliderCtrl m_ctrlBorderSize;
	CButton m_ctrlNoDisplay;
	RenderParameters& params;
	std::wstring m_MinString;
	double m_MinValue;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeMinsize();
};

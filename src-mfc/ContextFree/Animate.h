#pragma once
#include "afxdialogex.h"
#include "RenderParams.h"
#include <string>

// Animate dialog

class Animate : public CDialog
{
	DECLARE_DYNAMIC(Animate)

public:
	Animate(RenderParameters& p, bool frame, CWnd* pParent = nullptr);   // standard constructor
	virtual ~Animate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Animate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlWidth;
	CEdit m_ctrlHeight;
	CEdit m_ctrlMinSize;
	CSliderCtrl m_ctrlBorderSize;
	CButton m_ctrlZoom;
	CButton m_ctrlPreview;
	CButton m_ctrlLoop;
	CEdit m_ctrlLength;
	CComboBox m_ctrlFrameRate;
	CComboBox m_ctrlCodec;
	CStatic m_ctrlFrameLabel;
	CEdit m_ctrlFrame;
	RenderParameters& params;
	bool m_bFrame;
	std::wstring m_MinString;
	double m_MinValue;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeMinsize();
	CStatic m_ctrlCodecLabel;
};

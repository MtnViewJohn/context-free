#pragma once


// CFFontDialog

class CFFontDialog : public CFontDialog
{
	DECLARE_DYNAMIC(CFFontDialog)

public:
	CFFontDialog(LPLOGFONT lplfInitial = nullptr,
			DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS,
			CDC* pdcPrinter = nullptr,
			CWnd* pParentWnd = nullptr);
	virtual ~CFFontDialog();
	afx_msg void xOnShowWindow(BOOL bShow, UINT nStatus);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
};



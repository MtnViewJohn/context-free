// CFFontDialog.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "CFFontDialog.h"
#include <dlgs.h>

#ifndef _WIN32_WCE // CFontDialog is not supported for Windows CE.

// CFFontDialog

IMPLEMENT_DYNAMIC(CFFontDialog, CFontDialog)

CFFontDialog::CFFontDialog(LPLOGFONT lplfInitial, DWORD dwFlags, CDC* pdcPrinter, CWnd* pParentWnd) :
	CFontDialog(lplfInitial, dwFlags, pdcPrinter, pParentWnd)
{
}

CFFontDialog::~CFFontDialog()
{
}

void CFFontDialog::xOnShowWindow(BOOL bShow, UINT nStatus)
{
}


BEGIN_MESSAGE_MAP(CFFontDialog, CFontDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



// CFFontDialog message handlers


#endif // !_WIN32_WCE

void CFFontDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFontDialog::OnShowWindow(bShow, nStatus);

	GetDlgItem(cmb2)->EnableWindow(FALSE);
}

BOOL CFFontDialog::OnInitDialog()
{
	CFontDialog::OnInitDialog();

	SetDlgItemText(stc5, _T("startshape thingy\r\nCF::Tile = [s 2 5]"));
	GetDlgItem(stc5)->ShowWindow(SW_SHOWNOACTIVATE);

	return TRUE;
}

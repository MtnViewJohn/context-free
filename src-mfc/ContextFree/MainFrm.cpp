
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "ContextFree.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "variation.h"
#include <cstdlib>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND_RANGE(IDC_RENDERSPLIT, IDC_SIZE_HEIGHT, &CMainFrame::OnRenderBar)
	ON_COMMAND_RANGE(ID_RB_RENDER, ID_RB_FRAME, &CMainFrame::OnRenderBar)
	ON_UPDATE_COMMAND_UI_RANGE(IDC_RENDERSPLIT, IDC_SIZE_HEIGHT, &CMainFrame::OnUpdateRenderBar)
	ON_MESSAGE(WM_TICKLE_SIZE, OnTickleSize)
	ON_NOTIFY(BCN_DROPDOWN, IDC_RENDERSPLIT, &CMainFrame::OnRenderSplitMenu)
	ON_NOTIFY(UDN_DELTAPOS, IDC_VARIATION_SPIN, &CMainFrame::OnRenderVariationUD)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FRAME_SPIN, &CMainFrame::OnRenderFrameUD)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_VARIATION, IDC_SIZE_HEIGHT, &CMainFrame::OnRenderEdits)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_PROGRESS,	// progress bar
	ID_INDICATOR_STATUS,	// status test
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	m_wndMessageLog.m_wndMainFrm = this;
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::Message(LPCSTR msg)
{
	m_wndMessageLog.Message(msg);
}

void CMainFrame::ShowMessages()
{
	m_wndMessageLog.SetAutoHideMode(FALSE, CBRS_ALIGN_RIGHT, NULL, 0);
}

void CMainFrame::ForwardLink(LPCTSTR link)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c)
		c->RecvErrorLinkClick(link);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableMDITabs(TRUE, FALSE, CMFCBaseTabCtrl::LOCATION_TOP, FALSE, CMFCTabCtrl::STYLE_3D_SCROLLED, FALSE, TRUE);

	
	if (!m_wndRenderbar.Create(_T(""), this, FALSE, IDD_RENDERBAR, WS_CHILD | WS_VISIBLE | CBRS_TOP, IDD_RENDERBAR)) {
		TRACE0("Could not create renderbar\n");
		return -1;
	}
	CDockingManager::SetDockingMode(DT_SMART);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	m_wndRenderbar.EnableDocking(CBRS_ALIGN_ANY);
	if (!EnableDocking(CBRS_ALIGN_ANY) || !AddPane(&m_wndRenderbar)) {
		TRACE0("Could not dock renderbar\n");
		return -1;
	}
	DockPane(&m_wndRenderbar, AFX_IDW_DOCKBAR_TOP);
	m_wndRenderbar.ShowPane(TRUE, FALSE, FALSE);

	if (!m_wndMessageLog.Create(_T("Messages"), this, CRect(0, 0, 800, 300), TRUE, IDC_RICHLOG,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_HIDE_INPLACE))
	{
		TRACE0("Could not create log window.\n");
		return -1;
	}
	m_wndMessageLog.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMessageLog, AFX_IDW_DOCKBAR_RIGHT);
	m_wndMessageLog.SetAutoHideMode(TRUE, CBRS_ALIGN_RIGHT, NULL, 0);

	m_hSplitMenu = ::CreatePopupMenu();
	::AppendMenuW(m_hSplitMenu, MF_BYPOSITION, ID_RB_RENDER,  _T("Render"));
	::AppendMenuW(m_hSplitMenu, MF_BYPOSITION, ID_RB_SIZED,   _T("Render to Size"));
	::AppendMenuW(m_hSplitMenu, MF_BYPOSITION, ID_RB_ANIMATE, _T("Animate"));
	::AppendMenuW(m_hSplitMenu, MF_BYPOSITION, ID_RB_FRAME,   _T("Animate a Frame"));

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneWidth(nStatusProgress, 160);
	m_wndStatusBar.SetPaneStyle(nStatusText, SBPS_STRETCH | SBPS_NOBORDERS);
	m_wndStatusBar.EnablePaneProgressBar(nStatusProgress);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	CClientDC dc(this);
	int nFontSize = 10;
	int nHeight = -((dc.GetDeviceCaps(LOGPIXELSY) * nFontSize) / 72);
	m_editFont.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Cascadia Code"));

	// Create edit box

	return 0;
}

void CMainFrame::OnClose()
{
	bool canClose = true;
	for (auto child: CChildFrame::Children)
		canClose = child->CanClose(true) && canClose;	// always call CanClose()

	if (canClose)
		DestroyWindow();
}

void CMainFrame::UpdateStatusBar(int progress, const CString& text)
{
	m_wndStatusBar.SetPaneProgress(nStatusProgress, progress);
	m_wndStatusBar.SetPaneText(nStatusText, (LPCTSTR)text);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnRenderBar(UINT id)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c == nullptr) return;
	switch (id) {
	case IDC_RENDERSPLIT:
		if (c->m_hRenderThread && c->m_Renderer) {
			if (c->m_Renderer->requestFinishUp)
				c->m_Renderer->requestStop = true;
			else
				c->m_Renderer->requestFinishUp = true;
		} else {
			c->OnRenderAgain();
		}
		break;
	case IDC_SAVE:
		// not implemented yet
		break;
	case ID_RB_RENDER:
		c->renderParams.action = RenderParameters::RenderActions::Render;
		c->renderParams.renderSize = false;
		break;
	case ID_RB_SIZED:
		c->renderParams.action = RenderParameters::RenderActions::Render;
		c->renderParams.renderSize = true;
		break;
	case ID_RB_ANIMATE:
		c->renderParams.action = RenderParameters::RenderActions::Animate;
		c->renderParams.animateFrame = false;
		break;
	case ID_RB_FRAME:
		c->renderParams.action = RenderParameters::RenderActions::Animate;
		c->renderParams.animateFrame = true;
		break;
	default:
		break;
	}
}

void CMainFrame::OnUpdateRenderBar(CCmdUI* pCmdUI)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	HWND hDlgItem = ::GetDlgItem(m_wndRenderbar.GetSafeHwnd(), pCmdUI->m_nID);
	switch (pCmdUI->m_nID) {
	case IDC_RENDERSPLIT:
		if (c == nullptr) {
			pCmdUI->Enable(FALSE);
			pCmdUI->SetText(_T("Render"));
		} else {
			pCmdUI->Enable();
			if (c->m_hRenderThread && c->m_Renderer) {
				if (c->m_Renderer->requestFinishUp)
					pCmdUI->SetText(_T("STOP!"));
				else 
					pCmdUI->SetText(_T("Stop"));
			} else {
				switch (c->renderParams.action) {
				case RenderParameters::RenderActions::Render:
					if (c->renderParams.renderSize)
						pCmdUI->SetText(_T("Sized"));
					else
						pCmdUI->SetText(_T("Render"));
					break;
				case RenderParameters::RenderActions::Animate:
					if (c->renderParams.animateFrame)
						pCmdUI->SetText(_T("Frame"));
					else
						pCmdUI->SetText(_T("Animate"));
					break;
				default:
					break;
				}
			}
		}
		break;
	case IDC_SAVE:
		if (c)
			c->OnUpdateSaveImage(pCmdUI);
		else
			pCmdUI->Enable(FALSE);
		break;
	case IDC_VARIATION:
		if (c->renderParams.variation == 0) {
			pCmdUI->SetText(_T(""));
		} else {
			std::string v = Variation::toString(c->renderParams.variation, false);
			std::wstring v16 = Utf8ToUtf16(v.c_str());
			pCmdUI->SetText(v16.c_str());
		}
		break;
	case IDC_FRAME_EDIT: 
		if (c->renderParams.MovieFrame == 0) {
			pCmdUI->SetText(_T(""));
		} else {
			auto f16 = std::to_wstring(c->renderParams.MovieFrame);
			pCmdUI->SetText(f16.c_str());
		}
		[[fallthrough]];
	case IDC_FRAME_LABEL:
	case IDC_FRAME_SPIN:
		::ShowWindow(hDlgItem, (c->renderParams.action == RenderParameters::RenderActions::Animate &&
								c->renderParams.animateFrame) ? SW_SHOWNA : SW_HIDE);
		break;
	case IDC_SIZE_WIDTH: 
	case IDC_SIZE_HEIGHT: {
		int sz = pCmdUI->m_nID == IDC_SIZE_WIDTH ? c->renderParams.RenderWidth
												 : c->renderParams.RenderHeight;
		if (sz == 0) {
			pCmdUI->SetText(_T(""));
		} else {
			auto w16 = std::to_wstring(sz);
			pCmdUI->SetText(w16.c_str());
		}
	}
		[[fallthrough]];
	case IDC_SIZE_LABEL1:
	case IDC_SIZE_LABEL2:
		::ShowWindow(hDlgItem, (c->renderParams.action == RenderParameters::RenderActions::Render &&
								c->renderParams.renderSize) ? SW_SHOWNA : SW_HIDE);
		break;
	default:
		pCmdUI->ContinueRouting();
		break;
	}
}

void CMainFrame::OnRenderSplitMenu(NMHDR* pNotifyStruct, LRESULT* result)
{
	NMBCDROPDOWN* pDropDown = (NMBCDROPDOWN*)pNotifyStruct;
	HWND rb = NULL;
	m_wndRenderbar.GetDlgItem(IDC_RENDERSPLIT, &rb);
	if (pDropDown->hdr.hwndFrom == rb && pDropDown->hdr.idFrom == IDC_RENDERSPLIT) {
		// Get screen coordinates of the button.
		POINT pt;
		pt.x = pDropDown->rcButton.left;
		pt.y = pDropDown->rcButton.bottom;
		::ClientToScreen(pDropDown->hdr.hwndFrom, &pt);
		::TrackPopupMenu(m_hSplitMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, GetSafeHwnd(), NULL);
		*result = 1;
	}
	*result = 0;
}

void CMainFrame::OnRenderVariationUD(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMUPDOWN pUpDown = (LPNMUPDOWN)pNotifyStruct;
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c) {
		if (pUpDown->iDelta < 0)
			c->OnNextVariation();
		if (pUpDown->iDelta > 0)
			c->OnPrevVariation();
	}

	*result = 1;	// always block
}

void CMainFrame::OnRenderFrameUD(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMUPDOWN pUpDown = (LPNMUPDOWN)pNotifyStruct;
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c) {
		int v = c->renderParams.MovieFrame - pUpDown->iDelta;
		if (v < 1)
			v = 1;
		if (v > c->renderParams.AnimateFrameCount)
			v = c->renderParams.AnimateFrameCount;
		RenderParameters::Modify(c->renderParams.MovieFrame, v);
	}

	*result = 1;	// always block
}

void CMainFrame::OnRenderEdits(UINT id)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (!c) return;

	HWND hDlg = m_wndRenderbar.GetSafeHwnd();

	std::string buf(20, ' ');
	auto len = ::GetDlgItemTextA(hDlg, id, buf.data(), 20);
	buf.resize(len);

	int i = std::atoi(buf.c_str());

	switch (id) {
	case IDC_VARIATION:
		if (len == 0) {
			c->renderParams.variation = 0;
		} else {
			int v = Variation::fromString(buf.c_str());
			if (v == -1) {
				auto str = Variation::toString(c->renderParams.variation, false);
				::SetDlgItemTextA(hDlg, id, str.c_str());
			} else {
				c->renderParams.variation = v;
			}
		}
		break;
	case IDC_FRAME_EDIT:
		if (len == 0)
			i = 0;
		else if (i < 1)
			i = 1;
		else if (i > c->renderParams.AnimateFrameCount)
			i = c->renderParams.AnimateFrameCount;
		RenderParameters::Modify(c->renderParams.MovieFrame, i);
		break;
	case IDC_SIZE_WIDTH:
		if (len == 0)
			i = 0;
		else if (i < 10)
			i = 10;
		else if (i > 32768)
			i = 32768;
		RenderParameters::Modify(c->renderParams.RenderWidth, i);
		break;
	case IDC_SIZE_HEIGHT:
		if (len == 0)
			i = 0;
		else if (i < 10)
			i = 10;
		else if (i > 32768)
			i = 32768;
		RenderParameters::Modify(c->renderParams.RenderHeight, i);
		break;
	default:
		break;
	}
}

LRESULT CMainFrame::OnTickleSize(WPARAM wParam, LPARAM lParam)
{
	CRect cr;
	GetWindowRect(&cr);
	SetWindowPos(&wndTop, cr.left, cr.top, cr.Width(), cr.Height() + m_intTickleAmount, 0);
	m_intTickleAmount = -m_intTickleAmount;
	return 0;
}

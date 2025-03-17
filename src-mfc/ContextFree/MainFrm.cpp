
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "ContextFree.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "variation.h"
#include <cstdlib>
#include <map>
#include "Preferences.h"
#include "Settings.h"
#include "CFScintillaView.h"
#include <wininet.h>
#include "WinSystem.h"
#include <afxinet.h>
#include "upload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using WinSystem::WM_USER_RENDER_COMPLETE;

namespace {
	std::map<UINT, LPCTSTR> ExampleMenuMap = {
		{ID_EXAMPLE_CILIASUN,    L"ciliasun.cfdg"},
		{ID_EXAMPLE_DEMO1,       L"demo1.cfdg"},
		{ID_EXAMPLE_DEMO2,       L"demo2.cfdg"},
		{ID_EXAMPLE_FUNKY,       L"funky_flower.cfdg"},
		{ID_EXAMPLE_ICURVES,     L"i_curves.cfdg"},
		{ID_EXAMPLE_IPIX,        L"i_pix.cfdg"},
		{ID_EXAMPLE_IPOLYGONS,   L"i_polygons.cfdg"},
		{ID_EXAMPLE_LESSON,      L"lesson.cfdg"},
		{ID_EXAMPLE_LESSON2,     L"lesson2.cfdg"},
		{ID_EXAMPLE_MTREE,       L"mtree.cfdg"},
		{ID_EXAMPLE_OCTOPI,      L"octopi.cfdg"},
		{ID_EXAMPLE_QUADCITY,    L"quadcity.cfdg"},
		{ID_EXAMPLE_ROSE,        L"rose.cfdg"},
		{ID_EXAMPLE_SIERPINSKI,  L"sierpinski.cfdg"},
		{ID_EXAMPLE_SNOWFLAKE,   L"snowflake.cfdg"},
		{ID_EXAMPLE_TANGLE,      L"tangle.cfdg"},
		{ID_EXAMPLE_TRIPLES,     L"triples.cfdg"},
		{ID_EXAMPLE_UNDERGROUND, L"underground.cfdg"},
		{ID_EXAMPLE_WEIGHTING,   L"weighting_demo.cfdg"},
		{ID_EXAMPLE_WELCOME,     L"welcome.cfdg"},
		{ID_EXAMPLE_ZIGGY,       L"ziggy.cfdg"},
	};

	struct DownloadInfo {
		CMainFrame& m_hMainFrame;
		CString m_sUrl;
	};

	struct InternetCloser
	{
		void operator()(HINTERNET hInet) const {
			::InternetCloseHandle(hInet);
		}
	};

	using inet_ptr = std::unique_ptr<void, InternetCloser>;

	UINT DownloadControllingFunction(LPVOID pParam)
	{
		std::unique_ptr<DownloadInfo> pDI{ (DownloadInfo*)pParam };
		inet_ptr hInetInit;
		inet_ptr hInetCnxn;
		inet_ptr hInetReq;

		DWORD service = 0;
		CString server;
		CString object;
		INTERNET_PORT port = 0;
		if (!AfxParseURL(pDI->m_sUrl, service, server, object, port))
			return 1;
		if (service != AFX_INET_SERVICE_HTTP && service != AFX_INET_SERVICE_HTTPS)
			return 1;

		hInetInit.reset(::InternetOpen(L"Context Free", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0));

		if (hInetInit)
			hInetCnxn.reset(::InternetConnect(hInetInit.get(), server, port,
				NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL));

		if (hInetCnxn)
			hInetReq.reset(::HttpOpenRequest(hInetCnxn.get(), L"GET", object, L"HTTP/1.1",
				NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION | 
				(service == AFX_INET_SERVICE_HTTP ? 0 : INTERNET_FLAG_SECURE),
				NULL));

		if (hInetReq && ::HttpSendRequest(hInetReq.get(), NULL, 0, NULL, 0)) {
			DWORD length = sizeof(DWORD);
			DWORD status = 0;
			HttpQueryInfo(hInetReq.get(), HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
				&status, &length, NULL);
			if (status == 200) {
				char buf[200];
				DWORD bytesRead;
				std::string response;
				while (::InternetReadFile(hInetReq.get(), (LPVOID)buf, 200, &bytesRead) && bytesRead) {
					response.append(buf, bytesRead);
					bytesRead = 0;
				}

				if (!response.empty()) {
					if (pDI->m_sUrl.Right(5) == L".cfdg") {		// link to cfdg file
						CMainFrame::NextString = std::move(response);
						CMainFrame::NextName = pDI->m_sUrl;
						CMainFrame::NextVariation = 0;
					} else {									// link to gallery page
						Upload download(response.c_str(), response.length());
						if (!download.mId)
							return 1;
						CMainFrame::NextString = std::move(download.mPassword);
						CMainFrame::NextName = Utf8ToUtf16(download.mFileName.c_str()).c_str();
						CMainFrame::NextVariation = download.mVariation;
					}
					// Trim path components and extension
					int idx = CMainFrame::NextName.ReverseFind(L'/');
					if (idx != -1)
						CMainFrame::NextName = CMainFrame::NextName.Mid(idx + 1);
					if (CMainFrame::NextName.Right(5) == L".cfdg")
						CMainFrame::NextName = CMainFrame::NextName.Left(CMainFrame::NextName.GetLength() - 5);
					pDI->m_hMainFrame.PostMessageW(WM_USER_RENDER_COMPLETE);
				}
			}
		}

		return 0;
	}

}
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(IDC_RENDERSPLIT, IDC_SIZE_HEIGHT, &CMainFrame::OnRenderBar)
	ON_COMMAND_RANGE(ID_RB_RENDER, ID_RB_FRAME, &CMainFrame::OnRenderBar)
	ON_COMMAND_RANGE(ID_EXAMPLE_CILIASUN, ID_EXAMPLE_ZIGGY, &CMainFrame::OnExample)
	ON_UPDATE_COMMAND_UI_RANGE(IDC_RENDERSPLIT, IDC_SIZE_HEIGHT, &CMainFrame::OnUpdateRenderBar)
	ON_NOTIFY(BCN_DROPDOWN, IDC_RENDERSPLIT, &CMainFrame::OnRenderSplitMenu)
	ON_NOTIFY(UDN_DELTAPOS, IDC_VARIATION_SPIN, &CMainFrame::OnRenderVariationUD)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FRAME_SPIN, &CMainFrame::OnRenderFrameUD)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_VARIATION, IDC_SIZE_HEIGHT, &CMainFrame::OnRenderEdits)
	ON_COMMAND(ID_FILE_PREFERENCES, &CMainFrame::OnPreferences)
	ON_MESSAGE(WM_USER_RENDER_COMPLETE, &CMainFrame::DownloadDone)
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_PROGRESS,	// progress bar
	ID_INDICATOR_STATUS,	// status text
	ID_INDICATOR_LINE,		// line#
};

// CMainFrame construction/destruction

LPCTSTR CMainFrame::NextExample = nullptr;
std::string CMainFrame::NextString;
CString CMainFrame::NextName;
int CMainFrame::NextVariation = 0;

CMainFrame::CMainFrame() noexcept
: CMDIFrameWndEx()
, m_CFDropTarget(*this)
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

void CMainFrame::ShowMessages(BOOL bShow)
{
	m_wndMessageLog.ShowPane(bShow, FALSE, bShow);
	if (!bShow) {
		CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
		if (c)
			c->m_vwCfdgEditor->SetFocus();
	}
}

BOOL CMainFrame::ShowColorCalculator(BOOL bShow)
{
	BOOL showing = ::IsWindow(m_wndColorCalc.GetSafeHwnd());
	if (bShow) {
		if (showing) {
			showing = m_wndColorCalc.ShowWindow(SW_SHOW);
		} else {
			showing = m_wndColorCalc.Create(IDD_COLORCALC, this);
			showing = m_wndColorCalc.ShowWindow(SW_SHOW);
		}
		return TRUE;
	} else {
		return showing;
	}
}

void CMainFrame::ForwardLink(LPCTSTR link)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c)
		c->RecvErrorLinkClick(link);
}

DROPEFFECT CMainFrame::OnDragEnter(COleDataObject* pDataObject)
{
	if (pDataObject->IsDataAvailable(CF_TEXT) || pDataObject->IsDataAvailable(CF_UNICODETEXT))
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

DROPEFFECT CMainFrame::OnDragOver(COleDataObject* pDataObject)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	if (pDataObject->IsDataAvailable(CF_TEXT) || pDataObject->IsDataAvailable(CF_UNICODETEXT))
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

BOOL CMainFrame::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect)
{
	if (HGLOBAL hData = pDataObject->GetGlobalData(CF_UNICODETEXT)) {
		wchar_t* wtxt = reinterpret_cast<wchar_t*>(::GlobalLock(hData));
		if (wtxt && *wtxt) {
			std::wstring_view wview = wtxt;
			if (wview.starts_with(L"https://www.contextfreeart.org/gallery") ||
				wview.starts_with(L"http://www.contextfreeart.org/gallery") ||
				wview.starts_with(L"https://contextfreeart.org/gallery") ||
				wview.starts_with(L"http://contextfreeart.org/gallery"))
			{
				DownLoadGallery(wview);
			} else {
				NextString = Utf16ToUtf8(wtxt);
				theApp.m_pDocManager->OnFileNew();
			}
		}
		::GlobalUnlock(hData);
		::GlobalFree(hData);
		return TRUE;
	}
	if (HGLOBAL hData = pDataObject->GetGlobalData(CF_TEXT)) {
		char* txt = reinterpret_cast<char*>(::GlobalLock(hData));
		if (txt && *txt) {
			auto wview = Utf8ToUtf16(txt);
			if (wview.starts_with(L"https://www.contextfreeart.org/gallery") ||
				wview.starts_with(L"http://www.contextfreeart.org/gallery") ||
				wview.starts_with(L"https://contextfreeart.org/gallery") ||
				wview.starts_with(L"http://contextfreeart.org/gallery"))
			{
				DownLoadGallery(wview);
			} else {
				NextString = txt;
				theApp.m_pDocManager->OnFileNew();
			}
		}
		::GlobalUnlock(hData);
		::GlobalFree(hData);
		return TRUE;
	}
	return FALSE;
}

void CMainFrame::DownLoadGallery(std::wstring_view wview)
{
	DownloadInfo* di = new DownloadInfo{ *this, L"" };
	auto idx = wview.find(L"id=");
	if (idx != std::wstring_view::npos) {
		idx += 3;
	} else {
		idx = wview.find(L"#design/");
		if (idx != std::wstring_view::npos)
			idx += 8;
	}
	if (idx != std::wstring_view::npos) {
		wchar_t* end = nullptr;
		long id = std::wcstol(wview.data() + idx, &end, 10);
		if (end != wview.data() + idx && id != 0 && id != LONG_MAX)
			di->m_sUrl.Format(L"https://www.contextfreeart.org/gallery/data.php/%d/info/foo.json", id);
		else
			return;
	} else if (wview.ends_with(L".cfdg")) {
		di->m_sUrl = wview.data();
	} else {
		return;
	}

	CWinThread* rt = ::AfxBeginThread(DownloadControllingFunction, (LPVOID)di);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableMDITabs(TRUE, TRUE, CMFCBaseTabCtrl::LOCATION_TOP, FALSE, CMFCTabCtrl::STYLE_3D_SCROLLED, FALSE, TRUE);

	if (!m_CFDropTarget.Register(this)) {
		TRACE0("Could not register drop window\n");
	}


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
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_HIDE_INPLACE, AFX_CBRS_REGULAR_TABS, 
		AFX_CBRS_FLOAT | AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE))
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

	return 0;
}

void CMainFrame::OnClose()
{
	bool canClose = true;
	for (auto child: CChildFrame::Children)
		canClose = child->CanClose(true) && canClose;	// always call CanClose()

	if (canClose) {
		if (ShowColorCalculator(FALSE))
			m_wndColorCalc.DestroyWindow();
		DestroyWindow();
	}
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

	if (Settings::WindowWidth != 0 && Settings::WindowHeight != 0 &&
		Settings::WindowWidth != INT_MAX && Settings::WindowHeight != INT_MAX)
	{
		cs.cx = Settings::WindowWidth;
		cs.cy = Settings::WindowHeight;
	}

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

void CMainFrame::OnExample(UINT id)
{
	NextExample = id ? ExampleMenuMap[id] : ExampleMenuMap[ID_EXAMPLE_WELCOME];
	if (id)
		theApp.m_pDocManager->OnFileNew();
}

LRESULT CMainFrame::DownloadDone(WPARAM, LPARAM)
{
	theApp.m_pDocManager->OnFileNew();
	return 0;
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
			pCmdUI->SetText(_T(" ▶ Render"));
		} else {
			pCmdUI->Enable();
			std::wstring txt = L" ";
			txt.append(1, L"▶▘▝▗▖"[c->m_iBusyIndex]);
			if (c->m_hRenderThread && c->m_Renderer) {
				if (c->m_Renderer->requestFinishUp)
					txt.append(L" STOP!");
				else 
					txt.append(L" Stop");
			} else {
				switch (c->renderParams.action) {
				case RenderParameters::RenderActions::Render:
					if (c->renderParams.renderSize)
						txt.append(L" Sized");
					else
						txt.append(L" Render");
					break;
				case RenderParameters::RenderActions::Animate:
					if (c->renderParams.animateFrame)
						txt.append(L" Frame");
					else
						txt.append(L" Animate");
					break;
				default:
					txt.append(L" Render");
					break;
				}
			}
			pCmdUI->SetText(txt.c_str());
		}
		break;
	case IDC_SAVE:
		if (c)
			c->OnUpdateSaveImage(pCmdUI);
		else
			pCmdUI->Enable(FALSE);
		break;
	case IDC_VARIATION:
		if (!c) break;
		if (c->renderParams.variation == 0) {
			pCmdUI->SetText(_T(""));
		} else {
			std::string v = Variation::toString(c->renderParams.variation, false);
			std::wstring v16 = Utf8ToUtf16(v.c_str());
			pCmdUI->SetText(v16.c_str());
		}
		break;
	case IDC_VARIATION_SPIN:
		if (!m_bVariationSpinInit) {
			::SendMessage(hDlgItem, UDM_SETRANGE32, (WPARAM)0, (LPARAM)Variation::recommendedMax(6));
			m_bVariationSpinInit = true;
		}
		if (c)
			::SendMessage(hDlgItem, UDM_SETPOS32, 0, (LPARAM)c->renderParams.variation);
		break;
	case IDC_FRAME_EDIT: 
		if (!c) break;
		if (c->renderParams.MovieFrame == 0) {
			pCmdUI->SetText(_T(""));
		} else {
			auto f16 = std::to_wstring(c->renderParams.MovieFrame);
			pCmdUI->SetText(f16.c_str());
		}
		[[fallthrough]];
	case IDC_FRAME_SPIN:
		if (!c) break;
		::SendMessage(hDlgItem, UDM_SETRANGE32, (WPARAM)0, (LPARAM)c->renderParams.AnimateFrameCount);
		::SendMessage(hDlgItem, UDM_SETPOS32, 0, (LPARAM)c->renderParams.MovieFrame);
		[[fallthrough]];
	case IDC_FRAME_LABEL:
		if (!c) break;
		::ShowWindow(hDlgItem, (c->renderParams.action == RenderParameters::RenderActions::Animate &&
								c->renderParams.animateFrame) ? SW_SHOWNA : SW_HIDE);
		break;
	case IDC_SIZE_WIDTH: 
	case IDC_SIZE_HEIGHT: {
		if (!c) break;
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
		if (!c) break;
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
		if (pUpDown->iPos + pUpDown->iDelta > 0) {
			if (pUpDown->iDelta > 0)
				c->OnNextVariation();
			if (pUpDown->iDelta < 0)
				c->OnPrevVariation();
			*result = 0;	// allow valid change
			return;
		}
	}

	*result = 1;			// block invalid changes
}

void CMainFrame::OnRenderFrameUD(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMUPDOWN pUpDown = (LPNMUPDOWN)pNotifyStruct;
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (c && pUpDown->iPos + pUpDown->iDelta > 0) {
		RenderParameters::Modify(c->renderParams.MovieFrame, pUpDown->iPos + pUpDown->iDelta);
		*result = 0;		// allow valid change
		return;
	}

	*result = 1;			// block invalid changes
}

void CMainFrame::OnRenderEdits(UINT id)
{
	CChildFrame* c = dynamic_cast<CChildFrame*>(MDIGetActive());
	if (!c) return;

	HWND hDlg = m_wndRenderbar.GetSafeHwnd();
	HWND hDlgItem = NULL;

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
		hDlgItem = GetDlgItem(IDC_VARIATION_SPIN)->GetSafeHwnd();
		::SendMessage(hDlgItem, UDM_SETPOS32, 0, (LPARAM)c->renderParams.variation);
		break;
	case IDC_FRAME_EDIT:
		if (len == 0)
			i = 0;
		else if (i < 1)
			i = 1;
		else if (i > c->renderParams.AnimateFrameCount)
			i = c->renderParams.AnimateFrameCount;
		RenderParameters::Modify(c->renderParams.MovieFrame, i);
		hDlgItem = GetDlgItem(IDC_FRAME_SPIN)->GetSafeHwnd();
		::SendMessage(hDlgItem, UDM_SETPOS32, 0, (LPARAM)i);
		break;
	case IDC_SIZE_WIDTH:
	case IDC_SIZE_HEIGHT:
		if (len == 0)
			i = 0;
		if (i > 32768)
			i = 32768;
		RenderParameters::Modify(id == IDC_SIZE_WIDTH ? c->renderParams.RenderWidth
													  : c->renderParams.RenderHeight, i);
		break;
	default:
		break;
	}
}

void CMainFrame::OnPreferences()
{
	Preferences prefs;
	if (prefs.DoModal() == IDOK && (prefs.m_bFontChanged || prefs.m_bStyleChanged))
		UpdateEditors(prefs.m_bFontChanged, prefs.m_bStyleChanged);
}

void CMainFrame::UpdateEditors(bool font, bool style)
{
	for (auto&& child : CChildFrame::Children) {
		if (font)
			child->m_vwCfdgEditor->EditorFontChanged();
		if (style)
			child->m_vwCfdgEditor->EditorStyleChanged();
	}
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIFrameWndEx::OnSize(nType, cx, cy);

	switch (nType) {
	case SIZE_MAXIMIZED:
		Settings::WindowWidth = INT_MAX;
		Settings::WindowHeight = INT_MAX;
		break;
	case SIZE_RESTORED:
		Settings::WindowWidth = cx;
		Settings::WindowHeight = cy;
		break;
	default:
		return;
	}
	Settings::Save(true);
}

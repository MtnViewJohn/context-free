
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "pch.h"
#include "framework.h"
#include "ContextFree.h"

#include "ChildFrm.h"
#include "ContextFreeDoc.h"
#include "ContextFreeView.h"
#include "MainFrm.h"
#include "WinSystem.h"
#include "WinCanvas.h"
#include "winTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_RENDER, OnRender)
	ON_COMMAND(ID_RENDER_SIZE, OnRenderSize)
	ON_COMMAND(ID_RENDER_AGAIN, OnRenderAgain)
	ON_COMMAND(ID_ANIMATE, OnAnimate)
	ON_COMMAND(ID_ANIMATE_FRAME, OnAnimateFrame)
	ON_MESSAGE(WinSystem::WM_USER_STATUS_UPDATE, OnStatusUpdate)
	ON_MESSAGE(WinSystem::WM_USER_MESSAGE_UPDATE, OnMessage)
	ON_MESSAGE(WinSystem::WM_USER_RENDER_COMPLETE, OnRenderDone)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

std::set<CChildFrame*> CChildFrame::Children;

// CChildFrame construction/destruction

CChildFrame::CChildFrame() noexcept
{
	// TODO: add member initialization code here
	Children.insert(this);
}

CChildFrame::~CChildFrame()
{
	delete m_System; m_System = nullptr;
	Children.erase(this);
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect cr;
	GetClientRect(&cr);
	
	if (!m_wndSplitterCfdg.CreateStatic(this, 1, 2) ||
		!m_wndSplitterCfdg.CreateView(0, 0, RUNTIME_CLASS(CEditView), CSize(cr.Width() / 3, 0), pContext) ||
		!m_wndSplitterCfdg.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0, 0), pContext))
	{
		TRACE0("Could not create splitter.\n");
		return FALSE;
	}

	m_vwCfdgEditor = (CEditView*)m_wndSplitterCfdg.GetPane(0, 0);
	m_vwOutputView = (CContextFreeView*)m_wndSplitterCfdg.GetPane(0, 1);
	m_CFdoc = (CContextFreeDoc*)(pContext->m_pCurrentDoc);
	CMainFrame* mf = dynamic_cast<CMainFrame *>(GetMDIFrameWndEx());
	m_vwCfdgEditor->GetEditCtrl().SetFont(&(mf->m_editFont));
	m_vwOutputView->m_pWinCanvas = &m_WinCanvas;

	m_CFdoc->m_vwEditorView = m_vwCfdgEditor;

	m_bInitSplitter = TRUE;

	m_System = new ::WinSystem(GetSafeHwnd());

	ShowWindow(SW_MAXIMIZE);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);
	CRect cr;
	GetWindowRect(&cr);

	if (m_bInitSplitter && nType != SIZE_MINIMIZED) {
		m_wndSplitterCfdg.SetRowInfo(0, cy, 0);
		m_wndSplitterCfdg.SetColumnInfo(0, cr.Width() / 3, 50);
		m_wndSplitterCfdg.SetColumnInfo(1, cr.Width() * 2 / 3, 50);

		m_wndSplitterCfdg.RecalcLayout();
	}
}

LRESULT CChildFrame::OnStatusUpdate(WPARAM wParam, LPARAM lParam)
{
	std::unique_ptr<AbstractSystem::Stats> stat((AbstractSystem::Stats*)wParam);
	if (stat) {
		CString statusText;
		if ((stat->toDoCount > 0 && !stat->finalOutput) || !m_Canvas) {
			statusText.Format(_T("%d shapes and %d expansions to do"),
				stat->shapeCount, stat->toDoCount);
		} else if (m_Renderer) {
			LPCTSTR endText = (m_Engine && m_Engine->isTiledOrFrieze()) ? _T(", tiled") : _T("");
			statusText.Format(_T("%d shapes, %d x %d pixels%s"),
					stat->shapeCount, m_Renderer->m_width, m_Renderer->m_height, endText);
		}
		int ProgressBar = 0;
		if ((stat->inOutput && stat->fullOutput) || stat->showProgress) {
			if (m_iProgressDelay > 2) {
				int bar = 0;
				if (stat->outputCount > 0)
					bar = (int)((100.0 * (double)stat->outputDone) / stat->outputCount);
				if (bar >= 0 && bar <= 100)
					ProgressBar = bar;
			} else {
				m_iProgressDelay++;
			}
		} else {
			m_iProgressDelay = 0;
		}
		CMainFrame* mf = dynamic_cast<CMainFrame*>(GetMDIFrameWndEx());
		if (mf)
			mf->UpdateStatusBar(ProgressBar, statusText);
	} else {
		// update render box
		m_vwOutputView->Invalidate();
	}
	return 0;
}

LRESULT CChildFrame::OnMessage(WPARAM wParam, LPARAM lParam)
{
	std::unique_ptr<char[]> message((char*)wParam);
	return 0;
}

LRESULT CChildFrame::OnRenderDone(WPARAM wParam, LPARAM lParam)
{
	cleanupTimer();
	::CloseHandle(m_hRenderThread);
	m_hRenderThread = NULL;

	if (m_ePostRenderAction == PostRenderAction::Exit) {
		GetMDIFrame()->PostMessageW(WM_CLOSE);
		return 0;
	}
	if (m_ePostRenderAction == PostRenderAction::Close) {
		PostMessageW(WM_CLOSE);
		return 0;
	}

	// update render button

	// perform other actions

	// if nothing and animation is done then preveiw it
	return 0;
}

void CChildFrame::OnRender()
{
	// Update Render button

	// check if rendering -> post render action

	renderParams.Load();
	renderParams.action = RenderParameters::RenderActions::Render;
	CRect cr;
	m_vwOutputView->GetClientRect(&cr);
	renderParams.width = cr.Width();
	renderParams.height = cr.Height();

	DoRender(true);
}
void CChildFrame::OnRenderSize() {}
void CChildFrame::OnRenderAgain() {}
void CChildFrame::OnAnimate() {}
void CChildFrame::OnAnimateFrame() {}
void CChildFrame::OnNextVariation() {}
void CChildFrame::OnPrevVariation() {}

void CChildFrame::OnClose()
{
	if (CanClose(false))
		DestroyWindow();
}

bool CChildFrame::CanClose(bool andExit)
{
	if (isBusy()) {
		SetPostRenderAction(andExit ? PostRenderAction::Exit : PostRenderAction::Close);
		m_Renderer->requestStop = true;
		return false;
	}
	return true;
}

// CChildFrame implementation
void CChildFrame::DoRender(bool shrinkTiled)
{
	// clear message buffer

	bool modifiedSinceRender = SyncToSystem();
	if (!modifiedSinceRender && !m_bReuseVariation && renderParams.action != RenderParameters::RenderActions::Animate)
		OnNextVariation();
	m_bReuseVariation = false;

	// clean up movie preview

	bool useAnimateSize = renderParams.action == RenderParameters::RenderActions::Animate;
	int width = useAnimateSize ? renderParams.animateWidth : renderParams.width;
	int height = useAnimateSize ? renderParams.animateHeight : renderParams.height;

	m_Renderer.reset();		// TODO move deletion into async thread
	m_Engine.reset();
	m_WinCanvas.reset();
	m_Canvas = nullptr;

	m_Engine = CFDG::ParseFile(m_System->mName.c_str(), m_System, m_iCurrentVariation);
	if (!m_Engine)
		return;
	bool tiled = m_Engine->isTiledOrFrieze();
	if (shrinkTiled && tiled) {
		width = (9 * width) / 10;
		height = (9 * height) / 10;
	}

	m_vwOutputView->m_bTiled = tiled;
	m_vwOutputView->m_bBlendMode = m_Engine->usesBlendMode;

	m_Renderer = m_Engine->renderer(m_Engine, width, height,
		(float)renderParams.minimumSize, m_iCurrentVariation, renderParams.borderSize);

	if (!m_Renderer) {
		m_Engine.reset();
		::MessageBeep(0);
		return;
	}

	if (renderParams.action == RenderParameters::RenderActions::Render) {
		renderParams.width = width;
		renderParams.height = height;
	}

	if (renderParams.action == RenderParameters::RenderActions::Animate ?
		renderParams.animateFrame : renderParams.periodicUpdate)
	{
		MakeCanvas(width, height);
	}

	// setup animation canvas

	// clear post-render action
	PerformRender();
}

bool CChildFrame::SyncToSystem()
{
	auto txt = m_CFdoc->GetCfdg();
	const CString& wname = m_CFdoc->GetPathName();
	int len = ::WideCharToMultiByte(CP_UTF8, 0, wname, -1, nullptr, 0, NULL, NULL);
	std::string name(len - 1, ' ');
	::WideCharToMultiByte(CP_UTF8, 0, wname, -1, name.data(), len, NULL, NULL);
	return m_System->updateInfo(name.c_str(), txt.c_str());
}

void CChildFrame::MakeCanvas(int width, int height)
{
	m_WinCanvas = std::make_unique<WinCanvas>
		(m_System, WinCanvas::SuggestPixelFormat(m_Engine.get()),
			width, height, m_Engine->getBackgroundColor());
	m_Canvas = m_WinCanvas.get();
}

void CChildFrame::PerformRender()
{
	if (!m_Canvas || m_Canvas->mWidth > 0) {
		CWinThread* rt = AfxBeginThread(RenderControllingFunction, this, 0, 0, CREATE_SUSPENDED);
		BOOL good =
		::DuplicateHandle(	::GetCurrentProcess(),
							rt->m_hThread, 
							::GetCurrentProcess(),
							&m_hRenderThread,
							DUPLICATE_SAME_ACCESS,
							FALSE,
							0);
		::ResumeThread(m_hRenderThread);
		
		setupTimer(m_Renderer);
		// update render button
	} else {
		m_WinCanvas.reset();
		m_Canvas = nullptr;
	}
}

UINT CChildFrame::RenderControllingFunction(LPVOID pParam)
{
	CChildFrame* cf = (CChildFrame*)pParam;
	if (cf == NULL || !cf->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return 1;   // if cf is not valid

	cf->RunRenderThread();
	cf->PostMessageW(WinSystem::WM_USER_RENDER_COMPLETE);
	return 0;
}

void CChildFrame::RunRenderThread()
{
	RenderParameters rp = renderParams;	// make local copy

	switch (rp.action) {
	case RenderParameters::RenderActions::Animate:
		if (rp.animateFrame) {
			m_Renderer->animate(m_Canvas, rp.animateFrameCount,
				rp.frame, rp.animateZoom && !m_Engine->isTiledOrFrieze());
		} else {
			m_Renderer->animate(m_Canvas, rp.animateFrameCount, 0,
				rp.animateZoom && !m_Engine->isTiledOrFrieze());
			// delete animate canvas
		}
		break;
	case RenderParameters::RenderActions::SaveSVG:
		m_Renderer->draw(m_Canvas);
		// delete SVG canvas
		break;
	case RenderParameters::RenderActions::Render:
		m_Renderer->run(m_Canvas, rp.periodicUpdate);
		if (!m_Canvas && !m_Renderer->requestStop) {
			MakeCanvas(rp.width, rp.height);
			m_Renderer->draw(m_Canvas);
		}
		break;
	}
}

bool CChildFrame::isBusy()
{
	// Thread is considered "busy" until the handle is cleared in the UI thread
	//DWORD status;
	return m_hRenderThread != NULL; //&& ::GetExitCodeThread(m_hRenderThread, &status) && status == STILL_ACTIVE;
}

void CChildFrame::SetPostRenderAction(PostRenderAction v)
{
	switch (v) {
	case PostRenderAction::DoNothing:
	case PostRenderAction::Exit:
		m_ePostRenderAction = v;
		break;
	case PostRenderAction::Close:
		if (m_ePostRenderAction != PostRenderAction::Exit)
			m_ePostRenderAction = v;
		break;
	default:
		if (m_ePostRenderAction != PostRenderAction::Exit && m_ePostRenderAction != PostRenderAction::Close)
			m_ePostRenderAction = v;
		break;
	}
}
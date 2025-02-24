
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
#include "variation.h"
#include "RenderSize.h"
#include "Animate.h"
#include "MovieFileSave.h"
#include "ImageFileSave.h"
#include "WinPngCanvas.h"
#include <Gdipluspixelformats.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {
	Gdiplus::PixelFormat GetPixFormat(aggCanvas::PixelFormat pfmt)
	{
		switch (pfmt) {
		case aggCanvas::Gray8_Blend:
			return PixelFormat8bppIndexed;
		case aggCanvas::Gray16_Blend:
			return PixelFormat16bppGrayScale;
		case aggCanvas::RGB8_Blend:
			return PixelFormat24bppRGB;
		case aggCanvas::RGB16_Blend:
			return PixelFormat48bppRGB;
		case aggCanvas::RGBA8_Blend:
		case aggCanvas::RGBA8_Custom_Blend:
			return PixelFormat32bppARGB;
		case aggCanvas::RGBA16_Blend:
		case aggCanvas::RGBA16_Custom_Blend:
			return PixelFormat64bppPARGB;
		default:
			return 0;
		}
	}
}
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_RENDER, OnRender)
	ON_COMMAND(ID_RENDER_SIZE, OnRenderSize)
	ON_COMMAND(ID_RENDER_AGAIN, OnRenderAgain)
	ON_COMMAND(ID_ANIMATE, OnAnimate)
	ON_COMMAND(ID_ANIMATE_FRAME, OnAnimateFrame)
	ON_COMMAND(ID_RENDER_STOP, OnRenderStop)
	ON_COMMAND(ID_SAVE_IMAGE, OnSaveOutput)
	ON_UPDATE_COMMAND_UI(ID_SAVE_IMAGE, OnUpdateSaveImage)
	ON_UPDATE_COMMAND_UI(ID_RENDER_STOP, OnUpdateRenderStop)
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
	m_wndParent = dynamic_cast<CMainFrame *>(GetMDIFrameWndEx());
	m_vwCfdgEditor->GetEditCtrl().SetFont(&(m_wndParent->m_editFont));
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
		if (m_wndParent)
			m_wndParent->UpdateStatusBar(ProgressBar, statusText);
	} else {
		// update render box
		m_vwOutputView->Invalidate();
	}
	return 0;
}

LRESULT CChildFrame::OnMessage(WPARAM wParam, LPARAM lParam)
{
	std::unique_ptr<char[]> message((char*)wParam);
	m_wndParent->Message(message.get());
	if (message)
		m_wndParent->Message("\r\n");
	return 0;
}

void CChildFrame::RecvErrorLinkClick(LPCTSTR link)
{
	const wchar_t* start = link + 3;
	wchar_t* next = nullptr;
	int start_line = std::wcstol(start, &next, 10);
	if (*next != L':')
		return;
	start = next + 1;
	int start_char = std::wcstol(start, &next, 10);
	if (*next != L':')
		return;
	start = next + 1;
	int end_line = std::wcstol(start, &next, 10);
	if (*next != L':')
		return;
	start = next + 1;
	int end_char = std::wcstol(start, &next, 10);
	if (*next != L'\0')
		return;
	int start_line_char = m_vwCfdgEditor->GetEditCtrl().LineIndex(start_line - 1);
	int end_line_char = m_vwCfdgEditor->GetEditCtrl().LineIndex(end_line - 1);
	if (start_line_char >= 0 && end_line_char >= 0)
		m_vwCfdgEditor->GetEditCtrl().SetSel(start_line_char + start_char, end_line_char + end_char, TRUE);

}

LRESULT CChildFrame::OnRenderDone(WPARAM wParam, LPARAM lParam)
{
	m_Timer.Stop();
	::CloseHandle(m_hRenderThread);
	m_hRenderThread = NULL;

	if (renderParams.action == RenderParameters::RenderActions::SaveSVG)
		m_wndParent->Message("SVG save complete.\r\n");

	if (m_ePostRenderAction == PostRenderAction::Exit) {
		GetMDIFrame()->PostMessageW(WM_CLOSE);
		return 0;
	}
	if (m_ePostRenderAction == PostRenderAction::Close) {
		PostMessageW(WM_CLOSE);
		return 0;
	}

	if (!m_strMovieFile.empty()) {
		std::wstring tempMovie16 = Utf8ToUtf16(m_strMovieFile.c_str());
		bool moved = false;
		DWORD attr = ::GetFileAttributes(tempMovie16.c_str());
		if (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY)) {
			CString name = NameWithoutExtension();
			MovieFileSave fsDlg(tempMovie16, name);
			if (fsDlg.DoModal() == IDOK) {
				auto ofn = fsDlg.GetOFN();
				if (::MoveFileEx(tempMovie16.c_str(), ofn.lpstrFile, MOVEFILE_REPLACE_EXISTING)) {
					moved = true;
				} else {
					::MessageBeep(MB_ICONEXCLAMATION);
					::MessageBoxW(GetSafeHwnd(), _T("Failed to save movie."), _T("Movie file error"), MB_ICONEXCLAMATION);
				}
			}
		}
		if (!moved)
			::DeleteFile(tempMovie16.c_str());	// clean up unsaved movies
		m_strMovieFile.clear();					// file is moved or deleted
	}

	switch (m_ePostRenderAction) {
	case PostRenderAction::SaveOutput:
		OnSaveOutput();
		break;
	case PostRenderAction::Render:
		OnRender();
		break;
	case PostRenderAction::RenderSize:
		OnRenderSize();
		break;
	case PostRenderAction::Animate:
		OnAnimate();
		break;
	case PostRenderAction::AnimateFrame:
		OnAnimateFrame();
		break;
	default:
		break;
	}

	return 0;
}

void CChildFrame::OnRender()
{
	if (m_hRenderThread) {
		SetPostRenderAction(PostRenderAction::Render);
		return;
	}

	renderParams.action = RenderParameters::RenderActions::Render;
	renderParams.renderSize = false;

	CRect cr;
	m_vwOutputView->GetClientRect(&cr);
	renderParams.width = cr.Width();
	renderParams.height = cr.Height();

	DoRender(true);
}

void CChildFrame::OnRenderSize()
{
	if (m_hRenderThread) {
		SetPostRenderAction(PostRenderAction::RenderSize);
		return;
	}

	if (!m_bRenderAgain) {
		RenderSize rsDlg(renderParams, this);
		if (rsDlg.DoModal() != IDOK)
			return;
	}

	renderParams.action = RenderParameters::RenderActions::Render;
	renderParams.renderSize = true;
	renderParams.width = renderParams.RenderWidth;
	renderParams.height = renderParams.RenderHeight;

	DoRender(false);
}

void CChildFrame::OnRenderAgain()
{
	m_bRenderAgain = true;
	switch (renderParams.action) {
	case RenderParameters::RenderActions::Render:
	case RenderParameters::RenderActions::SaveSVG:
		if (renderParams.renderSize)
			OnRenderSize();
		else
			OnRender();
		break;
	case RenderParameters::RenderActions::Animate:
		if (renderParams.animateFrame)
			OnAnimateFrame();
		else
			OnAnimate();
		break;
	}
	m_bRenderAgain = false;
}

void CChildFrame::OnAnimate()
{
	if (m_hRenderThread) {
		SetPostRenderAction(PostRenderAction::Animate);
		return;
	}

	if (!m_bRenderAgain) {
		Animate aDlg(renderParams, false, this);
		if (aDlg.DoModal() != IDOK)
			return;
	}

	renderParams.action = RenderParameters::RenderActions::Animate;
	renderParams.animateFrame = false;

	DoRender(false);
}

void CChildFrame::OnAnimateFrame()
{
	if (m_hRenderThread) {
		SetPostRenderAction(PostRenderAction::AnimateFrame);
		return;
	}

	if (!m_bRenderAgain) {
		Animate aDlg(renderParams, true, this);
		if (aDlg.DoModal() != IDOK)
			return;
	}

	renderParams.action = RenderParameters::RenderActions::Animate;
	renderParams.animateFrame = true;

	DoRender(false);
}

void CChildFrame::OnRenderStop()
{
	if (m_hRenderThread && m_Renderer) {
		if (m_Renderer->requestFinishUp)
			m_Renderer->requestStop = true;
		else
			m_Renderer->requestFinishUp = true;
	}
}

void CChildFrame::OnSaveOutput()
{
	if (m_hRenderThread) {
		SetPostRenderAction(PostRenderAction::SaveOutput);
		return;
	}

	if (!m_WinCanvas || !m_Renderer) {
		::MessageBeep(MB_ICONASTERISK);
		MessageBoxW(_T("There is nothing to save."), NULL, MB_ICONASTERISK);
		return;
	}

	CString name = NameWithoutExtension();
	ImageFileSave ifsDlg(name, m_Renderer && m_Renderer->m_tiledCanvas, m_bCropped,
						 m_iJpegQuality, m_iMultWidth, m_iMultHeight);
	if (ifsDlg.DoModal() == IDOK) {
		std::string fileMB = Utf16ToUtf8(ifsDlg.m_ofn.lpstrFile);
		switch (ifsDlg.m_ofn.nFilterIndex) {
		case 1: {		// PNG
			WinPngCanvas saveCanvas(fileMB.c_str(), m_WinCanvas.get(), 
				m_bCropped || (m_Renderer && m_Renderer->m_tiledCanvas),
				renderParams.variation, m_Renderer.get(), m_iMultWidth, m_iMultHeight);
			saveCanvas.start(true, m_WinCanvas->mBackground, m_WinCanvas->cropWidth(),
				m_WinCanvas->cropHeight());
			saveCanvas.end();		// writes out the PNG file
			break;
		}
		case 2: {		// JPEG
			WinPngCanvas saveCanvas("", m_WinCanvas.get(), 
				m_bCropped || (m_Renderer && m_Renderer->m_tiledCanvas),
				renderParams.variation, m_Renderer.get(), m_iMultWidth, m_iMultHeight);
			saveCanvas.start(true, m_WinCanvas->mBackground, m_WinCanvas->cropWidth(),
				m_WinCanvas->cropHeight());
			saveCanvas.end();		// does not write a PNG file
			auto pixfmt = GetPixFormat(m_WinCanvas->mPixelFormat);
			if (pixfmt) {
				Gdiplus::Bitmap newBM(saveCanvas.mWidth, saveCanvas.mHeight, saveCanvas.mStride,
					pixfmt, (BYTE*)saveCanvas.mData.data());
				if (pixfmt == PixelFormat8bppIndexed)
					CContextFreeView::AddGrayPalette(&newBM);

				// image/jpeg : {557cf401-1a04-11d3-9a73-0000f81ef32e}
				const CLSID jpgEncoderClsId = { 0x557cf401, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };
				Gdiplus::Status  stat;
				Gdiplus::EncoderParameters encoderParameters;
				ULONG    quality = ifsDlg.m_iJpegQuality;

				encoderParameters.Count = 1;
				encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
				encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
				encoderParameters.Parameter[0].NumberOfValues = 1;
				encoderParameters.Parameter[0].Value = &quality;

				stat = newBM.Save(ifsDlg.m_ofn.lpstrFile, &jpgEncoderClsId, &encoderParameters);
				if (stat != Gdiplus::Status::Ok) {
					TRACE1("JPEG file save failed: %d\n", stat);
					::MessageBeep(MB_ICONASTERISK);
					::MessageBoxW(GetSafeHwnd(), _T("JPEG file save failed!"), _T(""), MB_ICONASTERISK);
				}
			}
			break;
		}
		case 3:			// SVG
			m_SvgCanvas = std::make_unique<SVGCanvas>(fileMB.c_str(), m_WinCanvas->mWidth,
				m_WinCanvas->mHeight, ifsDlg.m_bCropped);
			if (m_SvgCanvas->mError) {
				TRACE0("SVG file save failed\n");
				::MessageBeep(MB_ICONASTERISK);
				::MessageBoxW(GetSafeHwnd(), _T("SVG file save failed!"), _T(""), MB_ICONASTERISK);
				m_SvgCanvas.reset();
				break;
			}
			renderParams.action = RenderParameters::RenderActions::SaveSVG;
			SetPostRenderAction(PostRenderAction::DoNothing);
			PerformRender();
			m_wndParent->Message("Saving SVG file.\r\n");
			break;
		default:
			// unsupported
			break;
		}
	}
}

void CChildFrame::OnUpdateRenderStop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_hRenderThread && m_Renderer);
}

void CChildFrame::OnUpdateSaveImage(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_WinCanvas && m_Renderer && !m_hRenderThread);
}

void CChildFrame::OnNextVariation()
{
	++renderParams.variation;
	if (renderParams.variation > Variation::recommendedMax(6))
		renderParams.variation = Variation::recommendedMin();
}
void CChildFrame::OnPrevVariation()
{
	--renderParams.variation;
	if (renderParams.variation < Variation::recommendedMin())
		renderParams.variation = Variation::recommendedMax(6);
}

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
CString CChildFrame::NameWithoutExtension()
{
	CString name = m_CFdoc->GetPathName();
	if (name.IsEmpty())
		GetWindowTextW(name);
	::PathRemoveExtensionW(name.LockBuffer());
	name.UnlockBuffer();
	return name;
}

void CChildFrame::DoRender(bool shrinkTiled)
{
	OnMessage(0, 0);		// clear message window

	bool modifiedSinceRender = SyncToSystem();
	if (!modifiedSinceRender && !m_bReuseVariation && renderParams.action != RenderParameters::RenderActions::Animate)
		OnNextVariation();
	m_bReuseVariation = false;

	if (renderParams.variation == 0)
		OnNextVariation();

	bool useAnimateSize = renderParams.action == RenderParameters::RenderActions::Animate;
	int width = useAnimateSize ? renderParams.AnimateWidth : renderParams.width;
	int height = useAnimateSize ? renderParams.AnimateHeight : renderParams.height;

	m_Renderer.reset();		// TODO move deletion into async thread
	m_Engine.reset();
	m_WinCanvas.reset();
	m_Canvas = nullptr;
	m_vwOutputView->m_Renderer = nullptr;

	m_Engine = CFDG::ParseFile(m_System->mName.c_str(), m_System, renderParams.variation);
	if (!m_Engine) {
		::MessageBeep(0);
		m_wndParent->ShowMessages();
		return;
	}
	bool tiled = m_Engine->isTiledOrFrieze();
	if (shrinkTiled && tiled) {
		width = (9 * width) / 10;
		height = (9 * height) / 10;
	}

	m_vwOutputView->m_bTiled = tiled;
	m_vwOutputView->m_bBlendMode = m_Engine->usesBlendMode;

	m_Renderer = m_Engine->renderer(m_Engine, width, height,
		(float)renderParams.MinimumSize, renderParams.variation, renderParams.BorderSize);

	m_vwOutputView->m_Renderer = m_Renderer.get();

	if (!m_Renderer) {
		m_Engine.reset();
		::MessageBeep(MB_ICONEXCLAMATION);
		m_wndParent->ShowMessages();
		return;
	}

	if (renderParams.action == RenderParameters::RenderActions::Render) {
		renderParams.width = width;
		renderParams.height = height;
	}

	if (renderParams.action == RenderParameters::RenderActions::Animate ?
		renderParams.animateFrame : renderParams.PeriodicUpdate)
	{
		MakeCanvas(width, height);
	}

	if (renderParams.action == RenderParameters::RenderActions::Animate &&
		!renderParams.animateFrame)
	{
		m_AnimationCanvas = std::make_unique<ffCanvas>("", WinCanvas::SuggestPixelFormat(m_Engine.get()),
			renderParams.AnimateWidth, renderParams.AnimateHeight,
			renderParams.MovieFrameRate, (ffCanvas::QTcodec)renderParams.Codec, true);

		if (m_AnimationCanvas->mError) {
			::MessageBeep(MB_ICONEXCLAMATION);
			::MessageBoxA(GetSafeHwnd(), m_AnimationCanvas->mErrorMsg, "Animation Error", MB_ICONEXCLAMATION);
			m_AnimationCanvas.reset();
			return;
		}

		m_strMovieFile = m_AnimationCanvas->mFileName;
	}

	SetPostRenderAction(PostRenderAction::DoNothing);

	PerformRender();
}

bool CChildFrame::SyncToSystem()
{
	auto txt = m_CFdoc->GetCfdg();
	const CString& wname = m_CFdoc->GetPathName();
	std::string name = Utf16ToUtf8((LPCTSTR)wname);
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
		
		m_Timer.Start(m_Renderer);
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
			m_Renderer->animate(m_Canvas, rp.AnimateFrameCount,
				rp.MovieFrame, rp.AnimateZoom && !m_Engine->isTiledOrFrieze());
		} else {
			m_Renderer->animate(m_AnimationCanvas.get(), rp.AnimateFrameCount, 0,
				rp.AnimateZoom && !m_Engine->isTiledOrFrieze());
			m_AnimationCanvas.reset();
		}
		break;
	case RenderParameters::RenderActions::SaveSVG:
		m_Renderer->draw(m_SvgCanvas.get());	// draw SVG
		m_SvgCanvas.reset();					// save and close file
		break;
	case RenderParameters::RenderActions::Render:
		m_Renderer->run(m_Canvas, rp.PeriodicUpdate);
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
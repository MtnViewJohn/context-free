
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "RenderParams.h"
#include "cfdg.h"
#include "WinCanvas.h"
#include "ffCanvas.h"
#include <set>
#include "SVGCanvas.h"
#include "winTimer.h"

class CContextFreeView;
class CContextFreeDoc;
class WinSystem;
class CMainFrame;
class CFScintillaView;

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame() noexcept;

// Attributes
protected:
	CSplitterWnd m_wndSplitterCfdg;
	BOOL m_bInitSplitter = FALSE;
	CContextFreeDoc* m_CFdoc = nullptr;
	int m_iProgressDelay = 0;
public:
	BOOL m_bReuseVariation = FALSE;
	CFScintillaView* m_vwCfdgEditor = nullptr;
	CContextFreeView* m_vwOutputView = nullptr;
	static std::set<CChildFrame*> Children;

// Operations
public:
	bool CanClose(bool andExit);
// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	RenderParameters renderParams;
	std::shared_ptr<Renderer> m_Renderer;
	HANDLE m_hRenderThread = NULL;
	wincanvas_ptr m_WinCanvas;
	int m_iBusyIndex = 0;
	bool m_bDirty;
	void OnRenderAgain();
	void OnSaveOutput();
	void OnNextVariation();
	void OnPrevVariation();
	afx_msg void OnUpdateSaveImage(CCmdUI* pCmdUI);
	CString NameWithoutExtension();
	void RecvErrorLinkClick(LPCTSTR link);
	void UpdateDirtyIndicator(bool dirty);
	Gdiplus::Status SaveJPEG(IStream* out, LPCTSTR file, bool crop, int iMultWidth, int iMultHeight, int quality);
	void PaneResize();
protected:
	enum class PostRenderAction
	{
		DoNothing, Render, RenderSize, RenderRepeat,
		Animate, AnimateFrame, SaveOutput, Close, Exit
	};
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnStatusUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRenderDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateRenderStop(CCmdUI* pCmdUI);
	void OnRender();
	void OnRenderSize();
	void OnRenderStop();
	void OnAnimate();
	void OnAnimateFrame();
	afx_msg void OnClose();

	cfdg_ptr m_Engine;
	Canvas* m_Canvas = nullptr;
	WinSystem* m_System = nullptr;
	ffCanvas_ptr m_AnimationCanvas;
	svgCanvas_ptr m_SvgCanvas;
	PostRenderAction m_ePostRenderAction = PostRenderAction::DoNothing;
	void SetPostRenderAction(PostRenderAction v);
	bool m_bRenderAgain = false;
	std::string m_strMovieFile;
	int m_iJpegQuality = 80;
	int m_iMultWidth = 1;
	int m_iMultHeight = 1;
	bool m_bCropped = false;
	CMainFrame* m_wndParent = nullptr;

	void DoRender(bool shrinkTiled);
	bool SyncToSystem();
	void MakeCanvas(int width, int height);
	void PerformRender();
	static UINT RenderControllingFunction(LPVOID pParam);
	void RunRenderThread();
	bool isBusy();
	WinTimer m_Timer;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual HICON GetFrameIcon() const;
	afx_msg void OnInsertChars(UINT id);
	afx_msg void OnEditIndent(UINT id);
	afx_msg void OnColorCalculator();
	afx_msg void OnUploadGallery();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnFileRevert();
	afx_msg void OnUpdateFileRevert(CCmdUI* pCmdUI);
};

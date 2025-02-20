
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "RenderParams.h"
#include "cfdg.h"
#include "WinCanvas.h"
#include "ffCanvas.h"
#include <set>

class CContextFreeView;
class CContextFreeDoc;
class WinSystem;

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
	BOOL m_bReuseVariation = FALSE;
	int m_iProgressDelay = 0;
public:
	CEditView* m_vwCfdgEditor = nullptr;
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
	void OnRenderAgain();
	void OnNextVariation();
	void OnPrevVariation();
	CString NameWithoutExtension();
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
	void OnRender();
	void OnRenderSize();
	void OnAnimate();
	void OnAnimateFrame();
	afx_msg void OnClose();

	cfdg_ptr m_Engine;
	Canvas* m_Canvas = nullptr;
	WinSystem* m_System = nullptr;
	ffCanvas_ptr m_AnimationCanvas;
	PostRenderAction m_ePostRenderAction = PostRenderAction::DoNothing;
	void SetPostRenderAction(PostRenderAction v);
	bool m_bRenderAgain = false;
	std::string m_strMovieFile;

	void DoRender(bool shrinkTiled);
	bool SyncToSystem();
	void MakeCanvas(int width, int height);
	void PerformRender();
	static UINT RenderControllingFunction(LPVOID pParam);
	void RunRenderThread();
	bool isBusy();
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

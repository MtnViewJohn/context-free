
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "RenderParams.h"
#include "cfdg.h"
#include "WinCanvas.h"

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
	int m_iCurrentVariation = 42;
	int m_iProgressDelay = 0;
public:
	CEditView* m_vwCfdgEditor = nullptr;
	CContextFreeView* m_vwOutputView = nullptr;

// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnStatusUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRenderDone(WPARAM wParam, LPARAM lParam);
	void OnRender();
	void OnRenderSize();
	void OnRenderAgain();
	void OnAnimate();
	void OnAnimateFrame();
	void OnNextVariation();
	void OnPrevVariation();

	RenderParameters renderParams;
	cfdg_ptr m_Engine;
	std::shared_ptr<Renderer> m_Renderer;
	Canvas* m_Canvas = nullptr;
	wincanvas_ptr m_WinCanvas;
	WinSystem* m_System = nullptr;
	HANDLE m_hRenderThread = NULL;

	void DoRender(bool shrinkTiled);
	bool SyncToSystem();
	void MakeCanvas(int width, int height);
	void PerformRender();
	static UINT RenderControllingFunction(LPVOID pParam);
	void RunRenderThread();
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "pch.h"
#include "framework.h"
#include "ContextFree.h"

#include "ChildFrm.h"
#include "ContextFreeDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame() noexcept
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
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
	CCreateContext ccc;
	ccc.m_pNewViewClass = RUNTIME_CLASS(CEditView);

	CRect cr;
	GetClientRect(&cr);
	
	m_wndSplitterCfdg.CreateStatic(this, 1, 2);
	m_wndSplitterCfdg.CreateView(0, 0, RUNTIME_CLASS(CEditView), CSize(cr.Width() / 3, 0), pContext);
	m_wndSplitterCfdg.CreateView(0, 1, RUNTIME_CLASS(CEditView), CSize(0, 0), &ccc);

	m_vwCfdgEditor = (CEditView*)m_wndSplitterCfdg.GetPane(0, 0);
	m_vwDummyView = (CEditView*)m_wndSplitterCfdg.GetPane(0, 1);
	m_vwDummyView->GetEditCtrl().SetReadOnly(TRUE);

	CMainFrame* mf = dynamic_cast<CMainFrame *>(GetMDIFrameWndEx());
	m_vwCfdgEditor->GetEditCtrl().SetFont(&(mf->m_editFont));

	((CContextFreeDoc*)(pContext->m_pCurrentDoc))->m_vwEditorView = m_vwCfdgEditor;

	CString sizeText;
	CRect cr2;
	m_wndSplitterCfdg.GetClientRect(&cr2);
	sizeText.Format(_T("Client size (%d, %d)\nSplitter size (%d, %d)"), cr.Width(), cr.Height(), cr2.Width(), cr2.Height());
	m_vwDummyView->SetWindowTextW((LPCTSTR)sizeText);

	m_bInitSplitter = TRUE;

	GetMDIFrame()->PostMessageW(WM_TICKLE_SIZE, 0, 0);

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
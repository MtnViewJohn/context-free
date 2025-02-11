
// ContextFreeView.cpp : implementation of the CContextFreeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ContextFree.h"
#endif

#include "ContextFreeDoc.h"
#include "ContextFreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContextFreeView

IMPLEMENT_DYNCREATE(CContextFreeView, CView)

BEGIN_MESSAGE_MAP(CContextFreeView, CView)
END_MESSAGE_MAP()

// CContextFreeView construction/destruction

CContextFreeView::CContextFreeView() noexcept
{
	// TODO: add construction code here

}

CContextFreeView::~CContextFreeView()
{
}

BOOL CContextFreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CContextFreeView drawing

void CContextFreeView::OnDraw(CDC* /*pDC*/)
{
	CContextFreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CContextFreeView diagnostics

#ifdef _DEBUG
void CContextFreeView::AssertValid() const
{
	CView::AssertValid();
}

void CContextFreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContextFreeDoc* CContextFreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContextFreeDoc)));
	return (CContextFreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CContextFreeView message handlers

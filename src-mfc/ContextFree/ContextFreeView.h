
// ContextFreeView.h : interface of the CContextFreeView class
//

#pragma once

#include "WinCanvas.h"

class CContextFreeView : public CView
{
protected: // create from serialization only
	CContextFreeView() noexcept;
	DECLARE_DYNCREATE(CContextFreeView)

// Attributes
public:
	CContextFreeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnEraseBkgnd(CDC* pDC);
protected:

// Implementation
public:
	virtual ~CContextFreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	wincanvas_ptr* m_pWinCanvas = nullptr;
	BOOL m_bTiled;
	BOOL m_bBlendMode;
	int m_iBoxSize = 0;

protected:
	void DrawCheckerBoard(Gdiplus::Graphics& g, Gdiplus::Rect destRect);
// Generated message map functions
protected:
	std::unique_ptr<Gdiplus::Bitmap> MakeBitmap(bool cropped);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ContextFreeView.cpp
inline CContextFreeDoc* CContextFreeView::GetDocument() const
   { return reinterpret_cast<CContextFreeDoc*>(m_pDocument); }
#endif


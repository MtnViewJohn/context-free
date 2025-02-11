
// ContextFreeView.h : interface of the CContextFreeView class
//

#pragma once


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
protected:

// Implementation
public:
	virtual ~CContextFreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ContextFreeView.cpp
inline CContextFreeDoc* CContextFreeView::GetDocument() const
   { return reinterpret_cast<CContextFreeDoc*>(m_pDocument); }
#endif


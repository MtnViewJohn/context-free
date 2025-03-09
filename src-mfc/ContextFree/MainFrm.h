
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "MessagePane.h"
#include "ColorCalculator.h"

//-----------------
// Statusbar panes:
//-----------------
const int nStatusProgress = 0;
const int nStatusText = 1;

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame() noexcept;

// Attributes
public:
	static LPCTSTR NextExample;
// Operations
public:
	void UpdateStatusBar(int progress, const CString& text);
	void UpdateEditors(bool font, bool style);
	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void Message(LPCSTR msg);
	void ShowMessages(BOOL bShow = TRUE);
	BOOL ShowColorCalculator(BOOL bShow);
	void ForwardLink(LPCTSTR link);

protected:  // control bar embedded members
	CMFCStatusBar     m_wndStatusBar;
	CPaneDialog m_wndRenderbar;
	MessagePane m_wndMessageLog;
	HMENU m_hSplitMenu = NULL;
	ColorCalculator m_wndColorCalc;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRenderBar(UINT id);
public:
	afx_msg void OnExample(UINT id);
protected:
	afx_msg void OnUpdateRenderBar(CCmdUI* pCmdUI);
	afx_msg void OnRenderSplitMenu(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnRenderVariationUD(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnRenderFrameUD(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnRenderEdits(UINT id);
	afx_msg void OnPreferences();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

};



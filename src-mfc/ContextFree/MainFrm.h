
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "MessagePane.h"
#include "ColorCalculator.h"
#include "CFDropTarget.h"

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
	static std::string NextString;
	static CString NextName;
	static int NextVariation;

// Operations
public:
	void UpdateStatusBar(int progress, const CString& text);
	void UpdateEditors(bool font, bool style);
	DROPEFFECT OnDragEnter(COleDataObject* pDataObject);
	DROPEFFECT OnDragOver(COleDataObject* pDataObject);
	BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect);
	CFDropTarget m_CFDropTarget;

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
	bool m_bVariationSpinInit = false;
	void DownLoadGallery(std::wstring_view wview);

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRenderBar(UINT id);
	afx_msg LRESULT DownloadDone(WPARAM wParam, LPARAM lParam);
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



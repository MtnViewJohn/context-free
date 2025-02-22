#pragma once

class CMainFrame;

// MessagePane

class MessagePane : public CDockablePane
{
	DECLARE_DYNAMIC(MessagePane)

public:
	MessagePane();
	virtual ~MessagePane();

	void Message(LPCSTR msg);
	CMainFrame* m_wndMainFrm = nullptr;
protected:
	CRichEditCtrl m_wndRichLog;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLink(NMHDR* pnm, LRESULT* pResult);
};



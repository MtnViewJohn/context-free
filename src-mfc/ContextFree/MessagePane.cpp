// MessagePane.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "MessagePane.h"
#include <algorithm>
#include "MainFrm.h"

namespace {
    struct StreamInRtfCallbackData
    {
        char const* pRtf;
        size_t size;
    };

    DWORD CALLBACK StreamInRtfCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
    {
        StreamInRtfCallbackData* pData = reinterpret_cast<StreamInRtfCallbackData*>(dwCookie);

        // Copy the number of bytes requested by the control or the number of remaining characters
        // of the source buffer, whichever is smaller.
        size_t sizeToCopy = std::min<size_t>(cb, pData->size);
        memcpy(pbBuff, pData->pRtf, sizeToCopy);

        *pcb = (LONG)sizeToCopy;

        pData->pRtf += sizeToCopy;
        pData->size -= sizeToCopy;

        return 0;
    }

    DWORD StreamInRtf(CRichEditCtrl& richEdit, char const* pRtf, size_t size = -1, bool selection = false)
    {
        bool isRtf = std::strncmp(pRtf, "{\\rtf", 5) == 0;

        StreamInRtfCallbackData data;
        data.pRtf = pRtf;
        data.size = (size == -1 ? strlen(pRtf) : size);

        EDITSTREAM es;
        es.dwCookie = reinterpret_cast<DWORD_PTR>(&data);
        es.dwError = 0;
        es.pfnCallback = StreamInRtfCallback;

        int flags = (CP_UTF8 << 16) | SF_USECODEPAGE | (isRtf ? SF_RTF : SF_TEXT) | (selection ? SFF_SELECTION : 0);

        richEdit.StreamIn(flags, es);

        return es.dwError;
    }
}

// MessagePane

IMPLEMENT_DYNAMIC(MessagePane, CDockablePane)

MessagePane::MessagePane()
{

}

MessagePane::~MessagePane()
{
}

void MessagePane::Message(LPCSTR msg)
{
    if (msg) {
        DWORD err = StreamInRtf(m_wndRichLog, msg, -1, true);
        if (err) {
            TRACE2("Log error: %d %d\n", err, GetLastError());
        }
        m_wndRichLog.SendMessageW(WM_VSCROLL, SB_BOTTOM, 0);
    } else {
        m_wndRichLog.SetWindowTextW(_T(""));
    }
}


BEGIN_MESSAGE_MAP(MessagePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(EN_LINK, IDC_RICHLOG, OnLink)
END_MESSAGE_MAP()



// MessagePane message handlers



int MessagePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndRichLog.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL| ES_READONLY | ES_MULTILINE, 
                             rectDummy, this, IDC_RICHLOG)) {
		TRACE0("Could not create log window\n");
		return -1;
	}

	m_wndRichLog.SetEventMask(m_wndRichLog.GetEventMask() | ENM_LINK);

	return 0;
}

void MessagePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// fill whole client area
	m_wndRichLog.SetWindowPos(nullptr, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MessagePane::OnLink(NMHDR* pnm, LRESULT* pResult)
{
    ENLINK* link = reinterpret_cast<ENLINK*>(pnm);
    if (link->nmhdr.idFrom == IDC_RICHLOG && link->msg == WM_LBUTTONDOWN) {
        CString url;
        m_wndRichLog.GetTextRange(link->chrg.cpMin, link->chrg.cpMax, url);
        TRACE1("Link click: %s\n", (LPCTSTR)url);
        m_wndMainFrm->ForwardLink((LPCTSTR)url);
    }
}

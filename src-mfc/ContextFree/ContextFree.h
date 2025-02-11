
// ContextFree.h : main header file for the ContextFree application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#define WM_TICKLE_SIZE (WM_APP + 1)

// CContextFreeApp:
// See ContextFree.cpp for the implementation of this class
//

class CContextFreeApp : public CWinAppEx
{
public:
	CContextFreeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern CContextFreeApp theApp;

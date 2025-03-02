
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
	ULONG_PTR gdiplusToken;
	BOOL m_bRichEdit5;
	afx_msg void OnAppAbout();
	[[nodiscard]] CString GetModuleFileName(_Inout_opt_ DWORD* pdwLastError = nullptr);
	[[nodiscard]] HMODULE LoadLibraryFromApplicationDirectory(_In_z_ LPCTSTR lpFileName);
	HINSTANCE m_hScintilla{ nullptr };
	HINSTANCE m_hLexilla{ nullptr };
	Lexilla::CreateLexerFn m_pCreateLexer{ nullptr };
	DECLARE_MESSAGE_MAP()
};

extern CContextFreeApp theApp;

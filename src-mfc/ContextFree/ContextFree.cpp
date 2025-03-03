
// ContextFree.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ContextFree.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ContextFreeDoc.h"
#include "ContextFreeView.h"
#include "Settings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContextFreeApp

BEGIN_MESSAGE_MAP(CContextFreeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CContextFreeApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CContextFreeApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CContextFreeApp::OnFileOpen)
END_MESSAGE_MAP()


// CContextFreeApp construction

CContextFreeApp::CContextFreeApp() noexcept
{

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Ozonesoft.ContextFree.AppID.342"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CContextFreeApp object

CContextFreeApp theApp;

CString CContextFreeApp::GetModuleFileName(_Inout_opt_ DWORD* pdwLastError)
{
	CString sModuleFileName;
	DWORD dwSize{ _MAX_PATH };
	while (true)
	{
		TCHAR* pszModuleFileName{ sModuleFileName.GetBuffer(dwSize) };
		const DWORD dwResult{ ::GetModuleFileName(nullptr, pszModuleFileName, dwSize) };
		if (dwResult == 0)
		{
			if (pdwLastError != nullptr)
				*pdwLastError = GetLastError();
			sModuleFileName.ReleaseBuffer(0);
			return CString{};
		} else if (dwResult < dwSize)
		{
			if (pdwLastError != nullptr)
				*pdwLastError = ERROR_SUCCESS;
			sModuleFileName.ReleaseBuffer(dwResult);
			return sModuleFileName;
		} else if (dwResult == dwSize)
		{
			sModuleFileName.ReleaseBuffer(0);
			dwSize *= 2;
		}
	}
}

HMODULE CContextFreeApp::LoadLibraryFromApplicationDirectory(_In_z_ LPCTSTR lpFileName)
{
	//Get the Application directory
	CString sFullPath{ GetModuleFileName() };
	if (sFullPath.IsEmpty())
#pragma warning(suppress: 26487)
		return nullptr;

	//Form the new path
	std::filesystem::path path{ sFullPath.GetString() };
	std::filesystem::path DLLPath{ lpFileName };
	path.replace_filename(DLLPath.filename());

	//Delegate to LoadLibrary
	return LoadLibraryW(path.c_str());
}

// CContextFreeApp initialization

BOOL CContextFreeApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();
	m_bRichEdit5 = AfxInitRichEdit5();
	if (!m_bRichEdit5)
		AfxInitRichEdit2();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//Load the Scintilla \ Lexilla dlls
	CString sLexillaDLL;
	sLexillaDLL.Format(_T("%s%s"), _T(LEXILLA_LIB), _T(LEXILLA_EXTENSION));
	m_hLexilla = LoadLibraryFromApplicationDirectory(sLexillaDLL);
	if (m_hLexilla == nullptr) {
		CString sMsg;
		sMsg.Format(_T("%s is not installed, Please built the Scintilla '%s' and copy it into this application's directory\r\nError: %d"), sLexillaDLL.GetString(), sLexillaDLL.GetString(), GetLastError());
		AfxMessageBox(sMsg);
		return FALSE;
	}
	m_hScintilla = LoadLibraryFromApplicationDirectory(_T("Scintilla.dll"));
	if (m_hScintilla == nullptr) {
		AfxMessageBox(_T("Scintilla DLL is not installed, Please built the Scintilla 'Scintilla.dll' and copy it into this application's directory"));
		return FALSE;
	}

	//Create the C++ Lexer from Lexilla
#pragma warning(suppress: 26490)
	m_pCreateLexer = reinterpret_cast<Lexilla::CreateLexerFn>(GetProcAddress(m_hLexilla, LEXILLA_CREATELEXER)); //NOLINT(clang-diagnostic-cast-function-type-mismatch)
	if (m_pCreateLexer == nullptr)
	{
		AfxMessageBox(_T("Could not find the Lexilla CreateLexer function"));
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("OzoneSoft"));
	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ContextFreeTYPE,
		RUNTIME_CLASS(CContextFreeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CContextFreeView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	Settings setting;
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	switch (Settings::AtLaunch) {
	case Settings::LaunchActions::NoDocument:
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
			cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
		break;
	case Settings::LaunchActions::NewDocument:
		break;
	case Settings::LaunchActions::Welcome:
		pMainFrame->OnExample(0);
		break;
	}

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CContextFreeApp::ExitInstance()
{
	//Unload the Scintilla \ Lexilla dlls
	if (m_hScintilla != nullptr) {
		FreeLibrary(m_hScintilla);
		m_hScintilla = nullptr;
	}
	if (m_hLexilla != nullptr) {
		FreeLibrary(m_hLexilla);
		m_hLexilla = nullptr;
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return CWinAppEx::ExitInstance();
}

// CContextFreeApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_sCopyright;
	CString m_sMainCopyright;
	CString m_sTitle;
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
, m_sCopyright(
L"CFDG Copyright © 2005 Chris Coyne\r\n"
L"Anti-Grain Geometry library Copyright © 2002-2006 Maxim Shemanarev\r\n"
L"LLVM/libc++ random functions from <random> Copyright © 2009-2015 LLVM Team\r\n"
L"Scintilla text editor component, Copyright © 1998-2025 by Neil Hodgson <neilh@scintilla.org>\r\n"
L"CScintillaCtrl, CScintillaView & CScintillaDoc, Copyright © 2004-2025 by PJ Naughter <pjna@naughter.com>\r\n"
L"This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.\r\n"
L"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.\r\n"
L"You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA"
)
, m_sMainCopyright(_T("Copyright © 2005-2025\r\nJohn Horigan && Mark Lentczner"))
, m_sTitle(_T("Context Free, Version 3.4.2(v49)"))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COPYRIGHT, m_sCopyright);
	DDX_Text(pDX, IDC_COPYRIGHT2, m_sMainCopyright);
	DDX_Text(pDX, IDC_TITLE, m_sTitle);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CContextFreeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CContextFreeApp message handlers




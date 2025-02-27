// Preferences.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "Preferences.h"


// Preferences

IMPLEMENT_DYNAMIC(Preferences, CPropertySheet)

Preferences::Preferences()
	:CPropertySheet(_T("Preferences")), m_bFontChanged(m_wndEditorPage.m_FontChanged)
{
	AddPage(&m_wndGeneralPage);
	AddPage(&m_wndEditorPage);
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

Preferences::~Preferences()
{
}


BEGIN_MESSAGE_MAP(Preferences, CPropertySheet)
END_MESSAGE_MAP()


// Preferences message handlers

// PrefsPageGeneral.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "PrefsPageGeneral.h"
#include "Settings.h"

// PrefsPageGeneral dialog

IMPLEMENT_DYNAMIC(PrefsPageGeneral, CPropertyPage)

PrefsPageGeneral::PrefsPageGeneral()
	: CPropertyPage(IDD_PREF_GENERAL),
	m_bOpenRender(Settings::RenderOnOpen),
	m_bProgressive(Settings::PeriodicUpdate),
	m_iAtLaunch(2 - (int)Settings::AtLaunch)
{
}

PrefsPageGeneral::~PrefsPageGeneral()
{
}

void PrefsPageGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_WELCOME, m_iAtLaunch);
	DDX_Control(pDX, IDC_BORDERSLIDER, m_ctrlBorderSize);
	DDX_Check(pDX, IDC_OPENRENDER, m_bOpenRender);
	DDX_Check(pDX, IDC_PROGRESSIVE, m_bProgressive);
}


BEGIN_MESSAGE_MAP(PrefsPageGeneral, CPropertyPage)
END_MESSAGE_MAP()


// PrefsPageGeneral message handlers

BOOL PrefsPageGeneral::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_ctrlBorderSize.SetRange(-100, 200);
	m_ctrlBorderSize.SetTicFreq(100);
	m_ctrlBorderSize.SetPos((int)(Settings::BorderSize * 100.0));

	return TRUE;
}

void PrefsPageGeneral::OnOK()
{
	Settings::AtLaunch = (Settings::LaunchActions)(2 - m_iAtLaunch);
	Settings::BorderSize = m_ctrlBorderSize.GetPos() / 100.0;
	Settings::RenderOnOpen = m_bOpenRender;
	Settings::PeriodicUpdate = m_bProgressive;

	Settings::Save(true);
	RenderParameters::Save();

	CPropertyPage::OnOK();
}

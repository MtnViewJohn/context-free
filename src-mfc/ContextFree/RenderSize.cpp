// RenderSize.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "RenderSize.h"

// RenderSize dialog

IMPLEMENT_DYNAMIC(RenderSize, CDialog)

RenderSize::RenderSize(RenderParameters& p, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RenderSize, pParent),
	  params(p)
{

}

RenderSize::~RenderSize()
{
}

void RenderSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDERWIDTH, m_ctrlWidth);
	DDX_Control(pDX, IDC_RENDERHEIGHT, m_ctrlHeight);
	DDX_Control(pDX, IDC_MINSIZE, m_ctrlMinSize);
	DDX_Control(pDX, IDC_BORDERSLIDER, m_ctrlBorderSize);
	DDX_Control(pDX, IDC_NODISPLAY, m_ctrlNoDisplay);
}


BEGIN_MESSAGE_MAP(RenderSize, CDialog)
	ON_EN_CHANGE(IDC_MINSIZE, &RenderSize::OnChangeMinsize)
END_MESSAGE_MAP()


// RenderSize message handlers

BOOL RenderSize::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemInt(IDC_RENDERWIDTH, params.RenderWidth, FALSE);
	SetDlgItemInt(IDC_RENDERHEIGHT, params.RenderHeight, FALSE);

	m_MinString = std::to_wstring(params.MinimumSize);
	m_MinValue = params.MinimumSize;
	SetDlgItemTextW(IDC_MINSIZE, m_MinString.c_str());

	m_ctrlBorderSize.SetRange(-100, 200);
	m_ctrlBorderSize.SetTicFreq(100);
	m_ctrlBorderSize.SetPos((int)(params.BorderSize * 100.0));

	m_ctrlNoDisplay.SetCheck(params.SuppressDisplay ? BST_CHECKED : BST_UNCHECKED);

	return TRUE;
}

void RenderSize::OnOK()
{
	BOOL ok;
	auto v = GetDlgItemInt(IDC_RENDERWIDTH, &ok, FALSE);
	if (ok) {
		params.RenderWidth = (int)v;
	}
	v = GetDlgItemInt(IDC_RENDERHEIGHT, &ok, FALSE);
	if (ok) {
		params.RenderHeight = (int)v;
	}

	params.MinimumSize = m_MinValue;
	params.BorderSize = m_ctrlBorderSize.GetPos() / 100.0;
	params.SuppressDisplay = m_ctrlNoDisplay.GetState() == BST_CHECKED;
	params.Save();

	CDialog::OnOK();
}

void RenderSize::OnChangeMinsize()
{
	auto newTextLen = m_ctrlMinSize.GetWindowTextLengthW();

	std::wstring newText(newTextLen, L' ');
	m_ctrlMinSize.GetWindowTextW(newText.data(), newTextLen + 1);

	if (newText.empty()) {
		m_MinString.clear();
		m_MinValue = 0.0;
		return;
	}

	try {
		wchar_t* wend;
		double v = std::wcstod(newText.c_str(), &wend);
		if (*wend == L'\0') {
			m_MinString = newText;
			m_MinValue = v;
			return;
		}
	} catch (...) {}

	m_ctrlMinSize.SetWindowTextW(m_MinString.c_str());
}

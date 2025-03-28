// Animate.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "Animate.h"

namespace {
	auto rateStrings =
		{ _T("8"), _T("10"), _T("12"), _T("15"), _T("24"), _T("25"), _T("30"), _T("50"), _T("60") };
}

std::vector<int> Animate::Rates{ 8, 10, 12, 15, 24, 25, 30, 50, 60 };

// Animate dialog

IMPLEMENT_DYNAMIC(Animate, CDialog)

Animate::Animate(RenderParameters& p, bool frame, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Animate, pParent)
	, params(p)
	, m_iLength(p.MovieLength)
	, m_iFrameRate(p.MovieFrameRate)
	, m_bFrame(frame)
{

}

Animate::~Animate()
{
}

void Animate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDERWIDTH, m_ctrlWidth);
	DDX_Control(pDX, IDC_RENDERHEIGHT, m_ctrlHeight);
	DDX_Control(pDX, IDC_MINSIZE, m_ctrlMinSize);
	DDX_Control(pDX, IDC_BORDERSLIDER, m_ctrlBorderSize);
	DDX_Control(pDX, IDC_ZOOM, m_ctrlZoom);
	DDX_Control(pDX, IDC_LENGTH, m_ctrlLength);
	DDX_Control(pDX, IDC_FRAMERATE, m_ctrlFrameRate);
	DDX_Control(pDX, IDC_CODEC, m_ctrlCodec);
	DDX_Control(pDX, IDC_FRAME_LABEL, m_ctrlFrameLabel);
	DDX_Control(pDX, IDC_FRAME, m_ctrlFrame);
	DDX_Control(pDX, IDC_CODEC_LABEL, m_ctrlCodecLabel);
	DDX_Control(pDX, IDC_FRAME_SPIN, m_ctrlFrameSpin);
}


BEGIN_MESSAGE_MAP(Animate, CDialog)
	ON_EN_CHANGE(IDC_MINSIZE, &Animate::OnChangeMinsize)
	ON_EN_CHANGE(IDC_LENGTH, &Animate::OnChangeLength)
	ON_CBN_SELCHANGE(IDC_FRAMERATE, &Animate::OnChangeFramerate)
END_MESSAGE_MAP()


// Animate message handlers

BOOL Animate::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowTextW(m_bFrame ? _T("Animate a Frame") : _T("Animate"));

	SetDlgItemInt(IDC_RENDERWIDTH, params.AnimateWidth, FALSE);
	SetDlgItemInt(IDC_RENDERHEIGHT, params.AnimateHeight, FALSE);

	m_MinString = std::to_wstring(params.MinimumSize);
	m_MinValue = params.MinimumSize;
	SetDlgItemTextW(IDC_MINSIZE, m_MinString.c_str());

	m_ctrlBorderSize.SetRange(-100, 200);
	m_ctrlBorderSize.SetTicFreq(100);
	m_ctrlBorderSize.SetPos((int)(params.BorderSize * 100.0));

	m_ctrlZoom.SetCheck(params.AnimateZoom ? BST_CHECKED : BST_UNCHECKED);

	SetDlgItemInt(IDC_LENGTH, params.MovieLength, FALSE);

	for (auto rate : rateStrings)
		m_ctrlFrameRate.AddString(rate);
	auto it = std::find(Rates.begin(), Rates.end(), m_iFrameRate);
	if (it == Rates.end())
		m_ctrlFrameRate.SetCurSel(3);		// 15fps
	else
		m_ctrlFrameRate.SetCurSel((int)(it - Rates.begin()));

	m_ctrlCodec.AddString(_T("H.264"));
	m_ctrlCodec.AddString(_T("ProRes"));
	m_ctrlCodec.SetCurSel((int)(params.Codec));
	m_ctrlCodecLabel.ShowWindow(m_bFrame ? SW_HIDE : SW_SHOWNA);
	m_ctrlCodec.ShowWindow(m_bFrame ? SW_HIDE : SW_SHOWNA);

	m_ctrlFrameSpin.SetRange32(1, m_iLength * m_iFrameRate);
	m_ctrlFrameSpin.SetPos32(params.MovieFrame);
	m_ctrlFrameLabel.ShowWindow(m_bFrame ? SW_SHOWNA : SW_HIDE);
	m_ctrlFrame.ShowWindow(m_bFrame ? SW_SHOWNA : SW_HIDE);
	m_ctrlFrameSpin.ShowWindow(m_bFrame ? SW_SHOWNA : SW_HIDE);

	return TRUE;
}

void Animate::OnOK()
{
	BOOL ok;
	auto v = GetDlgItemInt(IDC_RENDERWIDTH, &ok, FALSE);
	if (ok) {
		params.AnimateWidth = (int)v;
	}
	v = GetDlgItemInt(IDC_RENDERHEIGHT, &ok, FALSE);
	if (ok) {
		params.AnimateHeight = (int)v;
	}

	params.MinimumSize = m_MinValue;
	params.BorderSize = m_ctrlBorderSize.GetPos() / 100.0;

	params.AnimateZoom = m_ctrlZoom.GetState() == BST_CHECKED;

	params.MovieLength = m_iLength;
	params.MovieFrameRate = m_iFrameRate;
	params.AnimateFrameCount = m_iLength * m_iFrameRate;

	if (!m_bFrame)
		params.Codec = (RenderParameters::Codecs)m_ctrlCodec.GetCurSel();

	params.MovieFrame = m_ctrlFrameSpin.GetPos32();

	params.Save();

	CDialog::OnOK();
}

void Animate::OnChangeMinsize()
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

void Animate::OnChangeLength()
{
	CString len;
	GetDlgItemText(IDC_LENGTH, len);
	if (len.IsEmpty())
		return;

	BOOL ok;
	auto v = GetDlgItemInt(IDC_LENGTH, &ok, FALSE);
	if (ok && v > 0) {
		m_iLength = (int)v;
		m_ctrlFrameSpin.SetRange32(1, m_iLength * m_iFrameRate);
		m_ctrlFrameSpin.SetPos32(std::clamp(m_ctrlFrameSpin.GetPos32(), 1, m_iLength * m_iFrameRate));
	}
}

void Animate::OnChangeFramerate()
{
	m_iFrameRate = *(Rates.begin() + m_ctrlFrameRate.GetCurSel());
	m_ctrlFrameSpin.SetRange32(1, m_iLength * m_iFrameRate);
	m_ctrlFrameSpin.SetPos32(std::clamp(m_ctrlFrameSpin.GetPos32(), 1, m_iLength * m_iFrameRate));
}

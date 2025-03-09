// ColorCalculator.cpp : implementation file
//

#include "pch.h"
#include "ContextFree.h"
#include "afxdialogex.h"
#include "ColorCalculator.h"
#include "HSBColor.h"

#define EQUALITY_THRESHOLD  0.00001

namespace {
	// Black for light colors. White for dark colors.
	COLORREF ContrastColor(COLORREF col)
	{
		DWORD lightness = GetRValue(col) * 77 + GetGValue(col) * 150 + GetBValue(col) * 29;
		return lightness > 32768 ? RGB(0, 0, 0) : RGB(255, 255, 255);
	}

	static const wchar_t* RGBformat = L"%3d %3d %3d";
	static const wchar_t* HSVformat = L"h %g sat %g b %g";

	// Put window text onto the clipboard
	void CopyText(CWnd& wnd)
	{
		CString txt;
		wnd.GetWindowTextW(txt);

		if (::OpenClipboard(NULL)) {
			::EmptyClipboard();

			if (HGLOBAL hClipboardData = ::GlobalAlloc(GMEM_DDESHARE, sizeof(TCHAR) * ((size_t)txt.GetLength() + 1))) {

				if (TCHAR* pchData = (TCHAR*)GlobalLock(hClipboardData)) {

					::wcscpy_s(pchData, (size_t)txt.GetLength() + 1, (LPCTSTR)txt);

					GlobalUnlock(hClipboardData);

					SetClipboardData(CF_UNICODETEXT, hClipboardData);
				}
			}

			CloseClipboard();
		}
	}

	// Return true is field text is valid and changes the value,
	// false otherwise. "" and "." are valid representations of
	// 0.0
	bool CheckDoubleText(CEdit& ctrl, double& val)
	{
		CString txt;
		ctrl.GetWindowTextW(txt);

		if (txt.GetLength() == 0 || txt == L".") {
			if (val == 0.)
				return false;
			val = 0.;
			return true;
		}

		wchar_t* end = nullptr;
		double v = std::wcstod((LPCTSTR)txt, &end);
		if (std::isfinite(v) && end && *end == L'\0') {
			if (std::fabs(val - v) < EQUALITY_THRESHOLD)
				return false;
			val = v;
		} else {
			txt.Format(L"%g", val);
			ctrl.SetWindowTextW((LPCTSTR)txt);
			::MessageBeep(MB_ICONERROR);
			return false;
		}
		return true;
	}

	class EditLock
	{
	public:
		EditLock()
		: m_iLock (MasterLock++)
		{ }

		~EditLock()
		{
			MasterLock--;
		}

		EditLock(const EditLock&) = delete;
		EditLock(EditLock&&) = delete;
		EditLock& operator=(const EditLock&) = delete;
		EditLock& operator=(EditLock&&) = delete;

		explicit operator bool() const
		{
			return m_iLock == 0;
		}

	protected:
		inline static int MasterLock = 0;
		int m_iLock;
	};

	double adjustFrom(double to, double from, unsigned int steps)
	{
		if (std::fabs(to - from) < EQUALITY_THRESHOLD)
			return 0.0;

		if (to > from)
			return -adjustFrom(1.0 - to, 1.0 - from, steps);

		// from >= EQUALITY_THRESHOLD
		if (steps == 1)
			return to / from - 1.0;

		return std::pow(to / from, 1.0 / ((double)steps)) - 1.0;
	}

	double adjustHueFrom(double to, double from, unsigned int steps)
	{
		return (to - from) / (double)steps;
	}
}

// ColorCalculator dialog

IMPLEMENT_DYNAMIC(ColorCalculator, CDialogEx)

ColorCalculator::ColorCalculator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORCALC, pParent)
	, m_sRGBtext(_T(""))
{
	m_hDropperCursor = theApp.LoadCursorW(IDC_DROPPER);
	m_hStandardCursor = theApp.LoadStandardCursor(IDC_ARROW);
}

ColorCalculator::~ColorCalculator()
{

}

void ColorCalculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_PICKER, m_ctrlColorPicker);
	DDX_Control(pDX, IDC_LUM_PICKER, m_ctrlLumPicker);
	DDX_Control(pDX, IDC_RED_PICKER, m_ctrlRedPicker);
	DDX_Control(pDX, IDC_GREEN_PICKER, m_ctrlGreenPicker);
	DDX_Control(pDX, IDC_BLUE_PICKER, m_ctrlBluePicker);
	DDX_Control(pDX, IDC_START_SELECT, m_ctrlStartSelect);
	DDX_Control(pDX, IDC_END_SELECT, m_ctrlEndSelect);
	DDX_Text(pDX, IDC_RGB_TEXT, m_sRGBtext);
	DDX_Control(pDX, IDC_START_HUE, m_ctrlStartHue);
	DDX_Control(pDX, IDC_START_SAT, m_ctrlStartSat);
	DDX_Control(pDX, IDC_START_VAL, m_ctrlStartVal);
	DDX_Control(pDX, IDC_END_HUE, m_ctrlEndHue);
	DDX_Control(pDX, IDC_END_SAT, m_ctrlEndSat);
	DDX_Control(pDX, IDC_END_VAL, m_ctrlEndVal);
	DDX_Control(pDX, IDC_START_TEXT, m_ctrlStartText);
	DDX_Control(pDX, IDC_END_TEXT, m_ctrlEndText);
	DDX_Control(pDX, IDC_RGB_TEXT, m_ctrlRGBtext);
	DDX_Control(pDX, IDC_STEPS_SPIN, m_ctrlStepsSpin);
	DDX_Control(pDX, IDC_DELTA_HUE, m_ctrlDeltaHue);
	DDX_Control(pDX, IDC_DELTA_SAT, m_ctrlDeltaSat);
	DDX_Control(pDX, IDC_DELTA_VAL, m_ctrlDeltaVal);
	DDX_Control(pDX, IDC_DELTA_TEXT, m_ctrlDeltaText);
	DDX_Control(pDX, IDC_SWAP, m_ctrlSwap);
	DDX_Control(pDX, IDC_DROPPERPIC, m_ctrlDropper);
}


BEGIN_MESSAGE_MAP(ColorCalculator, CDialogEx)
	ON_BN_CLICKED(IDC_COLOR_PICKER, &ColorCalculator::OnClickedColorPicker)
	ON_BN_CLICKED(IDC_LUM_PICKER, &ColorCalculator::OnClickedLumPicker)
	ON_BN_CLICKED(IDC_RED_PICKER, &ColorCalculator::OnClickedRedPicker)
	ON_BN_CLICKED(IDC_GREEN_PICKER, &ColorCalculator::OnClickedGreenPicker)
	ON_BN_CLICKED(IDC_BLUE_PICKER, &ColorCalculator::OnClickedBluePicker)
	ON_BN_CLICKED(IDC_SWAP, &ColorCalculator::OnClickedSwap)
	ON_BN_CLICKED(IDC_START_TEXT, &ColorCalculator::OnClickedStartText)
	ON_BN_CLICKED(IDC_DELTA_TEXT, &ColorCalculator::OnClickedDeltaText)
	ON_BN_CLICKED(IDC_END_TEXT, &ColorCalculator::OnClickedEndText)
	ON_BN_CLICKED(IDC_START_SELECT, &ColorCalculator::OnClickedStartSelect)
	ON_BN_CLICKED(IDC_END_SELECT, &ColorCalculator::OnClickedEndSelect)
	ON_EN_CHANGE(IDC_START_HUE, &ColorCalculator::OnChangeStartHue)
	ON_EN_CHANGE(IDC_START_SAT, &ColorCalculator::OnChangeStartSat)
	ON_EN_CHANGE(IDC_START_VAL, &ColorCalculator::OnChangeStartVal)
	ON_EN_CHANGE(IDC_DELTA_HUE, &ColorCalculator::OnChangeDeltaHue)
	ON_EN_CHANGE(IDC_DELTA_SAT, &ColorCalculator::OnChangeDeltaSat)
	ON_EN_CHANGE(IDC_DELTA_VAL, &ColorCalculator::OnChangeDeltaVal)
	ON_EN_CHANGE(IDC_END_HUE, &ColorCalculator::OnChangeEndHue)
	ON_EN_CHANGE(IDC_END_SAT, &ColorCalculator::OnChangeEndSat)
	ON_EN_CHANGE(IDC_END_VAL, &ColorCalculator::OnChangeEndVal)
	ON_EN_CHANGE(IDC_STEPS, &ColorCalculator::OnChangeSteps)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// Propagate color from the color pickers to the calculators
void ColorCalculator::UpdateColor(COLORREF col, double hue, double sat, double val)
{
	auto txtColor = ContrastColor(col);
	if (m_bStartActive) {
		m_ctrlStartSelect.SetFaceColor(col);
		m_ctrlStartSelect.SetTextColor(txtColor);
		m_cStartColor = col;
		m_dStartHue = hue;
		m_dStartSat = sat;
		m_dStartVal = val;
	} else {
		m_ctrlEndSelect.SetFaceColor(col);
		m_ctrlEndSelect.SetTextColor(txtColor);
		m_cEndColor = col;
		m_dEndHue = hue;
		m_dEndSat = sat;
		m_dEndVal = val;
	}
	m_sRGBtext.Format(RGBformat, GetRValue(col), GetGValue(col), GetBValue(col));
	auto lock = EditLock();
	UpdateStartEndControls(m_bStartActive);
	CalculateDelta();
	UpdateData(FALSE);
}

// Propagate color from the calculator to the color pickers
void ColorCalculator::UpdatePickers(COLORREF col, double hue, double sat, double val)
{
	m_ctrlColorPicker.SetHSV(hue, sat, val);
	m_ctrlLumPicker.SetHSV(hue, sat, val);
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	m_sRGBtext.Format(RGBformat, GetRValue(col), GetGValue(col), GetBValue(col));
	UpdateData(FALSE);
}

// Create control text from updated HSV
void ColorCalculator::UpdateStartEndControls(bool bStart)
{
	auto lock = EditLock();
	double hue = bStart ? m_dStartHue : m_dEndHue;
	double sat = bStart ? m_dStartSat : m_dEndSat;
	double val = bStart ? m_dStartVal : m_dEndVal;
	CString h, s, v;
	h.Format(L"%g", hue);
	s.Format(L"%g", sat);
	v.Format(L"%g", val);
	(bStart ? m_ctrlStartHue : m_ctrlEndHue).SetWindowTextW((LPCTSTR)h);
	(bStart ? m_ctrlStartSat : m_ctrlEndSat).SetWindowTextW((LPCTSTR)s);
	(bStart ? m_ctrlStartVal : m_ctrlEndVal).SetWindowTextW((LPCTSTR)v);
	h.Format(HSVformat, hue, sat, val);
	(bStart ? m_ctrlStartText : m_ctrlEndText).SetWindowTextW((LPCTSTR)h);
}

void ColorCalculator::StartChanged()
{
	m_cStartColor = CDrawingManager::HSVtoRGB(m_dStartHue, m_dStartSat, m_dStartVal);
	auto txtColor = ContrastColor(m_cStartColor);
	m_ctrlStartSelect.SetFaceColor(m_cStartColor);
	m_ctrlStartSelect.SetTextColor(txtColor);
	CString txt;
	txt.Format(HSVformat, m_dStartHue, m_dStartSat, m_dStartVal);
	m_ctrlStartText.SetWindowTextW(txt);

	if (m_bStartActive)
		UpdatePickers(m_cStartColor, m_dStartHue, m_dStartSat, m_dStartVal);

	CalculateDelta();
}

void ColorCalculator::DeltaChanged()
{
	CString txt;
	txt.Format(HSVformat, m_dDeltaHue, m_dDeltaSat, m_dDeltaVal);
	m_ctrlDeltaText.SetWindowTextW(txt);

	int steps = m_ctrlStepsSpin.GetPos();
	m_dEndHue = m_dStartHue;
	m_dEndSat = m_dStartSat;
	m_dEndVal = m_dStartVal;
	for (int i = 0; i < steps; ++i) {
		m_dEndHue = HSBColor::adjustHue(m_dEndHue, m_dDeltaHue);
		m_dEndSat = HSBColor::adjust(m_dEndSat, m_dDeltaSat);
		m_dEndVal = HSBColor::adjust(m_dEndVal, m_dDeltaVal);
	}

	UpdateStartEndControls(false);
}

void ColorCalculator::EndChanged()
{
	m_cEndColor = CDrawingManager::HSVtoRGB(m_dEndHue, m_dEndSat, m_dEndVal);
	auto txtColor = ContrastColor(m_cEndColor);
	m_ctrlEndSelect.SetFaceColor(m_cEndColor);
	m_ctrlEndSelect.SetTextColor(txtColor);
	CString txt;
	txt.Format(HSVformat, m_dEndHue, m_dEndSat, m_dEndVal);
	m_ctrlStartText.SetWindowTextW(txt);

	if (!m_bStartActive)
		UpdatePickers(m_cEndColor, m_dEndHue, m_dEndSat, m_dEndVal);

	CalculateDelta();
}

void ColorCalculator::CalculateDelta()
{
	auto lock = EditLock();
	int steps = m_ctrlStepsSpin.GetPos();
	m_dDeltaHue = adjustHueFrom(m_dEndHue, m_dStartHue, steps);
	m_dDeltaSat =    adjustFrom(m_dEndSat, m_dStartSat, steps);
	m_dDeltaVal =    adjustFrom(m_dEndVal, m_dStartVal, steps);

	CString txt;
	txt.Format(L"%g", m_dDeltaHue);
	m_ctrlDeltaHue.SetWindowTextW((LPCTSTR)txt);
	txt.Format(L"%g", m_dDeltaSat);
	m_ctrlDeltaSat.SetWindowTextW((LPCTSTR)txt);
	txt.Format(L"%g", m_dDeltaVal);
	m_ctrlDeltaVal.SetWindowTextW((LPCTSTR)txt);
	txt.Format(HSVformat, m_dDeltaHue, m_dDeltaSat, m_dDeltaVal);
	m_ctrlDeltaText.SetWindowTextW((LPCTSTR)txt);
}

// ColorCalculator message handlers

BOOL ColorCalculator::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_ctrlColorPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::CIRCLE);
	m_ctrlLumPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::LUMINANCE);
	m_ctrlColorPicker.SetSpace(myCMFCColorPickerCtrl::COLORSPACE::HSVspace);
	m_ctrlLumPicker.SetSpace(myCMFCColorPickerCtrl::COLORSPACE::HSVspace);
	m_ctrlRedPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::RED);
	m_ctrlGreenPicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::GREEN);
	m_ctrlBluePicker.SetType(myCMFCColorPickerCtrl::COLORTYPE::BLUE);

	// Create system palette:
	CClientDC dc(this);

	int nColors = 256; // Use 256 first entries
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
	LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = (USHORT)nColors;

	::GetSystemPaletteEntries(dc.GetSafeHdc(), 0, nColors, pLP->palPalEntry);

	m_Palette.CreatePalette(pLP);

	delete[] pLP;

	m_ctrlColorPicker.SetPalette(&m_Palette);
	m_ctrlLumPicker.SetPalette(&m_Palette);
	m_ctrlRedPicker.SetPalette(&m_Palette);
	m_ctrlGreenPicker.SetPalette(&m_Palette);
	m_ctrlBluePicker.SetPalette(&m_Palette);

	m_ctrlStepsSpin.SetRange(1, 1000);
	m_ctrlStepsSpin.SetPos(1);
	
	auto lock = EditLock();
	UpdateStartEndControls(false);
	UpdateStartEndControls(true);
	StartChanged();
	EndChanged();
	CalculateDelta();
	m_bStartActive = false;
	OnClickedStartSelect();

	m_RGBFont.CreatePointFont(80, L"Lucida Console", &dc);
	m_ctrlRGBtext.SetFont(&m_RGBFont);

	if (m_ToolTip.Create(this)) {
		m_ToolTip.AddTool(&m_ctrlStartText, _T("Click to copy text"));
		m_ToolTip.AddTool(&m_ctrlDeltaText, _T("Click to copy text"));
		m_ToolTip.AddTool(&m_ctrlEndText, _T("Click to copy text"));
		m_ToolTip.AddTool(&m_ctrlSwap, _T("Exchange Start and Finish colors"));
		m_ToolTip.AddTool(&m_ctrlStartSelect, _T("Use color picker on Start color"));
		m_ToolTip.AddTool(&m_ctrlEndSelect, _T("Use color picker on Finish color"));
	}

	return TRUE;
}

void ColorCalculator::OnClickedColorPicker()
{
	double hue, sat, val;
	m_ctrlColorPicker.GetHSV(&hue, &sat, &val);
	m_ctrlLumPicker.SetHSV(hue, sat, val);
	COLORREF col = m_ctrlColorPicker.GetColor();
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	UpdateColor(col, hue, sat, val);
}

void ColorCalculator::OnClickedLumPicker()
{
	double hue, sat, val;
	m_ctrlLumPicker.GetHSV(&hue, &sat, &val);
	m_ctrlColorPicker.SetValue(val);
	COLORREF col = m_ctrlLumPicker.GetColor();
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	UpdateColor(col, hue, sat, val);
}

void ColorCalculator::OnClickedRedPicker()
{
	COLORREF col = m_ctrlRedPicker.GetColor();
	m_ctrlColorPicker.SetColor(col);
	m_ctrlLumPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	double hue, sat, val;
	CDrawingManager::RGBtoHSV(col, &hue, &sat, &val);
	UpdateColor(col, hue, sat, val);
}

void ColorCalculator::OnClickedGreenPicker()
{
	COLORREF col = m_ctrlGreenPicker.GetColor();
	m_ctrlColorPicker.SetColor(col);
	m_ctrlLumPicker.SetColor(col);
	m_ctrlRedPicker.SetColor(col);
	m_ctrlBluePicker.SetColor(col);
	double hue, sat, val;
	CDrawingManager::RGBtoHSV(col, &hue, &sat, &val);
	UpdateColor(col, hue, sat, val);
}

void ColorCalculator::OnClickedBluePicker()
{
	COLORREF col = m_ctrlBluePicker.GetColor();
	m_ctrlColorPicker.SetColor(col);
	m_ctrlLumPicker.SetColor(col);
	m_ctrlRedPicker.SetColor(col);
	m_ctrlGreenPicker.SetColor(col);
	double hue, sat, val;
	CDrawingManager::RGBtoHSV(col, &hue, &sat, &val);
	UpdateColor(col, hue, sat, val);
}

void ColorCalculator::OnClickedSwap()
{
	double t;
	t = m_dStartHue; m_dStartHue = m_dEndHue; m_dEndHue = t;
	t = m_dStartSat; m_dStartSat = m_dEndSat; m_dEndSat = t;
	t = m_dStartVal; m_dStartVal = m_dEndVal; m_dEndVal = t;
	COLORREF tc = m_cStartColor; m_cStartColor = m_cEndColor; m_cEndColor = tc;

	m_ctrlStartSelect.SetFaceColor(m_cStartColor);
	m_ctrlEndSelect.SetFaceColor(m_cEndColor);
	m_ctrlStartSelect.SetTextColor(ContrastColor(m_cStartColor));
	m_ctrlEndSelect.SetTextColor(ContrastColor(m_cEndColor));

	m_bStartActive = !m_bStartActive;
	UpdateStartEndControls(true);
	UpdateStartEndControls(false);
	if (m_bStartActive)
		OnClickedEndSelect();
	else
		OnClickedStartSelect();

	CalculateDelta();
}

void ColorCalculator::OnClickedStartText()
{
	CopyText(m_ctrlStartText);
}

void ColorCalculator::OnClickedDeltaText()
{
	CopyText(m_ctrlDeltaText);
}

void ColorCalculator::OnClickedEndText()
{
	CopyText(m_ctrlEndText);
}

void ColorCalculator::OnClickedStartSelect()
{
	if (m_bStartActive)
		return;

	m_bStartActive = true;
	m_ctrlStartSelect.SetWindowTextW(L"⬛");
	m_ctrlEndSelect.SetWindowTextW(L"");
	m_ctrlRedPicker.SetColor(m_cStartColor);
	m_ctrlGreenPicker.SetColor(m_cStartColor);
	m_ctrlBluePicker.SetColor(m_cStartColor);
	m_ctrlColorPicker.SetHSV(m_dStartHue, m_dStartSat, m_dStartVal);
	m_ctrlLumPicker.SetHSV(m_dStartHue, m_dStartSat, m_dStartVal);
	m_sRGBtext.Format(RGBformat, GetRValue(m_cStartColor), GetGValue(m_cStartColor), GetBValue(m_cStartColor));
	UpdateData(FALSE);
}

void ColorCalculator::OnClickedEndSelect()
{
	if (!m_bStartActive)
		return;

	m_bStartActive = false;
	m_ctrlStartSelect.SetWindowTextW(L"");
	m_ctrlEndSelect.SetWindowTextW(L"⬛");
	m_ctrlRedPicker.SetColor(m_cEndColor);
	m_ctrlGreenPicker.SetColor(m_cEndColor);
	m_ctrlBluePicker.SetColor(m_cEndColor);
	m_ctrlColorPicker.SetHSV(m_dEndHue, m_dEndSat, m_dEndVal);
	m_ctrlLumPicker.SetHSV(m_dEndHue, m_dEndSat, m_dEndVal);
	m_sRGBtext.Format(RGBformat, GetRValue(m_cEndColor), GetGValue(m_cEndColor), GetBValue(m_cEndColor));
	UpdateData(FALSE);
}

BOOL ColorCalculator::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	if (pMsg->message == WM_KEYDOWN && m_bEyedropping) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
			StopCapture();
			return TRUE;
		case VK_UP:
			::SetCursorPos(pMsg->pt.x, pMsg->pt.y - 1);
			return TRUE;
		case VK_DOWN:
			::SetCursorPos(pMsg->pt.x, pMsg->pt.y + 1);
			return TRUE;
		case VK_LEFT:
			::SetCursorPos(pMsg->pt.x - 1, pMsg->pt.y);
			return TRUE;
		case VK_RIGHT:
			::SetCursorPos(pMsg->pt.x + 1, pMsg->pt.y);
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void ColorCalculator::OnChangeStartHue()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlStartHue, m_dStartHue))
			StartChanged();
}

void ColorCalculator::OnChangeStartSat()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlStartSat, m_dStartSat))
			StartChanged();
}

void ColorCalculator::OnChangeStartVal()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlStartVal, m_dStartVal))
			StartChanged();
}

void ColorCalculator::OnChangeDeltaHue()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlDeltaHue, m_dDeltaHue))
			DeltaChanged();
}

void ColorCalculator::OnChangeDeltaSat()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlDeltaSat, m_dDeltaSat))
			DeltaChanged();
}

void ColorCalculator::OnChangeDeltaVal()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlDeltaVal, m_dDeltaVal))
			DeltaChanged();
}

void ColorCalculator::OnChangeEndHue()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlEndHue, m_dEndHue))
			EndChanged();
}

void ColorCalculator::OnChangeEndSat()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlEndSat, m_dEndSat))
			EndChanged();
}

void ColorCalculator::OnChangeEndVal()
{
	if (auto lock = EditLock())
		if (CheckDoubleText(m_ctrlEndVal, m_dEndVal))
			EndChanged();
}

void ColorCalculator::OnChangeSteps()
{
	if (auto lock = EditLock())
		CalculateDelta();
}

BOOL ColorCalculator::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	auto lock = EditLock();

	return CDialogEx::Create(nIDTemplate, pParentWnd);
}

void ColorCalculator::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	CWnd* pWnd = ChildWindowFromPoint(point);
	if (pWnd && pWnd->GetSafeHwnd() == m_ctrlDropper.GetSafeHwnd()) {
		m_bEyedropping = true;
		::SetCursor(theApp.LoadCursorW(IDC_DROPPER));
		SetCapture();
	}
}

void ColorCalculator::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bEyedropping)
		StopCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void ColorCalculator::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bEyedropping) {
		if (::GetCapture() == NULL) {
			SetCapture();
		} else {
			ClientToScreen(&point);

			COLORREF crefxy;
			HDC hdc = ::GetDC(NULL);
			crefxy = ::GetPixel(hdc, point.x, point.y);
			if (crefxy != CLR_INVALID) {
				double hue, sat, val;
				CDrawingManager::RGBtoHSV(crefxy, &hue, &sat, &val);
				UpdateColor(crefxy, hue, sat, val);
				UpdatePickers(crefxy, hue, sat, val);
			}
			::ReleaseDC(::GetForegroundWindow(), hdc);
		}
		return;
	}

	CWnd* pWnd = ChildWindowFromPoint(point);
	m_bInDropper = pWnd && pWnd->GetSafeHwnd() == m_ctrlDropper.GetSafeHwnd();

	CDialogEx::OnMouseMove(nFlags, point);
}

void ColorCalculator::OnCaptureChanged(CWnd* pWnd)
{
	if (m_bEyedropping)
		StopCapture();

	CDialogEx::OnCaptureChanged(pWnd);
}

void ColorCalculator::StopCapture()
{
	m_bEyedropping = false;
	m_bInDropper = false;
	::ReleaseCapture();
	::SetCursor(m_hStandardCursor);
}

BOOL ColorCalculator::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bInDropper) {
		::SetCursor(theApp.LoadCursorW(IDC_DROPPER));
		return TRUE;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}

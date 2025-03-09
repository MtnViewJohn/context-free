#pragma once
#include "afxdialogex.h"
#include "myafxcolorpickerctrl.h"


// ColorCalculator dialog

class ColorCalculator : public CDialogEx
{
	DECLARE_DYNAMIC(ColorCalculator)

public:
	ColorCalculator(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ColorCalculator();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORCALC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CPalette m_Palette;
	CFont m_RGBFont;
	void UpdateColor(COLORREF col, double hue, double sat, double val);
	void UpdatePickers(COLORREF col, double hue, double sat, double val);
	void UpdateStartEndControls(bool bStart);
	void StartChanged();
	void DeltaChanged();
	void EndChanged();
	void CalculateDelta();
	bool m_bStartActive = true;
	COLORREF m_cStartColor = RGB(255, 255, 255);
	COLORREF m_cEndColor = RGB(0, 0, 0);
	double m_dStartHue = 0.;
	double m_dStartSat = 0.;
	double m_dStartVal = 1.;
	double m_dDeltaHue = 0.;
	double m_dDeltaSat = 0.;
	double m_dDeltaVal = 0.;
	double m_dEndHue = 0.;
	double m_dEndSat = 0.;
	double m_dEndVal = 0.;
	CToolTipCtrl m_ToolTip;
	HCURSOR m_hDropperCursor = NULL;
	HCURSOR m_hStandardCursor = NULL;
	void StopCapture();
	bool m_bEyedropping = false;
	bool m_bInDropper = false;

	DECLARE_MESSAGE_MAP()
public:
	myCMFCColorPickerCtrl m_ctrlColorPicker;
	myCMFCColorPickerCtrl m_ctrlLumPicker;
	myCMFCColorPickerCtrl m_ctrlRedPicker;
	myCMFCColorPickerCtrl m_ctrlGreenPicker;
	myCMFCColorPickerCtrl m_ctrlBluePicker;
	virtual BOOL OnInitDialog();
	CMFCButton m_ctrlStartSelect;
	CMFCButton m_ctrlEndSelect;
	afx_msg void OnClickedColorPicker();
	afx_msg void OnClickedLumPicker();
	afx_msg void OnClickedRedPicker();
	afx_msg void OnClickedGreenPicker();
	afx_msg void OnClickedBluePicker();
	CString m_sRGBtext;
	afx_msg void OnClickedSwap();
	CEdit m_ctrlStartHue;
	CEdit m_ctrlStartSat;
	CEdit m_ctrlStartVal;
	CEdit m_ctrlEndHue;
	CEdit m_ctrlEndSat;
	CEdit m_ctrlEndVal;
	CButton m_ctrlStartText;
	CButton m_ctrlEndText;
	afx_msg void OnClickedStartText();
	afx_msg void OnClickedDeltaText();
	afx_msg void OnClickedEndText();
	afx_msg void OnClickedStartSelect();
	afx_msg void OnClickedEndSelect();
	CEdit m_ctrlRGBtext;
	CSpinButtonCtrl m_ctrlStepsSpin;
	CEdit m_ctrlDeltaHue;
	CEdit m_ctrlDeltaSat;
	CEdit m_ctrlDeltaVal;
	CButton m_ctrlDeltaText;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_ctrlSwap;
	afx_msg void OnChangeStartHue();
	afx_msg void OnChangeStartSat();
	afx_msg void OnChangeStartVal();
	afx_msg void OnChangeDeltaHue();
	afx_msg void OnChangeDeltaSat();
	afx_msg void OnChangeDeltaVal();
	afx_msg void OnChangeEndHue();
	afx_msg void OnChangeEndSat();
	afx_msg void OnChangeEndVal();
	afx_msg void OnChangeSteps();
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CStatic m_ctrlDropper;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd* pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

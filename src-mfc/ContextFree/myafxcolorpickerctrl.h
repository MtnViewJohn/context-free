// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#pragma once

#include "afxcontrolbarutil.h"
#include <utility>

#include <__atlmfc_core.h>
#pragma warning(push)
#pragma warning(disable : _ATLMFC_DISABLED_WARNINGS)

#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif

/*============================================================================*/
// myCMFCColorPickerCtrl window

class myCMFCColorPickerCtrl : public CButton
{
// Construction
public:
	myCMFCColorPickerCtrl();
	virtual ~myCMFCColorPickerCtrl();

// Attributes
public:

	enum COLORTYPE { CURRENT, LUMINANCE, RED, GREEN, BLUE, PICKER, CIRCLE, HEX, HEX_GREYSCALE };
	enum COLORSPACE { HLSspace, HSVspace };

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	void SetType(COLORTYPE colorType);
	void SetSpace(COLORSPACE colorSpace);
	void SetPalette(CPalette*	pPalette);

	void SetOriginalColor(COLORREF ref);

	void SetHLS(double hue,double luminance, double saturation, BOOL bInvalidate = TRUE);
	void GetHLS(double *hue,double *luminance, double *saturation);
	void SetHSV(double hue, double saturation, double value, BOOL bInvalidate = TRUE);
	void GetHSV(double *hue, double *saturation, double *value);

	void SetLuminanceBarWidth	(int w);

	double GetHue() const        { return m_dblHue; };
	double GetLuminance() const  { return m_dblLum; };
	double GetSaturation() const { return m_dblSat; };
	double GetValue() const      { return m_dblLum; };
	COLORREF GetColor() const    { return m_colorNew; };

	void SetHue(double Hue)               { m_dblHue = Hue; };
	void SetLuminance(double Luminance)   { m_dblLum = Luminance; };
	void SetSaturation(double Saturation) { m_dblSat = Saturation; };
	void SetValue(double value)           { m_dblLum = value; };
	void SetColor(COLORREF Color);

	void SelectCellHexagon(BYTE R, BYTE G, BYTE B);

protected:
	void CreateHexagon();
	void CreateHexGreyScaleBar();

	void DrawHex(CDC* pDC);
	void DrawPicker(CDC* pDC);
	void DrawCircle(CDC* pDC);
	void DrawLuminanceBar(CDC* pDC);
	void DrawColorBar(CDC* pDC);

	int GetAngleFromPoint(int nX, int nY);
	virtual void DrawCursor(CDC* pDC, const CRect& rect);

 	BOOL SelectCellHexagon(int x, int y);

	double LumFromPoint(int nY);
	int PointFromLum(double dblLum);
	COLORREF ColorFromPoint(int nY);
	int PointFromColor(COLORREF col);
	COLORREF ReplaceColor(int c);
	std::pair<double, double> HueSatFromPoint(CPoint point);

	CPoint GetCursorPos();
	CRect GetCursorRect();

	void NotifyParent();

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
	COLORTYPE m_COLORTYPE;
	COLORSPACE m_COLORSPACE;

	double    m_dblLum, m_dblSat, m_dblHue;
	COLORREF  m_colorNew;
	COLORREF  m_colorOriginal;

	int       m_nRadius;
	int       m_nCenterX;
	int       m_nCenterY;
	int       m_nSizeX;
	int       m_nSizeY;

	int       m_nLumBarWidth;

	CPalette* m_pPalette;
	CBitmap   m_bmpPicker;
	CObArray  m_arCells;	// Array of CCellObj's
};

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif

// _ATLMFC_DISABLED_WARNINGS
#pragma warning(pop)

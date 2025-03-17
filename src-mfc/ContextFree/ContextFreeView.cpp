
// ContextFreeView.cpp : implementation of the CContextFreeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ContextFree.h"
#endif

#include "ContextFreeDoc.h"
#include "ContextFreeView.h"
#include "WinCanvas.h"
#include <gdipluspixelformats.h>
#include <vector>
#include "CMemDC.h"
#include "tiledCanvas.h"
#include "ChildFrm.h"
#include "EditLock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContextFreeView

IMPLEMENT_DYNCREATE(CContextFreeView, CView)

BEGIN_MESSAGE_MAP(CContextFreeView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CContextFreeView construction/destruction

CContextFreeView::CContextFreeView() noexcept
{
}

CContextFreeView::~CContextFreeView()
{
}

BOOL CContextFreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

BOOL CContextFreeView::OnEraseBkgnd(CDC* pDC)
{
	if (m_iBoxSize == 0)
		m_iBoxSize = pDC->GetDeviceCaps(LOGPIXELSY) / 12;

	if (!m_pWinCanvas || !*m_pWinCanvas)
		return CView::OnEraseBkgnd(pDC);

	return TRUE;
}

// CContextFreeView drawing

void CContextFreeView::OnDraw(CDC* pdc)
{
	if (m_iBoxSize == 0)
		m_iBoxSize = pdc->GetDeviceCaps(LOGPIXELSY) / 12;

	if (!m_pWinCanvas || !*m_pWinCanvas)
		return;

	CRect clipRect, cr;
	pdc->GetClipBox(&clipRect);
	GetClientRect(&cr);
	xCMemDC pDC(pdc, &cr);

	Gdiplus::Graphics g(pDC->GetSafeHdc());

	agg::rgba8 bk((*m_pWinCanvas)->mBackground);
	Gdiplus::Color bkColor = Gdiplus::Color(bk.a, bk.r, bk.g, bk.b);
	Gdiplus::SolidBrush backBrush(bkColor);

	double scale = 1.0;
	Gdiplus::Size destSize(cr.Width(), cr.Height());
	auto srcSize = m_bTiled ? Gdiplus::Size((*m_pWinCanvas)->cropWidth(), (*m_pWinCanvas)->cropHeight()) :
							  Gdiplus::Size((*m_pWinCanvas)->mWidth, (*m_pWinCanvas)->mHeight);

	// check if the bitmap is too big and shrink it to fit
	if (srcSize.Width > destSize.Width || srcSize.Height > destSize.Height) {
		double widthScale = (double)destSize.Width / srcSize.Width;
		double heightScale = (double)destSize.Height / srcSize.Height;
		scale = (widthScale < heightScale) ? widthScale : heightScale;
	}

	// scale the bitmap if it is too big
	int scaledWidth = (int)(srcSize.Width * scale);
	int scaledHeight = (int)(srcSize.Height * scale);

	// center the scaled bitmap
	int originX = (destSize.Width - scaledWidth) / 2;
	int originY = (destSize.Height - scaledHeight) / 2;

	auto newBitmap = MakeBitmap(m_bTiled);

	// Draw background
	Gdiplus::Rect destRect(originX, originY, scaledWidth, scaledHeight);
	Gdiplus::Rect fullRect(0, 0, destSize.Width, destSize.Height);
	if (bk.a < 255 || m_bBlendMode) {
		DrawCheckerBoard(g, fullRect);
	} else {
		g.Clear(bkColor);
	}

	if (!newBitmap)
		return;

	g.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	std::vector< Gdiplus::Rect> drawRects;

	if (m_bTiled && scale == 1.0) {
		tileList points = m_Renderer->m_tiledCanvas->getTessellation(cr.Width(), cr.Height(),
			originX, originY, true);
		drawRects.reserve(points.size());

		for (tileList::reverse_iterator pt = points.rbegin(), ept = points.rend();pt != ept; ++pt) {
			g.DrawImage(newBitmap.get(), pt->x, pt->y);
			drawRects.emplace_back(pt->x, pt->y, srcSize.Width, srcSize.Height);
		}
	} else {
		if (scale == 1.0) {
			g.DrawImage(newBitmap.get(), originX, originY);
			drawRects.emplace_back(originX, originY, srcSize.Width, srcSize.Height);
		} else {
			g.DrawImage(newBitmap.get(), destRect,
				0, 0, srcSize.Width, srcSize.Height,
				Gdiplus::Unit::UnitPixel);
			drawRects.push_back(destRect);
		}
	}

	if (bk.a < 255 || m_bBlendMode) {
		for (auto&& drawRect: drawRects)
			g.SetClip(drawRect, Gdiplus::CombineModeExclude);
		g.FillRectangle(&backBrush, fullRect);
		g.ResetClip();
	}

	Gdiplus::Pen p2(Gdiplus::Color::Black);
	p2.SetDashStyle(Gdiplus::DashStyle::DashStyleDashDot);
	g.DrawRectangle(&p2, originX - 1, originY - 1, scaledWidth + 1, scaledHeight + 1);
}

void CContextFreeView::AddGrayPalette(Gdiplus::Bitmap* bm)
{
	std::vector<char> paletteBuf(sizeof(Gdiplus::ColorPalette) + 255 * sizeof(Gdiplus::ARGB));
	Gdiplus::ColorPalette* gray = (Gdiplus::ColorPalette*)paletteBuf.data();
	for (int i = 0; i < 256; ++i)
		gray->Entries[i] = Gdiplus::Color::MakeARGB(255, i, i, i);
	gray->Count = 256;
	gray->Flags = Gdiplus::PaletteFlags::PaletteFlagsGrayScale;
	bm->SetPalette(gray);
}

void CContextFreeView::DrawCheckerBoard(Gdiplus::Graphics& g, Gdiplus::Rect destRect)
{
	Gdiplus::SolidBrush grayBrush(Gdiplus::Color::LightGray);
	g.SetClip(destRect);
	g.Clear(Gdiplus::Color::White);
	for (int y = destRect.Y - destRect.Y % m_iBoxSize; y <= destRect.GetBottom(); y += m_iBoxSize)
		for (int x = destRect.X - destRect.X % m_iBoxSize; x <= destRect.GetRight(); x += m_iBoxSize)
			if (((x / m_iBoxSize) ^ (y / m_iBoxSize)) & 1)
				g.FillRectangle(&grayBrush, x, y, m_iBoxSize, m_iBoxSize);
	g.ResetClip();
}

std::unique_ptr<Gdiplus::Bitmap> CContextFreeView::MakeBitmap(bool cropped)
{
	WinCanvas* canvas = m_pWinCanvas->get();
	if (canvas->mPixelFormat & aggCanvas::Has_16bit_Color) {
		canvas->Make8bitCopy(m_WinCanvas8);
		canvas = m_WinCanvas8.get();
	}

	BYTE* data = (BYTE*)(canvas->bitmap());
	int width = canvas->mWidth;
	int height = canvas->mHeight;
	if (cropped) {
		width = canvas->cropWidth();
		height = canvas->cropHeight();
		data += canvas->mStride * canvas->cropY() +
			aggCanvas::BytesPerPixel.at(canvas->mPixelFormat) * canvas->cropX();
	}


	try {
		switch (canvas->mPixelFormat) {
		case aggCanvas::Gray8_Blend: {
			auto bm = std::make_unique<Gdiplus::Bitmap>(width, height, canvas->mStride, PixelFormat8bppIndexed, data);
			AddGrayPalette(bm.get());
			return bm;
		}
		case aggCanvas::RGB8_Blend:
			return std::make_unique<Gdiplus::Bitmap>(width, height, canvas->mStride, PixelFormat24bppRGB, data);
		case aggCanvas::RGBA8_Blend:
		case aggCanvas::RGBA8_Custom_Blend:
			return std::make_unique<Gdiplus::Bitmap>(width, height, canvas->mStride, PixelFormat32bppPARGB, data);
		default:
			return nullptr;
		}
	} catch (...) {
		return nullptr;
	}
}


// CContextFreeView diagnostics

#ifdef _DEBUG
void CContextFreeView::AssertValid() const
{
	CView::AssertValid();
}

void CContextFreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContextFreeDoc* CContextFreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContextFreeDoc)));
	return (CContextFreeDoc*)m_pDocument;
}
#endif //_DEBUG

// CContextFreeView message handlers

void CContextFreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	auto lock = EditLock();
	if (m_wndChild && lock)
		m_wndChild->PaneResize();
}

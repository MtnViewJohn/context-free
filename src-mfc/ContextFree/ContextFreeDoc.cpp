
// ContextFreeDoc.cpp : implementation of the CContextFreeDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ContextFree.h"
#endif

#include "ContextFreeDoc.h"
#include <vector>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CContextFreeDoc

IMPLEMENT_DYNCREATE(CContextFreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CContextFreeDoc, CDocument)
END_MESSAGE_MAP()


// CContextFreeDoc construction/destruction

CContextFreeDoc::CContextFreeDoc() noexcept
{
	// TODO: add one-time construction code here

}

CContextFreeDoc::~CContextFreeDoc()
{
}

BOOL CContextFreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CContextFreeDoc serialization

void CContextFreeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		auto len = ar.GetFile()->GetLength();

		if (len > 0) {
			std::vector<char> bytes(len + 1);
			ar.Read(bytes.data(), len);
			bytes[len] = '\0';

			int crCount = 0, lfCount = 0;
			for (char c : bytes) {
				if (c == '\r') ++crCount;
				if (c == '\n') ++lfCount;
			}
			if (lfCount > crCount) {
				std::vector<char> bytes2(len + 1 + (lfCount - crCount));
				auto it = bytes.begin();
				auto it2 = bytes2.begin();
				while (*it) {
					if (*it == '\r' && *(it + 1) == '\n') {
						*it2++ = '\r';
						*it2++ = '\n';
						it += 2;
					} else if (*it == '\n') {
						*it2++ = '\r';
						*it2++ = '\n';
						it += 1;
					} else {
						*it2++ = *it++;
					}
				}
				*it2 = '\0';
				bytes.swap(bytes2);
			}
			auto wlen = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes.data(), -1, nullptr, 0);
			if (wlen > 0) {
				std::vector<wchar_t> u16chars(wlen);
				if (::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes.data(), -1, u16chars.data(), wlen) == wlen) {
					m_vwEditorView->GetEditCtrl().SetWindowTextW(u16chars.data());
					return;
				}
			}
		}
		m_vwEditorView->GetEditCtrl().SetWindowTextW(_T(""));
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CContextFreeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CContextFreeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CContextFreeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CContextFreeDoc diagnostics

#ifdef _DEBUG
void CContextFreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CContextFreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CContextFreeDoc commands

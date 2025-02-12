
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
	if (ar.IsStoring()) {
		auto utf8text = GetCfdg();
		ar.Write(utf8text.data(), (UINT)utf8text.length());
	} else {
		auto len = ar.GetFile()->GetLength();
		std::string bytes(len, ' ');
		ar.Read(bytes.data(), (UINT)len);
		LoadCfdg(std::move(bytes));
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
void CContextFreeDoc::LoadCfdg(std::string utf8text)
{
	auto len = utf8text.length();

	if (len > 0) {
		int crCount = 0, lfCount = 0;
		for (char c : utf8text) {
			if (c == '\r') ++crCount;
			if (c == '\n') ++lfCount;
		}
		if (lfCount > crCount) {
			std::string bytes2(len + 1 + (lfCount - crCount), ' ');
			auto it = utf8text.begin();
			auto it2 = bytes2.begin();
			while (it != utf8text.end()) {
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
			utf8text.swap(bytes2);
		}
		auto wlen = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8text.data(), -1, nullptr, 0);
		if (wlen > 0) {
			std::vector<wchar_t> u16chars(wlen);
			if (::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8text.data(), -1, u16chars.data(), wlen) == wlen) {
				m_vwEditorView->GetEditCtrl().SetWindowTextW(u16chars.data());
				return;
			}
		}
	}
	m_vwEditorView->GetEditCtrl().SetWindowTextW(_T(""));
}

std::string CContextFreeDoc::GetCfdg()
{
	std::string utf8text;
	CString wText;
	m_vwEditorView->GetEditCtrl().GetWindowTextW(wText);
	if (wText.GetLength() > 0) {
		auto len = ::WideCharToMultiByte(CP_UTF8, 0, wText, -1, nullptr, 0, NULL, NULL);
		if (len > 0) {
			utf8text.resize(len - 1);
			auto len2 = ::WideCharToMultiByte(CP_UTF8, 0, wText, -1, utf8text.data(), len, NULL, NULL);
			if (len2 < len)
				utf8text.resize(len2 - 1);		// should never happen
		}
	}
	return utf8text;
}
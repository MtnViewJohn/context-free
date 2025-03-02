
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
#include "cfdg.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include <set>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CContextFreeDoc
using namespace Scintilla;

IMPLEMENT_DYNCREATE(CContextFreeDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(CContextFreeDoc, CScintillaDoc)
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
	if (!CScintillaDoc::OnNewDocument())
		return FALSE;

	if (CMainFrame::NextExample) {
		auto name8 = Utf16ToUtf8(CMainFrame::NextExample);
		auto it = AbstractSystem::ExamplesMap.find(name8);
		if (it != AbstractSystem::ExamplesMap.end())
			LoadCfdg(it->second.first);
		m_vwEditorView->GetCtrl().SetSavePoint();
		std::wstring title = CMainFrame::NextExample;
		::PathRemoveExtensionW(title.data());
		SetTitle(title.data());
		CMainFrame::NextExample = nullptr;
	} else {
		// Ensure that the new document title is unique
		std::set<CString> titles;
		auto position = AfxGetApp()->GetFirstDocTemplatePosition();
		auto docTemp = AfxGetApp()->GetNextDocTemplate(position);
		position = docTemp->GetFirstDocPosition();
		while (position) {
			auto doc = docTemp->GetNextDoc(position);
			titles.insert(doc->GetTitle());
		}
		if (titles.count(GetTitle()) == 0)
			return TRUE;		// never happens
		CString newTitle;
		for (int i = 1;; ++i) {
			newTitle.Format(_T("%s%d"), (LPCTSTR)GetTitle(), i);
			if (titles.count(newTitle) == 0) {
				SetTitle(newTitle);
				return TRUE;
			}
		}
	}

	return TRUE;
}

void CContextFreeDoc::SetModifiedFlag(BOOL bModified)
{
	bool changed = IsModified() != bModified;
	CScintillaDoc::SetModifiedFlag(bModified);
	if (changed)
		m_wndChild->UpdateModifiedIndicator();
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
	CScintillaDoc::AssertValid();
}

void CContextFreeDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG


// CContextFreeDoc commands
void CContextFreeDoc::LoadCfdg(std::string utf8text)
{
	m_vwEditorView->GetCtrl().SetText(utf8text.c_str());
}

std::string CContextFreeDoc::GetCfdg()
{
	auto len = m_vwEditorView->GetCtrl().GetTextLength();
	std::string txt(len, ' ');
	auto len2 = m_vwEditorView->GetCtrl().GetText(len, txt.data());
	if (len2 != len)
		txt.resize(len2, ' ');
	return txt;
}

bool CContextFreeDoc::Empty()
{
	return m_vwEditorView->GetCtrl().GetTextLength() == 0;
}
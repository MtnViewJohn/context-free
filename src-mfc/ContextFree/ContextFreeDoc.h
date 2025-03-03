
// ContextFreeDoc.h : interface of the CContextFreeDoc class
//

#pragma once

#include <string>
#include "ScintillaDocView.h"

class CContextFreeDoc : public Scintilla::CScintillaDoc
{
protected: // create from serialization only
	CContextFreeDoc() noexcept;
	DECLARE_DYNCREATE(CContextFreeDoc)

// Attributes
public:
	Scintilla::CScintillaView* m_vwEditorView = nullptr;

// Operations
public:
	void LoadCfdg(std::string textUtf8);
    std::string GetCfdg();
	bool Empty();

// Overrides
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CContextFreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

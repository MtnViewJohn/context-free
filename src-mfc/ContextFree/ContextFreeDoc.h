
// ContextFreeDoc.h : interface of the CContextFreeDoc class
//


#pragma once


class CContextFreeDoc : public CDocument
{
protected: // create from serialization only
	CContextFreeDoc() noexcept;
	DECLARE_DYNCREATE(CContextFreeDoc)

// Attributes
public:
	CEditView* m_vwEditorView = nullptr;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
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

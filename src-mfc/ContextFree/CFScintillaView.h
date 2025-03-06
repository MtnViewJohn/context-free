#pragma once


#include "ScintillaDocView.h"

class CChildFrame;

class CScintillaDemoCtrl : public Scintilla::CScintillaCtrl
{
};

class CFScintillaView : public Scintilla::CScintillaView
{
protected: //create from serialization only
    CFScintillaView();

public:
//Constructors / Destructors
    CFScintillaView(const CFScintillaView&) = delete;
    CFScintillaView(CFScintillaView&&) = delete;
  ~CFScintillaView() = default; //NOLINT(modernize-use-override)

//Methods
  CFScintillaView& operator=(const CFScintillaView&) = delete;
  CFScintillaView& operator=(CFScintillaView&&) = delete;
  CContextFreeDoc* GetDocument();
  void OnDraw(CDC* pDC) override;
  void OnInitialUpdate() override;
  CChildFrame* m_wndChild = nullptr;
  void EditorStyleChanged();
  void EditorFontChanged();

protected:
//Member variables
  Scintilla::ILexer5* m_pCLexer;
  SciFnDirect m_pDirectFn = nullptr;
  Scintilla::sptr_t m_pSciPtr = 0;
  Scintilla::Position m_iLastCaretPosition = -1;

//Methods
  void OnCharAdded(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnStyleNeeded(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnDwellStart(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnDwellEnd(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnModifyAttemptRO(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnModified(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnSavePointReached(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnSavePointLeft(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  void OnUpdateUI(_Inout_ Scintilla::NotificationData* pSCNotification) override;
  std::unique_ptr<Scintilla::CScintillaCtrl> CreateScintillaControl() override;
  void SetAStyle(int style, COLORREF fore, COLORREF back = RGB(0xff, 0xff, 0xff), bool bold = false, bool italic = false, int size = -1, const char* face = nullptr);
  void DefineMarker(int marker, Scintilla::MarkerSymbol markerType, COLORREF fore, COLORREF back);
  void CheckAutoC();

//Message handlers
  afx_msg void OnOptionsAddmarker();
  afx_msg void OnOptionsDeletemarker();
  afx_msg void OnUpdateOptionsDeletemarker(CCmdUI* pCmdUI);
  afx_msg void OnOptionsFindNextmarker();
  afx_msg void OnOptionsFindPrevmarker();
  afx_msg void OnOptionsFoldMargin();
  afx_msg void OnOptionsSelectionMargin();
  afx_msg void OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI);
  afx_msg void OnOptionsViewLinenumbers();
  afx_msg void OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsAddmarker(CCmdUI* pCmdUI);
  afx_msg void OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI);
  afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
  afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFold(CCmdUI* pCmdUI);
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

  DECLARE_MESSAGE_MAP()

  DECLARE_DYNCREATE(CFScintillaView)
};

#include "pch.h"
#include "framework.h"
#include "ContextFree.h"
#include "ContextFreeDoc.h"
#include "CFScintillaView.h"
#include "ChildFrm.h"
#include "CFscintilla.h"
#include "EditorParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Scintilla;

#pragma warning(suppress: 26409 26433 26440 26477)
IMPLEMENT_DYNCREATE(CFScintillaView, CScintillaView)

#pragma warning(suppress: 26433 26435 26440)
BEGIN_MESSAGE_MAP(CFScintillaView, CScintillaView) //NOLINT(modernize-avoid-c-arrays)
#if 0
  ON_COMMAND(ID_OPTIONS_ADDMARKER, &CFScintillaView::OnOptionsAddmarker)
  ON_COMMAND(ID_OPTIONS_DELETEMARKER, &CFScintillaView::OnOptionsDeletemarker)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETEMARKER, &CFScintillaView::OnUpdateOptionsDeletemarker)
  ON_COMMAND(ID_OPTIONS_FIND_NEXTMARKER, &CFScintillaView::OnOptionsFindNextmarker)
  ON_COMMAND(ID_OPTIONS_FIND_PREVMARKER, &CFScintillaView::OnOptionsFindPrevmarker)
  ON_COMMAND(ID_OPTIONS_FOLD_MARGIN, &CFScintillaView::OnOptionsFoldMargin)
  ON_COMMAND(ID_OPTIONS_SELECTION_MARGIN, &CFScintillaView::OnOptionsSelectionMargin)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTION_MARGIN, &CFScintillaView::OnUpdateOptionsSelectionMargin)
  ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, &CFScintillaView::OnOptionsViewLinenumbers)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, &CFScintillaView::OnUpdateOptionsViewLinenumbers)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADDMARKER, &CFScintillaView::OnUpdateOptionsAddmarker)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_FOLD_MARGIN, &CFScintillaView::OnUpdateOptionsFoldMargin)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, &CFScintillaView::OnUpdateLine)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, &CFScintillaView::OnUpdateStyle)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, &CFScintillaView::OnUpdateFold)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, &CFScintillaView::OnUpdateInsert)
#endif
  ON_WM_ACTIVATE()
  ON_WM_CREATE()
END_MESSAGE_MAP()


#pragma warning(suppress: 26439 26455)
CFScintillaView::CFScintillaView() : m_pCLexer{nullptr}
{
  LoadMarginSettings();
}

void CFScintillaView::OnDraw(CDC* /*pDC*/)
{
  const CContextFreeDoc* pDoc{GetDocument()};
  ASSERT_VALID(pDoc);
  UNREFERENCED_PARAMETER(pDoc);
}

#pragma warning(suppress: 26434 26440)
CContextFreeDoc* CFScintillaView::GetDocument()
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContextFreeDoc)));
#pragma warning(suppress: 26466)
  return static_cast<CContextFreeDoc*>(m_pDocument);
}

void CFScintillaView::SetAStyle(int style, COLORREF fore, COLORREF back, bool bold, bool italic, int size, const char* face)
{
  auto& rCtrl{GetCtrl()};

  rCtrl.StyleSetFore(style, fore);
  rCtrl.StyleSetBold(style, bold);
  rCtrl.StyleSetItalic(style, italic);
  rCtrl.StyleSetBack(style, back);
  if (size >= 1)
    rCtrl.StyleSetSize(style, size);
  if (face)
    rCtrl.StyleSetFont(style, face);
}

void CFScintillaView::DefineMarker(int marker, Scintilla::MarkerSymbol markerType, COLORREF fore, COLORREF back)
{
  auto& rCtrl{GetCtrl()};

  rCtrl.MarkerDefine(marker, markerType);
  rCtrl.MarkerSetFore(marker, fore);
  rCtrl.MarkerSetBack(marker, back);
}

void CFScintillaView::EditorStyleChanged()
{
    GetCtrl().SetTabWidth(EditorParams::TabWidth);
    SetAStyle(CFscintilla::StyleDefault, EditorParams::DefaultColor, RGB(0xff, 0xff, 0xff), EditorParams::DefaultBold, EditorParams::DefaultItalic);
    SetAStyle(CFscintilla::StyleComment, EditorParams::CommentColor, RGB(0xff, 0xff, 0xff), EditorParams::CommentBold, EditorParams::CommentItalic);
    SetAStyle(CFscintilla::StyleSymbol, EditorParams::SymbolColor, RGB(0xff, 0xff, 0xff), EditorParams::SymbolBold, EditorParams::SymbolItalic);
    SetAStyle(CFscintilla::StyleIdentifier, EditorParams::IdentColor, RGB(0xff, 0xff, 0xff), EditorParams::IdentBold, EditorParams::IdentItalic);
    SetAStyle(CFscintilla::StyleKeywords, EditorParams::KeywordColor, RGB(0xff, 0xff, 0xff), EditorParams::KeywordBold, EditorParams::KeywordItalic);
    SetAStyle(CFscintilla::StyleBuiltins, EditorParams::BuiltinColor, RGB(0xff, 0xff, 0xff), EditorParams::BuiltinBold, EditorParams::BuiltinItalic);
    SetAStyle(CFscintilla::StyleString, EditorParams::FileColor, RGB(0xff, 0xff, 0xff), EditorParams::FileBold, EditorParams::FileItalic);
    SetAStyle(CFscintilla::StyleNumber, EditorParams::NumberColor, RGB(0xff, 0xff, 0xff), EditorParams::NumberBold, EditorParams::NumberItalic);
}

void CFScintillaView::EditorFontChanged()
{
    auto& rCtrl{ GetCtrl() };
    auto fontName = Utf16ToUtf8((LPCTSTR)EditorParams::FontName);

    rCtrl.StyleSetFont(static_cast<int>(Scintilla::StylesCommon::Default), fontName.c_str());
    rCtrl.StyleSetSize(static_cast<int>(Scintilla::StylesCommon::Default), EditorParams::FontSize);
    for (int i = CFscintilla::StyleDefault; i <= CFscintilla::StyleNumber; ++i) {
        rCtrl.StyleSetFont(i, fontName.c_str());
        rCtrl.StyleSetSize(i, EditorParams::FontSize);
    }
    rCtrl.StyleSetFont(static_cast<int>(Scintilla::StylesCommon::LineNumber), fontName.c_str());
    rCtrl.StyleSetSize(static_cast<int>(Scintilla::StylesCommon::LineNumber), EditorParams::FontSize);
    int w = rCtrl.TextWidth(static_cast<int>(Scintilla::StylesCommon::LineNumber), "88888");
    rCtrl.SetMarginWidthN(0, w);
}

void CFScintillaView::OnInitialUpdate()
{
  //Let the base class do its thing
  __super::OnInitialUpdate();

  auto& rCtrl{GetCtrl()};

  m_pDirectFn = (SciFnDirect)rCtrl.SendMessage(SCI_GETDIRECTFUNCTION, 0, 0);
  m_pSciPtr = (sptr_t)rCtrl.SendMessage(SCI_GETDIRECTPOINTER, 0, 0);

  //Setup styles
  auto fontName = Utf16ToUtf8((LPCTSTR)EditorParams::FontName);
  SetAStyle(static_cast<int>(Scintilla::StylesCommon::Default), EditorParams::DefaultColor,
      RGB(0xff, 0xff, 0xff), EditorParams::DefaultBold, EditorParams::DefaultItalic, EditorParams::FontSize,
      fontName.c_str());
  rCtrl.StyleClearAll();
  EditorFontChanged();
  EditorStyleChanged();
  rCtrl.SetSelFore(TRUE, RGB(0xff, 0xff, 0xff));
  rCtrl.SetSelBack(TRUE, RGB(0x11, 0x4d, 0x9c));

  //Setup auto completion
  rCtrl.SetWordChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:");
  rCtrl.AutoCStops("[]{}<>,1234567890()/*+-|=!&^ \t.\r\n");
  rCtrl.AutoCSetIgnoreCase(true);
  rCtrl.AutoCSetCaseInsensitiveBehaviour(Scintilla::CaseInsensitiveBehaviour::IgnoreCase);

  //Setup call tips
  rCtrl.SetMouseDwellTime(1000);

  //Enable Multiple selection
  rCtrl.SetMultipleSelection(TRUE);

  // Setup indentation
  rCtrl.SetTabIndents(TRUE);
  rCtrl.SetBackSpaceUnIndents(TRUE);

  // Brace highlighting
  SetAStyle(static_cast<int>(Scintilla::StylesCommon::BraceLight), RGB(0x8a, 0x2b, 0xe2), RGB(0xe6, 0xe6, 0xfa));
  SetAStyle(static_cast<int>(Scintilla::StylesCommon::BraceLight), RGB(0xff, 0, 0), RGB(0xff, 0xff, 0xff), true);
  /*
  auto ConvertColorRefToColorAlpha = [](COLORREF color, uint8_t alpha = 255) -> uint32_t
  {
    //Extract RGB components from the COLORREF value
    const uint8_t red = GetRValue(color);
    const uint8_t green = GetGValue(color);
    const uint8_t blue = GetBValue(color);

    // Combine into ARGB format
    const uint32_t colorAlpha = (alpha << 24) | (blue << 16) | (green << 8) | red;
    return colorAlpha;
  };

  //Retrieve the system highlight color
  const auto highlightColor = ConvertColorRefToColorAlpha(::GetSysColor(COLOR_HIGHLIGHT));
  //Retrieve the system highlight text color
  const auto highlightTextColor = ConvertColorRefToColorAlpha(::GetSysColor(COLOR_HIGHLIGHTTEXT));

  constexpr int redTransparent(0x030000FF);
  rCtrl.SetSelectionLayer(Scintilla::Layer::UnderText);
  rCtrl.SetElementColour(Scintilla::Element::SelectionText, highlightTextColor);
  rCtrl.SetElementColour(Scintilla::Element::SelectionBack, highlightColor);
  rCtrl.SetElementColour(Scintilla::Element::SelectionAdditionalBack, redTransparent);
  rCtrl.SetElementColour(Scintilla::Element::SelectionSecondaryBack, highlightColor);
  rCtrl.SetElementColour(Scintilla::Element::SelectionInactiveBack, highlightColor);

  auto sCopySeparator{rCtrl.GetCopySeparator()};
  rCtrl.SetCopySeparator(_T(" "));
  sCopySeparator = rCtrl.GetCopySeparator();
  auto fontStretch{rCtrl.StyleGetStretch(1)}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.StyleSetStretch(1, Scintilla::FontStretch::Condensed);
  fontStretch = rCtrl.StyleGetStretch(1);
  UNREFERENCED_PARAMETER(fontStretch);
  */

#ifdef _DEBUG
  AfxDump(this);
#endif
}

void CFScintillaView::OnOptionsAddmarker()
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  rCtrl.MarkerAdd(nLine, 0);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateOptionsAddmarker(CCmdUI* pCmdUI)
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  const int nBits{rCtrl.MarkerGet(nLine)};
#pragma warning(suppress: 26486)
  pCmdUI->Enable((nBits & 0x1) == 0);
}

void CFScintillaView::OnOptionsDeletemarker()
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  rCtrl.MarkerDelete(nLine, 0);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateOptionsDeletemarker(CCmdUI* pCmdUI)
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  const int nBits{rCtrl.MarkerGet(nLine)};
#pragma warning(suppress: 26486)
  pCmdUI->Enable(nBits & 0x1);
}

void CFScintillaView::OnOptionsFindNextmarker()
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  const auto nFoundLine{rCtrl.MarkerNext(nLine + 1, 0x1)};
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);
}

void CFScintillaView::OnOptionsFindPrevmarker()
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  const auto nFoundLine{rCtrl.MarkerPrevious(nLine - 1, 0x1)};
  if (nFoundLine >= 0)
    rCtrl.GotoLine(nFoundLine);
  else
    MessageBeep(MB_ICONHAND);
}

void CFScintillaView::OnOptionsFoldMargin()
{
  auto& rCtrl{GetCtrl()};
  const int nMarginWidth{rCtrl.GetMarginWidthN(2)};
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(2, 0);
  else
    rCtrl.SetMarginWidthN(2, 16);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateOptionsFoldMargin(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(2) != 0);
}

void CFScintillaView::OnOptionsSelectionMargin()
{
  auto& rCtrl{GetCtrl()};
  const int nMarginWidth{rCtrl.GetMarginWidthN(1)};
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(1, 0);
  else
    rCtrl.SetMarginWidthN(1, 16);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateOptionsSelectionMargin(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(1) != 0);
}

void CFScintillaView::OnOptionsViewLinenumbers()
{
  auto& rCtrl{GetCtrl()};
  const int nMarginWidth{rCtrl.GetMarginWidthN(0)};
  if (nMarginWidth)
    rCtrl.SetMarginWidthN(0, 0);
  else
    rCtrl.SetMarginWidthN(0, 32);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateOptionsViewLinenumbers(CCmdUI* pCmdUI)
{
#pragma warning(suppress: 26486)
  pCmdUI->SetCheck(GetCtrl().GetMarginWidthN(0) != 0);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateInsert(CCmdUI* pCmdUI)
{
  CString sText;
  if (GetCtrl().GetOvertype())
    VERIFY(sText.LoadString(ID_INDICATOR_OVR));
#pragma warning(suppress: 26486)
  pCmdUI->SetText(sText);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateStyle(CCmdUI* pCmdUI)
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const int nStyle{rCtrl.GetStyleAt(nPos)};
  CString sLine;
  // TBD sLine.Format(IDS_STYLE_INDICATOR, nStyle);
#pragma warning(suppress: 26486)
  pCmdUI->SetText(sLine);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateFold(CCmdUI* pCmdUI)
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  int nLevel{static_cast<int>(rCtrl.GetFoldLevel(nLine) & Scintilla::FoldLevel::NumberMask)};
  nLevel -= 1024;
  CString sLine;
  // TBD sLine.Format(IDS_FOLD_INDICATOR, nLevel);
#pragma warning(suppress: 26486)
  pCmdUI->SetText(sLine);
}

#pragma warning(suppress: 26429)
void CFScintillaView::OnUpdateLine(CCmdUI* pCmdUI)
{
  auto& rCtrl{GetCtrl()};
  const Scintilla::Position nPos{rCtrl.GetCurrentPos()};
  const auto nLine{rCtrl.LineFromPosition(nPos)};
  const Scintilla::Position nColumn{rCtrl.GetColumn(nPos)};

  CString sLine;
  // TBD sLine.Format(IDS_LINE_INDICATOR, nLine, nColumn, nPos);
#pragma warning(suppress: 26486)
  pCmdUI->SetText(sLine);
}

void CFScintillaView::OnCharAdded(_Inout_ Scintilla::NotificationData* pSCNotification)
{
  // auto unindent
  if (pSCNotification->ch == '}') {
      auto& rCtrl{GetCtrl()};

      auto pos = rCtrl.GetCurrentPos();
      auto lineno = rCtrl.LineFromPosition(pos);
      auto indentPos = rCtrl.GetLineIndentPosition(lineno);
      if (indentPos + 1 == pos) {
          auto indent = rCtrl.GetLineIndentation(lineno);
          indent -= EditorParams::TabWidth;
          if (indent < 0)
              indent = 0;
          rCtrl.SetLineIndentation(lineno, indent);
      }
  }

  CheckAutoC();
}

void CFScintillaView::OnStyleNeeded(NotificationData* pSCNotification)
{
    if (m_pDirectFn == nullptr || m_pSciPtr == 0)
        return;

    auto& rCtrl{ GetCtrl() };

    auto startPos = rCtrl.GetEndStyled();
    auto startLine = rCtrl.LineFromPosition(startPos);
    auto endPos = pSCNotification->position;
    auto endLine = rCtrl.LineFromPosition(endPos);
    CFscintilla::StyleLines(m_pDirectFn, m_pSciPtr, startLine, endLine);
}

//A simple example of call tips
void CFScintillaView::OnDwellStart(_Inout_ Scintilla::NotificationData* pSCNotification)
{
  auto& rCtrl{GetCtrl()};

  //Only display the call tip if the scintilla window has focus
  const CWnd* pFocusWnd{GetFocus()};
  if (pFocusWnd != nullptr)
  {
    if (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd())
    {
      //Get the previous 7 characters and next 7 characters around
      //the current dwell position and if it is "author " case insensitive
      //then display "PJ Naughter" as a call tip
      Scintilla::TextRangeFull tr{};
      tr.chrg.cpMin = std::max((long long)0, pSCNotification->position - 7);
      tr.chrg.cpMax = std::min(pSCNotification->position + 7, rCtrl.GetLength());
      CStringA sText;
      tr.lpstrText = sText.GetBuffer(14);
      rCtrl.GetTextRangeFull(&tr);
      sText.ReleaseBuffer();

      //Display the call tip
      sText.MakeUpper();
      if (sText.Find("AUTHOR ") != -1)
        rCtrl.CallTipShow(pSCNotification->position, _T("PJ Naughter"));
    }
  }
}

void CFScintillaView::OnDwellEnd(_Inout_ Scintilla::NotificationData* /*pSCNotification*/)
{
  auto& rCtrl{GetCtrl()};

  //Cancel any outstanding call tip
  if (rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

#pragma warning(suppress: 26434)
void CFScintillaView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
  //Let the base class do its thing
  __super::OnActivate(nState, pWndOther, bMinimized);

  auto& rCtrl{GetCtrl()};

  //Cancel any outstanding call tip
  if ((nState == WA_INACTIVE) && rCtrl.CallTipActive())
    rCtrl.CallTipCancel();
}

void CFScintillaView::OnModifyAttemptRO(_Inout_ Scintilla::NotificationData* /*pSCNotification*/)
{
#pragma warning(suppress: 26493)
  if (AfxMessageBox(IDP_ALLOW_MODIFY_READONLY_FILE, MB_YESNO) == IDYES)
    GetCtrl().SetReadOnly(FALSE);
}

#pragma warning(suppress: 26440)
void CFScintillaView::OnModified(_Inout_ Scintilla::NotificationData* pSCNotification)
{
  if (static_cast<int>(pSCNotification->modificationType) & 
      static_cast<int>(Scintilla::ModificationFlags::Undo | Scintilla::ModificationFlags::Redo |
                       Scintilla::ModificationFlags::DeleteText))
  {
      CheckAutoC();
  }

  if (static_cast<int>(pSCNotification->modificationType) & 
      static_cast<int>(Scintilla::ModificationFlags::InsertCheck))
  {
      // auto indent
      const char* text = pSCNotification->text;
      if (std::strcmp(text, "\r\n") == 0 || std::strcmp(text, "\n") == 0 || std::strcmp(text, "\r") == 0) {
          auto& rCtrl{GetCtrl()};

          auto lineno = rCtrl.LineFromPosition(pSCNotification->position);
          auto len = rCtrl.GetLine(lineno, nullptr);
          std::string line(len, ' ');
          rCtrl.GetLine(lineno, line.data());
          auto indent = rCtrl.GetLineIndentation(lineno);
          bool white = true;
          for (char c: line) {
              if (c == '{')
                  indent += EditorParams::TabWidth;
              if (c == '}' && !white)
                  indent -= EditorParams::TabWidth;
              if (c <= 0 || c >= 0x80 || !std::isspace((unsigned char)c))
                  white = false;
          }
          if (indent > 0) {
              std::string nextLine(indent, ' ');
              nextLine.insert(0, pSCNotification->text);
              rCtrl.ChangeInsertion(nextLine.length(), nextLine.c_str());
          }
      }
  }
}

void CFScintillaView::OnSavePointReached(Scintilla::NotificationData* pSCNotification)
{
    m_wndChild->UpdateDirtyIndicator(false);
}

void CFScintillaView::OnSavePointLeft(Scintilla::NotificationData* pSCNotification)
{
    m_wndChild->UpdateDirtyIndicator(true);
}

std::unique_ptr<Scintilla::CScintillaCtrl> CFScintillaView::CreateScintillaControl()
{
  return std::make_unique<CScintillaDemoCtrl>();
}

#pragma warning(suppress: 26434)
int CFScintillaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  //Let the base class do its thing
  if (__super::OnCreate(lpCreateStruct) == -1)
    return -1;

#if 0
  //Create the C++ Lexer  TODO cfdg lexer
#pragma warning(suppress: 26429)
  const CScintillaDemoApp* theApp{dynamic_cast<CScintillaDemoApp*>(AfxGetApp())};
  ASSERT(theApp != nullptr);
  ASSERT(theApp->m_pCreateLexer != nullptr);
  m_pCLexer = theApp->m_pCreateLexer("cpp");
  if (m_pCLexer == nullptr)
    return -1;
#endif
  return 0;
}

void CFScintillaView::CheckAutoC()
{
    auto& rCtrl = GetCtrl();
    auto pos = rCtrl.GetCurrentPos();
    auto wordPos = rCtrl.WordStartPosition(pos, true);
    auto len = pos - wordPos;
    if (len > 1) {
        std::string frag(len, ' ');
        Scintilla::TextRangeFull trf{ {wordPos, pos}, frag.data()};
        auto len2 = rCtrl.GetTextRangeFull(&trf);
        ASSERT(len == len2);
        auto [first, last] = CFscintilla::GetAutoCList(frag.c_str());
        if (first != last) {
            size_t total = 0;
            for (auto it = first; it != last; ++it)
                total += std::strlen(*it) + 1;
            std::string list;
            list.reserve(total);
            for (auto it = first; it != last; ++it) {
                list.append(*it);
                list.append(" ");
            }
            list.pop_back();
            rCtrl.AutoCShow(len, list.c_str());
            return;
        }
    }
    if (rCtrl.AutoCActive())
        rCtrl.AutoCCancel();
}

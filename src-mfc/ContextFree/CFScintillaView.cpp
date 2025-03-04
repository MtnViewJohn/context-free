#include "pch.h"
#include "framework.h"
#include "ContextFree.h"
#include "ContextFreeDoc.h"
#include "CFScintillaView.h"
#include "ChildFrm.h"
#include "CFscintilla.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Scintilla;

const TCHAR* g_cppKeyWords
{_T("alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept auto bitand bitor bool break ")
 _T("case catch char char8_t char16_t char32_t class compl concept const consteval constexpr constinit const_cast continue ")
 _T("co_await co_return co_yield decltype default delete do double dynamic_cast else enum explicit export extern false float for ")
 _T("friend goto if inline int long mutable namespace new noexcept not not_eq nullptr ")
 _T("operator or or_eq private protected public ")
 _T("reflexpr register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct switch synchronized ")
 _T("template this thread_local throw true try typedef typeid typename union unsigned using ")
 _T("virtual void volatile wchar_t while xor xor_eq")};


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

void CFScintillaView::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
  auto& rCtrl{GetCtrl()};

  rCtrl.StyleSetFore(style, fore);
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

void CFScintillaView::OnInitialUpdate()
{
  //Let the base class do its thing
  __super::OnInitialUpdate();

  auto& rCtrl{GetCtrl()};

  //Setup the C++ Lexer
  rCtrl.SetILexer(m_pCLexer);
  rCtrl.SetKeyWords(0, g_cppKeyWords);

  //Setup styles
  SetAStyle(static_cast<int>(Scintilla::StylesCommon::Default), RGB(0, 0, 0), RGB(0xff, 0xff, 0xff), 11, "Verdana");
  rCtrl.StyleClearAll();
  SetAStyle(SCE_C_DEFAULT, RGB(0, 0, 0));
  SetAStyle(SCE_C_COMMENT, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTLINE, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTLINEDOC, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOCKEYWORD, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_COMMENTDOCKEYWORDERROR, RGB(0, 0x80, 0));
  SetAStyle(SCE_C_NUMBER, RGB(0, 0x80, 0x80));
  SetAStyle(SCE_C_WORD, RGB(0, 0, 0x80));
  rCtrl.StyleSetBold(SCE_C_WORD, 1);
  SetAStyle(SCE_C_STRING, RGB(0x80, 0, 0x80));
  SetAStyle(SCE_C_IDENTIFIER, RGB(0, 0, 0));
  SetAStyle(SCE_C_PREPROCESSOR, RGB(0x80, 0, 0));
  SetAStyle(SCE_C_OPERATOR, RGB(0x80, 0x80, 0));

  //Setup folding
  rCtrl.SetMarginWidthN(2, 16);
  rCtrl.SetMarginSensitiveN(2, TRUE);
  rCtrl.SetMarginTypeN(2, Scintilla::MarginType::Symbol);
  rCtrl.SetMarginMaskN(2, Scintilla::MaskFolders);
  rCtrl.SetSCIProperty(_T("fold"), _T("1"));

  //Setup markers
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), Scintilla::MarkerSymbol::Minus, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::Folder), Scintilla::MarkerSymbol::Plus, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderSub), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderTail), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderEnd), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderOpenMid), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
  DefineMarker(static_cast<int>(Scintilla::MarkerOutline::FolderMidTail), Scintilla::MarkerSymbol::Empty, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));

  //Setup auto completion
  rCtrl.SetWordChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:");
  rCtrl.AutoCStops("[]{}<>,1234567890()/*+-|=!&^ \t.\r\n");
  rCtrl.AutoCSetIgnoreCase(true);
  rCtrl.AutoCSetCaseInsensitiveBehaviour(Scintilla::CaseInsensitiveBehaviour::IgnoreCase);

  //Setup call tips
  rCtrl.SetMouseDwellTime(1000);

  //Enable Multiple selection
  rCtrl.SetMultipleSelection(TRUE);

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

//Some simple examples of implementing auto completion
void CFScintillaView::OnCharAdded(_Inout_ Scintilla::NotificationData* pSCNotification)
{
  UNREFERENCED_PARAMETER(pSCNotification);

  // TODO autoindent

  CheckAutoC();
  
#ifdef _DEBUG
  /*
  //Test out some of the methods
  const auto ws{rCtrl.GetViewWS()};
  UNREFERENCED_PARAMETER(ws);
  rCtrl.SetViewWS(ws);
  const auto EOL{rCtrl.GetEOLMode()};
  UNREFERENCED_PARAMETER(EOL);
  rCtrl.SetEOLMode(EOL);
  rCtrl.ConvertEOLs(EOL);
  rCtrl.MarkerSetAlpha(1, Scintilla::Alpha::Opaque);
  const auto MarginType{rCtrl.GetMarginTypeN(1)};
  UNREFERENCED_PARAMETER(MarginType);
  rCtrl.SetMarginCursorN(1, Scintilla::CursorShape::Normal);
  const auto CursorShape{rCtrl.GetMarginCursorN(1)};
  UNREFERENCED_PARAMETER(CursorShape);
  const auto CaseVisible{rCtrl.StyleGetCase(1)};
  UNREFERENCED_PARAMETER(CaseVisible);
  const auto characterSet{rCtrl.StyleGetCharacterSet(1)};
  UNREFERENCED_PARAMETER(characterSet);
  rCtrl.StyleSetCase(1, Scintilla::CaseVisible::Camel);
  rCtrl.StyleSetWeight(1, Scintilla::FontWeight::Bold);
  const auto fw{rCtrl.StyleGetWeight(1)};
  UNREFERENCED_PARAMETER(fw);
  rCtrl.StyleSetCharacterSet(1, Scintilla::CharacterSet::Arabic);
  const auto alpha{rCtrl.GetSelAlpha()};
  UNREFERENCED_PARAMETER(alpha);
  rCtrl.SetSelAlpha(alpha);
  rCtrl.IndicSetStyle(1, Scintilla::IndicatorStyle::Box);
  auto indicStyle{rCtrl.IndicGetStyle(1)}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.IndicSetHoverStyle(1, Scintilla::IndicatorStyle::Box);
  indicStyle = rCtrl.IndicGetHoverStyle(1); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.IndicSetFlags(1, Scintilla::IndicFlag::ValueFore);
  const auto indicFlag{rCtrl.IndicGetFlags(1)};
  UNREFERENCED_PARAMETER(indicFlag);
  rCtrl.SetIndentationGuides(Scintilla::IndentView::LookBoth);
  const auto indentView{rCtrl.GetIndentationGuides()};
  UNREFERENCED_PARAMETER(indentView);
  const auto PrintOption{rCtrl.GetPrintColourMode()};
  UNREFERENCED_PARAMETER(PrintOption);
  rCtrl.SetPrintColourMode(PrintOption);
  Scintilla::TextToFind ft;
  ft.chrg.cpMax = -1;
  ft.chrg.cpMin = -1;
  ft.lpstrText = "author";
  ft.chrgText.cpMax = -1;
  ft.chrgText.cpMin = -1;
  auto pos{rCtrl.FindText(Scintilla::FindOption::None, &ft)};
  UNREFERENCED_PARAMETER(pos);
  rCtrl.SetFoldFlags(Scintilla::FoldFlag::LineAfterContracted);
  rCtrl.SetIdleStyling(Scintilla::IdleStyling::None);
  rCtrl.SetWrapMode(Scintilla::Wrap::WhiteSpace);
  const auto wm{rCtrl.GetWrapMode()};
  UNREFERENCED_PARAMETER(wm);
  rCtrl.SetWrapVisualFlags(Scintilla::WrapVisualFlag::Margin);
  const auto wf{rCtrl.GetWrapVisualFlags()};
  UNREFERENCED_PARAMETER(wf);
  rCtrl.SetWrapVisualFlagsLocation(Scintilla::WrapVisualLocation::EndByText);
  const auto wvl{rCtrl.GetWrapVisualFlagsLocation()};
  UNREFERENCED_PARAMETER(wvl);
  const auto wim{rCtrl.GetWrapIndentMode()};
  UNREFERENCED_PARAMETER(wim);
  rCtrl.SetWrapIndentMode(wim);
  const auto lc{rCtrl.GetLayoutCache()};
  rCtrl.SetLayoutCache(lc);
  const auto is{rCtrl.GetIdleStyling()};
  UNREFERENCED_PARAMETER(is);
  rCtrl.SetAccessibility(Scintilla::Accessibility::Enabled);
  const auto access{rCtrl.GetAccessibility()};
  UNREFERENCED_PARAMETER(access);
  rCtrl.SetModEventMask(Scintilla::ModificationFlags::ChangeAnnotation);
  const auto mem{rCtrl.GetModEventMask()};
  UNREFERENCED_PARAMETER(mem);
  const auto evs{rCtrl.GetEdgeMode()};
  UNREFERENCED_PARAMETER(evs);
  void* pDoc{rCtrl.CreateDocument(10, Scintilla::DocumentOption::Default)};
  rCtrl.ReleaseDocument(pDoc);
  const auto dop{rCtrl.GetDocumentOptions()};
  UNREFERENCED_PARAMETER(dop);
  rCtrl.SetStatus(Scintilla::Status::Failure);
  const auto stat{rCtrl.GetStatus()};
  UNREFERENCED_PARAMETER(stat);
  rCtrl.SetCursor(Scintilla::CursorShape::ReverseArrow);
  const auto cur{rCtrl.GetCursor()};
  UNREFERENCED_PARAMETER(cur);
  rCtrl.SetVisiblePolicy(Scintilla::VisiblePolicy::Slop, 2);
  rCtrl.SetXCaretPolicy(Scintilla::CaretPolicy::Slop, 2);
  rCtrl.SetYCaretPolicy(Scintilla::CaretPolicy::Slop, 2);
  rCtrl.SetPrintWrapMode(Scintilla::Wrap::WhiteSpace);
  const auto pwm{rCtrl.GetPrintWrapMode()};
  UNREFERENCED_PARAMETER(pwm);
  rCtrl.SetSelectionMode(Scintilla::SelectionMode::Lines);
  const auto selMode{rCtrl.GetSelectionMode()};
  UNREFERENCED_PARAMETER(selMode);
  rCtrl.AutoCSetCaseInsensitiveBehaviour(Scintilla::CaseInsensitiveBehaviour::RespectCase);
  const auto cib{rCtrl.AutoCGetCaseInsensitiveBehaviour()};
  UNREFERENCED_PARAMETER(cib);
  rCtrl.AutoCSetOrder(Scintilla::Ordering::Custom);
  const auto cgo{rCtrl.AutoCGetOrder()};
  UNREFERENCED_PARAMETER(cgo);
  rCtrl.SetCaretLineBackAlpha(Scintilla::Alpha::Opaque);
  const auto clba{rCtrl.GetCaretLineBackAlpha()};
  UNREFERENCED_PARAMETER(clba);
  rCtrl.SetCaretStyle(Scintilla::CaretStyle::Block);
  const auto cs{rCtrl.GetCaretStyle()};
  UNREFERENCED_PARAMETER(cs);
  rCtrl.IndicSetAlpha(1, Scintilla::Alpha::Opaque);
  const auto iga{rCtrl.IndicGetAlpha(1)};
  UNREFERENCED_PARAMETER(iga);
  rCtrl.IndicSetOutlineAlpha(1, Scintilla::Alpha::NoAlpha);
  const auto igoa{rCtrl.IndicGetOutlineAlpha(1)};
  UNREFERENCED_PARAMETER(igoa);
  rCtrl.SetMarginOptions(Scintilla::MarginOption::SubLineSelect);
  const auto gmo{rCtrl.GetMarginOptions()};
  UNREFERENCED_PARAMETER(gmo);
  rCtrl.AnnotationSetVisible(Scintilla::AnnotationVisible::Hidden);
  const auto agv{rCtrl.AnnotationGetVisible()};
  UNREFERENCED_PARAMETER(agv);
  rCtrl.AddUndoAction(1, Scintilla::UndoFlags::MayCoalesce);
  rCtrl.SetVirtualSpaceOptions(Scintilla::VirtualSpace::NoWrapLineStart);
  const auto gvso{rCtrl.GetVirtualSpaceOptions()};
  UNREFERENCED_PARAMETER(gvso);
  rCtrl.SetAdditionalSelAlpha(Scintilla::Alpha::Opaque);
  const auto asa{rCtrl.GetAdditionalSelAlpha()};
  UNREFERENCED_PARAMETER(asa);
  rCtrl.SetTechnology(Scintilla::Technology::DirectWrite);
  const auto t{rCtrl.GetTechnology()};
  UNREFERENCED_PARAMETER(t);
  //void* pLoader{rCtrl.CreateLoader(10, Scintilla::DocumentOption::TextLarge)};
  rCtrl.SetBidirectional(Scintilla::Bidirectional::L2R);
  const auto bd{rCtrl.GetBidirectional()};
  UNREFERENCED_PARAMETER(bd);
  rCtrl.AutoCSetOptions(Scintilla::AutoCompleteOption::FixedSize);
  const auto Options{rCtrl.AutoCGetOptions()}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  UNREFERENCED_PARAMETER(Options);
  rCtrl.AllocateLines(10);
  int nTabMinimumWidth{rCtrl.GetTabMinimumWidth()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.SetTabMinimumWidth(0);
  nTabMinimumWidth = rCtrl.GetTabMinimumWidth(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  BOOL bCommandEvents{rCtrl.GetCommandEvents()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.SetCommandEvents(FALSE);
  bCommandEvents = rCtrl.GetCommandEvents(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetCurrentPos();
  int nStyle{rCtrl.GetStyleAt(pos)}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  nStyle = rCtrl.GetStyleIndexAt(pos);
  UNREFERENCED_PARAMETER(nStyle);
  int nSubStyleStart{rCtrl.GetSubStylesStart(nStyle)}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  int nSubStyleLength{rCtrl.GetSubStylesLength(nStyle)}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.AllocateSubStyles(nStyle, 2);
  nSubStyleStart = rCtrl.GetSubStylesStart(nStyle); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nSubStyleLength = rCtrl.GetSubStylesLength(nStyle); //NOLINT(clang-analyzer-deadcode.DeadStores)
  const int nDistanceToSecondaryStyles{rCtrl.DistanceToSecondaryStyles()};
  UNREFERENCED_PARAMETER(nDistanceToSecondaryStyles);
  rCtrl.FreeSubStyles();
  auto LineTypesAllowed{rCtrl.GetLineEndTypesAllowed()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  const auto LineTypesSupported{rCtrl.GetLineEndTypesSupported()};
  UNREFERENCED_PARAMETER(LineTypesSupported);
  const auto LineTypesActive{rCtrl.GetLineEndTypesActive()};
  UNREFERENCED_PARAMETER(LineTypesActive);
  rCtrl.SetLineEndTypesAllowed(Scintilla::LineEndType::Unicode);
  LineTypesAllowed = rCtrl.GetLineEndTypesAllowed(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.AllocateExtendedStyles(3);
  rCtrl.ReleaseAllExtendedStyles();
  auto AutomaticFold{rCtrl.GetAutomaticFold()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.SetAutomaticFold(static_cast<Scintilla::AutomaticFold>(static_cast<int>(Scintilla::AutomaticFold::Show) | static_cast<int>(Scintilla::AutomaticFold::Change)));
  AutomaticFold = rCtrl.GetAutomaticFold(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetCurrentPos();
  auto nLine{rCtrl.LineFromPosition(pos)};
  UNREFERENCED_PARAMETER(nLine);
  rCtrl.FoldAll(Scintilla::FoldAction::Toggle);
  rCtrl.ScrollRange(40, 100);
  CString sLine1{rCtrl.GetCurLine()};
  CString sLine2{rCtrl.GetLine(0)};
  CString sProperty{rCtrl.GetSCIProperty(_T("fold"))};
  CString sProperty2{rCtrl.GetPropertyExpanded(_T("fold"))};
  CString sTempText{rCtrl.GetText(10)};
  CString sFont{rCtrl.StyleGetFont(1)};
  const int nProperty = rCtrl.GetPropertyInt(_T("fold"), 0);
  UNREFERENCED_PARAMETER(nProperty);
  rCtrl.AppendText(2, _T("XY"));
  rCtrl.SetTargetStart(0);
  rCtrl.SetTargetEnd(10);
  rCtrl.ReplaceTarget(2, _T("XY"));
  CString Target{rCtrl.GetTargetText()};
  CString sAutoCCurrentText{rCtrl.AutoCGetCurrentText()};
  CString sLexerLanguage{rCtrl.GetLexerLanguage()};
  CString sPropertyNames{rCtrl.PropertyNames()};
  const auto PropertyType{rCtrl.PropertyType(_T("fold.at.else"))};
  UNREFERENCED_PARAMETER(PropertyType);
  CString sPropertyDescription{rCtrl.DescribeProperty(_T("fold.at.else"))};
  CString sDescribeKeyWordSets{rCtrl.DescribeKeyWordSets()};
  rCtrl.SetWhitespaceSize(3);
  const int nWhitespaceSize{rCtrl.GetWhitespaceSize()};
  UNREFERENCED_PARAMETER(nWhitespaceSize);
  rCtrl.SetFontQuality(Scintilla::FontQuality::QualityAntialiased);
  const auto FontQuality{rCtrl.GetFontQuality()};
  UNREFERENCED_PARAMETER(FontQuality);
  rCtrl.SetFirstVisibleLine(3);
  rCtrl.SetMultiPaste(Scintilla::MultiPaste::Each);
  const auto MultiPaste{rCtrl.GetMultiPaste()};
  UNREFERENCED_PARAMETER(MultiPaste);
  rCtrl.SetCaretSticky(Scintilla::CaretSticky::On);
  const auto CaretSticky{rCtrl.GetCaretSticky()};
  UNREFERENCED_PARAMETER(CaretSticky);
  CString sTag{rCtrl.GetTag(0)};
  const char* pszPointer{rCtrl.GetCharacterPointer()};
  UNREFERENCED_PARAMETER(pszPointer);
  rCtrl.SetSelectionNStart(0, 2);
  const Scintilla::Position nSelectionNStart{rCtrl.GetSelectionNStart(0)};
  UNREFERENCED_PARAMETER(nSelectionNStart);
  const Scintilla::Position nSelectionNEnd{rCtrl.GetSelectionNEnd(0)};
  UNREFERENCED_PARAMETER(nSelectionNEnd);
  rCtrl.SetAdditionalCaretsVisible(FALSE);
  const BOOL bAdditionCaretVisible{rCtrl.GetAdditionalCaretsVisible()};
  UNREFERENCED_PARAMETER(bAdditionCaretVisible);
  const auto nContractedFoldNext{rCtrl.ContractedFoldNext(0)};
  UNREFERENCED_PARAMETER(nContractedFoldNext);
  rCtrl.VerticalCentreCaret();
  rCtrl.ChangeLexerState(0, -1);
  const Scintilla::Position nCharacters{rCtrl.CountCharacters(0, 100)};
  UNREFERENCED_PARAMETER(nCharacters);
  const BOOL bTest{rCtrl.GetSelectionEmpty()};
  UNREFERENCED_PARAMETER(bTest);
  const auto PhasesDraw{rCtrl.GetPhasesDraw()};
  rCtrl.SetPhasesDraw(PhasesDraw);
  rCtrl.AddTabStop(0, 40);
  rCtrl.AddTabStop(0, 60);
  const int nNextTabStop{rCtrl.GetNextTabStop(0, 40)};
  UNREFERENCED_PARAMETER(nNextTabStop);
  rCtrl.ClearTabStops(0);
  const auto IME{rCtrl.GetIMEInteraction()};
  rCtrl.SetIMEInteraction(IME);
  rCtrl.CallTipSetPosStart(100);
  const Scintilla::Position nPosition{rCtrl.PositionRelative(0, 3)};
  UNREFERENCED_PARAMETER(nPosition);
  const auto Multi{rCtrl.AutoCGetMulti()};
  rCtrl.AutoCSetMulti(Multi);
  const BOOL bMouseSelection{rCtrl.GetMouseSelectionRectangularSwitch()};
  rCtrl.SetMouseSelectionRectangularSwitch(bMouseSelection);
  rCtrl.DropSelectionN(0);
  rCtrl.SetRepresentation("\xe2\x84\xa6", "U+2126 \xe2\x84\xa6");
  CStringA sRepresentation;
#pragma warning(suppress: 26485)
  rCtrl.GetRepresentation("\xe2\x84\xa6", sRepresentation.GetBuffer(32));
  sRepresentation.ReleaseBuffer();
  rCtrl.ClearRepresentation("\xe2\x84\xa6");
  nStyle = rCtrl.GetStyleFromSubStyle(2);
  const int nPrimaryStyle{rCtrl.GetPrimaryStyleFromStyle(nStyle)};
  UNREFERENCED_PARAMETER(nPrimaryStyle);
  rCtrl.SetEdgeMode(Scintilla::EdgeVisualStyle::Background);
  rCtrl.SetEdgeColour(RGB(200, 0, 0));
  rCtrl.MultiEdgeAddLine(3, RGB(0, 200, 0));
  rCtrl.MultiEdgeClearAll();
  rCtrl.SetMouseWheelCaptures(TRUE);
  const BOOL bCaptures{rCtrl.GetMouseWheelCaptures()};
  UNREFERENCED_PARAMETER(bCaptures);
  rCtrl.ToggleFoldShowText(28, _T("PJ"));
  rCtrl.FoldDisplayTextSetStyle(Scintilla::FoldDisplayTextStyle::Boxed);
  auto Mode{rCtrl.GetTabDrawMode()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.SetTabDrawMode(Scintilla::TabDrawMode::StrikeOut);
  Mode = rCtrl.GetTabDrawMode(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.UsePopUp(Scintilla::PopUp::Text);
  const int nFrame{rCtrl.GetCaretLineFrame()};
  rCtrl.SetCaretLineFrame(nFrame);
  const Scintilla::Position nChars{rCtrl.CountCodeUnits(0, 3)};
  UNREFERENCED_PARAMETER(nChars);
  pos = rCtrl.PositionRelativeCodeUnits(0, 3); //NOLINT(clang-analyzer-deadcode.DeadStores)
  auto Index{rCtrl.GetLineCharacterIndex()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  rCtrl.AllocateLineCharacterIndex(Scintilla::LineCharacterIndexType::Utf16);
  Index = rCtrl.GetLineCharacterIndex(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.ReleaseLineCharacterIndex(Scintilla::LineCharacterIndexType::Utf16);
  nLine = rCtrl.LineFromIndexPosition(0, Scintilla::LineCharacterIndexType::Utf16);
  pos = rCtrl.IndexPositionFromLine(nLine, Scintilla::LineCharacterIndexType::Utf16); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetCharacterCategoryOptimization(0x1000);
  const int nTemp{rCtrl.GetCharacterCategoryOptimization()}; //NOLINT(clang-analyzer-deadcode.DeadStores, clang-diagnostic-unused-but-set-variable)
  UNREFERENCED_PARAMETER(nTemp);
  auto Temp2 = rCtrl.FoldDisplayTextGetStyle(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  UNREFERENCED_PARAMETER(Temp2);
  rCtrl.FoldDisplayTextSetStyle(Scintilla::FoldDisplayTextStyle::Boxed);
  Temp2 = rCtrl.FoldDisplayTextGetStyle(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetDefaultFoldDisplayText(_T("X"));
  CString sTemp{rCtrl.GetDefaultFoldDisplayText()};
  rCtrl.SetTargetStartVirtualSpace(42);
  pos = rCtrl.GetTargetStartVirtualSpace(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetTargetEndVirtualSpace(42);
  pos = rCtrl.GetTargetEndVirtualSpace(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetSelectionNStartVirtualSpace(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetSelectionNEndVirtualSpace(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.BraceMatchNext(0, 0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.EOLAnnotationSetText(0, _T("ASSEMBLER1"));
  rCtrl.EOLAnnotationSetText(1, _T("ASSEMBLER2"));
  CString sEOLText{rCtrl.EOLAnnotationGetText(0)};
  rCtrl.EOLAnnotationSetStyle(0, 3);
  rCtrl.EOLAnnotationSetStyle(1, 3);
  const int nEOLStyle{rCtrl.EOLAnnotationGetStyle(0)};
  UNREFERENCED_PARAMETER(nEOLStyle);
  //rCtrl.EOLAnnotationClearAll();
  rCtrl.EOLAnnotationSetVisible(Scintilla::EOLAnnotationVisible::Standard);
  const auto Visible{rCtrl.EOLAnnotationGetVisible()};
  UNREFERENCED_PARAMETER(Visible);
  rCtrl.SetFontLocale("en-us");
#pragma warning(suppress: 26496)
  int nSize{rCtrl.GetFontLocale(nullptr)};
  UNREFERENCED_PARAMETER(nSize);
  CStringA sFontLocale;
  rCtrl.GetFontLocale(sFontLocale.GetBuffer(nSize));
  sFontLocale.ReleaseBuffer();
  constexpr int redTransparent(0x030000FF);
  rCtrl.MarkerSetForeTranslucent(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), redTransparent);
  rCtrl.MarkerSetBackTranslucent(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), redTransparent);
  rCtrl.MarkerSetBackSelectedTranslucent(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), redTransparent);
  rCtrl.MarkerSetStrokeWidth(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), 50);
  rCtrl.SetElementColour(Scintilla::Element::List, redTransparent);
  rCtrl.SetElementColour(Scintilla::Element::ListBack, 0x0300FFFF);
  rCtrl.SetElementColour(Scintilla::Element::ListSelected, 0xFF00FF00);
  int nColor{rCtrl.GetElementColour(Scintilla::Element::List)};
  UNREFERENCED_PARAMETER(nColor);
  const BOOL bIsSet{rCtrl.GetElementIsSet(Scintilla::Element::List)};
  UNREFERENCED_PARAMETER(bIsSet);
  const BOOL bAllow{rCtrl.GetElementAllowsTranslucent(Scintilla::Element::List)};
  UNREFERENCED_PARAMETER(bAllow);
  rCtrl.ResetElementColour(Scintilla::Element::List);
  const BOOL bSupports{rCtrl.SupportsFeature(Scintilla::Supports::FractionalStrokeWidth)};
  UNREFERENCED_PARAMETER(bSupports);
  rCtrl.IndicSetStrokeWidth(0, 50);
  const int nWidth{rCtrl.IndicGetStrokeWidth(0)};
  UNREFERENCED_PARAMETER(nWidth);
  auto layer{rCtrl.MarkerGetLayer(static_cast<int>(Scintilla::MarkerOutline::FolderOpen))}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.MarkerSetLayer(static_cast<int>(Scintilla::MarkerOutline::FolderOpen), Scintilla::Layer::OverText);
  layer = rCtrl.MarkerGetLayer(static_cast<int>(Scintilla::MarkerOutline::FolderOpen));
  UNREFERENCED_PARAMETER(layer);
  nColor = rCtrl.GetElementBaseColour(Scintilla::Element::List);
  UNREFERENCED_PARAMETER(nColor);
  layer = rCtrl.GetSelectionLayer(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetSelectionLayer(Scintilla::Layer::Base);
  layer = rCtrl.GetSelectionLayer(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  layer = rCtrl.GetCaretLineLayer(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetCaretLineLayer(Scintilla::Layer::UnderText);
  layer = rCtrl.GetCaretLineLayer(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.ReplaceRectangular(0, "Hello World");
  rCtrl.ClearAllRepresentations();
  rCtrl.SetRepresentation("\x01", "U+001");
  rCtrl.SetRepresentationAppearance("\x01", Scintilla::RepresentationAppearance::Blob);
  const auto rep{rCtrl.GetRepresentationAppearance("\x01")};
  UNREFERENCED_PARAMETER(rep);
  rCtrl.SetRepresentationColour("\x01", RGB(255, 0, 0));
  const int nRepColour{rCtrl.GetRepresentationColour("\x01")};
  UNREFERENCED_PARAMETER(nRepColour);
  int nStatus{0};
#pragma warning(suppress: 26490)
  const LRESULT lResult{rCtrl.Call(static_cast<UINT>(Scintilla::Message::GetRepresentation), reinterpret_cast<WPARAM>("\x01"), 0, &nStatus)};
  UNREFERENCED_PARAMETER(lResult);
  UNREFERENCED_PARAMETER(nStatus);
  rCtrl.StyleSetCheckMonospaced(SCE_C_STRING, TRUE);
  const BOOL bMonospaced{rCtrl.StyleGetCheckMonospaced(SCE_C_STRING)};
  UNREFERENCED_PARAMETER(bMonospaced);
  rCtrl.SetCaretLineHighlightSubLine(TRUE);
  const BOOL bCaretLineHighlightSubLine{rCtrl.GetCaretLineHighlightSubLine()};
  UNREFERENCED_PARAMETER(bCaretLineHighlightSubLine);
  rCtrl.SetLayoutThreads(4);
  const int nThreads = rCtrl.GetLayoutThreads();
  UNREFERENCED_PARAMETER(nThreads);
  rCtrl.SetLineState(0, 12);
  const auto nState{rCtrl.GetLineState(0)};
  UNREFERENCED_PARAMETER(nState);
  const auto nMarker = rCtrl.MarkerNumberFromLine(0, 0);
  UNREFERENCED_PARAMETER(nMarker);
  const auto nMarkerHandle = rCtrl.MarkerHandleFromLine(0, 0);
  UNREFERENCED_PARAMETER(nMarkerHandle);
  nLine = rCtrl.MarkerLineFromHandle(nMarkerHandle); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.MarkerNumberFromLine(0, 0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.MarkerAddSet(0, 13);
  rCtrl.SetLineIndentation(0, 3);
  const auto nIndentation{rCtrl.GetLineIndentation(0)};
  UNREFERENCED_PARAMETER(nIndentation);
  pos = rCtrl.GetLineIndentPosition(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetLineEndPosition(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.GetFirstVisibleLine(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.GetLineCount(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.PositionFromLine(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.LineScroll(3, 4);
  nLine = rCtrl.VisibleFromDocLine(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.DocLineFromVisible(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.WrapCount(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.SetFoldLevel(0, Scintilla::FoldLevel::WhiteFlag);
  nLine = rCtrl.GetLastChild(0, Scintilla::FoldLevel::WhiteFlag); //NOLINT(clang-analyzer-deadcode.DeadStores)
  nLine = rCtrl.GetFoldParent(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.ShowLines(0, 1);
  rCtrl.HideLines(0, 1);
  const auto bVisible{rCtrl.GetLineVisible(0)};
  UNREFERENCED_PARAMETER(bVisible);
  rCtrl.SetFoldExpanded(0, TRUE);
  const auto bFolded{rCtrl.GetFoldExpanded(0)}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  UNREFERENCED_PARAMETER(bFolded);
  rCtrl.FoldLine(0, Scintilla::FoldAction::Toggle);
  rCtrl.FoldChildren(0, Scintilla::FoldAction::Toggle);
  rCtrl.ExpandChildren(0, Scintilla::FoldLevel::WhiteFlag);
  rCtrl.EnsureVisibleEnforcePolicy(0);
  const auto nHeight(rCtrl.TextHeight(0));
  UNREFERENCED_PARAMETER(nHeight);
  nLine = rCtrl.LinesOnScreen(); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetLineSelStartPosition(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.GetLineSelEndPosition(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  pos = rCtrl.FindColumn(0, 3); //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.MarginSetText(0, _T("X"));
  rCtrl.AnnotationSetText(0, _T("Y"));
  CStringA sMargin;
  rCtrl.MarginGetText(0, sMargin.GetBuffer(rCtrl.MarginGetText(0, nullptr)));
  sMargin.ReleaseBuffer();
  const auto sMargin2{rCtrl.MarginGetText(0)};
  rCtrl.MarginSetStyle(0, 3);
  nStyle = rCtrl.MarginGetStyle(0); //NOLINT(clang-analyzer-deadcode.DeadStores)
  const auto sWordChars{rCtrl.GetWordChars()};
  const auto sPunctuationChars{rCtrl.GetPunctuationChars()};
  const auto sStyle{rCtrl.NameOfStyle(1)};
  const auto sTags{rCtrl.TagsOfStyle(1)};
  const auto sDescription{rCtrl.DescriptionOfStyle(1)};
  const auto sLocale{rCtrl.GetFontLocale()};
  auto sStyles{rCtrl.MarginGetStyles(0)};
  const auto sAnnotation{rCtrl.AnnotationGetText(0)};
  sStyles = rCtrl.AnnotationGetStyles(0);
  const auto sBases{rCtrl.GetSubStyleBases()};
  const auto sWhitespace{rCtrl.GetWhitespaceChars()};
  rCtrl.AnnotationSetText(0, _T("G"));
  rCtrl.AnnotationSetStyle(0, 2);
  const auto nStyle2{rCtrl.AnnotationGetStyle(0)};
  UNREFERENCED_PARAMETER(nStyle2);
  rCtrl.AnnotationSetStyles(0, "H");
  const auto nAGetLines{rCtrl.AnnotationGetLines(0)};
  UNREFERENCED_PARAMETER(nAGetLines);
  rCtrl.SetChangeHistory(static_cast<Scintilla::ChangeHistoryOption>(static_cast<int>(Scintilla::ChangeHistoryOption::Enabled) | static_cast<int>(Scintilla::ChangeHistoryOption::Markers) | static_cast<int>(Scintilla::ChangeHistoryOption::Indicators)));
  const int nChangedHistory{rCtrl.GetChangeHistory()};
  UNREFERENCED_PARAMETER(nChangedHistory);
  BOOL bSelectionHidden{rCtrl.GetSelectionHidden()}; //NOLINT(clang-analyzer-deadcode.DeadStores)
  rCtrl.HideSelection(TRUE);
  bSelectionHidden = rCtrl.GetSelectionHidden();
  UNREFERENCED_PARAMETER(bSelectionHidden);
#ifdef _UNICODE
  rCtrl.StyleSetVisible(1, FALSE);
  rCtrl.StyleSetInvisibleRepresentation(1, L"A");
  CStringW sRep{rCtrl.StyleGetInvisibleRepresentation(1)};
#else
  rCtrl.StyleSetVisible(1, FALSE);
  rCtrl.StyleSetInvisibleRepresentation(1, "A");
  nSize = rCtrl.StyleGetInvisibleRepresentation(1, nullptr);
  CStringA sBuf;
  LPSTR pszBuf{sBuf.GetBuffer(nSize)};
  nSize = rCtrl.StyleGetInvisibleRepresentation(1, pszBuf); //NOLINT(clang-analyzer-deadcode.DeadStores)
  sBuf.ReleaseBuffer();
#endif //#ifdef _UNICODE
  const int nSelection{rCtrl.SelectionFromPoint(0, 0)};
  UNREFERENCED_PARAMETER(nSelection);
  Scintilla::SelectionMode mode{rCtrl.GetSelectionMode()};
  rCtrl.ChangeSelectionMode(Scintilla::SelectionMode::Rectangle);
  mode = rCtrl.GetSelectionMode();
  BOOL bMovesExtendSelection{rCtrl.GetMoveExtendsSelection()};
  rCtrl.SetMoveExtendsSelection(TRUE);
  bMovesExtendSelection = rCtrl.GetMoveExtendsSelection();
#pragma warning(suppress: 26462)
  Scintilla::IDocumentEditable* pDoc3{rCtrl.GetDocPointer()};
  UNREFERENCED_PARAMETER(pDoc3);
  Scintilla::IDocumentEditable* pDoc{rCtrl.CreateDocument(100, Scintilla::DocumentOption::Default) };
  rCtrl.SetDocPointer(pDoc);
  Scintilla::IDocumentEditable* pDoc2{rCtrl.CreateDocument(100, Scintilla::DocumentOption::Default) };
  rCtrl.AddRefDocument(pDoc2);
  rCtrl.ReleaseDocument(pDoc2);
  rCtrl.ReleaseDocument(pDoc2);
#pragma warning(suppress: 26462)
  Scintilla::IDocumentEditable* pDoc4{rCtrl.GetDocPointer()};
  UNREFERENCED_PARAMETER(pDoc4);
  int nActions{rCtrl.GetUndoActions()};
  UNREFERENCED_PARAMETER(nActions);
  const int nPoint{rCtrl.GetUndoSavePoint()};
  rCtrl.SetUndoSavePoint(nPoint);
  const int nAttach{rCtrl.GetUndoDetach()};
  rCtrl.SetUndoDetach(nAttach);
  const int nTentative{rCtrl.GetUndoTentative()};
  rCtrl.SetUndoTentative(nTentative);
  const int nCurrent{rCtrl.GetUndoCurrent()};
  rCtrl.SetUndoCurrent(nCurrent);
  rCtrl.PushUndoActionType(3, 4);
  const int nAction{rCtrl.GetUndoActionType(1)};
  UNREFERENCED_PARAMETER(nAction);
  rCtrl.ChangeLastUndoActionText(_T("HELP"));
  auto sAction{rCtrl.GetUndoActionText(1)};
  nActions = rCtrl.GetUndoActions();
  const Scintilla::Position pos2{rCtrl.GetUndoActionPosition(1)};
  UNREFERENCED_PARAMETER(pos2);
  nStyle = rCtrl.AutoCGetStyle();
  rCtrl.AutoCSetStyle(3);
  nStyle = rCtrl.AutoCGetStyle();
  rCtrl.CutAllowLine();
  const int nUndoSequence{rCtrl.GetUndoSequence()};
  UNREFERENCED_PARAMETER(nUndoSequence);
  rCtrl.LineIndent();
  rCtrl.LineDedent();
  */
#endif //#ifdef _DEBUG
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

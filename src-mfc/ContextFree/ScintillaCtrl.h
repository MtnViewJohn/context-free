/*
Module : ScintillaCtrl.h
Purpose: Defines the interface for an MFC wrapper class for the Scintilla edit control (www.scintilla.org)
Created: PJN / 19-03-2004

Copyright (c) 2004 - 2025 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code.

*/


//////////////////// Includes / Macros / Defines //////////////////////////////

#pragma once

#if _MSVC_LANG < 201703
#error CScintillaCtrl requires a minimum C++ language standard of /std:c++17
#endif //#if _MSVC_LANG < 201703

#ifndef __SCINTILLACTRL_H__
#define __SCINTILLACTRL_H__

#ifndef SCINTILLATYPES_H
#pragma message("To avoid this message, please put ScintillaTypes.h in your pre compiled header (normally stdafx.h)")
#include <ScintillaTypes.h>
#endif //#ifndef SCINTILLATYPES_H

#ifndef SCINTILLACALL_H
#pragma message("To avoid this message, please put ScintillaCall.h in your pre compiled header (normally stdafx.h)")
#include <string>
#include <ScintillaCall.h>
#endif //#ifndef SCINTILLACALL_H

#ifndef SCINTILLASTRUCTURES_H
#pragma message("To avoid this message, please put ScintillaStructures.h in your pre compiled header (normally stdafx.h)")
#include <ScintillaStructures.h>
#endif //#ifndef SCINTILLASTRUCTURES_H

#ifndef ILOADER_H
#pragma message("To avoid this message, please put ILoader.h in your pre compiled header (normally stdafx.h)")
#include <ILoader.h>
#endif //#ifndef ILOADER_H

#ifndef SCINTILLACTRL_EXT_CLASS
#define SCINTILLACTRL_EXT_CLASS
#endif //#ifndef SCINTILLACTRL_EXT_CLASS


//////////////////// Classes //////////////////////////////////////////////////

namespace Scintilla
{


#ifdef _AFX
class SCINTILLACTRL_EXT_CLASS CScintillaCtrl : public CWnd
#else
class SCINTILLACTRL_EXT_CLASS CScintillaCtrl : public ATL::CWindow
#endif //#ifdef _AFX
{
protected:
#ifdef _AFX
  using CWnd::Create; //To suppress C4263
#endif //#ifdef _AFX

public:
//Enums / Typedefs
#ifndef _AFX
  using String = _CSTRING_NS::CString;
  using StringA = _CSTRING_NS::CStringA;
  using StringW = _CSTRING_NS::CStringW;
#else
  using String = CString;
  using StringA = CStringA;
  using StringW = CStringW;
#endif //#ifndef _AFX

//Constructors / Destructors
  CScintillaCtrl() noexcept;

//Creation
#ifdef _AFX
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwExStyle = 0, LPVOID lpParam = nullptr);
#else
  BOOL Create(_In_ HWND hWndParent, _In_ ATL::_U_RECT rect, _In_ DWORD dwStyle, _In_ UINT nID, _In_ DWORD dwExStyle = 0, _In_opt_ LPVOID lpParam = nullptr);
#endif //#ifdef _AFX

//Misc
#ifdef _AFX
  void PreSubclassWindow() override;
#else
  static LPCTSTR GetWndClassName() noexcept
  {
    return _T("scintilla");
  }
#endif //#idef _AFX
  void SetupDirectAccess();

#pragma warning(suppress: 26440)
  inline LRESULT Call(_In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
  {
    //Validate our parameters
#pragma warning(suppress: 26477)
    ATLASSERT(::IsWindow(m_hWnd)); //Window must be valid

    if (::GetCurrentThreadId() == m_dwOwnerThreadID)
    {
      int nLastStatus{0};
      const auto nReturn = Call(message, wParam, lParam, &nLastStatus);
      m_LastStatus = static_cast<Status>(nLastStatus);
      return nReturn;
    }
    else
      return SendMessage(message, wParam, lParam);
  }

#pragma warning(suppress: 26440)
  inline LRESULT Call(_In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam, _Inout_ int* pStatus)
  {
    //Validate our parameters
#pragma warning(suppress: 26477)
    ATLASSERT(::IsWindow(m_hWnd)); //Window must be valid
#pragma warning(suppress: 26477)
    ATLASSERT(m_DirectStatusFunction != nullptr); //Direct status function must be valid

    return (m_DirectStatusFunction)(m_DirectPointer, message, wParam, lParam, pStatus);
  }

  [[nodiscard]] sptr_t GetDirectPointer();
  [[nodiscard]] FunctionDirect GetDirectStatusFunction();
  [[nodiscard]] Status GetLastStatus() const noexcept;

//Unicode support
  [[nodiscard]] static StringA W2UTF8(_In_NLS_string_(nLength) const wchar_t* pszText, _In_ int nLength);
  [[nodiscard]] static StringW UTF82W(_In_NLS_string_(nLength) const char* pszText, _In_ int nLength);
#ifdef _UNICODE
  void AddText(_In_ int length, _In_ const wchar_t* text);
  void InsertText(_In_ Position pos, _In_z_ const wchar_t* text);
  void ChangeInsertion(_In_ int length, _In_z_ const wchar_t* text);
  [[nodiscard]] StringW GetSelText();
  [[nodiscard]] StringW GetCurLine();
  void StyleSetFont(_In_ int style, _In_z_ const wchar_t* fontName);
  void SetWordChars(_In_z_ const wchar_t* characters);
  void AutoCShow(_In_ int lenEntered, _In_z_ const wchar_t* itemList);
  void AutoCStops(_In_z_ const wchar_t* characterSet);
  void AutoCSelect(_In_z_ const wchar_t* text);
  void AutoCSetFillUps(_In_z_ const wchar_t* characterSet);
  void UserListShow(_In_ int listType, _In_z_ const wchar_t* itemList);
  [[nodiscard]] StringW GetLine(_In_ Line line);
  void ReplaceSel(_In_z_ const wchar_t* text);
  void SetText(_In_z_ const wchar_t* text);
  [[nodiscard]] StringW GetText(_In_ int length);
  Position ReplaceTarget(_In_ Position length, _In_ const wchar_t* text);
  Position ReplaceTargetRE(_In_ Position length, _In_ const wchar_t* text);
  Position ReplaceTargetMinimal(_In_ Position length, _In_ const wchar_t* text);
  Position SearchInTarget(_In_ Position length, _In_ const wchar_t* text);
  void CallTipShow(_In_ Position pos, _In_z_ const wchar_t* definition);
  int TextWidth(_In_ int style, _In_z_ const wchar_t* text);
  void AppendText(_In_ int length, _In_ const wchar_t* text);
  Position SearchNext(_In_ FindOption flags, _In_z_ const wchar_t* text);
  Position SearchPrev(_In_ FindOption flags, _In_z_ const wchar_t* text);
  void CopyText(_In_ int length, _In_ const wchar_t* text);
  void SetWhitespaceChars(_In_z_ const wchar_t* characters);
  void SetSCIProperty(_In_z_ const wchar_t* key, _In_z_ const wchar_t* value);
  void SetKeyWords(_In_ int keywordSet, _In_z_ const wchar_t* keyWords);
  void SetIdentifiers(_In_ int style, _In_z_ const wchar_t* identifiers);
  void ChangeLastUndoActionText(_In_z_ const wchar_t* text);
  [[nodiscard]] StringW GetSCIProperty(_In_z_ const wchar_t* key);
  [[nodiscard]] StringW GetPropertyExpanded(_In_z_ const wchar_t* key);
  [[nodiscard]] int GetPropertyInt(_In_z_ const wchar_t* key, _In_ int defaultValue);
  [[nodiscard]] StringW StyleGetFont(_In_ int style);
  void MarginSetText(_In_ Line line, _In_z_ const wchar_t* text);
  void AnnotationSetText(_In_ Line line, _In_z_ const wchar_t* text);
  [[nodiscard]] StringW AutoCGetCurrentText();
  [[nodiscard]] StringW GetLexerLanguage();
  [[nodiscard]] StringW PropertyNames();
  [[nodiscard]] TypeProperty PropertyType(_In_z_ const wchar_t* name);
  void ToggleFoldShowText(_In_ Line line, _In_ const wchar_t* text);
  void SetDefaultFoldDisplayText(_In_z_ const wchar_t* text);
  void EOLAnnotationSetText(_In_ Line line, _In_ const wchar_t* text);
  void StyleSetInvisibleRepresentation(_In_ int style, _In_z_ const wchar_t* representation);
  void SetCopySeparator(_In_z_ const wchar_t* separator);
  [[nodiscard]] StringW EOLAnnotationGetText(_In_ Line line);
  [[nodiscard]] StringW DescribeProperty(_In_z_ const wchar_t* name);
  [[nodiscard]] StringW DescribeKeyWordSets();
  [[nodiscard]] StringW GetTag(_In_ int tagNumber);
  [[nodiscard]] StringW GetWordChars();
  [[nodiscard]] StringW GetWhitespaceChars();
  [[nodiscard]] StringW GetPunctuationChars();
  [[nodiscard]] StringW GetTargetText();
  [[nodiscard]] StringW NameOfStyle(_In_ int style);
  [[nodiscard]] StringW TagsOfStyle(_In_ int style);
  [[nodiscard]] StringW DescriptionOfStyle(_In_ int style);
  [[nodiscard]] StringW GetDefaultFoldDisplayText();
  [[nodiscard]] StringW MarginGetText(_In_ Line line);
  [[nodiscard]] StringW GetFontLocale();
  [[nodiscard]] StringW MarginGetStyles(_In_ Line line);
  [[nodiscard]] StringW AnnotationGetText(_In_ Line line);
  [[nodiscard]] StringW AnnotationGetStyles(_In_ Line line);
  [[nodiscard]] StringW GetSubStyleBases();
  [[nodiscard]] StringW StyleGetInvisibleRepresentation(_In_ int style);
  [[nodiscard]] StringW GetUndoActionText(_In_ int action);
  [[nodiscard]] StringW GetCopySeparator();
#else
  [[nodiscard]] StringA GetSelText();
  [[nodiscard]] StringA GetCurLine();
  [[nodiscard]] StringA GetLine(_In_ Line line);
  [[nodiscard]] StringA GetSCIProperty(_In_z_ const char* key);
  [[nodiscard]] StringA GetText(_In_ int length);
  [[nodiscard]] StringA GetPropertyExpanded(_In_z_ const char* key);
  [[nodiscard]] StringA StyleGetFont(_In_ int style);
  [[nodiscard]] StringA AutoCGetCurrentText();
  [[nodiscard]] StringA GetLexerLanguage();
  [[nodiscard]] StringA PropertyNames();
  [[nodiscard]] StringA EOLAnnotationGetText(_In_ Line line);
  [[nodiscard]] StringA DescribeProperty(_In_z_ const char* name);
  [[nodiscard]] StringA DescribeKeyWordSets();
  [[nodiscard]] StringA GetTag(_In_ int tagNumber);
  [[nodiscard]] StringA GetWordChars();
  [[nodiscard]] StringA GetWhitespaceChars();
  [[nodiscard]] StringA GetPunctuationChars();
  [[nodiscard]] StringA GetTargetText();
  [[nodiscard]] StringA NameOfStyle(_In_ int style);
  [[nodiscard]] StringA TagsOfStyle(_In_ int style);
  [[nodiscard]] StringA DescriptionOfStyle(_In_ int style);
  [[nodiscard]] StringA GetDefaultFoldDisplayText();
  [[nodiscard]] StringA MarginGetText(_In_ Line line);
  [[nodiscard]] StringA GetFontLocale();
  [[nodiscard]] StringA MarginGetStyles(_In_ Line line);
  [[nodiscard]] StringA AnnotationGetText(_In_ Line line);
  [[nodiscard]] StringA AnnotationGetStyles(_In_ Line line);
  [[nodiscard]] StringA GetSubStyleBases();
  [[nodiscard]] StringA StyleGetInvisibleRepresentation(_In_ int style);
  [[nodiscard]] StringA GetUndoActionText(_In_ int action);
  [[nodiscard]] StringA GetCopySeparator();
#endif //#ifdef _UNICODE

//Auto generated using the "ConvertScintillaiface.js" script
  void AddText(_In_ Position length, _In_reads_bytes_(length) const char* text);
  void AddStyledText(_In_ Position length, _In_reads_bytes_(length) char* c);
  void InsertText(_In_ Position pos, _In_z_ const char* text);
  void ChangeInsertion(_In_ Position length, _In_reads_bytes_(length) const char* text);
  void ClearAll();
  void DeleteRange(_In_ Position start, _In_ Position lengthDelete);
  void ClearDocumentStyle();
  [[nodiscard]] Position GetLength();
  [[nodiscard]] int GetCharAt(_In_ Position pos);
  [[nodiscard]] Position GetCurrentPos();
  [[nodiscard]] Position GetAnchor();
  [[nodiscard]] int GetStyleAt(_In_ Position pos);
  [[nodiscard]] int GetStyleIndexAt(_In_ Position pos);
  void Redo();
  void SetUndoCollection(_In_ BOOL collectUndo);
  void SelectAll();
  void SetSavePoint();
  Position GetStyledText(_Inout_ TextRange* tr);
  Position GetStyledTextFull(_Inout_ TextRangeFull* tr);
  BOOL CanRedo();
  [[nodiscard]] Line MarkerLineFromHandle(_In_ int markerHandle);
  void MarkerDeleteHandle(_In_ int markerHandle);
  [[nodiscard]] int MarkerHandleFromLine(_In_ Line line, _In_ int which);
  [[nodiscard]] int MarkerNumberFromLine(_In_ Line line, _In_ int which);
  [[nodiscard]] BOOL GetUndoCollection();
  [[nodiscard]] WhiteSpace GetViewWS();
  void SetViewWS(_In_ WhiteSpace viewWS);
  [[nodiscard]] TabDrawMode GetTabDrawMode();
  void SetTabDrawMode(_In_ TabDrawMode tabDrawMode);
  [[nodiscard]] Position PositionFromPoint(_In_ int x, _In_ int y);
  [[nodiscard]] Position PositionFromPointClose(_In_ int x, _In_ int y);
  void GotoLine(_In_ Line line);
  void GotoPos(_In_ Position caret);
  void SetAnchor(_In_ Position anchor);
  Position GetCurLine(_In_ Position length, _Inout_opt_z_ char* text);
  [[nodiscard]] Position GetEndStyled();
  void ConvertEOLs(_In_ EndOfLine eolMode);
  [[nodiscard]] EndOfLine GetEOLMode();
  void SetEOLMode(_In_ EndOfLine eolMode);
  void StartStyling(_In_ Position start, _In_ int unused);
  void SetStyling(_In_ Position length, _In_ int style);
  [[nodiscard]] BOOL GetBufferedDraw();
  void SetBufferedDraw(_In_ BOOL buffered);
  void SetTabWidth(_In_ int tabWidth);
  [[nodiscard]] int GetTabWidth();
  void SetTabMinimumWidth(_In_ int pixels);
  [[nodiscard]] int GetTabMinimumWidth();
  void ClearTabStops(_In_ Line line);
  void AddTabStop(_In_ Line line, _In_ int x);
  [[nodiscard]] int GetNextTabStop(_In_ Line line, _In_ int x);
  void SetCodePage(_In_ int codePage);
  void SetFontLocale(_In_z_ const char* localeName);
  int GetFontLocale(_Inout_opt_z_ char* localeName);
  [[nodiscard]] IMEInteraction GetIMEInteraction();
  void SetIMEInteraction(_In_ IMEInteraction imeInteraction);
  void MarkerDefine(_In_ int markerNumber, _In_ MarkerSymbol markerSymbol);
  void MarkerSetFore(_In_ int markerNumber, _In_ COLORREF fore);
  void MarkerSetBack(_In_ int markerNumber, _In_ COLORREF back);
  void MarkerSetBackSelected(_In_ int markerNumber, _In_ COLORREF back);
  void MarkerSetForeTranslucent(_In_ int markerNumber, _In_ int fore);
  void MarkerSetBackTranslucent(_In_ int markerNumber, _In_ int back);
  void MarkerSetBackSelectedTranslucent(_In_ int markerNumber, _In_ int back);
  void MarkerSetStrokeWidth(_In_ int markerNumber, _In_ int hundredths);
  void MarkerEnableHighlight(_In_ BOOL enabled);
  int MarkerAdd(_In_ Line line, _In_ int markerNumber);
  void MarkerDelete(_In_ Line line, _In_ int markerNumber);
  void MarkerDeleteAll(_In_ int markerNumber);
  [[nodiscard]] int MarkerGet(_In_ Line line);
  [[nodiscard]] Line MarkerNext(_In_ Line lineStart, _In_ int markerMask);
  [[nodiscard]] Line MarkerPrevious(_In_ Line lineStart, _In_ int markerMask);
  void MarkerDefinePixmap(_In_ int markerNumber, _In_ const char* pixmap);
  void MarkerAddSet(_In_ Line line, _In_ int markerSet);
  void MarkerSetAlpha(_In_ int markerNumber, _In_ Alpha alpha);
  [[nodiscard]] Layer MarkerGetLayer(_In_ int markerNumber);
  void MarkerSetLayer(_In_ int markerNumber, _In_ Layer layer);
  void SetMarginTypeN(_In_ int margin, _In_ MarginType marginType);
  [[nodiscard]] MarginType GetMarginTypeN(_In_ int margin);
  void SetMarginWidthN(_In_ int margin, _In_ int pixelWidth);
  [[nodiscard]] int GetMarginWidthN(_In_ int margin);
  void SetMarginMaskN(_In_ int margin, _In_ int mask);
  [[nodiscard]] int GetMarginMaskN(_In_ int margin);
  void SetMarginSensitiveN(_In_ int margin, _In_ BOOL sensitive);
  [[nodiscard]] BOOL GetMarginSensitiveN(_In_ int margin);
  void SetMarginCursorN(_In_ int margin, _In_ CursorShape cursor);
  [[nodiscard]] CursorShape GetMarginCursorN(_In_ int margin);
  void SetMarginBackN(_In_ int margin, _In_ COLORREF back);
  [[nodiscard]] COLORREF GetMarginBackN(_In_ int margin);
  void SetMargins(_In_ int margins);
  [[nodiscard]] int GetMargins();
  void StyleClearAll();
  void StyleSetFore(_In_ int style, _In_ COLORREF fore);
  void StyleSetBack(_In_ int style, _In_ COLORREF back);
  void StyleSetBold(_In_ int style, _In_ BOOL bold);
  void StyleSetItalic(_In_ int style, _In_ BOOL italic);
  void StyleSetSize(_In_ int style, _In_ int sizePoints);
  void StyleSetFont(_In_ int style, _In_z_ const char* fontName);
  void StyleSetEOLFilled(_In_ int style, _In_ BOOL eolFilled);
  void StyleResetDefault();
  void StyleSetUnderline(_In_ int style, _In_ BOOL underline);
  [[nodiscard]] COLORREF StyleGetFore(_In_ int style);
  [[nodiscard]] COLORREF StyleGetBack(_In_ int style);
  [[nodiscard]] BOOL StyleGetBold(_In_ int style);
  [[nodiscard]] BOOL StyleGetItalic(_In_ int style);
  [[nodiscard]] int StyleGetSize(_In_ int style);
  int StyleGetFont(_In_ int style, _Inout_opt_z_ char* fontName);
  [[nodiscard]] BOOL StyleGetEOLFilled(_In_ int style);
  [[nodiscard]] BOOL StyleGetUnderline(_In_ int style);
  [[nodiscard]] CaseVisible StyleGetCase(_In_ int style);
  [[nodiscard]] CharacterSet StyleGetCharacterSet(_In_ int style);
  [[nodiscard]] BOOL StyleGetVisible(_In_ int style);
  [[nodiscard]] BOOL StyleGetChangeable(_In_ int style);
  [[nodiscard]] BOOL StyleGetHotSpot(_In_ int style);
  void StyleSetCase(_In_ int style, _In_ CaseVisible caseVisible);
  void StyleSetSizeFractional(_In_ int style, _In_ int sizeHundredthPoints);
  [[nodiscard]] int StyleGetSizeFractional(_In_ int style);
  void StyleSetWeight(_In_ int style, _In_ FontWeight weight);
  [[nodiscard]] FontWeight StyleGetWeight(_In_ int style);
  void StyleSetCharacterSet(_In_ int style, _In_ CharacterSet characterSet);
  void StyleSetHotSpot(_In_ int style, _In_ BOOL hotspot);
  void StyleSetCheckMonospaced(_In_ int style, _In_ BOOL checkMonospaced);
  [[nodiscard]] BOOL StyleGetCheckMonospaced(_In_ int style);
  void StyleSetStretch(_In_ int style, _In_ FontStretch stretch);
  FontStretch StyleGetStretch(_In_ int style);
  void StyleSetInvisibleRepresentation(_In_ int style, _In_z_ const char* representation);
  int StyleGetInvisibleRepresentation(_In_ int style, _Inout_opt_z_ char* representation);
  void SetElementColour(_In_ Element element, _In_ int colourElement);
  [[nodiscard]] int GetElementColour(_In_ Element element);
  void ResetElementColour(_In_ Element element);
  [[nodiscard]] BOOL GetElementIsSet(_In_ Element element);
  [[nodiscard]] BOOL GetElementAllowsTranslucent(_In_ Element element);
  [[nodiscard]] int GetElementBaseColour(_In_ Element element);
  void SetSelFore(_In_ BOOL useSetting, _In_ COLORREF fore);
  void SetSelBack(_In_ BOOL useSetting, _In_ COLORREF back);
  [[nodiscard]] Alpha GetSelAlpha();
  void SetSelAlpha(_In_ Alpha alpha);
  [[nodiscard]] BOOL GetSelEOLFilled();
  void SetSelEOLFilled(_In_ BOOL filled);
  [[nodiscard]] Layer GetSelectionLayer();
  void SetSelectionLayer(_In_ Layer layer);
  [[nodiscard]] Layer GetCaretLineLayer();
  void SetCaretLineLayer(_In_ Layer layer);
  [[nodiscard]] BOOL GetCaretLineHighlightSubLine();
  void SetCaretLineHighlightSubLine(_In_ BOOL subLine);
  void SetCaretFore(_In_ COLORREF fore);
  void AssignCmdKey(_In_ DWORD keyDefinition, _In_ int sciCommand);
  void ClearCmdKey(_In_ DWORD keyDefinition);
  void ClearAllCmdKeys();
  void SetStylingEx(_In_ Position length, _In_ const char* styles);
  void StyleSetVisible(_In_ int style, _In_ BOOL visible);
  [[nodiscard]] int GetCaretPeriod();
  void SetCaretPeriod(_In_ int periodMilliseconds);
  void SetWordChars(_In_ const char* characters);
  int GetWordChars(_Inout_opt_z_ char* characters);
  void SetCharacterCategoryOptimization(_In_ int countCharacters);
  [[nodiscard]] int GetCharacterCategoryOptimization();
  void BeginUndoAction();
  void EndUndoAction();
  [[nodiscard]] int GetUndoSequence();
  [[nodiscard]] int GetUndoActions();
  void SetUndoSavePoint(_In_ int action);
  [[nodiscard]] int GetUndoSavePoint();
  void SetUndoDetach(_In_ int action);
  [[nodiscard]] int GetUndoDetach();
  void SetUndoTentative(_In_ int action);
  [[nodiscard]] int GetUndoTentative();
  void SetUndoCurrent(_In_ int action);
  [[nodiscard]] int GetUndoCurrent();
  void PushUndoActionType(_In_ int type, Position pos);
  void ChangeLastUndoActionText(_In_z_ const char* text);
  void ChangeLastUndoActionText(_In_ Position length, _In_reads_bytes_(length) const char* text);
  [[nodiscard]] int GetUndoActionType(_In_ int action);
  [[nodiscard]] Position GetUndoActionPosition(_In_ int action);
  int GetUndoActionText(_In_ int action, _Inout_opt_z_ char* text);
  void IndicSetStyle(_In_ int indicator, _In_ IndicatorStyle indicatorStyle);
  [[nodiscard]] IndicatorStyle IndicGetStyle(_In_ int indicator);
  void IndicSetFore(_In_ int indicator, _In_ COLORREF fore);
  [[nodiscard]] COLORREF IndicGetFore(_In_ int indicator);
  void IndicSetUnder(_In_ int indicator, _In_ BOOL under);
  [[nodiscard]] BOOL IndicGetUnder(_In_ int indicator);
  void IndicSetHoverStyle(_In_ int indicator, _In_ IndicatorStyle indicatorStyle);
  [[nodiscard]] IndicatorStyle IndicGetHoverStyle(_In_ int indicator);
  void IndicSetHoverFore(_In_ int indicator, _In_ COLORREF fore);
  [[nodiscard]] COLORREF IndicGetHoverFore(_In_ int indicator);
  void IndicSetFlags(_In_ int indicator, _In_ IndicFlag flags);
  [[nodiscard]] IndicFlag IndicGetFlags(_In_ int indicator);
  void IndicSetStrokeWidth(_In_ int indicator, _In_ int hundredths);
  [[nodiscard]] int IndicGetStrokeWidth(_In_ int indicator);
  void SetWhitespaceFore(_In_ BOOL useSetting, _In_ COLORREF fore);
  void SetWhitespaceBack(_In_ BOOL useSetting, _In_ COLORREF back);
  void SetWhitespaceSize(_In_ int size);
  [[nodiscard]] int GetWhitespaceSize();
  void SetLineState(_In_ Line line, _In_ int state);
  [[nodiscard]] int GetLineState(_In_ Line line);
  [[nodiscard]] int GetMaxLineState();
  [[nodiscard]] BOOL GetCaretLineVisible();
  void SetCaretLineVisible(_In_ BOOL show);
  [[nodiscard]] COLORREF GetCaretLineBack();
  void SetCaretLineBack(_In_ COLORREF back);
  [[nodiscard]] int GetCaretLineFrame();
  void SetCaretLineFrame(_In_ int width);
  void StyleSetChangeable(_In_ int style, _In_ BOOL changeable);
  void AutoCShow(_In_ Position lengthEntered, _In_z_ const char* itemList);
  void AutoCCancel();
  [[nodiscard]] BOOL AutoCActive();
  [[nodiscard]] Position AutoCPosStart();
  void AutoCComplete();
  void AutoCStops(_In_z_ const char* characterSet);
  void AutoCSetSeparator(_In_ int separatorCharacter);
  [[nodiscard]] int AutoCGetSeparator();
  void AutoCSelect(_In_z_ const char* select);
  void AutoCSetCancelAtStart(_In_ BOOL cancel);
  [[nodiscard]] BOOL AutoCGetCancelAtStart();
  void AutoCSetFillUps(_In_z_ const char* characterSet);
  void AutoCSetChooseSingle(_In_ BOOL chooseSingle);
  [[nodiscard]] BOOL AutoCGetChooseSingle();
  void AutoCSetIgnoreCase(_In_ BOOL ignoreCase);
  [[nodiscard]] BOOL AutoCGetIgnoreCase();
  void UserListShow(_In_ int listType, _In_z_ const char* itemList);
  void AutoCSetAutoHide(_In_ BOOL autoHide);
  [[nodiscard]] BOOL AutoCGetAutoHide();
  void AutoCSetOptions(_In_ AutoCompleteOption options);
  [[nodiscard]] AutoCompleteOption AutoCGetOptions();
  void AutoCSetDropRestOfWord(_In_ BOOL dropRestOfWord);
  [[nodiscard]] BOOL AutoCGetDropRestOfWord();
  void RegisterImage(_In_ int type, _In_ const char* xpmData);
  void ClearRegisteredImages();
  [[nodiscard]] int AutoCGetTypeSeparator();
  void AutoCSetTypeSeparator(_In_ int separatorCharacter);
  void AutoCSetMaxWidth(_In_ int characterCount);
  [[nodiscard]] int AutoCGetMaxWidth();
  void AutoCSetMaxHeight(_In_ int rowCount);
  [[nodiscard]] int AutoCGetMaxHeight();
  void AutoCSetStyle(_In_ int style);
  [[nodiscard]] int AutoCGetStyle();
  void SetIndent(_In_ int indentSize);
  [[nodiscard]] int GetIndent();
  void SetUseTabs(_In_ BOOL useTabs);
  [[nodiscard]] BOOL GetUseTabs();
  void SetLineIndentation(_In_ Line line, _In_ int indentation);
  [[nodiscard]] int GetLineIndentation(_In_ Line line);
  [[nodiscard]] Position GetLineIndentPosition(_In_ Line line);
  [[nodiscard]] Position GetColumn(_In_ Position pos);
  [[nodiscard]] Position CountCharacters(_In_ Position start, _In_ Position end);
  [[nodiscard]] Position CountCodeUnits(_In_ Position start, _In_ Position end);
  void SetHScrollBar(_In_ BOOL visible);
  [[nodiscard]] BOOL GetHScrollBar();
  void SetIndentationGuides(_In_ IndentView indentView);
  [[nodiscard]] IndentView GetIndentationGuides();
  void SetHighlightGuide(_In_ Position column);
  [[nodiscard]] Position GetHighlightGuide();
  [[nodiscard]] Position GetLineEndPosition(_In_ Line line);
  [[nodiscard]] int GetCodePage();
  [[nodiscard]] COLORREF GetCaretFore();
  [[nodiscard]] BOOL GetReadOnly();
  void SetCurrentPos(_In_ Position caret);
  void SetSelectionStart(_In_ Position anchor);
  [[nodiscard]] Position GetSelectionStart();
  void SetSelectionEnd(_In_ Position caret);
  [[nodiscard]] Position GetSelectionEnd();
  void SetEmptySelection(_In_ Position caret);
  void SetPrintMagnification(_In_ int magnification);
  [[nodiscard]] int GetPrintMagnification();
  void SetPrintColourMode(_In_ PrintOption mode);
  [[nodiscard]] PrintOption GetPrintColourMode();
  [[nodiscard]] Position FindText(_In_ FindOption searchFlags, _Inout_ TextToFind* ft);
  [[nodiscard]] Position FindTextFull(_In_ FindOption searchFlags, _Inout_ TextToFindFull* ft);
  [[nodiscard]] Position FormatRange(_In_ BOOL draw, _In_ RangeToFormat* fr);
  [[nodiscard]] Position FormatRangeFull(_In_ BOOL draw, _In_ RangeToFormatFull* fr);
  void SetChangeHistory(_In_ ChangeHistoryOption changeHistory);
  [[nodiscard]] int GetChangeHistory();
  [[nodiscard]] Line GetFirstVisibleLine();
  Position GetLine(_In_ Line line, _Inout_opt_z_ char* text);
  [[nodiscard]] Line GetLineCount();
  void AllocateLines(_In_ Line lines);
  void SetMarginLeft(_In_ int pixelWidth);
  [[nodiscard]] int GetMarginLeft();
  void SetMarginRight(_In_ int pixelWidth);
  [[nodiscard]] int GetMarginRight();
  [[nodiscard]] BOOL GetModify();
  void SetSel(_In_ Position anchor, _In_ Position caret);
  Position GetSelText(_Inout_opt_z_ char* text);
  Position GetTextRange(_Inout_ TextRange* tr);
  Position GetTextRangeFull(_Inout_ TextRangeFull* tr);
  void HideSelection(_In_ BOOL hide);
  [[nodiscard]] BOOL GetSelectionHidden();
  [[nodiscard]] int PointXFromPosition(_In_ Position pos);
  [[nodiscard]] int PointYFromPosition(_In_ Position pos);
  [[nodiscard]] Line LineFromPosition(_In_ Position pos);
  [[nodiscard]] Position PositionFromLine(_In_ Line line);
  void LineScroll(_In_ Position columns, _In_ Line lines);
  void ScrollCaret();
  void ScrollRange(_In_ Position secondary, _In_ Position primary);
  void ReplaceSel(_In_z_ const char* text);
  void SetReadOnly(_In_ BOOL readOnly);
  void Null();
  [[nodiscard]] BOOL CanPaste();
  [[nodiscard]] BOOL CanUndo();
  void EmptyUndoBuffer();
  void Undo();
  void Cut();
  void Copy();
  void Paste();
  void Clear();
  void SetText(_In_z_ const char* text);
  Position GetText(_In_ Position length, _Inout_updates_opt_(length+1) char* text);
  [[nodiscard]] Position GetTextLength();
  void SetOvertype(_In_ BOOL overType);
  [[nodiscard]] BOOL GetOvertype();
  void SetCaretWidth(_In_ int pixelWidth);
  [[nodiscard]] int GetCaretWidth();
  void SetTargetStart(_In_ Position start);
  [[nodiscard]] Position GetTargetStart();
  void SetTargetStartVirtualSpace(_In_ Position space);
  [[nodiscard]] Position GetTargetStartVirtualSpace();
  void SetTargetEnd(_In_ Position end);
  [[nodiscard]] Position GetTargetEnd();
  void SetTargetEndVirtualSpace(_In_ Position space);
  [[nodiscard]] Position GetTargetEndVirtualSpace();
  void SetTargetRange(_In_ Position start, _In_ Position end);
  Position GetTargetText(_Inout_opt_z_ char* text);
  void TargetFromSelection();
  void TargetWholeDocument();
  Position ReplaceTarget(_In_ Position length, _In_ const char* text);
  Position ReplaceTargetRE(_In_ Position length, _In_ const char* text);
  Position ReplaceTargetMinimal(_In_ Position length, _In_ const char* text);
  Position SearchInTarget(_In_ Position length, _In_reads_bytes_(length) const char* text);
  void SetSearchFlags(_In_ FindOption searchFlags);
  [[nodiscard]] FindOption GetSearchFlags();
  void CallTipShow(_In_ Position pos, _In_z_ const char* definition);
  void CallTipCancel();
  [[nodiscard]] BOOL CallTipActive();
  [[nodiscard]] Position CallTipPosStart();
  void CallTipSetPosStart(_In_ Position posStart);
  void CallTipSetHlt(_In_ Position highlightStart, _In_ Position highlightEnd);
  void CallTipSetBack(_In_ COLORREF back);
  void CallTipSetFore(_In_ COLORREF fore);
  void CallTipSetForeHlt(_In_ COLORREF fore);
  void CallTipUseStyle(_In_ int tabSize);
  void CallTipSetPosition(_In_ BOOL above);
  [[nodiscard]] Line VisibleFromDocLine(_In_ Line docLine);
  [[nodiscard]] Line DocLineFromVisible(_In_ Line displayLine);
  [[nodiscard]] Line WrapCount(_In_ Line docLine);
  void SetFoldLevel(_In_ Line line, _In_ FoldLevel level);
  [[nodiscard]] FoldLevel GetFoldLevel(_In_ Line line);
  [[nodiscard]] Line GetLastChild(_In_ Line line, _In_ FoldLevel level);
  [[nodiscard]] Line GetFoldParent(_In_ Line line);
  void ShowLines(_In_ Line lineStart, _In_ Line lineEnd);
  void HideLines(_In_ Line lineStart, _In_ Line lineEnd);
  [[nodiscard]] BOOL GetLineVisible(_In_ Line line);
  [[nodiscard]] BOOL GetAllLinesVisible();
  void SetFoldExpanded(_In_ Line line, _In_ BOOL expanded);
  [[nodiscard]] BOOL GetFoldExpanded(_In_ Line line);
  void ToggleFold(_In_ Line line);
  void ToggleFoldShowText(_In_ Line line, _In_ const char* text);
  void FoldDisplayTextSetStyle(_In_ FoldDisplayTextStyle style);
  [[nodiscard]] FoldDisplayTextStyle FoldDisplayTextGetStyle();
  void SetDefaultFoldDisplayText(_In_z_ const char* text);
  int GetDefaultFoldDisplayText(_Inout_opt_z_ char* text);
  void FoldLine(_In_ Line line, _In_ FoldAction action);
  void FoldChildren(_In_ Line line, _In_ FoldAction action);
  void ExpandChildren(_In_ Line line, _In_ FoldLevel level);
  void FoldAll(_In_ FoldAction action);
  void EnsureVisible(_In_ Line line);
  void SetAutomaticFold(_In_ AutomaticFold automaticFold);
  [[nodiscard]] AutomaticFold GetAutomaticFold();
  void SetFoldFlags(_In_ FoldFlag flags);
  void EnsureVisibleEnforcePolicy(_In_ Line line);
  void SetTabIndents(_In_ BOOL tabIndents);
  [[nodiscard]] BOOL GetTabIndents();
  void SetBackSpaceUnIndents(_In_ BOOL bsUnIndents);
  [[nodiscard]] BOOL GetBackSpaceUnIndents();
  void SetMouseDwellTime(_In_ int periodMilliseconds);
  [[nodiscard]] int GetMouseDwellTime();
  [[nodiscard]] Position WordStartPosition(_In_ Position pos, _In_ BOOL onlyWordCharacters);
  [[nodiscard]] Position WordEndPosition(_In_ Position pos, _In_ BOOL onlyWordCharacters);
  [[nodiscard]] BOOL IsRangeWord(_In_ Position start, _In_ Position end);
  void SetIdleStyling(_In_ IdleStyling idleStyling);
  [[nodiscard]] IdleStyling GetIdleStyling();
  void SetWrapMode(_In_ Wrap wrapMode);
  [[nodiscard]] Wrap GetWrapMode();
  void SetWrapVisualFlags(_In_ WrapVisualFlag wrapVisualFlags);
  [[nodiscard]] WrapVisualFlag GetWrapVisualFlags();
  void SetWrapVisualFlagsLocation(_In_ WrapVisualLocation wrapVisualFlagsLocation);
  [[nodiscard]] WrapVisualLocation GetWrapVisualFlagsLocation();
  void SetWrapStartIndent(_In_ int indent);
  [[nodiscard]] int GetWrapStartIndent();
  void SetWrapIndentMode(_In_ WrapIndentMode wrapIndentMode);
  [[nodiscard]] WrapIndentMode GetWrapIndentMode();
  void SetLayoutCache(_In_ LineCache cacheMode);
  [[nodiscard]] LineCache GetLayoutCache();
  void SetScrollWidth(_In_ int pixelWidth);
  [[nodiscard]] int GetScrollWidth();
  void SetScrollWidthTracking(_In_ BOOL tracking);
  [[nodiscard]] BOOL GetScrollWidthTracking();
  [[nodiscard]] int TextWidth(_In_ int style, _In_z_ const char* text);
  void SetEndAtLastLine(_In_ BOOL endAtLastLine);
  [[nodiscard]] BOOL GetEndAtLastLine();
  [[nodiscard]] int TextHeight(_In_ Line line);
  void SetVScrollBar(_In_ BOOL visible);
  [[nodiscard]] BOOL GetVScrollBar();
  void AppendText(_In_ Position length, _In_reads_bytes_(length) const char* text);
  [[nodiscard]] PhasesDraw GetPhasesDraw();
  void SetPhasesDraw(_In_ PhasesDraw phases);
  void SetFontQuality(_In_ FontQuality fontQuality);
  [[nodiscard]] FontQuality GetFontQuality();
  void SetFirstVisibleLine(_In_ Line displayLine);
  void SetMultiPaste(_In_ MultiPaste multiPaste);
  [[nodiscard]] MultiPaste GetMultiPaste();
  int GetTag(_In_ int tagNumber, _Inout_opt_z_ char* tagValue);
  void LinesJoin();
  void LinesSplit(_In_ int pixelWidth);
  void SetFoldMarginColour(_In_ BOOL useSetting, _In_ COLORREF back);
  void SetFoldMarginHiColour(_In_ BOOL useSetting, _In_ COLORREF fore);
  void SetAccessibility(_In_ Accessibility accessibility);
  [[nodiscard]] Accessibility GetAccessibility();
  void LineDown();
  void LineDownExtend();
  void LineUp();
  void LineUpExtend();
  void CharLeft();
  void CharLeftExtend();
  void CharRight();
  void CharRightExtend();
  void WordLeft();
  void WordLeftExtend();
  void WordRight();
  void WordRightExtend();
  void Home();
  void HomeExtend();
  void LineEnd();
  void LineEndExtend();
  void DocumentStart();
  void DocumentStartExtend();
  void DocumentEnd();
  void DocumentEndExtend();
  void PageUp();
  void PageUpExtend();
  void PageDown();
  void PageDownExtend();
  void EditToggleOvertype();
  void Cancel();
  void DeleteBack();
  void Tab();
  void LineIndent();
  void BackTab();
  void LineDedent();
  void NewLine();
  void FormFeed();
  void VCHome();
  void VCHomeExtend();
  void ZoomIn();
  void ZoomOut();
  void DelWordLeft();
  void DelWordRight();
  void DelWordRightEnd();
  void LineCut();
  void LineDelete();
  void LineTranspose();
  void LineReverse();
  void LineDuplicate();
  void LowerCase();
  void UpperCase();
  void LineScrollDown();
  void LineScrollUp();
  void DeleteBackNotLine();
  void HomeDisplay();
  void HomeDisplayExtend();
  void LineEndDisplay();
  void LineEndDisplayExtend();
  void HomeWrap();
  void HomeWrapExtend();
  void LineEndWrap();
  void LineEndWrapExtend();
  void VCHomeWrap();
  void VCHomeWrapExtend();
  void LineCopy();
  void MoveCaretInsideView();
  [[nodiscard]] Position LineLength(_In_ Line line);
  void BraceHighlight(_In_ Position posA, _In_ Position posB);
  void BraceHighlightIndicator(_In_ BOOL useSetting, _In_ int indicator);
  void BraceBadLight(_In_ Position pos);
  void BraceBadLightIndicator(_In_ BOOL useSetting, _In_ int indicator);
  [[nodiscard]] Position BraceMatch(_In_ Position pos, _In_ int maxReStyle);
  [[nodiscard]] Position BraceMatchNext(_In_ Position pos, _In_ Position startPos);
  [[nodiscard]] BOOL GetViewEOL();
  void SetViewEOL(_In_ BOOL visible);
  [[nodiscard]] IDocumentEditable* GetDocPointer();
  void SetDocPointer(_In_opt_ IDocumentEditable* doc);
  void SetModEventMask(_In_ ModificationFlags eventMask);
  [[nodiscard]] Position GetEdgeColumn();
  void SetEdgeColumn(_In_ Position column);
  [[nodiscard]] EdgeVisualStyle GetEdgeMode();
  void SetEdgeMode(_In_ EdgeVisualStyle edgeMode);
  [[nodiscard]] COLORREF GetEdgeColour();
  void SetEdgeColour(_In_ COLORREF edgeColour);
  void MultiEdgeAddLine(_In_ Position column, _In_ COLORREF edgeColour);
  void MultiEdgeClearAll();
  [[nodiscard]] Position GetMultiEdgeColumn(_In_ int which);
  void SearchAnchor();
  [[nodiscard]] Position SearchNext(_In_ FindOption searchFlags, _In_z_ const char* text);
  [[nodiscard]] Position SearchPrev(_In_ FindOption searchFlags, _In_z_ const char* text);
  [[nodiscard]] Line LinesOnScreen();
  void UsePopUp(_In_ PopUp popUpMode);
  [[nodiscard]] BOOL SelectionIsRectangle();
  void SetZoom(_In_ int zoomInPoints);
  [[nodiscard]] int GetZoom();
  [[nodiscard]] IDocumentEditable* CreateDocument(_In_ Position bytes, _In_ DocumentOption documentOptions);
  void AddRefDocument(_In_ IDocumentEditable* doc);
  void ReleaseDocument(_In_ IDocumentEditable* doc);
  [[nodiscard]] DocumentOption GetDocumentOptions();
  [[nodiscard]] ModificationFlags GetModEventMask();
  void SetCommandEvents(_In_ BOOL commandEvents);
  [[nodiscard]] BOOL GetCommandEvents();
  void SCISetFocus(_In_ BOOL focus);
  [[nodiscard]] BOOL GetFocus();
  void SetStatus(_In_ Status status);
  [[nodiscard]] Status GetStatus();
  void SetMouseDownCaptures(_In_ BOOL captures);
  [[nodiscard]] BOOL GetMouseDownCaptures();
  void SetMouseWheelCaptures(_In_ BOOL captures);
  [[nodiscard]] BOOL GetMouseWheelCaptures();
  void SetCursor(_In_ CursorShape cursorType);
  [[nodiscard]] CursorShape GetCursor();
  void SetControlCharSymbol(_In_ int symbol);
  [[nodiscard]] int GetControlCharSymbol();
  void WordPartLeft();
  void WordPartLeftExtend();
  void WordPartRight();
  void WordPartRightExtend();
  void SetVisiblePolicy(_In_ VisiblePolicy visiblePolicy, _In_ int visibleSlop);
  void DelLineLeft();
  void DelLineRight();
  void SetXOffset(_In_ int xOffset);
  [[nodiscard]] int GetXOffset();
  void ChooseCaretX();
  void GrabFocus();
  void SetXCaretPolicy(_In_ CaretPolicy caretPolicy, _In_ int caretSlop);
  void SetYCaretPolicy(_In_ CaretPolicy caretPolicy, _In_ int caretSlop);
  void SetPrintWrapMode(_In_ Wrap wrapMode);
  [[nodiscard]] Wrap GetPrintWrapMode();
  void SetHotspotActiveFore(_In_ BOOL useSetting, _In_ COLORREF fore);
  [[nodiscard]] COLORREF GetHotspotActiveFore();
  void SetHotspotActiveBack(_In_ BOOL useSetting, _In_ COLORREF back);
  [[nodiscard]] COLORREF GetHotspotActiveBack();
  void SetHotspotActiveUnderline(_In_ BOOL underline);
  [[nodiscard]] BOOL GetHotspotActiveUnderline();
  void SetHotspotSingleLine(_In_ BOOL singleLine);
  [[nodiscard]] BOOL GetHotspotSingleLine();
  void ParaDown();
  void ParaDownExtend();
  void ParaUp();
  void ParaUpExtend();
  [[nodiscard]] Position PositionBefore(_In_ Position pos);
  [[nodiscard]] Position PositionAfter(_In_ Position pos);
  [[nodiscard]] Position PositionRelative(_In_ Position pos, _In_ Position relative);
  [[nodiscard]] Position PositionRelativeCodeUnits(_In_ Position pos, _In_ Position relative);
  void CopyRange(_In_ Position start, _In_ Position end);
  void CopyText(_In_ Position length, _In_reads_bytes_(length) const char* text);
  void SetSelectionMode(_In_ SelectionMode selectionMode);
  void ChangeSelectionMode(_In_ SelectionMode selectionMode);
  [[nodiscard]] SelectionMode GetSelectionMode();
  void SetMoveExtendsSelection(_In_ BOOL moveExtendsSelection);
  [[nodiscard]] BOOL GetMoveExtendsSelection();
  [[nodiscard]] Position GetLineSelStartPosition(_In_ Line line);
  [[nodiscard]] Position GetLineSelEndPosition(_In_ Line line);
  void LineDownRectExtend();
  void LineUpRectExtend();
  void CharLeftRectExtend();
  void CharRightRectExtend();
  void HomeRectExtend();
  void VCHomeRectExtend();
  void LineEndRectExtend();
  void PageUpRectExtend();
  void PageDownRectExtend();
  void StutteredPageUp();
  void StutteredPageUpExtend();
  void StutteredPageDown();
  void StutteredPageDownExtend();
  void WordLeftEnd();
  void WordLeftEndExtend();
  void WordRightEnd();
  void WordRightEndExtend();
  void SetWhitespaceChars(_In_z_ const char* characters);
  int GetWhitespaceChars(_Inout_opt_z_ char* characters);
  void SetPunctuationChars(_In_z_ const char* characters);
  int GetPunctuationChars(_Inout_opt_z_ char* characters);
  void SetCharsDefault();
  [[nodiscard]] int AutoCGetCurrent();
  int AutoCGetCurrentText(_Inout_opt_z_ char* text);
  void AutoCSetCaseInsensitiveBehaviour(_In_ CaseInsensitiveBehaviour behaviour);
  [[nodiscard]] CaseInsensitiveBehaviour AutoCGetCaseInsensitiveBehaviour();
  void AutoCSetMulti(_In_ MultiAutoComplete multi);
  [[nodiscard]] MultiAutoComplete AutoCGetMulti();
  void AutoCSetOrder(_In_ Ordering order);
  [[nodiscard]] Ordering AutoCGetOrder();
  void Allocate(_In_ Position bytes);
  [[nodiscard]] Position TargetAsUTF8(_Inout_ char* s);
  void SetLengthForEncode(_In_ Position bytes);
  [[nodiscard]] Position EncodedFromUTF8(_In_ const char* utf8, _Inout_ char* encoded);
  [[nodiscard]] Position FindColumn(_In_ Line line, _In_ Position column);
  [[nodiscard]] CaretSticky GetCaretSticky();
  void SetCaretSticky(_In_ CaretSticky useCaretStickyBehaviour);
  void ToggleCaretSticky();
  void SetPasteConvertEndings(_In_ BOOL convert);
  [[nodiscard]] BOOL GetPasteConvertEndings();
  void ReplaceRectangular(_In_ Position length, _In_z_ const char* text);
  void SelectionDuplicate();
  void SetCaretLineBackAlpha(_In_ Alpha alpha);
  [[nodiscard]] Alpha GetCaretLineBackAlpha();
  void SetCaretStyle(_In_ CaretStyle caretStyle);
  [[nodiscard]] CaretStyle GetCaretStyle();
  void SetIndicatorCurrent(_In_ int indicator);
  [[nodiscard]] int GetIndicatorCurrent();
  void SetIndicatorValue(_In_ int value);
  [[nodiscard]] int GetIndicatorValue();
  void IndicatorFillRange(_In_ Position start, _In_ Position lengthFill);
  void IndicatorClearRange(_In_ Position start, _In_ Position lengthClear);
  [[nodiscard]] int IndicatorAllOnFor(_In_ Position pos);
  [[nodiscard]] int IndicatorValueAt(_In_ int indicator, _In_ Position pos);
  [[nodiscard]] Position IndicatorStart(_In_ int indicator, _In_ Position pos);
  [[nodiscard]] Position IndicatorEnd(_In_ int indicator, _In_ Position pos);
  void SetPositionCache(_In_ int size);
  [[nodiscard]] int GetPositionCache();
  void SetLayoutThreads(_In_ int threads);
  [[nodiscard]] int GetLayoutThreads();
  void CopyAllowLine();
  void CutAllowLine();
  void SetCopySeparator(_In_z_ const char* separator);
  int GetCopySeparator(_Inout_opt_z_ char* separator);
  [[nodiscard]] const char* GetCharacterPointer();
  [[nodiscard]] void* GetRangePointer(_In_ Position start, _In_ Position lengthRange);
  [[nodiscard]] Position GetGapPosition();
  void IndicSetAlpha(_In_ int indicator, _In_ Alpha alpha);
  [[nodiscard]] Alpha IndicGetAlpha(_In_ int indicator);
  void IndicSetOutlineAlpha(_In_ int indicator, _In_ Alpha alpha);
  [[nodiscard]] Alpha IndicGetOutlineAlpha(_In_ int indicator);
  void SetExtraAscent(_In_ int extraAscent);
  [[nodiscard]] int GetExtraAscent();
  void SetExtraDescent(_In_ int extraDescent);
  [[nodiscard]] int GetExtraDescent();
  [[nodiscard]] int MarkerSymbolDefined(_In_ int markerNumber);
  void MarginSetText(_In_ Line line, _In_z_ const char* text);
  int MarginGetText(_In_ Line line, _Inout_opt_z_ char* text);
  void MarginSetStyle(_In_ Line line, _In_ int style);
  [[nodiscard]] int MarginGetStyle(_In_ Line line);
  void MarginSetStyles(_In_ Line line, _In_z_ const char* styles);
  int MarginGetStyles(_In_ Line line, _Inout_opt_z_ char* styles);
  void MarginTextClearAll();
  void MarginSetStyleOffset(_In_ int style);
  [[nodiscard]] int MarginGetStyleOffset();
  void SetMarginOptions(_In_ MarginOption marginOptions);
  [[nodiscard]] MarginOption GetMarginOptions();
  void AnnotationSetText(_In_ Line line, _In_z_ const char* text);
  int AnnotationGetText(_In_ Line line, _Inout_opt_z_ char* text);
  void AnnotationSetStyle(_In_ Line line, _In_ int style);
  [[nodiscard]] int AnnotationGetStyle(_In_ Line line);
  void AnnotationSetStyles(_In_ Line line, _In_z_ const char* styles);
  int AnnotationGetStyles(_In_ Line line, _Inout_opt_z_ char* styles);
  [[nodiscard]] int AnnotationGetLines(_In_ Line line);
  void AnnotationClearAll();
  void AnnotationSetVisible(_In_ AnnotationVisible visible);
  [[nodiscard]] AnnotationVisible AnnotationGetVisible();
  void AnnotationSetStyleOffset(_In_ int style);
  [[nodiscard]] int AnnotationGetStyleOffset();
  void ReleaseAllExtendedStyles();
  int AllocateExtendedStyles(_In_ int numberStyles);
  void AddUndoAction(_In_ int token, _In_ UndoFlags flags);
  [[nodiscard]] Position CharPositionFromPoint(_In_ int x, _In_ int y);
  [[nodiscard]] Position CharPositionFromPointClose(_In_ int x, _In_ int y);
  void SetMouseSelectionRectangularSwitch(_In_ BOOL mouseSelectionRectangularSwitch);
  [[nodiscard]] BOOL GetMouseSelectionRectangularSwitch();
  void SetMultipleSelection(_In_ BOOL multipleSelection);
  [[nodiscard]] BOOL GetMultipleSelection();
  void SetAdditionalSelectionTyping(_In_ BOOL additionalSelectionTyping);
  [[nodiscard]] BOOL GetAdditionalSelectionTyping();
  void SetAdditionalCaretsBlink(_In_ BOOL additionalCaretsBlink);
  [[nodiscard]] BOOL GetAdditionalCaretsBlink();
  void SetAdditionalCaretsVisible(_In_ BOOL additionalCaretsVisible);
  [[nodiscard]] BOOL GetAdditionalCaretsVisible();
  [[nodiscard]] int GetSelections();
  [[nodiscard]] BOOL GetSelectionEmpty();
  void ClearSelections();
  void SetSelection(_In_ Position caret, _In_ Position anchor);
  void AddSelection(_In_ Position caret, _In_ Position anchor);
  [[nodiscard]] int SelectionFromPoint(_In_ int x, _In_ int y);
  void DropSelectionN(_In_ int selection);
  void SetMainSelection(_In_ int selection);
  [[nodiscard]] int GetMainSelection();
  void SetSelectionNCaret(_In_ int selection, _In_ Position caret);
  [[nodiscard]] Position GetSelectionNCaret(_In_ int selection);
  void SetSelectionNAnchor(_In_ int selection, _In_ Position anchor);
  [[nodiscard]] Position GetSelectionNAnchor(_In_ int selection);
  void SetSelectionNCaretVirtualSpace(_In_ int selection, _In_ Position space);
  [[nodiscard]] Position GetSelectionNCaretVirtualSpace(_In_ int selection);
  void SetSelectionNAnchorVirtualSpace(_In_ int selection, _In_ Position space);
  [[nodiscard]] Position GetSelectionNAnchorVirtualSpace(_In_ int selection);
  void SetSelectionNStart(_In_ int selection, _In_ Position anchor);
  [[nodiscard]] Position GetSelectionNStart(_In_ int selection);
  [[nodiscard]] Position GetSelectionNStartVirtualSpace(_In_ int selection);
  void SetSelectionNEnd(_In_ int selection, _In_ Position caret);
  [[nodiscard]] Position GetSelectionNEndVirtualSpace(_In_ int selection);
  [[nodiscard]] Position GetSelectionNEnd(_In_ int selection);
  void SetRectangularSelectionCaret(_In_ Position caret);
  [[nodiscard]] Position GetRectangularSelectionCaret();
  void SetRectangularSelectionAnchor(_In_ Position anchor);
  [[nodiscard]] Position GetRectangularSelectionAnchor();
  void SetRectangularSelectionCaretVirtualSpace(_In_ Position space);
  [[nodiscard]] Position GetRectangularSelectionCaretVirtualSpace();
  void SetRectangularSelectionAnchorVirtualSpace(_In_ Position space);
  [[nodiscard]] Position GetRectangularSelectionAnchorVirtualSpace();
  void SetVirtualSpaceOptions(_In_ VirtualSpace virtualSpaceOptions);
  [[nodiscard]] VirtualSpace GetVirtualSpaceOptions();
  void SetRectangularSelectionModifier(_In_ int modifier);
  [[nodiscard]] int GetRectangularSelectionModifier();
  void SetAdditionalSelFore(_In_ COLORREF fore);
  void SetAdditionalSelBack(_In_ COLORREF back);
  void SetAdditionalSelAlpha(_In_ Alpha alpha);
  [[nodiscard]] Alpha GetAdditionalSelAlpha();
  void SetAdditionalCaretFore(_In_ COLORREF fore);
  [[nodiscard]] COLORREF GetAdditionalCaretFore();
  void RotateSelection();
  void SwapMainAnchorCaret();
  void MultipleSelectAddNext();
  void MultipleSelectAddEach();
  int ChangeLexerState(_In_ Position start, _In_ Position end);
  [[nodiscard]] Line ContractedFoldNext(_In_ Line lineStart);
  void VerticalCentreCaret();
  void MoveSelectedLinesUp();
  void MoveSelectedLinesDown();
  void SetIdentifier(_In_ int identifier);
  [[nodiscard]] int GetIdentifier();
  void RGBAImageSetWidth(_In_ int width);
  void RGBAImageSetHeight(_In_ int height);
  void RGBAImageSetScale(_In_ int scalePercent);
  void MarkerDefineRGBAImage(_In_ int markerNumber, _In_ const char* pixels);
  void RegisterRGBAImage(_In_ int type, _In_ const char* pixels);
  void ScrollToStart();
  void ScrollToEnd();
  void SetTechnology(_In_ Technology technology);
  [[nodiscard]] Technology GetTechnology();
  [[nodiscard]] void* CreateLoader(_In_ Position bytes, _In_ DocumentOption documentOptions);
  void FindIndicatorShow(_In_ Position start, _In_ Position end);
  void FindIndicatorFlash(_In_ Position start, _In_ Position end);
  void FindIndicatorHide();
  void VCHomeDisplay();
  void VCHomeDisplayExtend();
  [[nodiscard]] BOOL GetCaretLineVisibleAlways();
  void SetCaretLineVisibleAlways(_In_ BOOL alwaysVisible);
  void SetLineEndTypesAllowed(_In_ LineEndType lineEndBitSet);
  [[nodiscard]] LineEndType GetLineEndTypesAllowed();
  [[nodiscard]] LineEndType GetLineEndTypesActive();
  void SetRepresentation(_In_z_ const char* encodedCharacter, _In_z_ const char* representation);
  int GetRepresentation(_In_z_ const char* encodedCharacter, _Inout_z_ char* representation);
  void ClearRepresentation(_In_z_ const char* encodedCharacter);
  void ClearAllRepresentations();
  void SetRepresentationAppearance(_In_z_ const char* encodedCharacter, _In_ RepresentationAppearance appearance);
  [[nodiscard]] RepresentationAppearance GetRepresentationAppearance(_In_z_ const char* encodedCharacter);
  void SetRepresentationColour(_In_z_ const char* encodedCharacter, _In_ int colour);
  [[nodiscard]] int GetRepresentationColour(_In_z_ const char* encodedCharacter);
  void EOLAnnotationSetText(_In_ Line line, _In_z_ const char* text);
  int EOLAnnotationGetText(_In_ Line line, _Inout_opt_z_ char* text);
  void EOLAnnotationSetStyle(_In_ Line line, _In_ int style);
  [[nodiscard]] int EOLAnnotationGetStyle(_In_ Line line);
  void EOLAnnotationClearAll();
  void EOLAnnotationSetVisible(_In_ EOLAnnotationVisible visible);
  [[nodiscard]] EOLAnnotationVisible EOLAnnotationGetVisible();
  void EOLAnnotationSetStyleOffset(_In_ int style);
  [[nodiscard]] int EOLAnnotationGetStyleOffset();
  [[nodiscard]] BOOL SupportsFeature(_In_ Supports feature);
  [[nodiscard]] LineCharacterIndexType GetLineCharacterIndex();
  void AllocateLineCharacterIndex(_In_ LineCharacterIndexType lineCharacterIndex);
  void ReleaseLineCharacterIndex(_In_ LineCharacterIndexType lineCharacterIndex);
  [[nodiscard]] Line LineFromIndexPosition(_In_ Position pos, _In_ LineCharacterIndexType lineCharacterIndex);
  [[nodiscard]] Position IndexPositionFromLine(_In_ Line line, _In_ LineCharacterIndexType lineCharacterIndex);
  void StartRecord();
  void StopRecord();
  [[nodiscard]] int GetLexer();
  void Colourise(_In_ Position start, _In_ Position end);
  void SetSCIProperty(_In_z_ const char* key, _In_z_ const char* value);
  void SetKeyWords(_In_ int keyWordSet, _In_z_ const char* keyWords);
  int GetSCIProperty(_In_z_ const char* key, _Inout_opt_z_ char* value);
  int GetPropertyExpanded(_In_z_ const char* key, _Inout_opt_z_ char* value);
  [[nodiscard]] int GetPropertyInt(_In_z_ const char* key, _In_ int defaultValue);
  int GetLexerLanguage(_Inout_opt_z_ char* language);
  [[nodiscard]] void* PrivateLexerCall(_In_ int operation, _In_opt_ void* pointer);
  int PropertyNames(_Inout_opt_z_ char* names);
  [[nodiscard]] TypeProperty PropertyType(_In_z_ const char* name);
  int DescribeProperty(_In_z_ const char* name, _Inout_opt_z_ char* description);
  int DescribeKeyWordSets(_Inout_opt_z_ char* descriptions);
  [[nodiscard]] LineEndType GetLineEndTypesSupported();
  int AllocateSubStyles(_In_ int styleBase, _In_ int numberStyles);
  [[nodiscard]] int GetSubStylesStart(_In_ int styleBase);
  [[nodiscard]] int GetSubStylesLength(_In_ int styleBase);
  [[nodiscard]] int GetStyleFromSubStyle(_In_ int subStyle);
  [[nodiscard]] int GetPrimaryStyleFromStyle(_In_ int style);
  void FreeSubStyles();
  void SetIdentifiers(_In_ int style, _In_z_ const char* identifiers);
  [[nodiscard]] int DistanceToSecondaryStyles();
  int GetSubStyleBases(_Inout_opt_z_ char* styles);
  [[nodiscard]] int GetNamedStyles();
  int NameOfStyle(_In_ int style, _Inout_opt_z_ char* name);
  int TagsOfStyle(_In_ int style, _Inout_opt_z_ char* tags);
  int DescriptionOfStyle(_In_ int style, _Inout_opt_z_ char* description);
  void SetILexer(_In_ void* ilexer);
  [[nodiscard]] Bidirectional GetBidirectional();
  void SetBidirectional(_In_ Bidirectional bidirectional);

protected:
#ifdef _AFX
  DECLARE_DYNAMIC(CScintillaCtrl)
#endif //#ifdef _AFX

//Member variables
  FunctionDirect m_DirectStatusFunction;
  sptr_t m_DirectPointer;
  Status m_LastStatus;
  DWORD m_dwOwnerThreadID;
  bool m_bDoneInitialSetup;
};


}; //namespace Scintilla


#endif //#ifndef __SCINTILLACTRL_H__

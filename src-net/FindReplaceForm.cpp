#include "StdAfx.h"
#include "FindReplaceForm.h"
#include "Document.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace WeifenLuo::WinFormsUI::Docking;

namespace ContextFreeNet {
    System::Void FindReplaceForm::findText_Changed(System::Object^  sender, System::EventArgs^  e)
    {
        bool canFind = findText->Text->Length > 0;
        nextButton->Enabled = canFind;
        prevButton->Enabled = canFind;
        replaceButton->Enabled = canFind;
        replaceAllButton->Enabled = canFind;
        replaceAllSelectionButton->Enabled = canFind;
    }

    System::Void FindReplaceForm::find_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doFind(haystack, true);
        haystack->Focus();
    }

    System::Void ContextFreeNet::FindReplaceForm::prev_Click(System::Object ^ sender, System::EventArgs ^ e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doFind(haystack, false);
        haystack->Focus();
    }

    System::Void FindReplaceForm::replace_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(haystack, false, false);
        haystack->Focus();
    }

    System::Void FindReplaceForm::replaceAll_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(haystack, true, false);
        haystack->Focus();
    }

    System::Void FindReplaceForm::replaceAllSelection_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(haystack, true, true);
        haystack->Focus();
    }

    bool FindReplaceForm::doFind(ScintillaNET::Scintilla^ haystack, bool forward)
    {
        bool found = false;
        if (haystack == nullptr) return false;

        bool up = !forward;
        bool whole = findWhole->Checked;
        bool start = findStarts->Checked;
        bool ic = ignoreCaseCheck->Checked;
        bool wrap = wrapAroundCheck->Checked;
        auto finds = 
            (whole ? ScintillaNET::SearchFlags::WholeWord : ScintillaNET::SearchFlags::None) |
            (start ? ScintillaNET::SearchFlags::WordStart : ScintillaNET::SearchFlags::None) |
            (ic ? ScintillaNET::SearchFlags::None : ScintillaNET::SearchFlags::MatchCase);

        if (up) {
            haystack->TargetStart = haystack->AnchorPosition;
            haystack->TargetEnd = 0;
        } else {
            haystack->TargetStart = haystack->CurrentPosition;
            haystack->TargetEnd = haystack->TextLength;
        }
        haystack->SearchFlags = finds;

        auto needle = haystack->SearchInTarget(findText->Text);
        found = needle >= 0;

        if (!found && wrap) {
            if (up) {
                haystack->TargetStart = haystack->TextLength;
                haystack->TargetEnd = 0;
            } else {
                haystack->TargetStart = 0;
                haystack->TargetEnd = haystack->TextLength;
            }
            needle = haystack->SearchInTarget(findText->Text);
            found = needle >= 0;
        }

        if (found) {
            haystack->SetSelection(haystack->TargetEnd, haystack->TargetStart);
            haystack->ScrollCaret();
        } else {
            notFoundSound->Play();
        }

        notFound->Visible = !found;

        return found;
    }

    void FindReplaceForm::doReplace(ScintillaNET::Scintilla^ rtb, bool all, bool selection)
    {
        ScintillaNET::Scintilla^ haystack = rtb;

        bool whole = findWhole->Checked;
        bool start = findStarts->Checked;
        bool ic = ignoreCaseCheck->Checked;
        bool wrap = wrapAroundCheck->Checked;
        auto finds =
            (whole ? ScintillaNET::SearchFlags::WholeWord : ScintillaNET::SearchFlags::None) |
            (start ? ScintillaNET::SearchFlags::WordStart : ScintillaNET::SearchFlags::None) |
            (ic ? ScintillaNET::SearchFlags::None : ScintillaNET::SearchFlags::MatchCase);

        int startPosition = (all && !selection) ? 0 : haystack->CurrentPosition;
        int endPosition = (all && selection) ? haystack->AnchorPosition : haystack->TextLength;

        if (all && endPosition < startPosition)
            std::swap(startPosition, endPosition);
        if (all && endPosition == startPosition)
            return;

        haystack->SearchFlags = finds;
        haystack->TargetStart = startPosition;
        haystack->TargetEnd = endPosition;

        if (all) {
            bool replaced = false;
            auto delta = replaceText->Text->Length - findText->Text->Length;
            for (;;) {
                auto needle = haystack->SearchInTarget(findText->Text);
                if (needle < 0) break;

                if (!replaced)
                    haystack->BeginUndoAction();
                replaced = true;

                haystack->ReplaceTarget(replaceText->Text);

                if (selection)
                    endPosition += delta;
                else
                    endPosition = haystack->TextLength;
                haystack->TargetStart = haystack->TargetEnd;
                haystack->TargetEnd = endPosition;
            }
            notFound->Visible = !replaced;
            if (replaced)
                haystack->EndUndoAction();
            else
                notFoundSound->Play();
        } else {
            auto needle = haystack->SearchInTarget(findText->Text);
            if (needle < 0 && wrap) {
                haystack->TargetStart = 0;
                haystack->TargetEnd = haystack->TextLength;
                needle = haystack->SearchInTarget(findText->Text);
            }
            notFound->Visible = needle < 0;
            if (needle >= 0) {
                haystack->ReplaceTarget(replaceText->Text);
                haystack->SetSelection(haystack->TargetEnd, haystack->TargetStart);
                haystack->ScrollCaret();
            } else {
                notFoundSound->Play();
            }
        }
    }

    ScintillaNET::Scintilla^ FindReplaceForm::getRTB()
    {
        Document^ cfdg = dynamic_cast<Document^>(DockPanel->ActiveDocument);
        return (cfdg != nullptr) ? cfdg->cfdgText : nullptr;
    }
}
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
        findButton->Enabled = canFind;
        replaceButton->Enabled = false;
        replaceAllButton->Enabled = canFind;
        replaceFindButton->Enabled = false;
    }

    System::Void FindReplaceForm::find_Click(System::Object^  sender, System::EventArgs^  e)
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
        ScintillaNET::Scintilla^ haystack = doReplace(nullptr);
        if (haystack != nullptr) haystack->Focus();
    }

    System::Void FindReplaceForm::replaceAll_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        haystack->SelectionStart = 0;
        haystack->SelectionEnd = 0;

        if (!doFind(haystack, true)) {
            notFound->Visible = true;
            System::Media::SystemSounds::Beep->Play();
            haystack->ClearSelections();
            haystack->Focus();
            return;
        }

        do {
            doReplace(haystack);
        } while (doFind(haystack, true));
        haystack->Focus();
    }

    System::Void FindReplaceForm::replaceFind_Click(System::Object^  sender, System::EventArgs^  e)
    {
        ScintillaNET::Scintilla^ haystack = doReplace(nullptr);
        if (haystack != nullptr) {
            doFind(haystack, false);
            haystack->Focus();
        }
    }

    bool FindReplaceForm::doFind(ScintillaNET::Scintilla^ haystack, bool allMode)
    {
        bool found = false;
        if (haystack == nullptr) return false;

        bool up = !allMode && upwardCheck->Checked;
        bool whole = wholeCheck->Checked;
        bool ic = ignoreCaseCheck->Checked;
        bool wrap = !allMode && wrapAroundCheck->Checked;
        auto finds = 
            (whole ? ScintillaNET::SearchFlags::WholeWord : ScintillaNET::SearchFlags::None) |
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
            haystack->ClearSelections();
        }

        replaceButton->Enabled = found;
        replaceFindButton->Enabled = found;
        notFound->Visible = !found && !allMode;
        if (!found && !allMode) System::Media::SystemSounds::Beep->Play();

        return found;
    }

    ScintillaNET::Scintilla^ FindReplaceForm::doReplace(ScintillaNET::Scintilla^ rtb)
    {
        ScintillaNET::Scintilla^ haystack = rtb;
        if (haystack == nullptr) haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr ||
            String::Compare(haystack->SelectedText, findText->Text, ignoreCaseCheck->Checked) != 0)
        {
            System::Media::SystemSounds::Beep->Play();
            return nullptr;
        }

        haystack->ReplaceSelection(replaceText->Text);

        if (!upwardCheck->Checked)
            haystack->SelectionStart = haystack->SelectionEnd;

        return haystack;
    }

    ScintillaNET::Scintilla^ FindReplaceForm::getRTB()
    {
        Document^ cfdg = dynamic_cast<Document^>(DockPanel->ActiveDocument);
        return (cfdg != nullptr) ? cfdg->cfdgText : nullptr;
    }
}
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
        RichTextBox^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doFind(haystack, false);
        haystack->Focus();
    }

    System::Void FindReplaceForm::replace_Click(System::Object^  sender, System::EventArgs^  e)
    {
        RichTextBox^ haystack = doReplace(nullptr);
        if (haystack != nullptr) haystack->Focus();
    }

    System::Void FindReplaceForm::replaceAll_Click(System::Object^  sender, System::EventArgs^  e)
    {
        RichTextBox^ haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        haystack->SelectionStart = 0;
        haystack->SelectionLength = 0;

        if (!doFind(haystack, true)) {
            notFound->Visible = true;
            System::Media::SystemSounds::Beep->Play();
            haystack->SelectionStart = haystack->Text->Length;
            haystack->SelectionLength = 0;
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
        RichTextBox^ haystack = doReplace(nullptr);
        if (haystack != nullptr) {
            doFind(haystack, false);
            haystack->Focus();
        }
    }

    bool FindReplaceForm::doFind(RichTextBox^ haystack, bool allMode)
    {
        bool found = false;
        if (haystack == nullptr) return false;

        bool up = !allMode && upwardCheck->Checked;
        bool whole = wholeCheck->Checked;
        bool ic = ignoreCaseCheck->Checked;
        bool wrap = !allMode && wrapAroundCheck->Checked;
        RichTextBoxFinds finds = 
            (up ? RichTextBoxFinds::Reverse : RichTextBoxFinds::None) |
            (whole ? RichTextBoxFinds::WholeWord : RichTextBoxFinds::None) |
            (ic ? RichTextBoxFinds::None : RichTextBoxFinds::MatchCase);
        int at = haystack->SelectionStart;
        if (!up) at += haystack->SelectionLength;

        int needle = up ? haystack->Find(findText->Text, 0, at, finds) : 
            haystack->Find(findText->Text, at, -1, finds);

        found = needle >= 0;
        if (!found && wrap) {
            needle = up ? haystack->Find(findText->Text, at, -1, finds) : 
                needle = haystack->Find(findText->Text, 0, at, finds);
            found = needle >= 0;
        }

        replaceButton->Enabled = found;
        replaceFindButton->Enabled = found;
        notFound->Visible = !found && !allMode;
        if (!found && !allMode) System::Media::SystemSounds::Beep->Play();

        return found;
    }

    System::Windows::Forms::RichTextBox^ FindReplaceForm::doReplace(System::Windows::Forms::RichTextBox^ rtb)
    {
        RichTextBox^ haystack = rtb;
        if (haystack == nullptr) haystack = getRTB();
        if (findText->Text->Length == 0 || haystack == nullptr ||
            String::Compare(haystack->SelectedText, findText->Text, ignoreCaseCheck->Checked) != 0)
        {
            System::Media::SystemSounds::Beep->Play();
            return nullptr;
        }

        haystack->SelectedText = replaceText->Text;

        if (!upwardCheck->Checked)
            haystack->SelectionStart += haystack->SelectionLength;
        haystack->SelectionLength = 0;

        return haystack;
    }

    System::Windows::Forms::RichTextBox^ FindReplaceForm::getRTB()
    {
        Document^ cfdg = dynamic_cast<Document^>(DockPanel->ActiveDocument);
        return (cfdg != nullptr) ? cfdg->cfdgText : nullptr;
    }
}
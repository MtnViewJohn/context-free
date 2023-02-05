// FindReplaceForm.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "pch.h"
#include "FindReplaceForm.h"
#include <utility>

using namespace System;
using namespace System::Windows::Forms;

namespace CppWrapper {
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
        if (findText->Text->Length == 0 || currentScintilla == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doFind(true);
        currentScintilla->Focus();
    }

    System::Void FindReplaceForm::prev_Click(System::Object ^ sender, System::EventArgs ^ e)
    {
        if (findText->Text->Length == 0 || currentScintilla == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doFind(false);
        currentScintilla->Focus();
    }

    System::Void FindReplaceForm::replace_Click(System::Object^  sender, System::EventArgs^  e)
    {
        if (findText->Text->Length == 0 || currentScintilla == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(ReplaceType::Once);
        currentScintilla->Focus();
    }

    System::Void FindReplaceForm::replaceAll_Click(System::Object^  sender, System::EventArgs^  e)
    {
        if (findText->Text->Length == 0 || currentScintilla == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(ReplaceType::All);
        currentScintilla->Focus();
    }

    System::Void FindReplaceForm::replaceAllSelection_Click(System::Object^  sender, System::EventArgs^  e)
    {
        if (findText->Text->Length == 0 || currentScintilla == nullptr) {
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        doReplace(ReplaceType::Selection);
        currentScintilla->Focus();
    }

    bool FindReplaceForm::doFind(bool forward)
    {
        bool found = false;
        foundStart = foundEnd = 0;
        if (currentScintilla == nullptr) return false;

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
            currentScintilla->TargetStart = currentScintilla->AnchorPosition;
            currentScintilla->TargetEnd = 0;
        } else {
            currentScintilla->TargetStart = currentScintilla->CurrentPosition;
            currentScintilla->TargetEnd = currentScintilla->TextLength;
        }
        currentScintilla->SearchFlags = finds;

        auto needle = currentScintilla->SearchInTarget(findText->Text);
        found = needle >= 0;

        if (!found && wrap) {
            if (up) {
                currentScintilla->TargetStart = currentScintilla->TextLength;
                currentScintilla->TargetEnd = 0;
            } else {
                currentScintilla->TargetStart = 0;
                currentScintilla->TargetEnd = currentScintilla->TextLength;
            }
            needle = currentScintilla->SearchInTarget(findText->Text);
            found = needle >= 0;
        }

        if (found) {
            currentScintilla->SetSelection(currentScintilla->TargetEnd, currentScintilla->TargetStart);
            currentScintilla->ScrollCaret();
            foundStart = currentScintilla->TargetStart;
            foundEnd = currentScintilla->TargetEnd;
        } else {
            notFoundSound->Play();
        }

        notFound->Visible = !found;

        return found;
    }

    void FindReplaceForm::doReplace(ReplaceType rt)
    {
        if (currentScintilla == nullptr) return;

        bool whole = findWhole->Checked;
        bool start = findStarts->Checked;
        bool ic = ignoreCaseCheck->Checked;
        bool wrap = wrapAroundCheck->Checked;
        auto finds =
            (whole ? ScintillaNET::SearchFlags::WholeWord : ScintillaNET::SearchFlags::None) |
            (start ? ScintillaNET::SearchFlags::WordStart : ScintillaNET::SearchFlags::None) |
            (ic ? ScintillaNET::SearchFlags::None : ScintillaNET::SearchFlags::MatchCase);

        int startPosition = 0;
        int endPosition = currentScintilla->TextLength;
        switch (rt) {
        case ReplaceType::Once:
            startPosition = currentScintilla->CurrentPosition;
            if (startPosition == foundEnd)
                startPosition = foundStart;
            break;
        case ReplaceType::All:
            break;
        case ReplaceType::Selection:
            endPosition = currentScintilla->AnchorPosition;
            if (endPosition < startPosition)
                std::swap(startPosition, endPosition);
            break;
        }

        if (startPosition == endPosition)
            return;

        currentScintilla->SearchFlags = finds;
        currentScintilla->TargetStart = startPosition;
        currentScintilla->TargetEnd = endPosition;

        if (rt != ReplaceType::Once) {
            bool replaced = false;
            auto delta = replaceText->Text->Length - findText->Text->Length;
            for (;;) {
                auto needle = currentScintilla->SearchInTarget(findText->Text);
                if (needle < 0) break;

                if (!replaced)
                    currentScintilla->BeginUndoAction();
                replaced = true;

                currentScintilla->ReplaceTarget(replaceText->Text);

                if (rt == ReplaceType::Selection)
                    endPosition += delta;
                else
                    endPosition = currentScintilla->TextLength;
                currentScintilla->TargetStart = currentScintilla->TargetEnd;
                currentScintilla->TargetEnd = endPosition;
            }
            notFound->Visible = !replaced;
            if (replaced)
                currentScintilla->EndUndoAction();
            else
                notFoundSound->Play();
        } else {
            auto needle = currentScintilla->SearchInTarget(findText->Text);
            if (needle < 0 && wrap) {
                currentScintilla->TargetStart = 0;
                currentScintilla->TargetEnd = currentScintilla->TextLength;
                needle = currentScintilla->SearchInTarget(findText->Text);
            }
            notFound->Visible = needle < 0;
            if (needle >= 0) {
                currentScintilla->ReplaceTarget(replaceText->Text);
                currentScintilla->SetSelection(currentScintilla->TargetEnd, currentScintilla->TargetStart);
                currentScintilla->ScrollCaret();
            } else {
                notFoundSound->Play();
            }
        }
        foundStart = foundEnd = 0;
    }
}
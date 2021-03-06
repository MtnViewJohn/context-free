﻿// Document.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
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

#pragma once

#include "Form1.h"
#include "RenderSizeDialog.h"
#include <memory>
#include "cfdg.h"

class WinCanvas;
class tiledCanvas;
class WinSystem;
class SVGCanvas;
class ffCanvas;
class TempFile;

namespace agg {
    struct trans_affine;
}

namespace ContextFreeNet {

    /// <summary>
    /// Summary for Document
    ///
    /// WARNING: If you change the name of this class, you will need to change the
    ///          'Resource File Name' property for the managed resource compiler tool
    ///          associated with all .resx files this class depends on.  Otherwise,
    ///          the designers will not be able to interact properly with localized
    ///          resources associated with this form.
    /// </summary>
    public ref class Document : public WeifenLuo::WinFormsUI::Docking::DockContent
    {
    public:
        Document(void) :
              reloadWhenReady(false),
              idleAction(Form1::IdleAction::Nothing),
              mSystem(0),
              mRenderButtonIndex(0),
              mReuseVariation(true),
              mEngine(new cfdg_ptr()),
              mRenderer(0),
              mCanvas(0),
              mTempCanvas(0),
              mSVGCanvas(0),
              mAnimationCanvas(0),
              mPostAction(PostRenderAction::DoNothing)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            InitializeStuff();
        }
        bool isNamed;
        bool reloadWhenReady;
        Form1::IdleAction idleAction;
        int  currentVariation;
        int maxVariation, minVariation;
        RenderParameters* renderParams;

        enum class PostRenderAction { DoNothing, Render, RenderSize, RenderRepeat, 
            Animate, AnimateFrame, SaveOutput, Close, Exit };
        enum class RenderButtonAction { Render, RenderSized, Animate, AnimateFrame };
        property PostRenderAction postAction {
            void set(PostRenderAction a) {
                if (a == PostRenderAction::DoNothing || a == PostRenderAction::Exit) {
                    mPostAction = a;
                } else if (mPostAction != PostRenderAction::Close && 
                           mPostAction != PostRenderAction::Exit) {
                    mPostAction = a;
                }
                if (!renderThread->IsBusy && mPostAction != PostRenderAction::DoNothing) {
                    RenderCompleted(nullptr, nullptr);
                }
            }
            PostRenderAction get() { return mPostAction; }
        }
        bool canceledByUser;

    private:
        PostRenderAction mPostAction;
        RenderButtonAction mRenderButtonAction;
        bool nonAlphaInVariation;
        WinSystem* mSystem;
        System::ComponentModel::BackgroundWorker^ renderThread;
        System::Windows::Forms::TextBox^ variationEdit;
        System::Windows::Forms::ToolStripSeparator^  rightSeparator;
        System::Windows::Forms::TextBox^ frameEdit;
        System::Windows::Forms::TextBox^ widthEdit;
        System::Windows::Forms::TextBox^ heightEdit;


    private: System::Windows::Forms::ToolStripLabel^  toolStripStatus;
    private: System::Windows::Forms::PictureBox^  renderBox;
    private: System::Windows::Forms::ToolStripMenuItem^  menuEUndo;
    private: System::Windows::Forms::ToolStripMenuItem^  menuERedo;


    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
    private: System::Windows::Forms::ToolStripMenuItem^  menuEDelete;
    private: System::Windows::Forms::ToolStripButton^  toolStripSaveButton;
    public: System::Windows::Forms::SplitContainer^  editorSplitter;
    private:


    private: 
    private: System::Windows::Forms::WebBrowser^  cfdgMessage;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
    private: System::Windows::Forms::ToolStripMenuItem^  menuEFindPrev;

    private: System::Windows::Forms::ToolStripMenuItem^  insertCharacterToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
    private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
    private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
    private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
    private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
    private: System::Windows::Forms::ToolStripMenuItem^  infToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  insertSymmetryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFCyclicToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFDihedralToolStripMenuItem;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
    private: System::Windows::Forms::ToolStripMenuItem^  insertVariableToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  insertFlagToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp11gToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp11mToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cfp1m1ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp2ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp2mgToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp2mmToolStripMenuItem;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp2ToolStripMenuItem1;
    private: System::Windows::Forms::ToolStripMenuItem^  cFpmToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFpgToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFcmToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFpmmToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFpmgToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFpggToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFcmmToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cfp4ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp4mToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp4gToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  friezeToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp3m1ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp31mToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp6ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  cFp6mToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFAllowOverlapToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFAlphaToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFBackgroundToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFBorderDynamicToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFBorderFixedToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFColorToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFColorDepthToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFFrameToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFFrametimeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFImpureToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFMaxShapesToolStripMenuItem;

private: System::Windows::Forms::ToolStripMenuItem^  cFMinimumSizeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFSizeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFSymmetryToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFTileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFTimeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFMiterJoinToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFRoundJoinToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFBevelJoinToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFButtCapToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFRoundCapToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFSquareCapToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFArcCWToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFArcLargeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFContinuousToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFAlignToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFEvenOddToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  cFIsoWidthToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  menuRAnimate;
private: System::Windows::Forms::ToolStripMenuItem^  menuRAnimateFrame;
private: System::Windows::Forms::ToolStripMenuItem^  piToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  renderToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  sizedToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  animateToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  frameToolStripMenuItem;
private: System::Windows::Forms::ToolStripLabel^  toolStripFrameLabel;
private: System::Windows::Forms::ToolStripTextBox^  toolStripFrameTextBox;
private: System::Windows::Forms::ToolStripSeparator^  toolStripFrameSeparator;
private: System::Windows::Forms::ToolStripButton^  toolStripPrevFrame;
private: System::Windows::Forms::ToolStripButton^  toolStripNextFrame;
private: System::Windows::Forms::ToolStripLabel^  toolStripSizeLabel1;
private: System::Windows::Forms::ToolStripTextBox^  toolStripWidthBox;
private: System::Windows::Forms::ToolStripLabel^  toolStripSizeLabel2;
private: System::Windows::Forms::ToolStripTextBox^  toolStripHeightBox;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSizeSeparator;
private: System::Windows::Forms::ToolStripMenuItem^  removeIndentToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  addIndentToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  menuEFind;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator8;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem7;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem8;



private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem11;








private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem19;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem20;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem21;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem22;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem23;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem24;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem25;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem26;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem27;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem28;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem29;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem30;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem31;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem9;


    public:









    public:
        System::String^ Name;
        void setMessageText(System::String^ txt);
        void setStatusText(System::String^ txt, bool addToMessages);
    public: void reload(bool justClear);

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Document()
        {
            if (components)
            {
                delete components;
            }
            DestroyStuff();
            delete mEngine;
        }
    private: System::Windows::Forms::ToolStrip^  toolStrip1;
public: System::Windows::Forms::SplitContainer^  documentSplitter;
private:
    int    lastCaretPosition;

    public:  ScintillaNET::Scintilla^               cfdgText;

    private: System::Windows::Forms::ToolStripSplitButton^ toolStripRenderButton;

    private: System::Windows::Forms::ToolStripTextBox^  toolStripVariation;
    private: System::Windows::Forms::ToolStripButton^  toolStripPrevVar;
    private: System::Windows::Forms::ToolStripButton^  toolStripNextVar;

    private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar;


    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
private: System::Windows::Forms::ToolStripSeparator^  toolStripVariationSeparator;

    private: System::Windows::Forms::MenuStrip^  menuStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^  menuFile;

    private: System::Windows::Forms::ToolStripMenuItem^  menuEdit;


    private: System::Windows::Forms::ToolStripMenuItem^  menuECut;
    private: System::Windows::Forms::ToolStripMenuItem^  menuECopy;
    private: System::Windows::Forms::ToolStripMenuItem^  menuEPaste;



    private: System::Windows::Forms::ToolStripMenuItem^  menuFSave;
    private: System::Windows::Forms::ToolStripMenuItem^  menuFClose;


    private: System::Windows::Forms::ToolStripMenuItem^  menuFSaveAs;
    private: System::Windows::Forms::ToolStripMenuItem^  menuRender;


    public: System::Windows::Forms::ToolStripMenuItem^  menuRRender;
    private: System::Windows::Forms::ToolStripMenuItem^  menuRRenderSize;
    private: System::Windows::Forms::ToolStripMenuItem^  menuRRenderAgain;
    private: System::Windows::Forms::ToolStripMenuItem^  menuRStop;




    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
private: System::Windows::Forms::ToolStripMenuItem^  menuROutput;


    private: System::Windows::Forms::ToolStripMenuItem^  menuRUpload;






    private: System::Windows::Forms::ToolStripMenuItem^  menuFRevert;










    protected: 

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Document::typeid));
            this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
            this->toolStripRenderButton = (gcnew System::Windows::Forms::ToolStripSplitButton());
            this->renderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->sizedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->animateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->frameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSaveButton = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
            this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolStripVariation = (gcnew System::Windows::Forms::ToolStripTextBox());
            this->toolStripPrevVar = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripNextVar = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripVariationSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolStripFrameLabel = (gcnew System::Windows::Forms::ToolStripLabel());
            this->toolStripFrameTextBox = (gcnew System::Windows::Forms::ToolStripTextBox());
            this->toolStripPrevFrame = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripNextFrame = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripFrameSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolStripSizeLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
            this->toolStripWidthBox = (gcnew System::Windows::Forms::ToolStripTextBox());
            this->toolStripSizeLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
            this->toolStripHeightBox = (gcnew System::Windows::Forms::ToolStripTextBox());
            this->toolStripSizeSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->toolStripStatus = (gcnew System::Windows::Forms::ToolStripLabel());
            this->documentSplitter = (gcnew System::Windows::Forms::SplitContainer());
            this->editorSplitter = (gcnew System::Windows::Forms::SplitContainer());
            this->cfdgText = (gcnew ScintillaNET::Scintilla());
            this->cfdgMessage = (gcnew System::Windows::Forms::WebBrowser());
            this->renderBox = (gcnew System::Windows::Forms::PictureBox());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->menuFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFSaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFClose = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFRevert = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuEdit = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuEUndo = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuERedo = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->menuECut = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuECopy = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuEPaste = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuEDelete = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->insertCharacterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->infToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->piToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->insertSymmetryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFCyclicToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFDihedralToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->cFp11gToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp11mToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cfp1m1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp2mgToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp2mmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->cFp2ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFpmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFpgToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFcmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFpmmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFpmgToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFpggToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFcmmToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cfp4ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp4mToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp4gToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->friezeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp3m1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp31mToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp6ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFp6mToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem19 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem20 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem21 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem22 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem23 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem24 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem25 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem26 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem27 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem28 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem29 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem30 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem31 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->insertVariableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFAllowOverlapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFAlphaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFBackgroundToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFBorderDynamicToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFBorderFixedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFColorDepthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFFrameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFFrametimeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFImpureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFMaxShapesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFMinimumSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFSizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFSymmetryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFTileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFTimeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->insertFlagToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFMiterJoinToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFRoundJoinToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFBevelJoinToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFButtCapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFRoundCapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFSquareCapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFArcCWToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFArcLargeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFContinuousToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFAlignToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFEvenOddToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->cFIsoWidthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->menuEFind = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuEFindPrev = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->removeIndentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->addIndentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRender = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRRender = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRRenderSize = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRRenderAgain = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRAnimate = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRAnimateFrame = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRStop = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->menuROutput = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRUpload = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStrip1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentSplitter))->BeginInit();
            this->documentSplitter->Panel1->SuspendLayout();
            this->documentSplitter->Panel2->SuspendLayout();
            this->documentSplitter->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editorSplitter))->BeginInit();
            this->editorSplitter->Panel1->SuspendLayout();
            this->editorSplitter->Panel2->SuspendLayout();
            this->editorSplitter->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->renderBox))->BeginInit();
            this->menuStrip1->SuspendLayout();
            this->SuspendLayout();
            // 
            // toolStrip1
            // 
            this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
            this->toolStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
            this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(19) {
                this->toolStripRenderButton,
                    this->toolStripSaveButton, this->toolStripProgressBar, this->toolStripSeparator1, this->toolStripVariation, this->toolStripPrevVar,
                    this->toolStripNextVar, this->toolStripVariationSeparator, this->toolStripFrameLabel, this->toolStripFrameTextBox, this->toolStripPrevFrame,
                    this->toolStripNextFrame, this->toolStripFrameSeparator, this->toolStripSizeLabel1, this->toolStripWidthBox, this->toolStripSizeLabel2,
                    this->toolStripHeightBox, this->toolStripSizeSeparator, this->toolStripStatus
            });
            this->toolStrip1->Location = System::Drawing::Point(0, 24);
            this->toolStrip1->Name = L"toolStrip1";
            this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
            this->toolStrip1->Size = System::Drawing::Size(1162, 47);
            this->toolStrip1->TabIndex = 0;
            this->toolStrip1->Text = L"CFDGstrip";
            // 
            // toolStripRenderButton
            // 
            this->toolStripRenderButton->AutoSize = false;
            this->toolStripRenderButton->AutoToolTip = false;
            this->toolStripRenderButton->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->renderToolStripMenuItem,
                    this->sizedToolStripMenuItem, this->animateToolStripMenuItem, this->frameToolStripMenuItem
            });
            this->toolStripRenderButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripRenderButton.Image")));
            this->toolStripRenderButton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->toolStripRenderButton->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->toolStripRenderButton->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripRenderButton->Name = L"toolStripRenderButton";
            this->toolStripRenderButton->Size = System::Drawing::Size(85, 22);
            this->toolStripRenderButton->Text = L"Render";
            this->toolStripRenderButton->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->toolStripRenderButton->ButtonClick += gcnew System::EventHandler(this, &Document::RenderButton_Click);
            // 
            // renderToolStripMenuItem
            // 
            this->renderToolStripMenuItem->Name = L"renderToolStripMenuItem";
            this->renderToolStripMenuItem->Size = System::Drawing::Size(164, 22);
            this->renderToolStripMenuItem->Tag = L"0";
            this->renderToolStripMenuItem->Text = L"Render";
            this->renderToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::actionToolStripMenuItem_Click);
            // 
            // sizedToolStripMenuItem
            // 
            this->sizedToolStripMenuItem->Name = L"sizedToolStripMenuItem";
            this->sizedToolStripMenuItem->Size = System::Drawing::Size(164, 22);
            this->sizedToolStripMenuItem->Tag = L"1";
            this->sizedToolStripMenuItem->Text = L"Render to Size";
            this->sizedToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::actionToolStripMenuItem_Click);
            // 
            // animateToolStripMenuItem
            // 
            this->animateToolStripMenuItem->Name = L"animateToolStripMenuItem";
            this->animateToolStripMenuItem->Size = System::Drawing::Size(164, 22);
            this->animateToolStripMenuItem->Tag = L"2";
            this->animateToolStripMenuItem->Text = L"Animate";
            this->animateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::actionToolStripMenuItem_Click);
            // 
            // frameToolStripMenuItem
            // 
            this->frameToolStripMenuItem->Name = L"frameToolStripMenuItem";
            this->frameToolStripMenuItem->Size = System::Drawing::Size(164, 22);
            this->frameToolStripMenuItem->Tag = L"3";
            this->frameToolStripMenuItem->Text = L"Animate a Frame";
            this->frameToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::actionToolStripMenuItem_Click);
            // 
            // toolStripSaveButton
            // 
            this->toolStripSaveButton->AutoToolTip = false;
            this->toolStripSaveButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->toolStripSaveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripSaveButton.Image")));
            this->toolStripSaveButton->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->toolStripSaveButton->Name = L"toolStripSaveButton";
            this->toolStripSaveButton->Size = System::Drawing::Size(76, 44);
            this->toolStripSaveButton->Text = L"Save Output";
            this->toolStripSaveButton->Click += gcnew System::EventHandler(this, &Document::menuRSaveOutput_Click);
            // 
            // toolStripProgressBar
            // 
            this->toolStripProgressBar->AutoSize = false;
            this->toolStripProgressBar->Margin = System::Windows::Forms::Padding(5, 2, 5, 1);
            this->toolStripProgressBar->Name = L"toolStripProgressBar";
            this->toolStripProgressBar->Size = System::Drawing::Size(100, 30);
            // 
            // toolStripSeparator1
            // 
            this->toolStripSeparator1->Name = L"toolStripSeparator1";
            this->toolStripSeparator1->Size = System::Drawing::Size(6, 47);
            // 
            // toolStripVariation
            // 
            this->toolStripVariation->AutoSize = false;
            this->toolStripVariation->MaxLength = 6;
            this->toolStripVariation->Name = L"toolStripVariation";
            this->toolStripVariation->Size = System::Drawing::Size(75, 47);
            // 
            // toolStripPrevVar
            // 
            this->toolStripPrevVar->AutoToolTip = false;
            this->toolStripPrevVar->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolStripPrevVar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripPrevVar.Image")));
            this->toolStripPrevVar->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->toolStripPrevVar->Name = L"toolStripPrevVar";
            this->toolStripPrevVar->Size = System::Drawing::Size(23, 44);
            this->toolStripPrevVar->Text = L"toolStripButton3";
            this->toolStripPrevVar->ToolTipText = L"Previous Variation";
            this->toolStripPrevVar->Click += gcnew System::EventHandler(this, &Document::PrevVar_Click);
            // 
            // toolStripNextVar
            // 
            this->toolStripNextVar->AutoToolTip = false;
            this->toolStripNextVar->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolStripNextVar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripNextVar.Image")));
            this->toolStripNextVar->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->toolStripNextVar->Name = L"toolStripNextVar";
            this->toolStripNextVar->Size = System::Drawing::Size(23, 44);
            this->toolStripNextVar->Text = L"toolStripButton4";
            this->toolStripNextVar->ToolTipText = L"Next Variation";
            this->toolStripNextVar->Click += gcnew System::EventHandler(this, &Document::NextVar_Click);
            // 
            // toolStripVariationSeparator
            // 
            this->toolStripVariationSeparator->Name = L"toolStripVariationSeparator";
            this->toolStripVariationSeparator->Size = System::Drawing::Size(6, 47);
            // 
            // toolStripFrameLabel
            // 
            this->toolStripFrameLabel->Name = L"toolStripFrameLabel";
            this->toolStripFrameLabel->Size = System::Drawing::Size(43, 44);
            this->toolStripFrameLabel->Text = L"Frame:";
            this->toolStripFrameLabel->Visible = false;
            // 
            // toolStripFrameTextBox
            // 
            this->toolStripFrameTextBox->AutoSize = false;
            this->toolStripFrameTextBox->Name = L"toolStripFrameTextBox";
            this->toolStripFrameTextBox->Size = System::Drawing::Size(50, 39);
            this->toolStripFrameTextBox->Text = L"9999";
            this->toolStripFrameTextBox->Visible = false;
            // 
            // toolStripPrevFrame
            // 
            this->toolStripPrevFrame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolStripPrevFrame->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripPrevFrame.Image")));
            this->toolStripPrevFrame->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->toolStripPrevFrame->Name = L"toolStripPrevFrame";
            this->toolStripPrevFrame->Size = System::Drawing::Size(23, 44);
            this->toolStripPrevFrame->Text = L"toolStripButton1";
            this->toolStripPrevFrame->ToolTipText = L"Previous frame";
            this->toolStripPrevFrame->Visible = false;
            this->toolStripPrevFrame->Click += gcnew System::EventHandler(this, &Document::PrevFrame_Click);
            // 
            // toolStripNextFrame
            // 
            this->toolStripNextFrame->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->toolStripNextFrame->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripNextFrame.Image")));
            this->toolStripNextFrame->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->toolStripNextFrame->Name = L"toolStripNextFrame";
            this->toolStripNextFrame->Size = System::Drawing::Size(23, 44);
            this->toolStripNextFrame->Text = L"toolStripButton1";
            this->toolStripNextFrame->ToolTipText = L"Next frame";
            this->toolStripNextFrame->Visible = false;
            this->toolStripNextFrame->Click += gcnew System::EventHandler(this, &Document::NextFrame_Click);
            // 
            // toolStripFrameSeparator
            // 
            this->toolStripFrameSeparator->Name = L"toolStripFrameSeparator";
            this->toolStripFrameSeparator->Size = System::Drawing::Size(6, 47);
            this->toolStripFrameSeparator->Visible = false;
            // 
            // toolStripSizeLabel1
            // 
            this->toolStripSizeLabel1->Name = L"toolStripSizeLabel1";
            this->toolStripSizeLabel1->Size = System::Drawing::Size(30, 44);
            this->toolStripSizeLabel1->Text = L"Size:";
            this->toolStripSizeLabel1->Visible = false;
            // 
            // toolStripWidthBox
            // 
            this->toolStripWidthBox->Name = L"toolStripWidthBox";
            this->toolStripWidthBox->Size = System::Drawing::Size(100, 47);
            this->toolStripWidthBox->Visible = false;
            // 
            // toolStripSizeLabel2
            // 
            this->toolStripSizeLabel2->Name = L"toolStripSizeLabel2";
            this->toolStripSizeLabel2->Size = System::Drawing::Size(15, 44);
            this->toolStripSizeLabel2->Text = L"×";
            this->toolStripSizeLabel2->Visible = false;
            // 
            // toolStripHeightBox
            // 
            this->toolStripHeightBox->Name = L"toolStripHeightBox";
            this->toolStripHeightBox->Size = System::Drawing::Size(100, 47);
            this->toolStripHeightBox->Visible = false;
            // 
            // toolStripSizeSeparator
            // 
            this->toolStripSizeSeparator->Name = L"toolStripSizeSeparator";
            this->toolStripSizeSeparator->Size = System::Drawing::Size(6, 47);
            this->toolStripSizeSeparator->Visible = false;
            // 
            // toolStripStatus
            // 
            this->toolStripStatus->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripStatus->AutoSize = false;
            this->toolStripStatus->AutoToolTip = true;
            this->toolStripStatus->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->toolStripStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->toolStripStatus->Name = L"toolStripStatus";
            this->toolStripStatus->Size = System::Drawing::Size(75, 22);
            this->toolStripStatus->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // documentSplitter
            // 
            this->documentSplitter->Dock = System::Windows::Forms::DockStyle::Fill;
            this->documentSplitter->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
            this->documentSplitter->Location = System::Drawing::Point(0, 71);
            this->documentSplitter->Name = L"documentSplitter";
            // 
            // documentSplitter.Panel1
            // 
            this->documentSplitter->Panel1->Controls->Add(this->editorSplitter);
            // 
            // documentSplitter.Panel2
            // 
            this->documentSplitter->Panel2->BackColor = System::Drawing::SystemColors::Window;
            this->documentSplitter->Panel2->Controls->Add(this->renderBox);
            this->documentSplitter->Size = System::Drawing::Size(1162, 737);
            this->documentSplitter->SplitterDistance = 386;
            this->documentSplitter->TabIndex = 1;
            // 
            // editorSplitter
            // 
            this->editorSplitter->Dock = System::Windows::Forms::DockStyle::Fill;
            this->editorSplitter->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
            this->editorSplitter->Location = System::Drawing::Point(0, 0);
            this->editorSplitter->Name = L"editorSplitter";
            this->editorSplitter->Orientation = System::Windows::Forms::Orientation::Horizontal;
            // 
            // editorSplitter.Panel1
            // 
            this->editorSplitter->Panel1->Controls->Add(this->cfdgText);
            // 
            // editorSplitter.Panel2
            // 
            this->editorSplitter->Panel2->Controls->Add(this->cfdgMessage);
            this->editorSplitter->Size = System::Drawing::Size(386, 737);
            this->editorSplitter->SplitterDistance = 570;
            this->editorSplitter->TabIndex = 1;
            // 
            // cfdgText
            // 
            this->cfdgText->Dock = System::Windows::Forms::DockStyle::Fill;
            this->cfdgText->Location = System::Drawing::Point(0, 0);
            this->cfdgText->Name = L"cfdgText";
            this->cfdgText->Size = System::Drawing::Size(386, 570);
            this->cfdgText->TabIndex = 0;
            // 
            // cfdgMessage
            // 
            this->cfdgMessage->AllowWebBrowserDrop = false;
            this->cfdgMessage->Dock = System::Windows::Forms::DockStyle::Fill;
            this->cfdgMessage->IsWebBrowserContextMenuEnabled = false;
            this->cfdgMessage->Location = System::Drawing::Point(0, 0);
            this->cfdgMessage->MinimumSize = System::Drawing::Size(20, 20);
            this->cfdgMessage->Name = L"cfdgMessage";
            this->cfdgMessage->Size = System::Drawing::Size(386, 163);
            this->cfdgMessage->TabIndex = 0;
            // 
            // renderBox
            // 
            this->renderBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->renderBox->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"renderBox.InitialImage")));
            this->renderBox->Location = System::Drawing::Point(0, 0);
            this->renderBox->Name = L"renderBox";
            this->renderBox->Size = System::Drawing::Size(772, 737);
            this->renderBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
            this->renderBox->TabIndex = 0;
            this->renderBox->TabStop = false;
            this->renderBox->Click += gcnew System::EventHandler(this, &Document::renderBox_Click);
            // 
            // menuStrip1
            // 
            this->menuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->menuFile, this->menuEdit,
                    this->menuRender
            });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(1162, 24);
            this->menuStrip1->TabIndex = 2;
            this->menuStrip1->Text = L"menuStrip1";
            this->menuStrip1->Visible = false;
            this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Document::menuStrip1_ItemClicked);
            // 
            // menuFile
            // 
            this->menuFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                this->menuFSave,
                    this->menuFSaveAs, this->menuFClose, this->menuFRevert
            });
            this->menuFile->MergeAction = System::Windows::Forms::MergeAction::MatchOnly;
            this->menuFile->Name = L"menuFile";
            this->menuFile->Size = System::Drawing::Size(37, 20);
            this->menuFile->Text = L"&File";
            // 
            // menuFSave
            // 
            this->menuFSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuFSave.Image")));
            this->menuFSave->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuFSave->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuFSave->MergeIndex = 2;
            this->menuFSave->Name = L"menuFSave";
            this->menuFSave->ShortcutKeyDisplayString = L"Ctrl-S";
            this->menuFSave->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
            this->menuFSave->Size = System::Drawing::Size(135, 22);
            this->menuFSave->Text = L"&Save";
            this->menuFSave->Click += gcnew System::EventHandler(this, &Document::menuFSave_Click);
            // 
            // menuFSaveAs
            // 
            this->menuFSaveAs->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuFSaveAs.Image")));
            this->menuFSaveAs->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuFSaveAs->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuFSaveAs->MergeIndex = 3;
            this->menuFSaveAs->Name = L"menuFSaveAs";
            this->menuFSaveAs->Size = System::Drawing::Size(135, 22);
            this->menuFSaveAs->Text = L"Save &As";
            this->menuFSaveAs->Click += gcnew System::EventHandler(this, &Document::menuFSaveAs_Click);
            // 
            // menuFClose
            // 
            this->menuFClose->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuFClose->MergeIndex = 4;
            this->menuFClose->Name = L"menuFClose";
            this->menuFClose->Size = System::Drawing::Size(135, 22);
            this->menuFClose->Text = L"&Close";
            this->menuFClose->Click += gcnew System::EventHandler(this, &Document::menuFClose_Click);
            // 
            // menuFRevert
            // 
            this->menuFRevert->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuFRevert->MergeIndex = 5;
            this->menuFRevert->Name = L"menuFRevert";
            this->menuFRevert->Size = System::Drawing::Size(135, 22);
            this->menuFRevert->Text = L"Re&vert";
            this->menuFRevert->Click += gcnew System::EventHandler(this, &Document::menuFRevert_Click);
            // 
            // menuEdit
            // 
            this->menuEdit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(19) {
                this->menuEUndo,
                    this->menuERedo, this->toolStripSeparator2, this->menuECut, this->menuECopy, this->menuEPaste, this->menuEDelete, this->toolStripSeparator6,
                    this->insertCharacterToolStripMenuItem, this->insertSymmetryToolStripMenuItem, this->toolStripMenuItem7, this->insertVariableToolStripMenuItem,
                    this->insertFlagToolStripMenuItem, this->toolStripSeparator5, this->menuEFind, this->menuEFindPrev, this->toolStripSeparator8,
                    this->removeIndentToolStripMenuItem, this->addIndentToolStripMenuItem
            });
            this->menuEdit->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuEdit->MergeIndex = 1;
            this->menuEdit->Name = L"menuEdit";
            this->menuEdit->Size = System::Drawing::Size(39, 20);
            this->menuEdit->Text = L"&Edit";
            // 
            // menuEUndo
            // 
            this->menuEUndo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuEUndo.Image")));
            this->menuEUndo->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuEUndo->Name = L"menuEUndo";
            this->menuEUndo->ShortcutKeyDisplayString = L"Ctrl-Z";
            this->menuEUndo->Size = System::Drawing::Size(220, 22);
            this->menuEUndo->Text = L"&Undo";
            this->menuEUndo->Click += gcnew System::EventHandler(this, &Document::menuEUndo_Click);
            // 
            // menuERedo
            // 
            this->menuERedo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuERedo.Image")));
            this->menuERedo->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuERedo->Name = L"menuERedo";
            this->menuERedo->ShortcutKeyDisplayString = L"Ctrl-Y";
            this->menuERedo->Size = System::Drawing::Size(220, 22);
            this->menuERedo->Text = L"&Redo";
            this->menuERedo->Click += gcnew System::EventHandler(this, &Document::menuERedo_Click);
            // 
            // toolStripSeparator2
            // 
            this->toolStripSeparator2->Name = L"toolStripSeparator2";
            this->toolStripSeparator2->Size = System::Drawing::Size(217, 6);
            // 
            // menuECut
            // 
            this->menuECut->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuECut.Image")));
            this->menuECut->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuECut->Name = L"menuECut";
            this->menuECut->ShortcutKeyDisplayString = L"Ctrl-X";
            this->menuECut->Size = System::Drawing::Size(220, 22);
            this->menuECut->Text = L"Cu&t";
            this->menuECut->Click += gcnew System::EventHandler(this, &Document::menuECut_Click);
            // 
            // menuECopy
            // 
            this->menuECopy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuECopy.Image")));
            this->menuECopy->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuECopy->Name = L"menuECopy";
            this->menuECopy->ShortcutKeyDisplayString = L"Ctrl-C";
            this->menuECopy->Size = System::Drawing::Size(220, 22);
            this->menuECopy->Text = L"&Copy";
            this->menuECopy->Click += gcnew System::EventHandler(this, &Document::menuECopy_Click);
            // 
            // menuEPaste
            // 
            this->menuEPaste->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuEPaste.Image")));
            this->menuEPaste->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuEPaste->Name = L"menuEPaste";
            this->menuEPaste->ShortcutKeyDisplayString = L"Ctrl-V";
            this->menuEPaste->Size = System::Drawing::Size(220, 22);
            this->menuEPaste->Text = L"&Paste";
            this->menuEPaste->Click += gcnew System::EventHandler(this, &Document::menuEPaste_Click);
            // 
            // menuEDelete
            // 
            this->menuEDelete->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuEDelete.Image")));
            this->menuEDelete->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuEDelete->Name = L"menuEDelete";
            this->menuEDelete->ShortcutKeyDisplayString = L"DEL";
            this->menuEDelete->Size = System::Drawing::Size(220, 22);
            this->menuEDelete->Text = L"&Delete";
            this->menuEDelete->Click += gcnew System::EventHandler(this, &Document::menuEDelete_Click);
            // 
            // toolStripSeparator6
            // 
            this->toolStripSeparator6->Name = L"toolStripSeparator6";
            this->toolStripSeparator6->Size = System::Drawing::Size(217, 6);
            // 
            // insertCharacterToolStripMenuItem
            // 
            this->insertCharacterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
                this->toolStripMenuItem2,
                    this->toolStripMenuItem3, this->toolStripMenuItem4, this->toolStripMenuItem5, this->toolStripMenuItem6, this->infToolStripMenuItem,
                    this->piToolStripMenuItem
            });
            this->insertCharacterToolStripMenuItem->Name = L"insertCharacterToolStripMenuItem";
            this->insertCharacterToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->insertCharacterToolStripMenuItem->Text = L"Insert Character";
            // 
            // toolStripMenuItem2
            // 
            this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
            this->toolStripMenuItem2->Size = System::Drawing::Size(84, 22);
            this->toolStripMenuItem2->Tag = L"8804";
            this->toolStripMenuItem2->Text = L"≤";
            this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem3
            // 
            this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
            this->toolStripMenuItem3->Size = System::Drawing::Size(84, 22);
            this->toolStripMenuItem3->Tag = L"8805";
            this->toolStripMenuItem3->Text = L"≥";
            this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem4
            // 
            this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
            this->toolStripMenuItem4->Size = System::Drawing::Size(84, 22);
            this->toolStripMenuItem4->Tag = L"8800";
            this->toolStripMenuItem4->Text = L"≠";
            this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem5
            // 
            this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
            this->toolStripMenuItem5->Size = System::Drawing::Size(84, 22);
            this->toolStripMenuItem5->Tag = L"8230";
            this->toolStripMenuItem5->Text = L"…";
            this->toolStripMenuItem5->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem6
            // 
            this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
            this->toolStripMenuItem6->Size = System::Drawing::Size(84, 22);
            this->toolStripMenuItem6->Tag = L"177";
            this->toolStripMenuItem6->Text = L"±";
            this->toolStripMenuItem6->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // infToolStripMenuItem
            // 
            this->infToolStripMenuItem->Name = L"infToolStripMenuItem";
            this->infToolStripMenuItem->Size = System::Drawing::Size(84, 22);
            this->infToolStripMenuItem->Tag = L"8734";
            this->infToolStripMenuItem->Text = L"∞";
            this->infToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // piToolStripMenuItem
            // 
            this->piToolStripMenuItem->Name = L"piToolStripMenuItem";
            this->piToolStripMenuItem->Size = System::Drawing::Size(84, 22);
            this->piToolStripMenuItem->Text = L"π";
            this->piToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // insertSymmetryToolStripMenuItem
            // 
            this->insertSymmetryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(26) {
                this->cFCyclicToolStripMenuItem,
                    this->cFDihedralToolStripMenuItem, this->toolStripSeparator4, this->cFp11gToolStripMenuItem, this->cFp11mToolStripMenuItem, this->cfp1m1ToolStripMenuItem,
                    this->cFp2ToolStripMenuItem, this->cFp2mgToolStripMenuItem, this->cFp2mmToolStripMenuItem, this->toolStripSeparator7, this->cFp2ToolStripMenuItem1,
                    this->cFpmToolStripMenuItem, this->cFpgToolStripMenuItem, this->cFcmToolStripMenuItem, this->cFpmmToolStripMenuItem, this->cFpmgToolStripMenuItem,
                    this->cFpggToolStripMenuItem, this->cFcmmToolStripMenuItem, this->cfp4ToolStripMenuItem, this->cFp4mToolStripMenuItem, this->cFp4gToolStripMenuItem,
                    this->friezeToolStripMenuItem, this->cFp3m1ToolStripMenuItem, this->cFp31mToolStripMenuItem, this->cFp6ToolStripMenuItem, this->cFp6mToolStripMenuItem
            });
            this->insertSymmetryToolStripMenuItem->Name = L"insertSymmetryToolStripMenuItem";
            this->insertSymmetryToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->insertSymmetryToolStripMenuItem->Text = L"Insert Symmetry";
            // 
            // cFCyclicToolStripMenuItem
            // 
            this->cFCyclicToolStripMenuItem->Name = L"cFCyclicToolStripMenuItem";
            this->cFCyclicToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFCyclicToolStripMenuItem->Text = L"CF::Cyclic";
            this->cFCyclicToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFDihedralToolStripMenuItem
            // 
            this->cFDihedralToolStripMenuItem->Name = L"cFDihedralToolStripMenuItem";
            this->cFDihedralToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFDihedralToolStripMenuItem->Text = L"CF::Dihedral";
            this->cFDihedralToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripSeparator4
            // 
            this->toolStripSeparator4->Name = L"toolStripSeparator4";
            this->toolStripSeparator4->Size = System::Drawing::Size(135, 6);
            // 
            // cFp11gToolStripMenuItem
            // 
            this->cFp11gToolStripMenuItem->Name = L"cFp11gToolStripMenuItem";
            this->cFp11gToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp11gToolStripMenuItem->Text = L"CF::p11g";
            this->cFp11gToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp11mToolStripMenuItem
            // 
            this->cFp11mToolStripMenuItem->Name = L"cFp11mToolStripMenuItem";
            this->cFp11mToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp11mToolStripMenuItem->Text = L"CF::p11m";
            this->cFp11mToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cfp1m1ToolStripMenuItem
            // 
            this->cfp1m1ToolStripMenuItem->Name = L"cfp1m1ToolStripMenuItem";
            this->cfp1m1ToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cfp1m1ToolStripMenuItem->Text = L"CF::p1m1";
            this->cfp1m1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp2ToolStripMenuItem
            // 
            this->cFp2ToolStripMenuItem->Name = L"cFp2ToolStripMenuItem";
            this->cFp2ToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp2ToolStripMenuItem->Text = L"CF::p2";
            this->cFp2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp2mgToolStripMenuItem
            // 
            this->cFp2mgToolStripMenuItem->Name = L"cFp2mgToolStripMenuItem";
            this->cFp2mgToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp2mgToolStripMenuItem->Text = L"CF::p2mg";
            this->cFp2mgToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp2mmToolStripMenuItem
            // 
            this->cFp2mmToolStripMenuItem->Name = L"cFp2mmToolStripMenuItem";
            this->cFp2mmToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp2mmToolStripMenuItem->Text = L"CF::p2mm";
            this->cFp2mmToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripSeparator7
            // 
            this->toolStripSeparator7->Name = L"toolStripSeparator7";
            this->toolStripSeparator7->Size = System::Drawing::Size(135, 6);
            // 
            // cFp2ToolStripMenuItem1
            // 
            this->cFp2ToolStripMenuItem1->Name = L"cFp2ToolStripMenuItem1";
            this->cFp2ToolStripMenuItem1->Size = System::Drawing::Size(138, 22);
            this->cFp2ToolStripMenuItem1->Text = L"CF::p2";
            this->cFp2ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFpmToolStripMenuItem
            // 
            this->cFpmToolStripMenuItem->Name = L"cFpmToolStripMenuItem";
            this->cFpmToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFpmToolStripMenuItem->Text = L"CF::pm";
            this->cFpmToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFpgToolStripMenuItem
            // 
            this->cFpgToolStripMenuItem->Name = L"cFpgToolStripMenuItem";
            this->cFpgToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFpgToolStripMenuItem->Text = L"CF::pg";
            this->cFpgToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFcmToolStripMenuItem
            // 
            this->cFcmToolStripMenuItem->Name = L"cFcmToolStripMenuItem";
            this->cFcmToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFcmToolStripMenuItem->Text = L"CF::cm";
            this->cFcmToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFpmmToolStripMenuItem
            // 
            this->cFpmmToolStripMenuItem->Name = L"cFpmmToolStripMenuItem";
            this->cFpmmToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFpmmToolStripMenuItem->Text = L"CF::pmm";
            this->cFpmmToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFpmgToolStripMenuItem
            // 
            this->cFpmgToolStripMenuItem->Name = L"cFpmgToolStripMenuItem";
            this->cFpmgToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFpmgToolStripMenuItem->Text = L"CF::pmg";
            this->cFpmgToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFpggToolStripMenuItem
            // 
            this->cFpggToolStripMenuItem->Name = L"cFpggToolStripMenuItem";
            this->cFpggToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFpggToolStripMenuItem->Text = L"CF::pgg";
            this->cFpggToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFcmmToolStripMenuItem
            // 
            this->cFcmmToolStripMenuItem->Name = L"cFcmmToolStripMenuItem";
            this->cFcmmToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFcmmToolStripMenuItem->Text = L"CF::cmm";
            this->cFcmmToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cfp4ToolStripMenuItem
            // 
            this->cfp4ToolStripMenuItem->Name = L"cfp4ToolStripMenuItem";
            this->cfp4ToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cfp4ToolStripMenuItem->Text = L"CF::p4";
            this->cfp4ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp4mToolStripMenuItem
            // 
            this->cFp4mToolStripMenuItem->Name = L"cFp4mToolStripMenuItem";
            this->cFp4mToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp4mToolStripMenuItem->Text = L"CF::p4m";
            this->cFp4mToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp4gToolStripMenuItem
            // 
            this->cFp4gToolStripMenuItem->Name = L"cFp4gToolStripMenuItem";
            this->cFp4gToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp4gToolStripMenuItem->Text = L"CF::p4g";
            this->cFp4gToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // friezeToolStripMenuItem
            // 
            this->friezeToolStripMenuItem->Name = L"friezeToolStripMenuItem";
            this->friezeToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->friezeToolStripMenuItem->Text = L"CF::p3";
            this->friezeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp3m1ToolStripMenuItem
            // 
            this->cFp3m1ToolStripMenuItem->Name = L"cFp3m1ToolStripMenuItem";
            this->cFp3m1ToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp3m1ToolStripMenuItem->Text = L"CF::p3m1";
            this->cFp3m1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp31mToolStripMenuItem
            // 
            this->cFp31mToolStripMenuItem->Name = L"cFp31mToolStripMenuItem";
            this->cFp31mToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp31mToolStripMenuItem->Text = L"CF::p31m";
            this->cFp31mToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp6ToolStripMenuItem
            // 
            this->cFp6ToolStripMenuItem->Name = L"cFp6ToolStripMenuItem";
            this->cFp6ToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp6ToolStripMenuItem->Text = L"CF::p6";
            this->cFp6ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFp6mToolStripMenuItem
            // 
            this->cFp6mToolStripMenuItem->Name = L"cFp6mToolStripMenuItem";
            this->cFp6mToolStripMenuItem->Size = System::Drawing::Size(138, 22);
            this->cFp6mToolStripMenuItem->Text = L"CF::p6m";
            this->cFp6mToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem7
            // 
            this->toolStripMenuItem7->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {
                this->toolStripMenuItem11,
                    this->toolStripMenuItem8, this->toolStripMenuItem19, this->toolStripMenuItem20, this->toolStripMenuItem21, this->toolStripMenuItem22,
                    this->toolStripMenuItem23, this->toolStripMenuItem24, this->toolStripMenuItem25, this->toolStripMenuItem26, this->toolStripMenuItem27,
                    this->toolStripMenuItem28, this->toolStripMenuItem29, this->toolStripMenuItem30, this->toolStripMenuItem31
            });
            this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
            this->toolStripMenuItem7->Size = System::Drawing::Size(220, 22);
            this->toolStripMenuItem7->Text = L"Insert Blend";
            // 
            // toolStripMenuItem11
            // 
            this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
            this->toolStripMenuItem11->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem11->Text = L"CF::Normal";
            this->toolStripMenuItem11->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem8
            // 
            this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
            this->toolStripMenuItem8->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem8->Text = L"CF::Clear";
            this->toolStripMenuItem8->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem19
            // 
            this->toolStripMenuItem19->Name = L"toolStripMenuItem19";
            this->toolStripMenuItem19->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem19->Text = L"CF::Xor";
            this->toolStripMenuItem19->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem20
            // 
            this->toolStripMenuItem20->Name = L"toolStripMenuItem20";
            this->toolStripMenuItem20->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem20->Text = L"CF::Plus";
            this->toolStripMenuItem20->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem21
            // 
            this->toolStripMenuItem21->Name = L"toolStripMenuItem21";
            this->toolStripMenuItem21->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem21->Text = L"CF::Multiply";
            this->toolStripMenuItem21->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem22
            // 
            this->toolStripMenuItem22->Name = L"toolStripMenuItem22";
            this->toolStripMenuItem22->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem22->Text = L"CF::Screen";
            this->toolStripMenuItem22->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem23
            // 
            this->toolStripMenuItem23->Name = L"toolStripMenuItem23";
            this->toolStripMenuItem23->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem23->Text = L"CF::Overlay";
            this->toolStripMenuItem23->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem24
            // 
            this->toolStripMenuItem24->Name = L"toolStripMenuItem24";
            this->toolStripMenuItem24->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem24->Text = L"CF::Darken";
            this->toolStripMenuItem24->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem25
            // 
            this->toolStripMenuItem25->Name = L"toolStripMenuItem25";
            this->toolStripMenuItem25->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem25->Text = L"CF::Lighten";
            this->toolStripMenuItem25->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem26
            // 
            this->toolStripMenuItem26->Name = L"toolStripMenuItem26";
            this->toolStripMenuItem26->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem26->Text = L"CF::ColorDodge";
            this->toolStripMenuItem26->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem27
            // 
            this->toolStripMenuItem27->Name = L"toolStripMenuItem27";
            this->toolStripMenuItem27->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem27->Text = L"CF::ColorBurn";
            this->toolStripMenuItem27->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem28
            // 
            this->toolStripMenuItem28->Name = L"toolStripMenuItem28";
            this->toolStripMenuItem28->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem28->Text = L"CF::HardLight";
            this->toolStripMenuItem28->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem29
            // 
            this->toolStripMenuItem29->Name = L"toolStripMenuItem29";
            this->toolStripMenuItem29->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem29->Text = L"CF::SoftLight";
            this->toolStripMenuItem29->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem30
            // 
            this->toolStripMenuItem30->Name = L"toolStripMenuItem30";
            this->toolStripMenuItem30->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem30->Text = L"CF::Difference";
            this->toolStripMenuItem30->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem31
            // 
            this->toolStripMenuItem31->Name = L"toolStripMenuItem31";
            this->toolStripMenuItem31->Size = System::Drawing::Size(158, 22);
            this->toolStripMenuItem31->Text = L"CF::Exclusion";
            this->toolStripMenuItem31->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // insertVariableToolStripMenuItem
            // 
            this->insertVariableToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(18) {
                this->cFAllowOverlapToolStripMenuItem,
                    this->cFAlphaToolStripMenuItem, this->cFBackgroundToolStripMenuItem, this->cFBorderDynamicToolStripMenuItem, this->cFBorderFixedToolStripMenuItem,
                    this->cFColorToolStripMenuItem, this->cFColorDepthToolStripMenuItem, this->cFFrameToolStripMenuItem, this->cFFrametimeToolStripMenuItem,
                    this->cFImpureToolStripMenuItem, this->toolStripMenuItem1, this->cFMaxShapesToolStripMenuItem, this->cFMinimumSizeToolStripMenuItem,
                    this->cFSizeToolStripMenuItem, this->toolStripMenuItem9, this->cFSymmetryToolStripMenuItem, this->cFTileToolStripMenuItem, this->cFTimeToolStripMenuItem
            });
            this->insertVariableToolStripMenuItem->Name = L"insertVariableToolStripMenuItem";
            this->insertVariableToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->insertVariableToolStripMenuItem->Text = L"Insert Variable";
            // 
            // cFAllowOverlapToolStripMenuItem
            // 
            this->cFAllowOverlapToolStripMenuItem->Name = L"cFAllowOverlapToolStripMenuItem";
            this->cFAllowOverlapToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFAllowOverlapToolStripMenuItem->Text = L"CF::AllowOverlap = 1";
            this->cFAllowOverlapToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFAlphaToolStripMenuItem
            // 
            this->cFAlphaToolStripMenuItem->Name = L"cFAlphaToolStripMenuItem";
            this->cFAlphaToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFAlphaToolStripMenuItem->Text = L"CF::Alpha = 1";
            this->cFAlphaToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFBackgroundToolStripMenuItem
            // 
            this->cFBackgroundToolStripMenuItem->Name = L"cFBackgroundToolStripMenuItem";
            this->cFBackgroundToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFBackgroundToolStripMenuItem->Text = L"CF::Background = [b 1]";
            this->cFBackgroundToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFBorderDynamicToolStripMenuItem
            // 
            this->cFBorderDynamicToolStripMenuItem->Name = L"cFBorderDynamicToolStripMenuItem";
            this->cFBorderDynamicToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFBorderDynamicToolStripMenuItem->Text = L"CF::BorderDynamic = 0";
            this->cFBorderDynamicToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFBorderFixedToolStripMenuItem
            // 
            this->cFBorderFixedToolStripMenuItem->Name = L"cFBorderFixedToolStripMenuItem";
            this->cFBorderFixedToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFBorderFixedToolStripMenuItem->Text = L"CF::BorderFixed = 0";
            this->cFBorderFixedToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFColorToolStripMenuItem
            // 
            this->cFColorToolStripMenuItem->Name = L"cFColorToolStripMenuItem";
            this->cFColorToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFColorToolStripMenuItem->Text = L"CF::Color = 1";
            this->cFColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFColorDepthToolStripMenuItem
            // 
            this->cFColorDepthToolStripMenuItem->Name = L"cFColorDepthToolStripMenuItem";
            this->cFColorDepthToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFColorDepthToolStripMenuItem->Text = L"CF::ColorDepth = 16";
            this->cFColorDepthToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFFrameToolStripMenuItem
            // 
            this->cFFrameToolStripMenuItem->Name = L"cFFrameToolStripMenuItem";
            this->cFFrameToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFFrameToolStripMenuItem->Text = L"CF::Frame = 60";
            this->cFFrameToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFFrametimeToolStripMenuItem
            // 
            this->cFFrametimeToolStripMenuItem->Name = L"cFFrametimeToolStripMenuItem";
            this->cFFrametimeToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFFrametimeToolStripMenuItem->Text = L"CF::FrameTime = 0.2";
            this->cFFrametimeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFImpureToolStripMenuItem
            // 
            this->cFImpureToolStripMenuItem->Name = L"cFImpureToolStripMenuItem";
            this->cFImpureToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFImpureToolStripMenuItem->Text = L"CF::Impure = 1";
            this->cFImpureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripMenuItem1
            // 
            this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
            this->toolStripMenuItem1->Size = System::Drawing::Size(266, 22);
            this->toolStripMenuItem1->Text = L"CF::MaxNatural = 10000";
            // 
            // cFMaxShapesToolStripMenuItem
            // 
            this->cFMaxShapesToolStripMenuItem->Name = L"cFMaxShapesToolStripMenuItem";
            this->cFMaxShapesToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFMaxShapesToolStripMenuItem->Text = L"CF::MaxShapes = 1000000";
            this->cFMaxShapesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFMinimumSizeToolStripMenuItem
            // 
            this->cFMinimumSizeToolStripMenuItem->Name = L"cFMinimumSizeToolStripMenuItem";
            this->cFMinimumSizeToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFMinimumSizeToolStripMenuItem->Text = L"CF::MinimumSize = 0.1";
            this->cFMinimumSizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFSizeToolStripMenuItem
            // 
            this->cFSizeToolStripMenuItem->Name = L"cFSizeToolStripMenuItem";
            this->cFSizeToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFSizeToolStripMenuItem->Text = L"CF::Size = [s 4 5]";
            this->cFSizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFSymmetryToolStripMenuItem
            // 
            this->cFSymmetryToolStripMenuItem->Name = L"cFSymmetryToolStripMenuItem";
            this->cFSymmetryToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFSymmetryToolStripMenuItem->Text = L"CF::Symmetry = CF::pmg, 1, 0.2, -0.5";
            this->cFSymmetryToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFTileToolStripMenuItem
            // 
            this->cFTileToolStripMenuItem->Name = L"cFTileToolStripMenuItem";
            this->cFTileToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFTileToolStripMenuItem->Text = L"CF::Tile = [skew 15 15 r 15]";
            this->cFTileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFTimeToolStripMenuItem
            // 
            this->cFTimeToolStripMenuItem->Name = L"cFTimeToolStripMenuItem";
            this->cFTimeToolStripMenuItem->Size = System::Drawing::Size(266, 22);
            this->cFTimeToolStripMenuItem->Text = L"CF::Time = [time 0 1]";
            this->cFTimeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // insertFlagToolStripMenuItem
            // 
            this->insertFlagToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {
                this->cFMiterJoinToolStripMenuItem,
                    this->cFRoundJoinToolStripMenuItem, this->cFBevelJoinToolStripMenuItem, this->cFButtCapToolStripMenuItem, this->cFRoundCapToolStripMenuItem,
                    this->cFSquareCapToolStripMenuItem, this->cFArcCWToolStripMenuItem, this->cFArcLargeToolStripMenuItem, this->cFContinuousToolStripMenuItem,
                    this->cFAlignToolStripMenuItem, this->cFEvenOddToolStripMenuItem, this->cFIsoWidthToolStripMenuItem
            });
            this->insertFlagToolStripMenuItem->Name = L"insertFlagToolStripMenuItem";
            this->insertFlagToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->insertFlagToolStripMenuItem->Text = L"Insert Flag";
            // 
            // cFMiterJoinToolStripMenuItem
            // 
            this->cFMiterJoinToolStripMenuItem->Name = L"cFMiterJoinToolStripMenuItem";
            this->cFMiterJoinToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFMiterJoinToolStripMenuItem->Text = L"CF::MiterJoin";
            this->cFMiterJoinToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFRoundJoinToolStripMenuItem
            // 
            this->cFRoundJoinToolStripMenuItem->Name = L"cFRoundJoinToolStripMenuItem";
            this->cFRoundJoinToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFRoundJoinToolStripMenuItem->Text = L"CF::RoundJoin";
            this->cFRoundJoinToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFBevelJoinToolStripMenuItem
            // 
            this->cFBevelJoinToolStripMenuItem->Name = L"cFBevelJoinToolStripMenuItem";
            this->cFBevelJoinToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFBevelJoinToolStripMenuItem->Text = L"CF::BevelJoin";
            this->cFBevelJoinToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFButtCapToolStripMenuItem
            // 
            this->cFButtCapToolStripMenuItem->Name = L"cFButtCapToolStripMenuItem";
            this->cFButtCapToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFButtCapToolStripMenuItem->Text = L"CF::ButtCap";
            this->cFButtCapToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFRoundCapToolStripMenuItem
            // 
            this->cFRoundCapToolStripMenuItem->Name = L"cFRoundCapToolStripMenuItem";
            this->cFRoundCapToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFRoundCapToolStripMenuItem->Text = L"CF::RoundCap";
            this->cFRoundCapToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFSquareCapToolStripMenuItem
            // 
            this->cFSquareCapToolStripMenuItem->Name = L"cFSquareCapToolStripMenuItem";
            this->cFSquareCapToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFSquareCapToolStripMenuItem->Text = L"CF::SquareCap";
            this->cFSquareCapToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFArcCWToolStripMenuItem
            // 
            this->cFArcCWToolStripMenuItem->Name = L"cFArcCWToolStripMenuItem";
            this->cFArcCWToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFArcCWToolStripMenuItem->Text = L"CF::ArcCW";
            this->cFArcCWToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFArcLargeToolStripMenuItem
            // 
            this->cFArcLargeToolStripMenuItem->Name = L"cFArcLargeToolStripMenuItem";
            this->cFArcLargeToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFArcLargeToolStripMenuItem->Text = L"CF::ArcLarge";
            this->cFArcLargeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFContinuousToolStripMenuItem
            // 
            this->cFContinuousToolStripMenuItem->Name = L"cFContinuousToolStripMenuItem";
            this->cFContinuousToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFContinuousToolStripMenuItem->Text = L"CF::Continuous";
            this->cFContinuousToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFAlignToolStripMenuItem
            // 
            this->cFAlignToolStripMenuItem->Name = L"cFAlignToolStripMenuItem";
            this->cFAlignToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFAlignToolStripMenuItem->Text = L"CF::Align";
            this->cFAlignToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFEvenOddToolStripMenuItem
            // 
            this->cFEvenOddToolStripMenuItem->Name = L"cFEvenOddToolStripMenuItem";
            this->cFEvenOddToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFEvenOddToolStripMenuItem->Text = L"CF::EvenOdd";
            this->cFEvenOddToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // cFIsoWidthToolStripMenuItem
            // 
            this->cFIsoWidthToolStripMenuItem->Name = L"cFIsoWidthToolStripMenuItem";
            this->cFIsoWidthToolStripMenuItem->Size = System::Drawing::Size(156, 22);
            this->cFIsoWidthToolStripMenuItem->Text = L"CF::IsoWidth";
            this->cFIsoWidthToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::toolStripMenuUnicode_Click);
            // 
            // toolStripSeparator5
            // 
            this->toolStripSeparator5->Name = L"toolStripSeparator5";
            this->toolStripSeparator5->Size = System::Drawing::Size(217, 6);
            // 
            // menuEFind
            // 
            this->menuEFind->Name = L"menuEFind";
            this->menuEFind->ShortcutKeyDisplayString = L"Ctrl-F";
            this->menuEFind->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
            this->menuEFind->Size = System::Drawing::Size(220, 22);
            this->menuEFind->Text = L"Find/Replace...";
            // 
            // menuEFindPrev
            // 
            this->menuEFindPrev->Name = L"menuEFindPrev";
            this->menuEFindPrev->ShortcutKeyDisplayString = L"Shift-Ctrl-F";
            this->menuEFindPrev->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
                | System::Windows::Forms::Keys::F));
            this->menuEFindPrev->Size = System::Drawing::Size(220, 22);
            this->menuEFindPrev->Tag = L"prev";
            this->menuEFindPrev->Text = L"Find Previous...";
            // 
            // toolStripSeparator8
            // 
            this->toolStripSeparator8->Name = L"toolStripSeparator8";
            this->toolStripSeparator8->Size = System::Drawing::Size(217, 6);
            // 
            // removeIndentToolStripMenuItem
            // 
            this->removeIndentToolStripMenuItem->Name = L"removeIndentToolStripMenuItem";
            this->removeIndentToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl-[";
            this->removeIndentToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::OemOpenBrackets));
            this->removeIndentToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->removeIndentToolStripMenuItem->Tag = L"-1";
            this->removeIndentToolStripMenuItem->Text = L"Remove Indent";
            this->removeIndentToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::Indent_Click);
            // 
            // addIndentToolStripMenuItem
            // 
            this->addIndentToolStripMenuItem->Name = L"addIndentToolStripMenuItem";
            this->addIndentToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl-]";
            this->addIndentToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Oem6));
            this->addIndentToolStripMenuItem->Size = System::Drawing::Size(220, 22);
            this->addIndentToolStripMenuItem->Tag = L"1";
            this->addIndentToolStripMenuItem->Text = L"Add Indent";
            this->addIndentToolStripMenuItem->Click += gcnew System::EventHandler(this, &Document::Indent_Click);
            // 
            // menuRender
            // 
            this->menuRender->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
                this->menuRRender,
                    this->menuRRenderSize, this->menuRRenderAgain, this->menuRAnimate, this->menuRAnimateFrame, this->menuRStop, this->toolStripSeparator3,
                    this->menuROutput, this->menuRUpload
            });
            this->menuRender->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuRender->MergeIndex = 2;
            this->menuRender->Name = L"menuRender";
            this->menuRender->Size = System::Drawing::Size(56, 20);
            this->menuRender->Text = L"&Render";
            // 
            // menuRRender
            // 
            this->menuRRender->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuRRender.Image")));
            this->menuRRender->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuRRender->Name = L"menuRRender";
            this->menuRRender->ShortcutKeyDisplayString = L"Ctrl-R";
            this->menuRRender->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
            this->menuRRender->Size = System::Drawing::Size(232, 22);
            this->menuRRender->Text = L"&Render";
            this->menuRRender->Click += gcnew System::EventHandler(this, &Document::menuRRender_Click);
            // 
            // menuRRenderSize
            // 
            this->menuRRenderSize->Name = L"menuRRenderSize";
            this->menuRRenderSize->ShortcutKeyDisplayString = L"Ctrl-Shft-R";
            this->menuRRenderSize->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
                | System::Windows::Forms::Keys::R));
            this->menuRRenderSize->Size = System::Drawing::Size(232, 22);
            this->menuRRenderSize->Text = L"Render to si&ze...";
            this->menuRRenderSize->Click += gcnew System::EventHandler(this, &Document::menuRRenderSize_Click);
            // 
            // menuRRenderAgain
            // 
            this->menuRRenderAgain->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuRRenderAgain.Image")));
            this->menuRRenderAgain->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuRRenderAgain->Name = L"menuRRenderAgain";
            this->menuRRenderAgain->ShortcutKeyDisplayString = L"Ctrl-Alt-R";
            this->menuRRenderAgain->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
                | System::Windows::Forms::Keys::R));
            this->menuRRenderAgain->Size = System::Drawing::Size(232, 22);
            this->menuRRenderAgain->Text = L"Repea&t Last Render";
            this->menuRRenderAgain->Click += gcnew System::EventHandler(this, &Document::RenderButton_Click);
            // 
            // menuRAnimate
            // 
            this->menuRAnimate->Name = L"menuRAnimate";
            this->menuRAnimate->ShortcutKeyDisplayString = L"Ctrl-Alt-A";
            this->menuRAnimate->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
                | System::Windows::Forms::Keys::A));
            this->menuRAnimate->Size = System::Drawing::Size(232, 22);
            this->menuRAnimate->Text = L"&Animate...";
            this->menuRAnimate->Click += gcnew System::EventHandler(this, &Document::menuRAnimate_Click);
            // 
            // menuRAnimateFrame
            // 
            this->menuRAnimateFrame->Name = L"menuRAnimateFrame";
            this->menuRAnimateFrame->ShortcutKeyDisplayString = L"Ctrl-Alt-F";
            this->menuRAnimateFrame->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
                | System::Windows::Forms::Keys::F));
            this->menuRAnimateFrame->Size = System::Drawing::Size(232, 22);
            this->menuRAnimateFrame->Text = L"Animate &Frame...";
            this->menuRAnimateFrame->Click += gcnew System::EventHandler(this, &Document::menuRAnimateFrame_Click);
            // 
            // menuRStop
            // 
            this->menuRStop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuRStop.Image")));
            this->menuRStop->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuRStop->Name = L"menuRStop";
            this->menuRStop->ShortcutKeyDisplayString = L"Ctrl-END";
            this->menuRStop->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::End));
            this->menuRStop->Size = System::Drawing::Size(232, 22);
            this->menuRStop->Text = L"&Stop";
            this->menuRStop->Click += gcnew System::EventHandler(this, &Document::menuRStop_Click);
            // 
            // toolStripSeparator3
            // 
            this->toolStripSeparator3->Name = L"toolStripSeparator3";
            this->toolStripSeparator3->Size = System::Drawing::Size(229, 6);
            // 
            // menuROutput
            // 
            this->menuROutput->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuROutput.Image")));
            this->menuROutput->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuROutput->Name = L"menuROutput";
            this->menuROutput->ShortcutKeyDisplayString = L"Ctrl-O";
            this->menuROutput->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
            this->menuROutput->Size = System::Drawing::Size(232, 22);
            this->menuROutput->Text = L"Save &output...";
            this->menuROutput->Click += gcnew System::EventHandler(this, &Document::menuRSaveOutput_Click);
            // 
            // menuRUpload
            // 
            this->menuRUpload->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"menuRUpload.Image")));
            this->menuRUpload->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
            this->menuRUpload->Name = L"menuRUpload";
            this->menuRUpload->ShortcutKeyDisplayString = L"Ctrl-U";
            this->menuRUpload->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::U));
            this->menuRUpload->Size = System::Drawing::Size(232, 22);
            this->menuRUpload->Text = L"&Upload to gallery...";
            this->menuRUpload->Click += gcnew System::EventHandler(this, &Document::menuRUpload_Click);
            // 
            // toolStripMenuItem9
            // 
            this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
            this->toolStripMenuItem9->Size = System::Drawing::Size(266, 22);
            this->toolStripMenuItem9->Text = L"CF::StartShape = foo,[b 1]";
            // 
            // Document
            // 
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
            this->ClientSize = System::Drawing::Size(1162, 808);
            this->Controls->Add(this->documentSplitter);
            this->Controls->Add(this->toolStrip1);
            this->Controls->Add(this->menuStrip1);
            this->DockAreas = WeifenLuo::WinFormsUI::Docking::DockAreas::Document;
            this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"Document";
            this->TabText = L"Document";
            this->Text = L"Document";
            this->toolStrip1->ResumeLayout(false);
            this->toolStrip1->PerformLayout();
            this->documentSplitter->Panel1->ResumeLayout(false);
            this->documentSplitter->Panel2->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentSplitter))->EndInit();
            this->documentSplitter->ResumeLayout(false);
            this->editorSplitter->Panel1->ResumeLayout(false);
            this->editorSplitter->Panel2->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->editorSplitter))->EndInit();
            this->editorSplitter->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->renderBox))->EndInit();
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
private: 
    System::Void RenderButton_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void PrevVar_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void NextVar_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuFSave_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuFSaveAs_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuFClose_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuFRevert_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuRRender_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuRRenderSize_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuRStop_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuRSaveOutput_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void menuRUpload_Click(System::Object^  sender, System::EventArgs^  e);

    System::Void modifiedCFDG(System::Object^  sender, System::EventArgs^  e);

    System::Void stripSizeChanged(System::Object^ sender, System::EventArgs^ e);

    System::Void renderSizeChanging(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e);

    System::Void variationKeyDown(Object^ , System::Windows::Forms::KeyEventArgs^ e);

    System::Void variationKeyPress(Object^ , System::Windows::Forms::KeyPressEventArgs^);

    System::Void variationChanged(System::Object^ sender, System::EventArgs^ e);

    void InitializeStuff();
    void DestroyStuff();
    System::Void moreInitialization(System::Object^ sender, System::EventArgs^ e);
    System::EventHandler^ moreInitHandler;

protected: 
    System::Void FormIsClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
    virtual void WndProc(System::Windows::Forms::Message% m) override;
    void RunRenderThread(System::Object^, System::ComponentModel::DoWorkEventArgs^);
    void RenderCompleted(System::Object^, System::ComponentModel::RunWorkerCompletedEventArgs^);
    void DoRender();
    void updateRenderButton();
    int mRenderButtonIndex;
    bool SyncToSystem();
    System::Drawing::Bitmap^ MakeBitmap(bool cropped, WinCanvas* canvas);
    void renderSizeChanged();
    void setupCanvas(Renderer* r);
    void updateRenderBox();
    int mProgressDelay;
    int mResizeDelay;
    bool mReuseVariation;
    int imageListBase;

    cfdg_ptr* mEngine;
    Renderer* mRenderer;
    WinCanvas* mCanvas;
    WinCanvas* mTempCanvas;
    SVGCanvas* mSVGCanvas;
    ffCanvas* mAnimationCanvas;
    System::String^ mMovieFile;
    System::Diagnostics::Process^ mMoviePlayer;
    bool mTiled;
    array<double>^ mOutputMultiplier;
    System::Drawing::Bitmap^ displayImage;
    System::Windows::Forms::Timer^ statusTimer;
    System::Void statusTick(System::Object^ sender, System::EventArgs^ e);
    System::Windows::Forms::Timer^ resizeTimer;
    System::Void resizeTick(System::Object^ sender, System::EventArgs^ e);

    System::EventHandler^ activateHandler;

private: System::Void menuEUndo_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void menuERedo_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void menuECut_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuECopy_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuEPaste_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuRAnimate_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuRAnimateFrame_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuFile_Popup(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuEdit_Popup(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuEDelete_Click(System::Object^  sender, System::EventArgs^  e);

public: bool saveToPNGorJPEG(System::String^ path, System::IO::Stream^ str, bool JPEG);
private: void saveToSVG(System::String^ path);
private: void drawTiled(System::Drawing::Bitmap^ src, System::Drawing::Bitmap^ dest,
             System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ gray, 
             int x, int y);
private: void drawCheckerBoard(System::Drawing::Graphics^ g, 
             System::Drawing::SolidBrush^ grayBrush, System::Drawing::Rectangle destRect);

private: System::Void renderBox_Click(System::Object^  sender, System::EventArgs^  e) {
             cfdgText->Focus();
         }
private: System::Void textFontHandler(System::Object^ sender, System::EventArgs^ e);
private: System::Void errorNavigation(System::Object^ sender, System::Windows::Forms::WebBrowserNavigatingEventArgs^ e);
private: System::EventHandler^ processVariationChange;
private: System::Void splitterMoved(System::Object^ sender, System::Windows::Forms::SplitterEventArgs^ e);
private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
         }
private: System::Void messageWindowReady(System::Object^ sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^ e);
         System::Text::StringBuilder^ deferredHtml;
         bool messageWindowUnready;
private: System::Void toolStripMenuUnicode_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void actionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void PrevFrame_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void NextFrame_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Frame_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
private: System::Void Frame_Changed(System::Object^ sender, System::EventArgs^ e);
private: System::Void Size_Changed(System::Object^ sender, System::EventArgs^ e);
         System::Void Style_Cfdg(System::Object^ sender, ScintillaNET::StyleNeededEventArgs^ e);
         System::Void StyleChanged(System::Object^ sender, System::EventArgs^ e);
         System::Void InsertionCheck(System::Object^ sender, ScintillaNET::InsertCheckEventArgs^ e);
         System::Void CharAdded(System::Object^ sender, ScintillaNET::CharAddedEventArgs^ e);
         System::Void UpdateUI(System::Object^ sender, ScintillaNET::UpdateUIEventArgs^ e);
         System::Void Text_Changed(System::Object^ sender, ScintillaNET::ModificationEventArgs^ e);
         System::Void AutoCCharDeleted(System::Object^ sender, System::EventArgs^ e);
         System::Void CheckAutoC();
private: System::Void Indent_Click(System::Object^  sender, System::EventArgs^  e);
         System::Void PictureDragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
         System::Void PictureDragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
         System::Void DownLoaded(System::Object^ sender, System::Net::DownloadStringCompletedEventArgs^ e);
         System::EventHandler^ revertHandler;
         System::EventHandler^ fontHandler;
         System::EventHandler^ styleHandler;
};
}

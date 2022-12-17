// RenderHelper.h
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


#pragma once
#include <cstdlib>
#include "Scintilla.h"
#include "RenderParameters.h"
#include "RenderStats.h"
#include "variation.h"
#include "UploadPrefs.h"
#include "WinSystem.h"

class ffCanvas;
class SVGCanvas;
class WinCanvas;

namespace CppWrapper {
    public ref class RenderHelper : public System::IDisposable
    {
    public:
        RenderHelper(void* editHwnd, void* docHwnd, void* formHwnd);
        RenderHelper();

        ~RenderHelper();
        !RenderHelper();

        sptr_t DirectMessage(int msg)
        {
            return DirectMessage(msg, 0, 0);
        }

        sptr_t DirectMessage(int msg, intptr_t wParam)
        {
            return DirectMessage(msg, wParam, 0);
        }

        sptr_t DirectMessage(int msg, intptr_t wParam, intptr_t lParam)
        {
            return directFunction(SciPtr, msg, wParam, lParam);
        }

        void StyleLines(int startLine, int endLine);

        static cli::array<System::String^>^ GetAutoC();

        enum class WM_USER 
        {
            MESSAGE_UPDATE = WinSystem::WM_USER_MESSAGE_UPDATE,
            STATUS_UPDATE = WinSystem::WM_USER_STATUS_UPDATE
        };
        static System::String^ GetMessage(System::IntPtr wParam);
        static RenderStats GetStats(System::IntPtr wParam);

        static int VariationFromString(System::String^ s);
        static System::String^ VariationToString(int v);
        static int RandomVariation(int length);
        static const int MinVariation = Variation::recommendedMin();
        static const int MaxVariation = Variation::recommendedMax(6);

        void RunRenderThread(RenderParameters^ rp);
        bool SyncToSystem(System::String^ name, System::String^ cfdg);

        static void AbortEverything();
        property bool RequestFinishUp {
            void set(bool value) {
                if (mRenderer)
                    mRenderer->requestFinishUp = value;
            }
            bool get() { return mRenderer ? mRenderer->requestFinishUp.load() : false; }
        }
        property bool RequestStop {
            void set(bool value) {
                if (mRenderer)
                    mRenderer->requestStop = value;
            }
            bool get() { return mRenderer ? mRenderer->requestStop.load() : false; }
        }
        property intptr_t Renderer {
            void set(intptr_t v) { mRenderer = (::Renderer*)v; }
            intptr_t get() { return (intptr_t)mRenderer; }
        }
        property bool Engine {
            bool get() { return mEngine->get() != nullptr; }
        }
        property bool Tiled {
            bool get() {
                if (mEngine->get() != nullptr)
                    return (*mEngine)->isTiledOrFrieze();
                else
                    return false;
            }
        }
        property int Frieze {
            int get() {
                if (mEngine->get() != nullptr)
                    return (int)((*mEngine)->isFrieze());
                else
                    return 0;
            }
        }
        property bool Canvas {
            bool get() { return mCanvas != nullptr; }
        }
        property int Width {
            int get() { return mRenderer->m_width; }
        }
        property int Height {
            int get() { return mRenderer->m_height; }
        }

        System::String^ GetExample(System::String^ name);
        static bool IsExample(System::String^ name);

        void PrepareForRender(int width, int height, double minSize, double border, 
            int variation, bool shrinkTiled);
        void MakeCanvas(int width, int height);
        System::String^ MakeAnimationCanvas(RenderParameters^ params);
        bool CanAnimate();
        bool MakeSVGCanvas(System::String^ path, int width, int height, UploadPrefs^ prefs);
        void UpdateRenderBox(System::Windows::Forms::PictureBox^ renderBox, 
            System::Drawing::Bitmap^ displayImage, bool noDisplay);
        bool PerformRender(System::ComponentModel::BackgroundWorker^ renderThread);
        System::Drawing::Bitmap^ MakeBitmap(bool cropped, WinCanvas* canvas);
        void RequestUpdate();
        void UploadDesign(System::Windows::Forms::Form^ owner, UploadPrefs^ prefs);
        static UploadPrefs^ DownloadDesign(System::String^ responseBody);
        bool SaveToPNGorJPEG(UploadPrefs^ prefs, System::String^ path, bool JPEG);
        bool SaveToPNGorJPEG(UploadPrefs^ prefs, System::IO::Stream^ str, bool JPEG);
        cli::array<System::String^>^ FindTempFiles();

    private:
        void DrawCheckerBoard(System::Drawing::Graphics^ g, System::Drawing::Rectangle destRect);
        void DrawTiled(System::Drawing::Bitmap^ src, System::Drawing::Bitmap^ dest,
                       System::Drawing::Graphics^ g, int x, int y);
        System::ComponentModel::BackgroundWorker^ renderDeleter = nullptr;
        void DeleteRenderer(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        sptr_t SciPtr = 0;
        SciFnDirect directFunction = nullptr;
        WinSystem* mSystem = nullptr;
        ::Renderer* mRenderer = nullptr;
        cfdg_ptr* mEngine;
        WinCanvas* mCanvas = nullptr;
        WinCanvas* tempCanvas = nullptr;
        ffCanvas* animationCanvas = nullptr;
        SVGCanvas* SVGcanvas = nullptr;
    };
}


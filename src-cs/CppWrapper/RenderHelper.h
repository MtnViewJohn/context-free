#pragma once
#include <cstdlib>
#include "Scintilla.h"
#include "RenderParameters.h"
#include "RenderStats.h"
#include "WinSystem.h"
#include "WinCanvas.h"
#include "variation.h"

namespace CppWrapper {
    public ref class RenderHelper
    {
    public:
        RenderHelper(intptr_t editHwnd, intptr_t docHwnd);
        RenderHelper();

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
            STATUS_UPDATE = WinSystem::WM_USER_STATUS_UPDATE,
            SYNTAX_ERROR = WinSystem::WM_USER_SYNTAX_ERROR
        };
        static System::String^ getMessage(System::IntPtr wParam);
        static RenderStats getStats(System::IntPtr wParam);

        static int VariationFromString(System::String^ s);
        static System::String^ VariationToString(int v);
        static int RandomVariation(int length);
        static const int MinVariation = Variation::recommendedMin();
        static const int MaxVariation = Variation::recommendedMax(6);

        void runRenderThread(RenderParameters^ rp);
        bool syncToSystem(System::String^ name, System::String^ cfdg);

        property bool requestFinishUp {
            void set(bool value) { mRenderer->requestFinishUp = value; }
            bool get() { return mRenderer->requestFinishUp; }
        }
        property bool requestStop {
            void set(bool value) { mRenderer->requestStop = value; }
            bool get() { return mRenderer->requestStop; }
        }
        property intptr_t renderer {
            void set(intptr_t v) { mRenderer = (Renderer*)v; }
            intptr_t get() { return (intptr_t)mRenderer; }
        }
        property bool engine {
            bool get() { return mEngine->get() != nullptr; }
        }
        property bool tiled {
            bool get() {
                if (mEngine->get() != nullptr)
                    return (*mEngine)->isTiledOrFrieze();
                else
                    return false;
            }
        }
        property bool canvas {
            bool get() { return mCanvas != nullptr; }
        }
        property int width {
            int get() { return mRenderer->m_width; }
        }
        property int height {
            int get() { return mRenderer->m_height; }
        }

        System::String^ getExample(System::String^ name);
        static bool IsExample(System::String^ name);

        void prepareForRender(int width, int height, double minSize, double border, 
            int variation, bool shrinkTiled);
        void makeCanvas(int width, int height);
        void updateRenderBox(System::Windows::Forms::PictureBox^ renderBox, 
            System::Drawing::Bitmap^ displayImage, bool noDisplay);
        bool performRender(System::ComponentModel::BackgroundWorker^ renderThread);
        System::Drawing::Bitmap^ MakeBitmap(bool cropped, WinCanvas* canvas);
        void drawCheckerBoard(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ grayBrush, 
            System::Drawing::Rectangle destRect);
        void drawTiled(System::Drawing::Bitmap^ src, System::Drawing::Bitmap^ dest,
            System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ grayBrush, int x, int y);

    private:
        sptr_t SciPtr = 0;
        SciFnDirect directFunction = nullptr;
        WinSystem* mSystem = nullptr;
        Renderer* mRenderer = nullptr;
        cfdg_ptr* mEngine;
        WinCanvas* mCanvas = nullptr;
        WinCanvas* tempCanvas = nullptr;
        Canvas* animationCanvas = nullptr;
    };
}


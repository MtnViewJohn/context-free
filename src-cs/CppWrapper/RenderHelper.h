#pragma once
#include <cstdlib>
#include "Scintilla.h"
#include "RenderParameters.h"
#include "WinSystem.h"

namespace CppWrapper {
    public ref class RenderHelper
    {
    public:
        RenderHelper(intptr_t editHwnd, intptr_t docHwnd);

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

        static const int WM_USER_MESSAGE_UPDATE = WinSystem::WM_USER_MESSAGE_UPDATE;
        static const int WM_USER_STATUS_UPDATE  = WinSystem::WM_USER_STATUS_UPDATE;
        static const int WM_USER_SYNTAX_ERROR   = WinSystem::WM_USER_SYNTAX_ERROR;

        static int VariationFromString(System::String^ s);
        static System::String^ VariationToString(int v);
        static int RandomVariation(int length);
        static int MinVariation();
        static int MaxVariation();

        void runRenderThread(RenderParameters^ rp);

        System::String^ getExample(System::String^ name);
        static bool IsExample(System::String^ name);

    private:
        sptr_t SciPtr = 0;
        SciFnDirect directFunction = nullptr;
        WinSystem* mSystem = nullptr;
    };
}


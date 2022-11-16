#pragma once
#include <cstdlib>
#include "Scintilla.h"
#include "RenderParameters.h"

namespace CppWrapper {
	public ref class RenderHelper
	{
	public:
		RenderHelper(intptr_t hwnd);

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

		static int VariationFromString(System::String^ s);
		static System::String^ VariationToString(int v);
		static int RandomVariation(int length);
		static int MinVariation();
		static int MaxVariation();

		void runRenderThread(RenderParameters^ rp);

	private:
		sptr_t SciPtr = 0;
		SciFnDirect directFunction = nullptr;
	};
}


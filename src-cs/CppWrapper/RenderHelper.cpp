#include "pch.h"
#include "RenderHelper.h"
#include <Windows.h>
#include "CFscintilla.h"
#include <algorithm>
#include "variation.h"

using namespace System;
using namespace System::ComponentModel;

namespace CppWrapper {
	RenderHelper::RenderHelper(intptr_t hwndp)
	{
		HWND hwnd = (HWND)hwndp;
		SciPtr = (sptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
		directFunction = (SciFnDirect)SendMessage(hwnd, SCI_GETDIRECTFUNCTION, 0, 0);
	}

	cli::array<System::String^>^
	RenderHelper::GetAutoC()
	{
		std::sort(CFscintilla::AutoComplete.begin(), CFscintilla::AutoComplete.end(), CFscintilla::AutoCmp());
		int sz = static_cast<int>(CFscintilla::AutoComplete.size());
		auto ac = gcnew cli::array<System::String^>(sz);
		for (int i = 0; i < sz; ++i)
			ac[i] = gcnew System::String(CFscintilla::AutoComplete[i]);
		return ac;
	}

	void
	RenderHelper::StyleLines(int startLine, int endLine)
	{
		CFscintilla::StyleLines(directFunction, SciPtr, startLine, endLine);
	}

	int 
	RenderHelper::VariationFromString(System::String^ s)
	{
		auto u8var = System::Text::Encoding::UTF8->GetBytes(s);
		if (u8var->Length == 0)
			return -1;
		pin_ptr<Byte> pinnedVar = &u8var[0];
		return Variation::fromString(reinterpret_cast<const char*>(pinnedVar));
	}

	System::String^
	RenderHelper::VariationToString(int v)
	{
		return gcnew String(Variation::toString(v, false).c_str());
	}

	int 
	RenderHelper::RandomVariation(int length)
	{
		return Variation::random(length);
	}

	int 
	RenderHelper::MinVariation()
	{
		return Variation::recommendedMin();
	}

	int 
	RenderHelper::MaxVariation()
	{
		return Variation::recommendedMax();
	}

	void 
	RenderHelper::runRenderThread(RenderParameters^ rp)
	{}

}
#pragma once

#include "hsbColorClr.h"

namespace CppWrapper {
    public ref class ColorChangeEventArgs : public System::EventArgs
    {
    public: ColorChangeEventArgs(System::Drawing::Color c)
                : changedColorSpace(ColorSpace::RGB), newRGBColor(c)
            { }
            ColorChangeEventArgs(hsbColorClr c)
                : changedColorSpace(ColorSpace::HSB), newHSBColor(c)
            { }


        enum class ColorSpace {HSB, RGB};

        ColorSpace changedColorSpace;
        System::Drawing::Color newRGBColor;
        hsbColorClr newHSBColor;
    };

    public delegate System::Void ColorChangeEventHandler(System::Object^ sender, 
        ColorChangeEventArgs^ e);
}


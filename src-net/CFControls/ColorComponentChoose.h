#pragma once

#include "ColorChangeEventArgs.h"

namespace CFControls {

	/// <summary>
	/// Summary for ColorComponentChoose
	/// </summary>
	public ref class ColorComponentChoose : public System::Windows::Forms::Control
	{
	public:
		ColorComponentChoose(void) : myColor(0.0, 0.0, 0.0)
		{
            MoreInitialization();
		}

        event ColorChangeEventHandler^ ColorChange;

        property double Hue {
            double get() { return myColor.Hue; }
            void set(double v) { myColor.Hue = v; redrawChannel(); }
        }
        property double Sat {
            double get() { return myColor.Sat; }
            void set(double v) { myColor.Sat = v; redrawChannel(); }
        }
        property double Bright {
            double get() { return myColor.Bright; }
            void set(double v) { myColor.Bright = v; calcMarkerRect(); }
        }
        property hsbColor CurrentColor {
            hsbColor get() { return myColor; }
            void set(hsbColor c) { myColor = c; redrawChannel(); calcMarkerRect(); }
        }
        static const int minimumWidth = 15;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ColorComponentChoose()
		{
		}

        void OnColorChange(ColorChangeEventArgs^ e);

	private:
        System::Drawing::Bitmap^ colorChannel;
        System::Drawing::Rectangle colorRect;
        System::Drawing::Rectangle focusRect;
        System::Drawing::Pen^ focusPen;
        System::Drawing::Rectangle markerRect;
        System::Drawing::Pen^ markerPen;
        static const int markerSize = 3;
        hsbColor myColor;

    protected:
        virtual bool IsInputKey (System::Windows::Forms::Keys keyData) override;

    private:
        System::Void resizeHandler(System::Object^ sender, System::EventArgs^ e);
        void initForSize();
        System::Void initForColors(System::Object^ sender, System::EventArgs^ e);
        void calcMarkerRect();
        System::Void mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void paintMe(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
        System::Void focusHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void arrowHandler(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
        void MoreInitialization();
        void redrawChannel();
	};
}

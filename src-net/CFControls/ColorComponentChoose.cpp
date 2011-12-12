// ColorComponentChoose.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008 John Horigan - john@glyphic.com
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

#include "StdAfx.h"
#include "ColorComponentChoose.h"

using namespace CFControls;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


void ColorComponentChoose::MoreInitialization()
{
    this->Size = System::Drawing::Size(20, 100);
    Resize += gcnew EventHandler(this, &ColorComponentChoose::resizeHandler);

    Paint += gcnew PaintEventHandler(this, &ColorComponentChoose::paintMe);

    EventHandler^ colorHandler = gcnew EventHandler(this, &ColorComponentChoose::initForColors);
    BackColorChanged += colorHandler;
    SystemColorsChanged += colorHandler;
    ForeColorChanged += colorHandler;

    EventHandler^ focus = gcnew EventHandler(this, &ColorComponentChoose::focusHandler);
    GotFocus += focus;
    LostFocus += focus;

    //initForSize();
    initForColors(nullptr, nullptr);    // calls InitForSize()

    SetStyle(ControlStyles::DoubleBuffer, true);
    SetStyle(ControlStyles::AllPaintingInWmPaint, true);
    SetStyle(ControlStyles::UserPaint, true);
    SetStyle(ControlStyles::Selectable, true);

    calcMarkerRect();

    MouseDown += gcnew MouseEventHandler(this, &ColorComponentChoose::mouseDown);
    MouseUp   += gcnew MouseEventHandler(this, &ColorComponentChoose::mouseUp);
    MouseMove += gcnew MouseEventHandler(this, &ColorComponentChoose::mouseMove);
    KeyDown   += gcnew   KeyEventHandler(this, &ColorComponentChoose::arrowHandler);
}

void ColorComponentChoose::OnColorChange(ColorChangeEventArgs^ e)
{
    //if (ColorChange)
        ColorChange(this, e);
}

System::Void ColorComponentChoose::resizeHandler(System::Object^ sender, System::EventArgs^ e)
{
    Control^ control = dynamic_cast<Control^>(sender);

    // Ensure the control remains square (Height = Width).
    if (control->Size.Width < minimumWidth) {
        control->Size = System::Drawing::Size(minimumWidth, control->Size.Height);
    }
    initForSize();
}

void ColorComponentChoose::initForSize()
{
    focusRect = Drawing::Rectangle(0, 0, Size.Width - 1, Size.Height - 1);
    colorRect = focusRect;
    colorRect.Inflate(-(markerSize + 2), -(markerSize + 2));
    ++colorRect.Width;
    ++colorRect.Height;

    if (colorChannel != nullptr)
        delete colorChannel;
    colorChannel = gcnew Bitmap(colorRect.Width, colorRect.Height, Imaging::PixelFormat::Format24bppRgb);

    redrawChannel();
    calcMarkerRect();
}

void ColorComponentChoose::redrawChannel()
{
    Graphics^ g = Graphics::FromImage(colorChannel);
    hsbColor hsb = myColor;
    hsb.Bright = 1.0;
    Color c = hsb.GetColor();
    Rectangle drawRect = Rectangle(Point(0, 0), colorChannel->Size);
    Drawing2D::LinearGradientBrush^ lgb = gcnew Drawing2D::LinearGradientBrush(drawRect,
        c, Color::Black, Drawing2D::LinearGradientMode::Vertical);
    g->FillRectangle(lgb, drawRect);

    Invalidate();
}

System::Void ColorComponentChoose::initForColors(System::Object^ sender, System::EventArgs^ e)
{
    if (focusPen != nullptr)
        delete focusPen;
    focusPen = gcnew Pen(Color::Black);
    focusPen->DashStyle = Drawing::Drawing2D::DashStyle::Dot;

    if (markerPen != nullptr)
        delete markerPen;
    markerPen = gcnew Pen(ForeColor);
    markerPen->Width = 2;

    initForSize();
}

void ColorComponentChoose::calcMarkerRect()
{
    markerRect.Inflate(1, 1);
    Invalidate(markerRect);
    int pos = (int)((1.0 - myColor.Bright) * colorChannel->Height + 0.5);
    markerRect = Rectangle(focusRect.X + 2, pos + colorRect.Y - markerSize, 
        focusRect.Width - 3, 2 * markerSize);	
    Rectangle newRect = markerRect;
    newRect.Inflate(1, 1);
    Invalidate(newRect);
}

System::Void ColorComponentChoose::mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (focusRect.Contains(e->Location)) {
        Capture = true;
        mouseMove(sender, e);
        Focus();
    }
}

System::Void ColorComponentChoose::mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (Capture)
        Capture = false;
}

System::Void ColorComponentChoose::mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (!Capture) return;

    myColor.Bright = (double)(e->Location.Y - colorRect.Y) / colorRect.Height;
    if (myColor.Bright < 0.0) myColor.Bright = 0.0;
    if (myColor.Bright > 1.0) myColor.Bright = 1.0;
    myColor.Bright = 1.0 - myColor.Bright;

    calcMarkerRect();
    ColorChange(this, gcnew ColorChangeEventArgs(myColor));
}

System::Void ColorComponentChoose::arrowHandler(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
    if (e->Alt || e->Control || e->Shift) return;

    switch (e->KeyCode) {
        case Keys::Down:
            myColor.Bright -= 0.003922;
            if (myColor.Bright < 0.0) myColor.Bright = 0.0;
            break;
        case Keys::Up:
            myColor.Bright += 0.003922;
            if (myColor.Bright > 1.0) myColor.Bright = 1.0;
            break;
        default:
            return;
    }

    calcMarkerRect();
    ColorChange(this, gcnew ColorChangeEventArgs(myColor));
}

bool ColorComponentChoose::IsInputKey(System::Windows::Forms::Keys k)
{
    if (k == Keys::Up || k == Keys::Down)
        return true;

    return Control::IsInputKey(k);
}

System::Void ColorComponentChoose::paintMe(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
    e->Graphics->Clear(BackColor);
    e->Graphics->DrawImage(colorChannel, colorRect.Location);
    e->Graphics->DrawRectangle(markerPen, markerRect);
    if (Focused) {
        e->Graphics->DrawRectangle(focusPen, focusRect);
    }
}

System::Void ColorComponentChoose::focusHandler(System::Object^ sender, System::EventArgs^ e)
{
    Invalidate();
}


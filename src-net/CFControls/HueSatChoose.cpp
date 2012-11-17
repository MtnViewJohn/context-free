// HueSatChoose.cpp
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
#include "HueSatChoose.h"
#include "math.h"

using namespace CFControls;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


void HueSatChoose::MoreInitialization()
{
    this->Size = System::Drawing::Size(100, 100);
    Resize += gcnew EventHandler(this, &HueSatChoose::resizeHandler);

    Paint += gcnew PaintEventHandler(this, &HueSatChoose::paintMe);

    EventHandler^ colorHandler = gcnew EventHandler(this, &HueSatChoose::initForColors);
    BackColorChanged += colorHandler;
    SystemColorsChanged += colorHandler;
    ForeColorChanged += colorHandler;

    EventHandler^ focus = gcnew EventHandler(this, &HueSatChoose::focusHandler);
    GotFocus += focus;
    LostFocus += focus;

    //initForSize();
    initForColors(nullptr, nullptr);    // calls InitForSize()

    SetStyle(ControlStyles::DoubleBuffer, true);
    SetStyle(ControlStyles::AllPaintingInWmPaint, true);
    SetStyle(ControlStyles::UserPaint, true);
    SetStyle(ControlStyles::Selectable, true);

    calcMarkerRect();

    MouseDown += gcnew MouseEventHandler(this, &HueSatChoose::mouseDown);
    MouseUp   += gcnew MouseEventHandler(this, &HueSatChoose::mouseUp);
    MouseMove += gcnew MouseEventHandler(this, &HueSatChoose::mouseMove);
    KeyDown   += gcnew KeyEventHandler(this, &HueSatChoose::arrowHandler);
}

void HueSatChoose::OnColorChange(ColorChangeEventArgs^ e)
{
    //if (ColorChange)
        ColorChange(this, e);
}

System::Void HueSatChoose::resizeHandler(System::Object^ sender, System::EventArgs^ e)
{
    Control^ control = dynamic_cast<Control^>(sender);

    // Ensure the control remains square (Height = Width).
    if (control->Size.Height != control->Size.Width) {
        int newSize = control->Size.Height < control->Size.Width ? 
            control->Size.Height : control->Size.Width;
        control->Size = System::Drawing::Size(newSize, newSize);
    }
    initForSize();
}

void HueSatChoose::initForSize()
{
    int mySize = Size.Width - 1;
    if ((mySize & 1) == 0) --mySize;

    if (colorWheel != nullptr)
        delete colorWheel;
    colorWheel = gcnew Bitmap(mySize, mySize, Imaging::PixelFormat::Format24bppRgb);

    if (clipPath != nullptr)
        delete clipPath;
    clipPath = gcnew Drawing2D::GraphicsPath();
    clipPath->AddEllipse(markerSize + 1, markerSize + 1, 
        mySize - 2 * markerSize - 1, mySize - 2 * markerSize - 1);

    focusRect = Drawing::Rectangle(0, 0, mySize, mySize);
    colorCenter = Point(mySize / 2 + 1, mySize / 2 + 1);
    radius = (double)(mySize / 2 - markerSize - 1);
    calcMarkerRect();

    for (int y = 0; y < mySize; ++y) {
        for (int x = 0; x < mySize; ++x) {
            Point p(x, y);
            double sat = Distance(p) / radius;
            double hue = AngleFromPoint(p);

            if (sat > 1.0) sat = 1.0;
            hsbColor ptColor(hue, sat, 1.0);
            colorWheel->SetPixel(x, y, ptColor.GetColor());
        }
    }

    Graphics^ g = Graphics::FromImage(colorWheel);
    g->SetClip(clipPath, Drawing2D::CombineMode::Exclude);
    g->Clear(BackColor);

    Invalidate();
}

System::Void HueSatChoose::initForColors(System::Object^ sender, System::EventArgs^ e)
{
    if (focusPen != nullptr)
        delete focusPen;
    focusPen = gcnew Pen(Color::Black);
    focusPen->DashStyle = Drawing::Drawing2D::DashStyle::Dot;

    if (markerPen != nullptr)
        delete markerPen;
    markerPen = gcnew Pen(ForeColor);

    initForSize();
}

void HueSatChoose::calcMarkerRect()
{
    //markerRect.Inflate(1, 1);
    ++markerRect.Width;
    ++markerRect.Height;
    Invalidate(markerRect);
    Point pt = PointFromAngle(myColor.Hue, myColor.Sat);
	markerRect = Rectangle(pt.X - markerSize, pt.Y - markerSize, 
                           2 * markerSize, 2 * markerSize);	
    Rectangle newRect = markerRect;
    //newRect.Inflate(1, 1);
    ++newRect.Width;
    ++newRect.Height;
    Invalidate(newRect);
}

System::Void HueSatChoose::mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (Distance(e->Location) > radius + 5.0) return;

    Capture = true;
    mouseMove(sender, e);
    Focus();
}

System::Void HueSatChoose::mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (Capture)
        Capture = false;
}

System::Void HueSatChoose::mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    if (!Capture) return;

    myColor.Sat = Distance(e->Location) / radius;
    if (myColor.Sat > 1.0) myColor.Sat = 1.0;

    myColor.Hue = AngleFromPoint(e->Location);
    if (myColor.Hue < 0.0) myColor.Hue += 360.0;

    calcMarkerRect();
    ColorChange(this, gcnew ColorChangeEventArgs(myColor));
}

System::Void HueSatChoose::arrowHandler(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
    if (e->Alt || e->Control || e->Shift) return;

    switch (e->KeyCode) {
        case Keys::Up:
            myColor.Hue += 3.6;
            if (myColor.Hue >= 360.0) myColor.Hue -= 360.0;
            break;
        case Keys::Down:
            myColor.Hue -= 3.6;
            if (myColor.Hue < 0.0) myColor.Hue += 360.0;
            break;
        case Keys::Left:
            myColor.Sat -= 0.01;
            if (myColor.Sat < 0.0) myColor.Sat = 0.0;
            break;
        case Keys::Right:
            myColor.Sat += 0.01;
            if (myColor.Sat > 1.0) myColor.Sat = 1.0;
            break;
        default:
            return;
    }

    calcMarkerRect();
    ColorChange(this, gcnew ColorChangeEventArgs(myColor));
}

bool HueSatChoose::IsInputKey(System::Windows::Forms::Keys k)
{
    if (k == Keys::Up || k == Keys::Down || k == Keys::Left || k == Keys::Right)
        return true;

    return Control::IsInputKey(k);
}

System::Void HueSatChoose::paintMe(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
    e->Graphics->DrawImage(colorWheel, 0, 0);

    int darkness = 255 - (int)(myColor.Bright * 255.0 + 0.5);
    SolidBrush^ d = gcnew SolidBrush(Color::FromArgb(darkness, 0, 0, 0));
    e->Graphics->FillPath(d, clipPath);

    if (myColor.Bright > 0.3) {
        e->Graphics->DrawRectangle(markerPen, markerRect);
    } else {
        e->Graphics->DrawRectangle(SystemPens::Window, markerRect);
    }

    if (Focused) {
        e->Graphics->DrawRectangle(focusPen, focusRect);
    }
}

System::Void HueSatChoose::focusHandler(System::Object^ sender, System::EventArgs^ e)
{
    Invalidate();
}

double HueSatChoose::Distance(System::Drawing::Point pt1)
{
    return sqrt((double)((pt1.X - colorCenter.X) * (pt1.X - colorCenter.X) + 
                         (pt1.Y - colorCenter.Y) * (pt1.Y - colorCenter.Y)));
}

double HueSatChoose::AngleFromPoint(System::Drawing::Point pt) 
{
    if (pt.Y == colorCenter.Y && pt.X == colorCenter.X) return 0.0;
    return ::atan2((double)(colorCenter.Y - pt.Y), (double)(pt.X - colorCenter.X))
        * 57.29577951308;
}

System::Drawing::Point HueSatChoose::PointFromAngle(double angle, double sat)
{
    angle = angle / 57.29577951308;

    double x = sat * radius * cos(angle);
    double y = sat * radius * sin(angle);

    return Point(colorCenter.X + (int)x, colorCenter.Y - (int)y);
}

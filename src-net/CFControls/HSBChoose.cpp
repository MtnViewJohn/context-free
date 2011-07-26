// HSBChoose.cpp
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
#include "HSBChoose.h"
#include "HueSatChoose.h"
#include "ColorComponentChoose.h"

using namespace CFControls;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void HSBChoose::MoreInitialization()
{
    this->Resize += gcnew EventHandler(this, &HSBChoose::resizeHandler);
    resizeHandler(this, nullptr);
    brightChooser->CurrentColor = hueSatChooser->CurrentColor;

    ColorChangeEventHandler^ cceh = gcnew ColorChangeEventHandler(this, &HSBChoose::colorHandler);
    hueSatChooser->ColorChange += cceh;
    brightChooser->ColorChange += cceh;
}

System::Void HSBChoose::resizeHandler(System::Object^ sender, EventArgs^ e)
{
    Control^ ctrl = dynamic_cast<Control^>(sender);

    SuspendLayout();

    if (ctrl->Width < (ctrl->Height + ColorComponentChoose::minimumWidth))
        ctrl->Width = ctrl->Height + ColorComponentChoose::minimumWidth;

    hueSatChooser->Location = Point(ctrl->Margin.Left, ctrl->Margin.Top);
    hueSatChooser->Size = System::Drawing::Size(ctrl->Height - ctrl->Margin.Vertical, 
        ctrl->Height - ctrl->Margin.Vertical);
    brightChooser->Location = Point(ctrl->Margin.Left + ctrl->Height - 
        ctrl->Margin.Vertical + ctrl->Padding.Horizontal, ctrl->Margin.Top);
    brightChooser->Size = System::Drawing::Size(ctrl->Width - ctrl->Margin.Left - 
        ctrl->Height + ctrl->Margin.Vertical - ctrl->Padding.Horizontal - ctrl->Margin.Right, 
        ctrl->Height - ctrl->Margin.Vertical);

    ResumeLayout();
}

System::Void HSBChoose::colorHandler(System::Object^ sender, ColorChangeEventArgs^ e)
{
    if (ReferenceEquals(sender, hueSatChooser)) {
        brightChooser->CurrentColor = e->newHSBColor;
    } else {
        hueSatChooser->CurrentColor = e->newHSBColor;
    }

    OnColorChange(e);
}

void HSBChoose::OnColorChange(ColorChangeEventArgs^ e)
{
    //if (ColorChange)
        ColorChange(this, e);
}


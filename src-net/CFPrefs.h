// CFPrefs.h
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

#pragma once

#include "PreferenceManager.h"

namespace ContextFreeNet {
    public ref class CFPrefs : public OzoneUtil::PreferenceManager
    {
    public:
        CFPrefs()
            : OzoneUtil::PreferenceManager("Software\\OzoneSoft\\ContextFree\\Settings", false)
        { }

    protected:
        ~CFPrefs()
        { }

    public:
        enum class OpenAction { Welcome = 0, New = 1, Nothing = 2 };
        property bool AnimateZoom {
            void set(bool setTo) { SetPrefBool("AnimateZoom", setTo); }
            bool get() { return GetPrefBool("AnimateZoom", true); }
        }
        property bool ProgressiveRender {
            void set(bool setTo) { SetPrefBool("ProgressiveRender", setTo); }
            bool get() { return GetPrefBool("ProgressiveRender", true); }
        }
        property bool DontDisplay {
            void set(bool setTo) { SetPrefBool("DontDisplay", setTo); }
            bool get() { return GetPrefBool("DontDisplay", false); }
        }
        property bool ImageCrop {
            void set(bool setTo) { SetPrefBool("ImageCrop", setTo); }
            bool get() { return GetPrefBool("ImageCrop", true); }
        }
        property bool ImageAppendVariation {
            void set(bool setTo) { SetPrefBool("ImageAppendVariation", setTo); }
            bool get() { return GetPrefBool("ImageAppendVariation", false); }
        }
        property bool RenderOnOpen {
            void set(bool setTo) { SetPrefBool("RenderOnOpen", setTo); }
            bool get() { return GetPrefBool("RenderOnOpen", true); }
        }
        property double BorderWidth {
            void set(double setTo) { SetPrefDouble("BorderWidth", setTo); }
            double get() { return GetPrefDouble("BorderWidth", 2.0); }
        }
        property double MinimumSize {
            void set(double setTo) { SetPrefDouble("MinimumSize", setTo); }
            double get() { return GetPrefDouble("MinimumSize", 0.3); }
        }
        property int AnimateLength {
            void set(int setTo) { SetPrefInt("AnimateLength", setTo); }
            int get() { return GetPrefInt("AnimateLength", 10); }
        }
        property int AnimateFrameRate {
            void set(int setTo) { SetPrefInt("AnimateFPS", setTo); }
            int get() { return GetPrefInt("AnimateFPS", 15); }
        }
        property int JPEGQuality {
            void set(int setTo) { SetPrefInt("JPEGQuality", setTo); }
            int get() { return GetPrefInt("JPEGQuality", 90); }
        }
        property int RenderHeight {
            void set(int setTo) { SetPrefInt("RenderHeight", setTo); }
            int get() { return GetPrefInt("RenderHeight", 1000); }
        }
        property int RenderWidth {
            void set(int setTo) { SetPrefInt("RenderWidth", setTo); }
            int get() { return GetPrefInt("RenderWidth", 1000); }
        }
        property int FormHeight {
            void set(int setTo) { SetPrefInt("FormHeight", setTo); }
            int get() { return GetPrefInt("FormHeight", 715); }
        }
        property int FormWidth {
            void set(int setTo) { SetPrefInt("FormWidth", setTo); }
            int get() { return GetPrefInt("FormWidth", 1100); }
        }
        property double EditorSplitter {
            void set(double setTo) { SetPrefDouble("EditorSplitter", setTo); }
            double get() { return GetPrefDouble("EditorSplitter", 0.80); }
        }
        property double DocumentSplitter {
            void set(double setTo) { SetPrefDouble("DocumentSplitter", setTo); }
            double get() { return GetPrefDouble("DocumentSplitter", 0.33); }
        }
        property OpenAction StartupDocument {
            void set(OpenAction setTo) { SetPrefInt("StartupDocument", (int)setTo); }
            OpenAction get() { return (OpenAction)GetPrefInt("StartupDocument", (int)OpenAction::Welcome); }
        }
        property bool SkipAccount {
            void set(bool setTo) { SetPrefBool("SkipAccount", setTo); }
            bool get() { return GetPrefBool("SkipAccount", false); }
        }
        property System::String^ GalUsername {
            void set(System::String^ setTo) { SetPrefString("GalUsername", setTo); }
            System::String^ get() { return GetPrefString("GalUsername", "please specify"); }
        }
        property System::String^ GalPassword {
            void set(System::String^ setTo) { SetPrefString("GalPassword", setTo); }
            System::String^ get() { return GetPrefString("GalPassword", ""); }
        }
        property System::String^ ccLicense {
            void set(System::String^ setTo) { SetPrefString("ccLicense", setTo); }
            System::String^ get() { return GetPrefString("ccLicense", ""); }
        }
        property System::String^ ccImage {
            void set(System::String^ setTo) { SetPrefString("ccImage", setTo); }
            System::String^ get() { return GetPrefString("ccImage", ""); }
        }
        property System::String^ ccName {
            void set(System::String^ setTo) { SetPrefString("ccName", setTo); }
            System::String^ get() { return GetPrefString("ccName", ""); }
        }
        property System::Drawing::Font^ TextFont {
            void set(System::Drawing::Font^ setTo)
            {
                try {
                    System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream();
                    System::Runtime::Serialization::Formatters::Binary::BinaryFormatter^ fmt = 
                        gcnew System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();
                    fmt->Serialize(ms, setTo);
                    SetPrefBinary("TextFont", ms->GetBuffer());
                } catch (System::Runtime::Serialization::SerializationException^ e) {
                    System::Console::WriteLine("Failed to serialize. Reason: {0}", e->Message );
                }
            }
            System::Drawing::Font^ get() {
                array<System::Byte>^ data = GetPrefBinary("TextFont", nullptr);

                if (data != nullptr) {
                    try {
                        System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(data, false);
                        System::Runtime::Serialization::Formatters::Binary::BinaryFormatter^ fmt = 
                            gcnew System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();
                        return dynamic_cast<System::Drawing::Font^>(fmt->Deserialize(ms));
                    } catch (System::Runtime::Serialization::SerializationException^ e) {
                        System::Console::WriteLine("Failed to deserialize. Reason: {0}", e->Message );
                    }
                }

                return gcnew System::Drawing::Font("Microsoft Sans Serif", 8.0);
            }
        }
    } ;
}

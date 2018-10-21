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
        // These random bytes are courtesy of http://www.fourmilab.ch/hotbits/
        static array<System::Byte>^ CFentropy = {
            210, 61, 229, 177, 254, 52, 150, 62, 81, 246, 248, 185, 59, 89, 93, 117,
            142, 120, 64, 79, 229, 71, 195, 27, 181, 140, 195, 78, 123, 167, 45,
            224, 108, 172, 164, 130, 68, 64, 103, 98, 136, 132, 14, 3, 240, 232,
            152, 220, 29, 154, 78, 181, 92, 109, 92, 176, 46, 128, 13, 79, 108, 144,
            83, 219, 42, 161, 158, 81, 213, 120, 13, 198, 163, 40, 14, 135, 30, 13,
            117, 128, 172, 184, 61, 69, 50, 233, 116, 202, 161, 204, 223, 52, 126,
            151, 223, 14, 123, 12, 29, 100, 71, 22, 247, 41, 231, 97, 116, 58, 168,
            125, 92, 26, 4, 3, 228, 182, 204, 43, 185, 79, 118, 137, 173, 163, 215,
            111, 60, 253
        };
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
        property int AnimateHeight {
            void set(int setTo) { SetPrefInt("AnimateHeight", setTo); }
            int get() { return GetPrefInt("AnimateHeight", 480); }
        }
        property int AnimateWidth {
            void set(int setTo) { SetPrefInt("AnimateWidth", setTo); }
            int get() { return GetPrefInt("AnimateWidth", 640); }
        }
        property int AnimateLength {
            void set(int setTo) { SetPrefInt("AnimateLength", setTo); }
            int get() { return GetPrefInt("AnimateLength", 10); }
        }
        property int AnimateFrameRate {
            void set(int setTo) { SetPrefInt("AnimateFPS", setTo); }
            int get() { return GetPrefInt("AnimateFPS", 15); }
        }
        property int AnimateCodec {
            void set(int setTo) { SetPrefInt("AnimateCodec", setTo); }
            int get() { return GetPrefInt("AnimateCodec", 0); }
        }
        property bool AnimatePreview {
            void set(bool setTo) { SetPrefBool("AnimatePreview", setTo); }
            bool get() { return GetPrefBool("AnimatePreview", true); }
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
        property int EditorSplitter {
            void set(int setTo) { SetPrefInt("EditorSplitterInt", setTo); }
            int get() { return GetPrefInt("EditorSplitterInt", 600); }
        }
        property int DocumentSplitter {
            void set(int setTo) { SetPrefInt("DocumentSplitterInt", setTo); }
            int get() { return GetPrefInt("DocumentSplitterInt", 300); }
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
            void set(System::String^ setTo) { SetPrefProtectedString("GalPassword", CFentropy, setTo); }
            System::String^ get() { return GetPrefProtectedString("GalPassword", CFentropy, nullptr); }
        }
        property System::String^ GalPasswordCleartext {
            // No setter, destructive getter
            System::String^ get()
            { 
                System::String^ ret = GetPrefString("GalPassword", nullptr);
                if (ret)
                    DeletePref("GalPassword");
                return ret;
            }
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
        property int TabWidth {
            void set(int setTo) { SetPrefInt("TabWidth", setTo); }
            int get() { return GetPrefInt("TabWidth", 4); }
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
        property bool StyleDefaultBold {
            void set(bool setTo) { SetPrefBool("StyleDefaultBold", setTo); }
            bool get() { return GetPrefBool("StyleDefaultBold", false); }
        }
        property bool StyleCommentsBold {
            void set(bool setTo) { SetPrefBool("StyleCommentsBold", setTo); }
            bool get() { return GetPrefBool("StyleCommentsBold", false); }
        }
        property bool StyleSymbolsBold {
            void set(bool setTo) { SetPrefBool("StyleSymbolsBold", setTo); }
            bool get() { return GetPrefBool("StyleSymbolsBold", false); }
        }
        property bool StyleIdentifiersBold {
            void set(bool setTo) { SetPrefBool("StyleIdentifiersBold", setTo); }
            bool get() { return GetPrefBool("StyleIdentifiersBold", false); }
        }
        property bool StyleKeywordsBold {
            void set(bool setTo) { SetPrefBool("StyleKeywordsBold", setTo); }
            bool get() { return GetPrefBool("StyleKeywordsBold", true); }
        }
        property bool StyleBuiltinsBold {
            void set(bool setTo) { SetPrefBool("StyleBuiltinsBold", setTo); }
            bool get() { return GetPrefBool("StyleBuiltinsBold", true); }
        }
        property bool StyleStringsBold {
            void set(bool setTo) { SetPrefBool("StyleStringsBold", setTo); }
            bool get() { return GetPrefBool("StyleStringsBold", false); }
        }
        property bool StyleNumbersBold {
            void set(bool setTo) { SetPrefBool("StyleNumbersBold", setTo); }
            bool get() { return GetPrefBool("StyleNumbersBold", false); }
        }
        property bool StyleDefaultItalic {
            void set(bool setTo) { SetPrefBool("StyleDefaultItalic", setTo); }
            bool get() { return GetPrefBool("StyleDefaultItalic", false); }
        }
        property bool StyleCommentsItalic {
            void set(bool setTo) { SetPrefBool("StyleCommentsItalic", setTo); }
            bool get() { return GetPrefBool("StyleCommentsItalic", true); }
        }
        property bool StyleSymbolsItalic {
            void set(bool setTo) { SetPrefBool("StyleSymbolsItalic", setTo); }
            bool get() { return GetPrefBool("StyleSymbolsItalic", false); }
        }
        property bool StyleIdentifiersItalic {
            void set(bool setTo) { SetPrefBool("StyleIdentifiersItalic", setTo); }
            bool get() { return GetPrefBool("StyleIdentifiersItalic", false); }
        }
        property bool StyleKeywordsItalic {
            void set(bool setTo) { SetPrefBool("StyleKeywordsItalic", setTo); }
            bool get() { return GetPrefBool("StyleKeywordsItalic", false); }
        }
        property bool StyleBuiltinsItalic {
            void set(bool setTo) { SetPrefBool("StyleBuiltinsItalic", setTo); }
            bool get() { return GetPrefBool("StyleBuiltinsItalic", false); }
        }
        property bool StyleStringsItalic {
            void set(bool setTo) { SetPrefBool("StyleStringsItalic", setTo); }
            bool get() { return GetPrefBool("StyleStringsItalic", false); }
        }
        property bool StyleNumbersItalic {
            void set(bool setTo) { SetPrefBool("StyleNumbersItalic", setTo); }
            bool get() { return GetPrefBool("StyleNumbersItalic", false); }
        }
        property System::String^ StyleDefaultColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleDefaultColor", setTo, "#000"); }
            System::String^ get() { return GetPrefString("StyleDefaultColor", "#000"); }
        }
        property System::String^ StyleCommentsColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleCommentsColor", setTo, "#097BF7"); }
            System::String^ get() { return GetPrefString("StyleCommentsColor", "#097BF7"); }
        }
        property System::String^ StyleSymbolsColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleSymbolsColor", setTo, "#101010"); }
            System::String^ get() { return GetPrefString("StyleSymbolsColor", "#101010"); }
        }
        property System::String^ StyleIdentifiersColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleIdentifiersColor", setTo, "#00567F"); }
            System::String^ get() { return GetPrefString("StyleIdentifiersColor", "#00567F"); }
        }
        property System::String^ StyleKeywordsColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleKeywordsColor", setTo, "#56007F"); }
            System::String^ get() { return GetPrefString("StyleKeywordsColor", "#56007F"); }
        }
        property System::String^ StyleBuiltinsColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleBuiltinsColor", setTo, "#007F00"); }
            System::String^ get() { return GetPrefString("StyleBuiltinsColor", "#007F00"); }
        }
        property System::String^ StyleStringsColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleStringsColor", setTo, "#FFAA3E"); }
            System::String^ get() { return GetPrefString("StyleStringsColor", "#FFAA3E"); }
        }
        property System::String^ StyleNumbersColor {
            void set(System::String^ setTo) { SetPrefColorString("StyleNumbersColor", setTo, "#7F7F00"); }
            System::String^ get() { return GetPrefString("StyleNumbersColor", "#7F7F00"); }
        }
    } ;
}

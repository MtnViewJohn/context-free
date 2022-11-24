#pragma once

namespace CppWrapper
{
    public ref class UploadPrefs
    {
    public:
        System::String^ CfdgName;
        System::String^ CfdgText;
        int Variation;
        System::String^ VariationText;
        bool ImageAppendVariation;
        double JPEGQuality;
        array<double>^ OutputMultiplier;
        System::String^ Username;
        System::String^ Password;
        bool ImageCrop;
        System::String^ ccLicense;
        System::String^ ccImage;
        System::String^ ccName;
        bool Updated;
    };
}

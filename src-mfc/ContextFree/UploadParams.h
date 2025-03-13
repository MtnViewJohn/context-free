#pragma once

#include <string>

class UploadParams
{
public:
    UploadParams();
    static void Load();
    static void Save();
    static void Modify(CString& param, CString v);

    CString cfdgName;
    std::string cfdgText;
    int variation;
    CString variationText;
    int JPEGQuality = 0;
    int Tiled = 0;
    std::pair<int, int> outputMultiplier = { 1, 1 };
    static CString Username;
    static CString Password;
    static CString Salt;
    bool ImageCrop = false;
    static CString ccLicense;
    static CString ccImage;
    static CString ccName;
    static bool Modified;
};


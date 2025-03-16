#include "pch.h"
#include "UploadParams.h"
#include <dpapi.h>
#include "GalleryUpload.h"

CString UploadParams::Username;
CString UploadParams::Password;
CString UploadParams::Salt;
CString UploadParams::ccLicense;
CString UploadParams::ccImage;
CString UploadParams::ccName;
bool UploadParams::Modified = false;

UploadParams::UploadParams()
{
    static bool Loaded = false;
    if (!Loaded) {
        Load();
        Loaded = true;
    }
}

void UploadParams::Load()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    Username = pApp->GetProfileStringW(pszKey, _T("GalleryUsername"), _T(""));
    ccLicense = pApp->GetProfileStringW(pszKey, _T("ccLicense"), _T(""));
    ccImage = pApp->GetProfileStringW(pszKey, _T("ccImage"), _T(""));
    ccName = pApp->GetProfileStringW(pszKey, _T("ccName"), _T(""));
    Salt = pApp->GetProfileStringW(pszKey, _T("Salt"), _T(""));

    if (Salt.GetLength() > 200)
        Salt.Empty();

    BYTE* passwordBin = nullptr;
    UINT passwordBinLength = 0;
    pApp->GetProfileBinary(pszKey, _T("GalleryPassword"), &passwordBin, &passwordBinLength);

    DATA_BLOB passwordBlob{ passwordBinLength, passwordBin };
    DATA_BLOB saltBlob{ (DWORD)Salt.GetLength() * 2, (BYTE*)Salt.LockBuffer() };
    DATA_BLOB outBlob{};

    if (::CryptUnprotectData(&passwordBlob, NULL, &saltBlob, NULL, NULL, 0, &outBlob)) {
        Password = CString(reinterpret_cast<wchar_t*>(outBlob.pbData), outBlob.cbData / 2);
        ::LocalFree(outBlob.pbData);
    } else {
        Password.Empty();
    }
    Salt.UnlockBuffer();

    if (Username.GetLength() < 3 || Username.GetLength() > 20)
        Username.Empty();
    if (!GalleryUpload::Validate(ccName, ccLicense, ccImage)) {
        ccName.Empty(); ccLicense.Empty(); ccImage.Empty();
    }
    if (Password.GetLength() > 200)
        Password.Empty();

    Modified = false;
}

void UploadParams::Save()
{
    CWinApp* pApp = AfxGetApp();

    const TCHAR* pszKey = _T("Settings");

    pApp->WriteProfileStringW(pszKey, _T("GalleryUsername"), Username);
    pApp->WriteProfileStringW(pszKey, _T("ccLicense"), ccLicense);
    pApp->WriteProfileStringW(pszKey, _T("ccImage"), ccImage);
    pApp->WriteProfileStringW(pszKey, _T("ccName"), ccName);

    if (Salt.IsEmpty()) {
        GUID newGuid;
        ::UuidCreate(&newGuid);
        Salt.Format(L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            newGuid.Data1, newGuid.Data2, newGuid.Data3, newGuid.Data4[0], newGuid.Data4[1],
            newGuid.Data4[2], newGuid.Data4[3], newGuid.Data4[4],
            newGuid.Data4[5], newGuid.Data4[6], newGuid.Data4[7]);
    }
    pApp->WriteProfileStringW(pszKey, _T("Salt"), Salt);

    DATA_BLOB passwordBlob{ (DWORD)Password.GetLength() * 2, (BYTE*)Password.LockBuffer()};
    DATA_BLOB saltBlob{ (DWORD)Salt.GetLength() * 2, (BYTE*)Salt.LockBuffer() };
    DATA_BLOB outBlob{};

    if (::CryptProtectData(&passwordBlob, NULL, &saltBlob, NULL, NULL, 0, &outBlob)) {
        pApp->WriteProfileBinary(pszKey, _T("GalleryPassword"), outBlob.pbData, outBlob.cbData);
        ::LocalFree(outBlob.pbData);
    }
    Password.UnlockBuffer();
    Salt.UnlockBuffer();

    Modified = false;
}

void UploadParams::Modify(CString& param, CString v)
{
    if (param != v) {
        param = v;
        Modified = true;
    }
}

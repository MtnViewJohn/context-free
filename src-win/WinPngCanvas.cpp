// WinPngCanvas.cpp
// Context Free
// ---------------------
// Copyright (C) 2026 John Horigan - john@glyphic.com
//

#include "WinPngCanvas.h"
#include <shlwapi.h>
#include <io.h>
#include <format>
#include <string>

bool WinPngCanvas::completeMovie(int fps, int loops, OutputFormat fmt, QTcodec codec, bool alpha)
{
    TCHAR szFileName[MAX_PATH];
    ::GetModuleFileNameW(NULL, szFileName, MAX_PATH);
    ::PathRemoveFileSpecW(szFileName);
    ::PathAppendW(szFileName, L"ffmpeg.exe");
    std::wstring wtempdir = pngCanvas::mbstowcs(mTempDirectory);
    std::wstring wtempfile = std::format(L"{}\\outfile.mov", wtempdir);
    std::wstring cmdline;

    if (fmt == pngCanvas::GIFfile) {
        if (loops == 1)
            loops = -1;
        if (loops > 1)
            --loops;

        wtempfile = std::format(L"{}\\outfile.gif", wtempdir);
        cmdline = std::format(L"ffmpeg.exe -hide_banner -framerate {} -i %04d.png -vf \"split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse\" -loop {} outfile.gif",
            fps, loops);
    } else {
        if (codec == pngCanvas::H264) {
            cmdline = std::format(L"ffmpeg.exe -hide_banner -framerate {} -i %04d.png -vcodec libx264 -preset slow -crf 20.0 outfile.mov",
                fps);
        } else {
            if (alpha)
                cmdline = std::format(L"ffmpeg.exe -hide_banner -framerate {} -i %04d.png -c:v prores_ks -profile:v 4 -vendor apl0 -pix_fmt yuva444p10le outfile.mov",
                    fps);
            else
                cmdline = std::format(L"ffmpeg.exe -hide_banner  -framerate {} -i %04d.png -c:v prores_ks -profile:v 2 -vendor apl0 -pix_fmt yuv422p10le outfile.mov",
                    fps);
        }
    }

    PROCESS_INFORMATION processInfo;
    STARTUPINFOW startupInfo = { sizeof(STARTUPINFO) };
    if (::CreateProcessW(szFileName, cmdline.data(), NULL, NULL, FALSE,
        0, NULL, wtempdir.c_str(), &startupInfo, &processInfo) &&
        !::WaitForSingleObject(processInfo.hProcess, INFINITE) &&
        ::PathFileExistsW(wtempfile.c_str()))
    {
        std::wstring outfile = pngCanvas::mbstowcs(mOrigName);
        ::MoveFileExW(wtempfile.c_str(), outfile.c_str(), MOVEFILE_REPLACE_EXISTING);
    } else {
        return false;
    }

    return true;
}

FILE* WinPngCanvas::makeTemp(int frame)
{
    FILE* fp = nullptr;
    if (frame) {
        if (!mTempDirectory.empty()) {
            mFileName = std::format("{}\\{:04d}.png",
                mTempDirectory, frame - 1);
            if (fopen_s(&fp, mFileName.c_str(), "wb") == 0)
                return fp;
        }
    } else {
        auto wTemplate = std::format(L"{}\\cfdg_temp_image_XXXXXX",
            mSystem.tempFileDirectory());
        mFileName = pngCanvas::wcstomsb(wTemplate);
        if (_mktemp_s(mFileName.data(), mFileName.length() + 1) == 0 &&
            fopen_s(&fp, mFileName.c_str(), "wb") == 0)
        {
            return fp;
        }
    }
    return nullptr;
}

bool WinPngCanvas::ffAvailable()
{
    TCHAR szFileName[MAX_PATH];
    ::GetModuleFileNameW(NULL, szFileName, MAX_PATH);
    ::PathRemoveFileSpecW(szFileName);
    ::PathAppendW(szFileName, L"ffmpeg.exe");
    return ::PathFileExistsW(szFileName);
}

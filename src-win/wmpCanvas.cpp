// wmpCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
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

#include "wmpCanvas.h"
#include "WinSystem.h"
#include <windows.h>
#include <wmsdk.h>
#include <wmsysprf.h>

#ifndef WMFORMAT_SDK_VERSION
#define WMFORMAT_SDK_VERSION WMT_VER_9_0
#endif


class wmpCanvas::Impl
{
private:
    Impl(wchar_t* name, int fps, WinCanvas* c);
    ~Impl();

    HRESULT addFrame();

    const char*         mErrorMsg;
    char*               mBits;
    IWMProfile*			mWMProfile;
    IWMWriter*			mWMWriter;
    IWMInputMediaProps*	mVideoProps;
    IWMProfileManager*	mWMProfileManager;
    HDC					mmvDC;
    DWORD				mVideoInput;
    DWORD				mCurrentVideoSample;
    QWORD				mVideoTime;
    DWORD				mFrameRate;				// Frames Per Second Rate (FPS)
    bool                mWritten;
    BITMAPINFOHEADER	mBmpInfo;
    RGBQUAD             mGrayPalette[256];

    friend class wmpCanvas;
};

wmpCanvas::Impl::Impl(wchar_t* name, int fps, WinCanvas* c)
: mErrorMsg(NULL), mBits(c->mBM), mWMProfile(NULL), mWMWriter(NULL), 
  mVideoProps(NULL), mWMProfileManager(NULL), mmvDC(NULL), mVideoInput(0), 
  mCurrentVideoSample(0), mFrameRate(fps), mWritten(false)
{
    CoInitialize(NULL);

    const GUID& guidProfileID = WMProfile_V80_BESTVBRVideo;
    IWMProfileManager2	*profileManager2 = NULL;

    if (FAILED(WMCreateProfileManager(&mWMProfileManager))) {
        mErrorMsg = "Unable to Create WindowsMedia Profile Manager";
        return;
    }

    if (FAILED(mWMProfileManager->QueryInterface(IID_IWMProfileManager2,
                                                 (void**)&profileManager2)))
    {
        mErrorMsg = "Unable to Query Interface for ProfileManager2";
        return;
    }

    HRESULT	hr = profileManager2->SetSystemProfileVersion(WMFORMAT_SDK_VERSION);
    profileManager2->Release();
    if (FAILED(hr)) {
        mErrorMsg = "Unable to Set System Profile Version";
        return;
    }

    if (FAILED(mWMProfileManager->LoadProfileByID(guidProfileID, &mWMProfile))) {
        mErrorMsg = "Unable to Load System Profile";
        return;
    }

    DWORD cnt = 0;
    IWMStreamConfig* streamConfig = NULL;
    hr = mWMProfile->CreateNewStream(WMMEDIATYPE_Video, &streamConfig);
    hr = mWMProfile->GetStreamCount(&cnt);

    hr = streamConfig->SetBitrate(c->mHeight * c->mStride * fps * 8);
    hr = streamConfig->SetBufferWindow(0);
    hr = streamConfig->SetStreamNumber(cnt);

    hr = mWMProfile->AddStream(streamConfig);

    if (FAILED(WMCreateWriter(NULL, &mWMWriter))) {
        mErrorMsg = "Unable to Create Media Writer Object";
        return;
    }

    if (FAILED(mWMWriter->SetProfile(mWMProfile))) {
        mErrorMsg = "Unable to Set System Profile";
        return;
    }

    DWORD	inputCount = 0;
    if (FAILED(mWMWriter->GetInputCount(&inputCount))) {
        mErrorMsg = "Unable to Get input count For Profile";
        return;
    }

    for (DWORD i = 0; i < inputCount; ++i) {
        IWMInputMediaProps* inputProps = NULL;
        GUID    guidInputType;
        if (FAILED(mWMWriter->GetInputProps(i, &inputProps))) {
            mErrorMsg = "Unable to GetInput Properties";
            return;
        }
        if (FAILED(inputProps->GetType(&guidInputType))) {
            mErrorMsg = "Unable to Get Input Property Type";
            return;
        }
        if (guidInputType == WMMEDIATYPE_Video) {
            mVideoProps = inputProps;
            mVideoInput = i;
            break;
        } else {
            inputProps->Release();
        }
    }

    if (mVideoProps == NULL) {
        mErrorMsg = "Profile Does not Accept Video input";
        return;
    }

    if (FAILED(mWMWriter->SetOutputFilename(name))) {
        mErrorMsg = "Unable to Set Output Filename";
        return;
    }

    mmvDC = CreateCompatibleDC(NULL);
    if (mmvDC == NULL) {
        mErrorMsg = "Unable to Create Device Context";
        return;
    }

    int	maxWidth  = GetSystemMetrics(SM_CXSCREEN);
    int maxHeight = GetSystemMetrics(SM_CYSCREEN);

    ZeroMemory(&mBmpInfo, sizeof(BITMAPINFOHEADER));
    mBmpInfo.biSize = sizeof(BITMAPINFOHEADER);
    mBmpInfo.biBitCount = 8 * aggCanvas::BytesPerPixel[c->mPixelFormat];
    mBmpInfo.biWidth = min(c->mWidth, maxWidth);
    mBmpInfo.biHeight = min(c->mHeight, maxHeight);	
    mBmpInfo.biCompression = BI_RGB;
    mBmpInfo.biPlanes = 1;
    mBmpInfo.biSizeImage = c->mHeight * c->mStride;
    mBmpInfo.biClrUsed = 0;
    mBmpInfo.biClrImportant = 0;

    struct videoInfoType {
        WMVIDEOINFOHEADER   info;
        RGBQUAD             grayPalette[256];
    };

    videoInfoType	videoInfo;
    videoInfo.info.rcSource.left	= 0;
    videoInfo.info.rcSource.top		= 0;
    videoInfo.info.rcSource.right	= mBmpInfo.biWidth;
    videoInfo.info.rcSource.bottom	= mBmpInfo.biHeight;
    videoInfo.info.rcTarget			= videoInfo.info.rcSource;
    videoInfo.info.rcTarget.right	= videoInfo.info.rcSource.right;
    videoInfo.info.rcTarget.bottom	= videoInfo.info.rcSource.bottom;
    videoInfo.info.dwBitRate        = mBmpInfo.biWidth * mBmpInfo.biHeight * 
                                      mBmpInfo.biBitCount * mFrameRate;
    videoInfo.info.dwBitErrorRate	= 0;
    videoInfo.info.AvgTimePerFrame	= ((QWORD)1) * 10000 * 1000 / mFrameRate;
    memcpy(&(videoInfo.info.bmiHeader), &mBmpInfo, sizeof(BITMAPINFOHEADER));

    for (int i = 0; i < 256; ++i) {
        mGrayPalette[i].rgbBlue = 
            mGrayPalette[i].rgbGreen = 
            mGrayPalette[i].rgbRed = i;
        mGrayPalette[i].rgbReserved = 0;
        videoInfo.grayPalette[i].rgbBlue = 
            videoInfo.grayPalette[i].rgbGreen = 
            videoInfo.grayPalette[i].rgbRed = i;
        videoInfo.grayPalette[i].rgbReserved = 0;
    }

    WM_MEDIA_TYPE mt;
    mt.majortype = WMMEDIATYPE_Video;
    switch (mBmpInfo.biBitCount) {
        case 32:
            mt.subtype = WMMEDIASUBTYPE_RGB32;
            break;
        case 24:
            mt.subtype = WMMEDIASUBTYPE_RGB24;
            break;
        case 8:
            mt.subtype = WMMEDIASUBTYPE_RGB8;
            break;
        default:
            mt.subtype = GUID_NULL;
            break;
    }
    mt.bFixedSizeSamples	= true;
    mt.bTemporalCompression	= false;
    mt.lSampleSize			= 0;
    mt.formattype			= WMFORMAT_VideoInfo;
    mt.pUnk					= NULL;
    mt.cbFormat				= sizeof(videoInfoType);
    mt.pbFormat				= (BYTE*)&videoInfo;

    if (FAILED(mVideoProps->SetMediaType(&mt))) {
        mErrorMsg = "Unable to Set Media Type";
        return;
    }

    if (FAILED(mWMWriter->SetInputProps(mVideoInput, mVideoProps))) {
        mErrorMsg = "Unable to Set Input Properties for Media Writer";
        return;
    }

    hr = mWMWriter->BeginWriting();
    if (FAILED(hr)) {
        mErrorMsg = "Unable to Initialize Writing";
        return;
    }

    mWritten = true;
}

wmpCanvas::Impl::~Impl()
{
    if (mWritten && mWMWriter)
        mWMWriter->EndWriting();	

    if (mVideoProps) {
        mVideoProps->Release();
        mVideoProps = NULL;
    }

    if (mWMWriter) {
        mWMWriter->Release();
        mWMWriter = NULL;
    }

    if (mWMProfile) {
        mWMProfile->Release();
        mWMProfile = NULL;
    }

    if (mWMProfileManager) {
        mWMProfileManager->Release();
        mWMProfileManager = NULL;
    }

    if (mmvDC) {
        DeleteDC(mmvDC);
        mmvDC = NULL;
    }

    CoUninitialize();
}

HRESULT
wmpCanvas::Impl::addFrame()
{
    INSSBuffer		*sample = NULL;
    BYTE			*buffer = NULL;
    DWORD			bufferLength = 0;

    if (FAILED(mWMWriter->AllocateSample(mBmpInfo.biSizeImage, &sample))) {
        mErrorMsg = "Unable to Allocate Memory";
        return E_FAIL;
    }

    if (FAILED(sample->GetBufferAndLength(&buffer, &bufferLength))) {
        mErrorMsg = "Unable to Lock Buffer";
        if (sample)
            sample->Release();
        return E_FAIL;
    }

    memcpy(buffer, mBits, mBmpInfo.biSizeImage);

    HRESULT hr = mWMWriter->WriteSample(mVideoInput, 10000 * mVideoTime, 0, sample);
    mVideoTime = (++mCurrentVideoSample * 1000) / mFrameRate;

    if (sample)
        sample->Release();

    if (FAILED(hr)) {
        mErrorMsg = "Unable to Write Frame";
        return hr;
    }

    return S_OK;
}

wmpCanvas::wmpCanvas(WinSystem* sys, wchar_t* name, int fps, 
                     aggCanvas::PixelFormat pixfmt, 
                     int width, int height, agg::rgba bkgrnd)
: WinCanvas(sys, (aggCanvas::PixelFormat)(pixfmt & (~Has_16bit_Color)), 
            width & (~3), -(height & (~3)), bkgrnd), mError(NULL)
{
    impl = new Impl(name, fps, this);
    if (impl->mErrorMsg) {
        mError = impl->mErrorMsg;
        delete impl;
        impl = NULL;
        sys->message("Movie setup failed: %s", mError);
    }
}

wmpCanvas::~wmpCanvas()
{
    delete impl; impl = NULL;
}

void
wmpCanvas::end()
{
    aggCanvas::end();
    if (impl && FAILED(impl->addFrame())) {
        mError = impl->mErrorMsg;
        delete impl;
        impl = NULL;
        mSystem->message("Movie writing failed: %s", mError);
    }
}

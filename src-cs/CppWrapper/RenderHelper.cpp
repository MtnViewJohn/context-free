// RenderHelper.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
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


#include "pch.h"
#include "RenderHelper.h"
#include <Windows.h>
#include "CFscintilla.h"
#include <algorithm>
#include "variation.h"
#include "tiledCanvas.h"
#include "GalleryUploader.h"
#include "upload.h"
#include "WinCanvas.h"
#include "ffCanvas.h"
#include "SVGCanvas.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Windows::Media::Imaging;

namespace CppWrapper {
    public ref class RendererHolder
    {
    public:
        RendererHolder(Renderer* r, WinSystem* sys)
            : renderer(r), winsystem(sys)
        {}
        Renderer* renderer;
        WinSystem* winsystem;
    };

    RenderHelper::RenderHelper(void* editHwnd, void* docHwnd)
    : mEngine(new cfdg_ptr())
    {
        HWND hwnd = (HWND)editHwnd;
        SciPtr = (sptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
        directFunction = (SciFnDirect)SendMessage(hwnd, SCI_GETDIRECTFUNCTION, 0, 0);
        mSystem = new WinSystem((void*)docHwnd);
        renderDeleter = gcnew BackgroundWorker();
        renderDeleter->DoWork += gcnew DoWorkEventHandler(this, &RenderHelper::DeleteRenderer);
    }

    void
    RenderHelper::InitWinSystem(void* formHwnd)
    {
        WinSystem::MainWindow = (void*)formHwnd;
    }

    RenderHelper::RenderHelper()
    {
        mSystem = new WinSystem(nullptr);
    }

    RenderHelper::~RenderHelper()
    {
        this->!RenderHelper();
    }

    RenderHelper::!RenderHelper()
    {
        delete SVGcanvas;           SVGcanvas = nullptr;
        delete animationCanvas;     animationCanvas = nullptr;
        delete tempCanvas;          tempCanvas = nullptr;
        delete mCanvas;             mCanvas = nullptr;
        if (mRenderer) {
            renderDeleter->RunWorkerAsync(gcnew RendererHolder(mRenderer, mSystem));
            mRenderer = nullptr;
            mSystem = nullptr;
        } else {
            delete mSystem;             mSystem = nullptr;
        }
        delete mEngine;             mEngine = nullptr;
    }

    void RenderHelper::DeleteRenderer(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
    {
        // Force application to wait for thread to terminate. This prevents
        // temp files from clogging the disk. Renderer::AbortEverything
        // will cause the rest of deletion to bypass
        Threading::Thread::CurrentThread->IsBackground = false;

        RendererHolder^ holder = dynamic_cast<RendererHolder^>(e->Argument);
        if (holder) {
            delete holder->renderer;
            delete holder->winsystem;
            holder->renderer = nullptr;
            holder->winsystem = nullptr;
        }
    }

    cli::array<System::String^>^
    RenderHelper::FindTempFiles()
    {
        WinSystem sys{nullptr};
        auto temps = sys.findTempFiles();
        if (!temps.empty()) {
            cli::array<String^>^ names = gcnew  cli::array<String^>(static_cast<int>(temps.size()));
            int i = 0;
            for (auto&& temp: temps)
                names[i++] = gcnew String(temp.c_str());
            return names;
        } else {
            return nullptr;
        }
    }

    cli::array<System::String^>^
    RenderHelper::GetAutoC()
    {
        std::sort(CFscintilla::AutoComplete.begin(), CFscintilla::AutoComplete.end(), CFscintilla::AutoCmp());
        int sz = static_cast<int>(CFscintilla::AutoComplete.size());
        auto ac = gcnew cli::array<System::String^>(sz);
        for (int i = 0; i < sz; ++i)
            ac[i] = gcnew System::String(CFscintilla::AutoComplete[i]);
        return ac;
    }

    void
    RenderHelper::StyleLines(Sci_Position startLine, Sci_Position endLine)
    {
        CFscintilla::StyleLines(directFunction, SciPtr, startLine, endLine);
    }

    System::String^
    RenderHelper::GetMessage(IntPtr wParam)
    {
        char* msg = (char*)wParam.ToPointer();
        String^ msgText = gcnew String(msg, 0, static_cast<int>(strlen(msg)), System::Text::Encoding::UTF8);
        delete[] msg;
        return msgText;
    }

    RenderStats
    RenderHelper::GetStats(IntPtr wParam)
    {
        WinSystem::Stats* stat = (WinSystem::Stats*)wParam.ToPointer();
        if (stat == nullptr) {
            RenderStats rs = { true };
            return rs;
        }
        RenderStats rs = {
            false,
            stat->shapeCount,
            stat->toDoCount,
            stat->inOutput,
            stat->fullOutput,
            stat->finalOutput,
            stat->showProgress,
            stat->outputCount,
            stat->outputDone,
            stat->outputTime,
            stat->animating
        };
        return rs;
    }


    int 
    RenderHelper::VariationFromString(System::String^ s)
    {
        auto u8var = System::Text::Encoding::UTF8->GetBytes(s);
        if (u8var->Length == 0)
            return -1;
        pin_ptr<Byte> pinnedVar = &u8var[0];
        return Variation::fromString(reinterpret_cast<const char*>(pinnedVar));
    }

    System::String^
    RenderHelper::VariationToString(int v)
    {
        return gcnew String(Variation::toString(v, false).c_str());
    }

    int 
    RenderHelper::RandomVariation(int length)
    {
        return Variation::random(length);
    }

    void 
    RenderHelper::RunRenderThread(RenderParameters^ rp)
    {
        switch (rp->action) {
        case RenderParameters::RenderActions::Animate:
            if (rp->animateFrame) {
                mRenderer->animate(mCanvas, rp->animateFrameCount,
                    rp->frame, rp->animateZoom && !Tiled);
            } else {
                mRenderer->animate(animationCanvas, rp->animateFrameCount, 0,
                    rp->animateZoom && !Tiled);

                delete animationCanvas;
                animationCanvas = nullptr;
            }
            break;
        case RenderParameters::RenderActions::SaveSVG:
            mRenderer->draw(SVGcanvas);
            delete SVGcanvas;
            SVGcanvas = nullptr;
            break;
        case RenderParameters::RenderActions::Render:
            mRenderer->run(mCanvas, rp->periodicUpdate);
            if (!mCanvas && !mRenderer->requestStop) {
                MakeCanvas(rp->width, rp->height);
                mRenderer->draw(mCanvas);
            }
            break;
        }
    }

    void RenderHelper::RequestUpdate()
    {
        if (mRenderer != nullptr)
            mRenderer->requestUpdate = true;
    }

    bool
    RenderHelper::SyncToSystem(String^ name, String^ cfdg)
    {
        array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(cfdg);
        array<Byte>^ encodedName = System::Text::Encoding::UTF8->GetBytes(name);
        array<Byte>^ zero = { '\0' };
        if (encodedCfdg->Length == 0) encodedCfdg = zero;
        if (encodedName->Length == 0) encodedName = zero;

        // prevent GC moving the bytes around while this variable is on the stack
        pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];
        pin_ptr<Byte> pinnedName = &encodedName[0];

        return mSystem->updateInfo(reinterpret_cast<const char*>(pinnedName),
                                   reinterpret_cast<const char*>(pinnedCfdg));
    }

    void RenderHelper::AbortEverything()
    {
        ::Renderer::AbortEverything = true;
    }

    String^
    RenderHelper::GetExample(String^ name)
    {
        array<Byte>^ encodedName = System::Text::Encoding::UTF8->GetBytes(name);
        pin_ptr<Byte> pinnedName = &encodedName[0];
        std::string nameStr{ reinterpret_cast<const char*>(pinnedName) };

        auto example = AbstractSystem::ExamplesMap.find(nameStr);
        if (example != AbstractSystem::ExamplesMap.end()) {
            auto [v3cfdg, v2cfdg] = example->second;
            auto cfdg = mSystem->cfdgVersion == 2 ? v2cfdg : v3cfdg;
            return gcnew String(cfdg, 0, (int)std::strlen(cfdg), System::Text::Encoding::UTF8);
        } else {
            return nullptr;
        }

    }

    bool
    RenderHelper::IsExample(String^ name)
    {
        array<Byte>^ encodedName = System::Text::Encoding::UTF8->GetBytes(name);
        pin_ptr<Byte> pinnedName = &encodedName[0];
        std::string nameStr{ reinterpret_cast<const char*>(pinnedName) };

        return AbstractSystem::ExamplesMap.find(nameStr) != AbstractSystem::ExamplesMap.end();
    }

    void
    RenderHelper::PrepareForRender(int width, int height, double minSize, double border, 
        int variation, bool shrinkTiled)
    {
        if (mRenderer) {
            renderDeleter->RunWorkerAsync(gcnew RendererHolder(mRenderer, nullptr));
            mRenderer = nullptr;
        }
        mEngine->reset();
        delete mCanvas; mCanvas = nullptr;

        *mEngine = CFDG::ParseFile(mSystem->mName.c_str(), mSystem, variation);
        if (!(*mEngine))
            return;

        if (shrinkTiled && (*mEngine)->isTiledOrFrieze()) {
            width = (9 * width) / 10;
            height = (9 * height) / 10;
        }

        mRenderer = (*mEngine)->renderer(*mEngine, width, height,
            (float)minSize, variation, border).release();

        if (mRenderer == nullptr)
            mEngine->reset();
    }

    void
    RenderHelper::MakeCanvas(int width, int height)
    {
        if (mCanvas) return;
        mCanvas = new WinCanvas(mSystem, WinCanvas::SuggestPixelFormat(mEngine->get()),
            width, height, (*mEngine)->getBackgroundColor());
    }

    System::String^
    RenderHelper::MakeAnimationCanvas(RenderParameters^ renderParams)
    {
        animationCanvas = new ffCanvas("", WinCanvas::SuggestPixelFormat(mEngine->get()),
            renderParams->animateWidth, renderParams->animateHeight,
            renderParams->frameRate, (ffCanvas::QTcodec)renderParams->codec, true);

        if (animationCanvas->mError) {
            String^ msg = gcnew String(animationCanvas->mErrorMsg);
            delete animationCanvas;
            animationCanvas = nullptr;
            return msg;
        } else {
            return gcnew String(animationCanvas->mFileName.c_str());
        }
    }

    bool
    RenderHelper::CanAnimate()
    {
        return ffCanvas::Available();
    }

    bool
    RenderHelper::MakeSVGCanvas(String^ path, int w, int h, UploadPrefs^ prefs)
    {
        if (SVGcanvas) return !SVGcanvas->mError;
        if (mRenderer == nullptr) return false;

        array<Byte>^ pathutf8 = System::Text::Encoding::UTF8->GetBytes(path);
        pin_ptr<Byte> pathutf8pin = &pathutf8[0];
        const char* cpath = reinterpret_cast<const char*>(pathutf8pin);

        SVGcanvas = new SVGCanvas(cpath, w, h, prefs->ImageCrop);
        return !SVGcanvas->mError;
    }

    void
    RenderHelper::UpdateRenderBox(PictureBox^ renderBox, Bitmap^ displayImage, bool noDisplay)
    {
        Graphics^ g = Graphics::FromImage(displayImage);

        if (!mCanvas) {
            g->Clear(Color::White);
            renderBox->Invalidate();
            delete g;
            return;
        }

        System::Drawing::Size destSize = renderBox->Image->Size;
        System::Drawing::Size srcSize = Tiled ? System::Drawing::Size(mCanvas->cropWidth(), mCanvas->cropHeight())
            : System::Drawing::Size(mCanvas->mWidth, mCanvas->mHeight);

        double scale = 1.0;
        agg::rgba8 bk(mCanvas->mBackground);
        Color back = Color::FromArgb(bk.a, bk.r, bk.g, bk.b);
        SolidBrush^ backBrush = nullptr;
        if (mCanvas->mBackground.a < 1.0)
            backBrush = gcnew SolidBrush(back);

        // check if the bitmap is too big and shrink it to fit
        if (srcSize.Width > destSize.Width || srcSize.Height > destSize.Height) {
            double widthScale = (double)destSize.Width / srcSize.Width;
            double heightScale = (double)destSize.Height / srcSize.Height;
            scale = (widthScale < heightScale) ? widthScale : heightScale;
        }

        // scale the bitmap if it is too big
        int scaledWidth = (int)(srcSize.Width * scale);
        int scaledHeight = (int)(srcSize.Height * scale);

        // center the scaled bitmap
        int originX = (destSize.Width - scaledWidth) / 2;
        int originY = (destSize.Height - scaledHeight) / 2;

        // Draw the bitmap scaled
        System::Drawing::Rectangle destRect(originX, originY, scaledWidth, scaledHeight);
        if (backBrush) {
            System::Drawing::Rectangle fullRect(0, 0, destSize.Width, destSize.Height);
            DrawCheckerBoard(g, fullRect);
            g->FillRectangle(backBrush, fullRect);
        } else {
            g->Clear(back);
        }

        if (noDisplay) {
            renderBox->Invalidate();
            delete g;
            return;
        }

        Bitmap^ newBitmap = MakeBitmap(Tiled, mCanvas);
        if (newBitmap == nullptr) {
            delete g;
            delete tempCanvas;
            tempCanvas = nullptr;
            return;
        }

        g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;

        if (Tiled && scale == 1.0) {
            DrawTiled(newBitmap, displayImage, g, originX, originY);
        } else {
            if (mCanvas->mBackground.a < 1.0 || (*mEngine)->usesBlendMode)
                DrawCheckerBoard(g, destRect);
            if (scale == 1.0) {
                g->DrawImageUnscaled(newBitmap, originX, originY);
            } else {
                g->DrawImage(newBitmap, destRect,
                    0, 0, srcSize.Width, srcSize.Height,
                    System::Drawing::GraphicsUnit::Pixel);
            }
        }

        System::Drawing::Pen^ p2 = gcnew System::Drawing::Pen(Color::Black, 1.0);
        p2->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
        g->DrawRectangle(p2, originX - 1, originY - 1, scaledWidth + 1, scaledHeight + 1);

        delete newBitmap;
        delete g;
        delete tempCanvas;
        tempCanvas = nullptr;

        renderBox->Invalidate();
    }

    bool
    RenderHelper::PerformRender(System::ComponentModel::BackgroundWorker^ renderThread)
    {
        if (!mCanvas || mCanvas->mWidth > 0) {
            renderThread->RunWorkerAsync();
            return true;
        } else {
            delete mCanvas;
            mCanvas = nullptr;
            return false;
        }
    }


    Bitmap^
    RenderHelper::MakeBitmap(bool cropped, WinCanvas* canvas)
    {
        if (canvas->mPixelFormat & aggCanvas::Has_16bit_Color) {
            delete tempCanvas;
            tempCanvas = canvas->Make8bitCopy();
            canvas = tempCanvas;
        }

        Bitmap^ bm;
        char* data = (char*)(canvas->bitmap());
        int width = canvas->mWidth;
        int height = canvas->mHeight;
        if (cropped) {
            width = canvas->cropWidth();
            height = canvas->cropHeight();
            data += canvas->mStride * canvas->cropY() +
                aggCanvas::BytesPerPixel.at(canvas->mPixelFormat) * canvas->cropX();
        }

        IntPtr pixelStore = IntPtr((void*)data);

        try {
            switch (canvas->mPixelFormat) {
            case aggCanvas::Gray8_Blend: {
                bm = gcnew Bitmap(width, height, canvas->mStride, Imaging::PixelFormat::Format8bppIndexed, pixelStore);
                Imaging::ColorPalette^ gray = bm->Palette;
                for (int i = 0; i < 256; ++i) {
                    gray->Entries[i] = Color::FromArgb(255, i, i, i);
                }
                bm->Palette = gray;
                break;
            }
            case aggCanvas::RGB8_Blend:
                bm = gcnew Bitmap(width, height, canvas->mStride, Imaging::PixelFormat::Format24bppRgb, pixelStore);
                break;
            case aggCanvas::RGBA8_Blend:
            case aggCanvas::RGBA8_Custom_Blend:
                bm = gcnew Bitmap(width, height, canvas->mStride, Imaging::PixelFormat::Format32bppPArgb, pixelStore);
                break;
            default:
                bm = nullptr;
                break;
            }
        } catch (ArgumentException^) {
            return nullptr;
        }

        return bm;
    }

    void 
    RenderHelper::DrawCheckerBoard(Graphics^ g, System::Drawing::Rectangle destRect)
    {
        SolidBrush^ grayBrush = gcnew SolidBrush(Color::LightGray);
        g->SetClip(destRect, System::Drawing::Drawing2D::CombineMode::Replace);
        g->Clear(Color::White);
        for (int y = destRect.Y & ~7; y <= destRect.Y + destRect.Height; y += 8)
            for (int x = destRect.X & ~7; x <= destRect.X + destRect.Width; x += 8)
                if ((x ^ y) & 8) {
                    g->FillRectangle(grayBrush, x, y, 8, 8);
                }
        g->ResetClip();
    }

    void
    RenderHelper::DrawTiled(Bitmap^ src, Bitmap^ dest, Graphics^ g, int x, int y)
    {
        if (!mRenderer || !mRenderer->m_tiledCanvas)
            return;

        tileList points = mRenderer->m_tiledCanvas->getTessellation(dest->Width, dest->Height,
            x, y, true);

        for (tileList::reverse_iterator pt = points.rbegin(), ept = points.rend();
            pt != ept; ++pt) {
            System::Drawing::Rectangle tileRect(pt->x, pt->y, src->Width, src->Height);
            DrawCheckerBoard(g, tileRect);
            g->DrawImageUnscaled(src, pt->x, pt->y);
        }
    }

    bool RenderHelper::SaveToPNGorJPEG(UploadPrefs^ prefs, String^ path, bool JPEG)
    {
        String^ fileName = path;
        if (prefs->ImageAppendVariation) {
            fileName = Path::GetDirectoryName(path) + "\\" +
                Path::GetFileNameWithoutExtension(path) +
                "-" + prefs->VariationText +
                Path::GetExtension(path);
        }
        try {
            FileStream^ str = gcnew FileStream(fileName, FileMode::Create);
            bool ret = SaveToPNGorJPEG(prefs, str, JPEG);
            str->Close();
            return ret;
        } catch (...) {
            mSystem->message("Cannot write to file.");
            System::Console::Beep();
            return false;
        }
    }

    bool RenderHelper::SaveToPNGorJPEG(UploadPrefs^ prefs, System::IO::Stream^ str, bool JPEG)
    {
        System::Windows::Media::PixelFormat pixfmt = System::Windows::Media::PixelFormats::Pbgra32;
        switch (mCanvas->mPixelFormat) {
        case aggCanvas::Gray8_Blend:
            pixfmt = System::Windows::Media::PixelFormats::Gray8;
            break;
        case aggCanvas::Gray16_Blend:
            pixfmt = System::Windows::Media::PixelFormats::Gray16;
            break;
        case aggCanvas::RGB8_Blend:
            pixfmt = System::Windows::Media::PixelFormats::Bgr24;
            break;
        case aggCanvas::RGB16_Blend:
            pixfmt = System::Windows::Media::PixelFormats::Rgb48;
            break;
        case aggCanvas::RGBA8_Blend:
        case aggCanvas::RGBA8_Custom_Blend:
            break;
        case aggCanvas::RGBA16_Blend:
        case aggCanvas::RGBA16_Custom_Blend:
            pixfmt = System::Windows::Media::PixelFormats::Prgba64;
            break;
        default:
            mSystem->message("Unsupported pixel format.");
            System::Console::Beep();
            return false;
        }

        mSystem->message("Saving image...");

        BitmapEncoder^ encoder = nullptr;
        if (JPEG) {
            JpegBitmapEncoder^ jbe = gcnew JpegBitmapEncoder();
            jbe->QualityLevel = prefs->JPEGQuality;
            encoder = jbe;
        } else {
            encoder = gcnew PngBitmapEncoder();
        }

        bool isTiled = (*mEngine)->isTiled();
        char* data = (char*)(mCanvas->bitmap());
        int srcWidth = mCanvas->mWidth;
        int srcHeight = mCanvas->mHeight;
        if (isTiled || prefs->ImageCrop) {
            srcWidth = mCanvas->cropWidth();
            srcHeight = mCanvas->cropHeight();
            data += mCanvas->mStride * mCanvas->cropY() +
                aggCanvas::BytesPerPixel.at(mCanvas->mPixelFormat) * mCanvas->cropX();
        }
        int destWidth = srcWidth;
        int destHeight = srcHeight;
        if (isTiled && (prefs->OutputMultiplier[0] != 1.0 || prefs->OutputMultiplier[1] != 1.0)) {
            destWidth = (int)(prefs->OutputMultiplier[0] * srcWidth);
            destHeight = (int)(prefs->OutputMultiplier[1] * srcHeight);
        }

        IntPtr pixelStore = IntPtr((void*)data);

        tileList points = { {0, 0} };
        if (mRenderer && mRenderer->m_tiledCanvas)
            points = mRenderer->m_tiledCanvas->getTessellation(destWidth, destHeight,
                (destWidth - srcWidth) / 2, (destHeight - srcHeight) / 2, true);

        try {
            WriteableBitmap^ image = gcnew WriteableBitmap(destWidth, destHeight, 96.0, 96.0, pixfmt, nullptr);

            for (auto point: points) {
                auto rect = System::Windows::Int32Rect(0, 0, srcWidth, srcHeight);
                // Clip sides of source rect that are outside of dest rect
                if (point.x < 0) {
                    rect.X = -point.x;
                    rect.Width += point.x;
                    point.x = 0;
                }
                if (point.x + srcWidth > destWidth)
                    rect.Width -= point.x + srcWidth - destWidth;
                if (point.y < 0) {
                    rect.Y = -point.y;
                    rect.Height += point.y;
                    point.y = 0;
                }
                if (point.y + srcHeight > destHeight)
                    rect.Height -= point.y + srcHeight - destHeight;

                if (rect.Width > 0 && rect.Height > 0)
                    image->WritePixels(rect, pixelStore, srcHeight * mCanvas->mStride,
                        mCanvas->mStride, point.x, point.y);
            }

            encoder->Frames->Add(BitmapFrame::Create(image));

            encoder->Save(str);
            return true;
        } catch (...) {
            mSystem->message("Image save failed.");
            System::Console::Beep();
            return false;
        }
    }

    void RenderHelper::UploadDesign(System::Windows::Forms::Form^ owner, UploadPrefs^ prefs)
    {
        if (!mCanvas) {
            mSystem->message("Nothing to upload, try rendering first.");
            return;
        }
        MemoryStream^ bitmapStream = gcnew MemoryStream();
        if (!SaveToPNGorJPEG(prefs, bitmapStream, false) || bitmapStream->Length == 0) {
            mSystem->message("Upload failed because of image problems.");
            return;
        }

        bool compression = mCanvas->colorCount256() ? Upload::CompressPNG8 : Upload::CompressJPEG;

        array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(prefs->CfdgText);
        pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];

        GalleryUploader toGal(prefs, bitmapStream, (*mEngine)->isFrieze(), (*mEngine)->isTiled(), compression);

        toGal.ShowDialog(owner);
    }

    UploadPrefs^ RenderHelper::DownloadDesign(System::String^ responseBody)
    {
        System::Text::Encoding^ encodeutf8 = System::Text::Encoding::UTF8;
        array<Byte>^ utf8array = encodeutf8->GetBytes(dynamic_cast<String^>(responseBody));
        pin_ptr<Byte> utf8arraypin = &utf8array[0];

        Upload upload(reinterpret_cast<const char*> (utf8arraypin), utf8array->Length);
        if (upload.mId) {
            auto ret = gcnew UploadPrefs();
            String^ path = gcnew System::String(upload.mFileName.c_str(), 0,
                static_cast<int>(upload.mFileName.length()),
                System::Text::Encoding::UTF8);
            ret->CfdgName = Path::GetFileName(path);
            ret->CfdgText = gcnew System::String(upload.mPassword.c_str(), 0,
                static_cast<int>(upload.mPassword.length()),
                System::Text::Encoding::UTF8);
            ret->Variation = upload.mVariation;
            return ret;
        } else {
            return nullptr;
        }
    }
}
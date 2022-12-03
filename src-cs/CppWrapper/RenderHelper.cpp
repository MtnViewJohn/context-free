#include "pch.h"
#include "RenderHelper.h"
#include <Windows.h>
#include "CFscintilla.h"
#include <algorithm>
#include "variation.h"
#include "tiledCanvas.h"
#include "GalleryUploader.h"
#include "upload.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;

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

    RenderHelper::RenderHelper(intptr_t editHwnd, intptr_t docHwnd)
    : mEngine(new cfdg_ptr())
    {
        HWND hwnd = (HWND)editHwnd;
        SciPtr = (sptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
        directFunction = (SciFnDirect)SendMessage(hwnd, SCI_GETDIRECTFUNCTION, 0, 0);
        mSystem = new WinSystem((void*)docHwnd);
        renderDeleter = gcnew BackgroundWorker();
        renderDeleter->DoWork += gcnew DoWorkEventHandler(this, &RenderHelper::deleteRenderer);
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

    void RenderHelper::deleteRenderer(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
    {
        RendererHolder^ holder = dynamic_cast<RendererHolder^>(e->Argument);
        if (holder) {
            delete holder->renderer;
            delete holder->winsystem;
            holder->renderer = nullptr;
            holder->winsystem = nullptr;
        }
    }

    cli::array<System::String^>^
    RenderHelper::findTempFiles()
    {
        auto temps = mSystem->findTempFiles();
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
    RenderHelper::StyleLines(int startLine, int endLine)
    {
        CFscintilla::StyleLines(directFunction, SciPtr, startLine, endLine);
    }

    System::String^
    RenderHelper::getMessage(IntPtr wParam)
    {
        char* msg = (char*)wParam.ToPointer();
        String^ msgText = gcnew String(msg, 0, static_cast<int>(strlen(msg)), System::Text::Encoding::UTF8);
        delete[] msg;
        return msgText;
    }

    RenderStats
    RenderHelper::getStats(IntPtr wParam)
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
    RenderHelper::runRenderThread(RenderParameters^ rp)
    {
        switch (rp->action) {
        case RenderParameters::RenderActions::Animate:
            if (rp->animateFrame) {
                mRenderer->animate(mCanvas, rp->animateFrameCount,
                    rp->frame, rp->animateZoom && !tiled);
            } else {
                mRenderer->animate(animationCanvas, rp->animateFrameCount, 0,
                    rp->animateZoom && !tiled);

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
                int width = rp->action == RenderParameters::RenderActions::Render ?
                    rp->width : rp->animateWidth;
                int height = rp->action == RenderParameters::RenderActions::Render ?
                    rp->height : rp->animateHeight;
                makeCanvas(width, height);
                mRenderer->draw(mCanvas);
            }
            break;
        }
    }

    void RenderHelper::requestUpdate()
    {
        if (mRenderer != nullptr)
            mRenderer->requestUpdate = true;
    }

    bool
    RenderHelper::syncToSystem(String^ name, String^ cfdg)
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
        Renderer::AbortEverything = true;
    }

    String^
    RenderHelper::getExample(String^ name)
    {
        array<Byte>^ encodedName = System::Text::Encoding::UTF8->GetBytes(name);
        pin_ptr<Byte> pinnedName = &encodedName[0];
        std::string nameStr{ reinterpret_cast<const char*>(pinnedName) };

        auto example = AbstractSystem::ExamplesMap.find(nameStr);
        if (example != AbstractSystem::ExamplesMap.end()) {
            auto cfdg = mSystem->cfdgVersion == 2 ? example->second.second : example->second.first;
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
    RenderHelper::prepareForRender(int width, int height, double minSize, double border, 
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
    RenderHelper::makeCanvas(int width, int height)
    {
        if (mCanvas) return;
        mCanvas = new WinCanvas(mSystem, WinCanvas::SuggestPixelFormat(mEngine->get()),
            width, height, (*mEngine)->getBackgroundColor());
    }

    bool
    RenderHelper::makeSVGCanvas(String^ path, int w, int h, UploadPrefs^ prefs)
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
    RenderHelper::updateRenderBox(PictureBox^ renderBox, Bitmap^ displayImage, bool noDisplay)
    {
        Graphics^ g = Graphics::FromImage(displayImage);

        if (!mCanvas) {
            g->Clear(Color::White);
            renderBox->Invalidate();
            delete g;
            return;
        }

        System::Drawing::Size destSize = renderBox->Image->Size;
        System::Drawing::Size srcSize = tiled ? System::Drawing::Size(mCanvas->cropWidth(), mCanvas->cropHeight())
            : System::Drawing::Size(mCanvas->mWidth, mCanvas->mHeight);

        double scale = 1.0;
        SolidBrush^ grayBrush = gcnew SolidBrush(Color::LightGray);
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
            drawCheckerBoard(g, grayBrush, fullRect);
            g->FillRectangle(backBrush, fullRect);
        } else {
            g->Clear(back);
        }

        if (noDisplay) {
            renderBox->Invalidate();
            delete g;
            return;
        }

        Bitmap^ newBitmap = MakeBitmap(tiled, mCanvas);
        if (newBitmap == nullptr) {
            delete g;
            delete tempCanvas;
            tempCanvas = nullptr;
            return;
        }

        g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;

        if (tiled && scale == 1.0) {
            drawTiled(newBitmap, displayImage, g, grayBrush, originX, originY);
        } else {
            if (mCanvas->mBackground.a < 1.0 || (*mEngine)->usesBlendMode)
                drawCheckerBoard(g, grayBrush, destRect);
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
    RenderHelper::performRender(System::ComponentModel::BackgroundWorker^ renderThread)
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
    RenderHelper::drawCheckerBoard(Graphics^ g, SolidBrush^ grayBrush, System::Drawing::Rectangle destRect)
    {
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
    RenderHelper::drawTiled(Bitmap^ src, Bitmap^ dest, Graphics^ g,
        SolidBrush^ grayBrush, int x, int y)
    {
        if (!mRenderer || !mRenderer->m_tiledCanvas)
            return;

        tileList points = mRenderer->m_tiledCanvas->getTessellation(dest->Width, dest->Height,
            x, y, true);

        for (tileList::reverse_iterator pt = points.rbegin(), ept = points.rend();
            pt != ept; ++pt) {
            if (grayBrush) {
                System::Drawing::Rectangle tileRect(pt->x, pt->y, src->Width, src->Height);
                drawCheckerBoard(g, grayBrush, tileRect);
            }
            g->DrawImageUnscaled(src, pt->x, pt->y);
        }
    }

    bool RenderHelper::saveToPNGorJPEG(UploadPrefs^ prefs, String^ path, System::IO::Stream^ str, bool JPEG)
    {
        bool success = true;

        mSystem->message("Saving image...");

        array<Imaging::ImageCodecInfo^>^ codecs = Imaging::ImageCodecInfo::GetImageEncoders();
        Imaging::ImageCodecInfo^ jpegCodec = nullptr;
        for each (Imaging::ImageCodecInfo ^ codec in codecs) {
            if (codec->MimeType->Equals("image/jpeg"))
                jpegCodec = codec;
        }

        if (jpegCodec == nullptr) {
            mSystem->message("Can't seem to find an image encoder.");
            return false;
        }

        Imaging::EncoderParameters^ iParams = gcnew Imaging::EncoderParameters(1);
        long long qual = (long long)(prefs->JPEGQuality);
        iParams->Param[0] = gcnew Imaging::EncoderParameter(Imaging::Encoder::Quality, qual);
        bool isTiled = (*mEngine)->isTiled();

        try {
            Bitmap^ bm = MakeBitmap(isTiled || prefs->ImageCrop, mCanvas);
            if (bm == nullptr)
                throw gcnew ArgumentNullException();

            if (isTiled && (prefs->OutputMultiplier[0] != 1.0 || prefs->OutputMultiplier[1] != 1.0)) {
                Imaging::PixelFormat fmt = bm->PixelFormat;
                if (fmt == Imaging::PixelFormat::Format8bppIndexed)
                    fmt = Imaging::PixelFormat::Format24bppRgb;

                int w = (int)(bm->Width * prefs->OutputMultiplier[0] + 0.5);
                int h = (int)(bm->Height * prefs->OutputMultiplier[1] + 0.5);

                Bitmap^ newBM = gcnew Bitmap(w, h, fmt);
                Graphics^ g = Graphics::FromImage(newBM);
                g->Clear(Color::White);
                drawTiled(bm, newBM, g, nullptr, 0, 0);

                delete g;
                delete bm;
                bm = newBM;
            }

            if (path != nullptr) {
                String^ fileName = path;
                if (prefs->ImageAppendVariation) {
                    fileName = Path::GetDirectoryName(path) + "\\" +
                        Path::GetFileNameWithoutExtension(path) +
                        "-" + prefs->VariationText +
                        Path::GetExtension(path);
                }

                if (JPEG)
                    bm->Save(fileName, jpegCodec, iParams);
                else
                    bm->Save(fileName, Imaging::ImageFormat::Png);
            }
            else if (str != nullptr) {
                if (JPEG)
                    bm->Save(str, jpegCodec, iParams);
                else
                    bm->Save(str, Imaging::ImageFormat::Png);
            }
            else {
                mSystem->message("Nowhere to save the image.");
                System::Console::Beep();
            }
            delete bm;
            mSystem->message("Image save complete.");
        }
        catch (Exception^) {
            mSystem->message("Image save failed.");
            System::Console::Beep();
            success = false;
        }
        delete tempCanvas;
        tempCanvas = nullptr;
        return success;
    }

    void RenderHelper::uploadDesign(System::Windows::Forms::Form^ owner, UploadPrefs^ prefs)
    {
        if (!mCanvas) {
            mSystem->message("Nothing to upload, try rendering first.");
            return;
        }
        MemoryStream^ bitmapStream = gcnew MemoryStream();
        if (!saveToPNGorJPEG(prefs, nullptr, bitmapStream, false) || bitmapStream->Length == 0) {
            mSystem->message("Upload failed because of image problems.");
            return;
        }

        bool compression = mCanvas->colorCount256() ? Upload::CompressPNG8 : Upload::CompressJPEG;

        array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(prefs->CfdgText);
        pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];

        GalleryUploader toGal(prefs, bitmapStream, (*mEngine)->isFrieze(), (*mEngine)->isTiled(), compression);

        toGal.ShowDialog(owner);
    }

    UploadPrefs^ RenderHelper::downloadDesign(System::String^ responseBody)
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
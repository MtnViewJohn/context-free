#include "pch.h"
#include "RenderHelper.h"
#include <Windows.h>
#include "CFscintilla.h"
#include <algorithm>
#include "variation.h"
#include "tiledCanvas.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace CppWrapper {
    RenderHelper::RenderHelper(intptr_t editHwnd, intptr_t docHwnd)
    : mEngine(new cfdg_ptr())
    {
        HWND hwnd = (HWND)editHwnd;
        SciPtr = (sptr_t)SendMessage(hwnd, SCI_GETDIRECTPOINTER, 0, 0);
        directFunction = (SciFnDirect)SendMessage(hwnd, SCI_GETDIRECTFUNCTION, 0, 0);
        mSystem = new WinSystem((void*)docHwnd);
    }

    RenderHelper::RenderHelper()
    {}

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
            //mRenderer->draw(mSVGCanvas);
            //delete mSVGCanvas;
            //mSVGCanvas = nullptr;
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
        delete mRenderer; mRenderer = nullptr;
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
}
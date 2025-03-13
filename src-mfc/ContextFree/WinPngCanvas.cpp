#include "pch.h"
#include "WinPngCanvas.h"
#include "WinCanvas.h"

WinPngCanvas::WinPngCanvas( const char* name, WinCanvas* canvas, bool crop,
                            int variation, Renderer* r, int mx, int my)
: pngCanvas(name, true, crop ? canvas->cropWidth() : canvas->mWidth,
    crop ? canvas->cropHeight() : canvas->mHeight, canvas->mPixelFormat,
    crop, 0, variation, false, r, mx, my, false),
    m_Canvas(canvas), mEncoder(std::strlen(name) ? Encoder::libpng : Encoder::gdiplus)
{
}

WinPngCanvas::~WinPngCanvas() = default;

void WinPngCanvas::end()
{
    // Copy source WinCanvas to center of this canvas
    int bpp = BytesPerPixel.at(mPixelFormat);
    int destx = mOriginX * bpp;
    int desty = mOriginY;
    int srcx = mCrop ? m_Canvas->cropX() * bpp : 0;
    int srcy = mCrop ? m_Canvas->cropY() : 0;
    unsigned char* sourceData = reinterpret_cast<unsigned char*>(m_Canvas->mBM.get());

    for (int y = 0; y < mHeight; ++y) {
        if (y + desty < 0 || y + desty >= mFullHeight) continue;
        for (int x = 0; x < mWidth * bpp; x += bpp) {
            if (destx + x >= 0 && destx + x < mStride)
                if (mEncoder == Encoder::libpng) {
                    switch (mPixelFormat) {
                    case Gray8_Blend:           // Gray8 <- Gray8
                        mData[(y + desty) * mStride + destx + x] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x];
                        break;
                    case Gray16_Blend:          // Gray16 <- Gray16
                        mData[(y + desty) * mStride + destx + x] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x];
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        break;
                    case RGB8_Blend:            // RGB24 <- BGR24
                        mData[(y + desty) * mStride + destx + x + 0] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 2];
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        mData[(y + desty) * mStride + destx + x + 2] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 0];
                        break;
                    case RGB16_Blend:           // RGB48 <- RGB48
                        mData[(y + desty) * mStride + destx + x + 0] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 0];
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        mData[(y + desty) * mStride + destx + x + 2] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 2];
                        mData[(y + desty) * mStride + destx + x + 3] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 3];
                        mData[(y + desty) * mStride + destx + x + 4] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 4];
                        mData[(y + desty) * mStride + destx + x + 5] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 5];
                        break;
                    case RGBA8_Blend:
                    case RGBA8_Custom_Blend:    // RGBA32 <- BGRA32
                        mData[(y + desty) * mStride + destx + x + 0] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 2];
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        mData[(y + desty) * mStride + destx + x + 2] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 0];
                        mData[(y + desty) * mStride + destx + x + 3] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 3];
                        break;
                    case RGBA16_Blend:
                    case RGBA16_Custom_Blend:   // RGBA64 <- RGBA64
                        mData[(y + desty) * mStride + destx + x + 0] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 0];
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        mData[(y + desty) * mStride + destx + x + 2] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 2];
                        mData[(y + desty) * mStride + destx + x + 3] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 3];
                        mData[(y + desty) * mStride + destx + x + 4] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 4];
                        mData[(y + desty) * mStride + destx + x + 5] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 5];
                        mData[(y + desty) * mStride + destx + x + 6] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 6];
                        mData[(y + desty) * mStride + destx + x + 7] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 7];
                        break;
                    default:
                        TRACE0("Unsupported pixel format in WinPngCanvas!\n");
                        break;
                    }
                } else {
                    switch (bpp) {
                    case 8:
                        mData[(y + desty) * mStride + destx + x + 7] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 7];
                        mData[(y + desty) * mStride + destx + x + 6] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 6];
                        [[fallthrough]];
                    case 6:
                        mData[(y + desty) * mStride + destx + x + 5] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 5];
                        mData[(y + desty) * mStride + destx + x + 4] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 4];
                        [[fallthrough]];
                    case 4:
                        mData[(y + desty) * mStride + destx + x + 3] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 3];
                        [[fallthrough]];
                    case 3:
                        mData[(y + desty) * mStride + destx + x + 2] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 2];
                        [[fallthrough]];
                    case 2:
                        mData[(y + desty) * mStride + destx + x + 1] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 1];
                        [[fallthrough]];
                    default:
                        mData[(y + desty) * mStride + destx + x + 0] = sourceData[(y + srcy) * m_Canvas->mStride + srcx + x + 0];
                    }
                }
        }
    }

    // tile source WinCanvas and then output to PNG
    pngCanvas::end();
}

void WinPngCanvas::output(const char* outfilename, int frame)
{
    // Skip PNG output for canvas that will be used for JPEG output
    if (std::strlen(outfilename))
        pngCanvas::output(outfilename, frame);
}


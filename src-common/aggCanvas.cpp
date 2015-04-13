// aggCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2013 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "aggCanvas.h"

#include "agg_rendering_buffer.h"
#include "agg_pixfmt_rgba.h"
#include "agg_pixfmt_rgb.h"
#include "agg_pixfmt_gray.h"
#include "agg_renderer_base.h"
#include "agg_renderer_scanline.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_p.h"
#include "agg_fast_ellipse.h"
#include "agg_trans_affine.h"
#include "agg_copy_rect.h"
#include "primShape.h"
#include "ast.h"
#include "CmdInfo.h"
#include "pathIterator.h"
#include <set>
#include <cassert>

#ifdef _WIN32
typedef agg::pixfmt_bgra64_pre  color64_pixel_fmt;
typedef agg::pixfmt_bgr48_pre   color48_pixel_fmt;
typedef agg::pixfmt_bgra32_pre  color32_pixel_fmt;
typedef agg::pixfmt_bgr24_pre   color24_pixel_fmt;
#else
typedef agg::pixfmt_rgba64_pre  color64_pixel_fmt;
typedef agg::pixfmt_rgb48_pre   color48_pixel_fmt;
typedef agg::pixfmt_rgba32_pre  color32_pixel_fmt;
typedef agg::pixfmt_rgb24_pre   color24_pixel_fmt;
#endif

typedef agg::pixfmt_argb32_pre  ff_pixel_fmt;
typedef agg::pixfmt_rgb24_pre   ff24_pixel_fmt;
typedef agg::pixfmt_rgba32_pre  qt_pixel_fmt;

typedef agg::pixfmt_gray8_pre  gray_pixel_fmt;
typedef agg::pixfmt_gray16_pre gray16_pixel_fmt;

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

#define PNG8Limit 32

#define ADJ_SMALL_SIZE      5.000
#define ADJ_CIRCLE_SIZE     0.30
#define ADJ_SQUARE_SIZE     0.80
#define ADJ_TRIANGLE_SIZE   0.90

const std::map<aggCanvas::PixelFormat, int> aggCanvas::BytesPerPixel = {
    {UnknownPixelFormat, 4},
    { Gray8_Blend, 1 },
    { RGBA8_Blend, 4 },
    { RGB8_Blend, 3 },
    { FF_Blend, 4 },
    { FF24_Blend, 3 },
    { QT_Blend, 4 },
    { Gray16_Blend, 2 },
    { RGBA16_Blend, 8 },
    { RGB16_Blend, 6 }
};

namespace {
    inline double
    adjustShapeSize(agg::trans_affine& tr, double adjustment)
    {
        double origx = 0;
        double origy = 0;
        tr.transform(&origx, &origy);
        double px = 1;
        double py = 0;
        tr.transform(&px, &py);
        double sizex = sqrt((px - origx) * (px - origx) + (py - origy) * (py - origy));
        px = 0; py = 1;
        tr.transform(&px, &py);
        double sizey = sqrt((px - origx) * (px - origx) + (py - origy) * (py - origy));
        double scalex = (sizex < ADJ_SMALL_SIZE)
            ? ((ADJ_SMALL_SIZE + adjustment) / ADJ_SMALL_SIZE)
            : ((sizex + adjustment) / sizex);
        double scaley = (sizey < ADJ_SMALL_SIZE)
            ? ((ADJ_SMALL_SIZE + adjustment) / ADJ_SMALL_SIZE)
            : ((sizey + adjustment) / sizey);

        // Scale the linear part of the affine transform (not the translation)
        agg::trans_affine_scaling sc(scalex, scaley);
        tr.premultiply(sc); 

        return (sizex + sizey) / 2;
    }

    inline double
    adjustCircleSize(agg::trans_affine& tr)
    {
        return adjustShapeSize(tr, ADJ_CIRCLE_SIZE);
    }

    inline double
    adjustSquareSize(agg::trans_affine& tr)
    {
        return adjustShapeSize(tr, ADJ_SQUARE_SIZE);
    }

    inline double
    adjustTriangleSize(agg::trans_affine& tr)
    {
        return adjustShapeSize(tr, ADJ_TRIANGLE_SIZE);
    }
};


class aggCanvas::impl {
    public:
        typedef agg::conv_transform<agg::path_storage>          TransSquare;
        typedef agg::conv_transform<agg::path_storage>          TransTriangle;
        typedef agg::conv_transform<agg::fast_ellipse>          TransEllipse;

    agg::rendering_buffer   buffer;
        aggCanvas*          mCanvas;
    
        agg::fast_ellipse   unitEllipse;
        
        agg::trans_affine   unitTrans;
        primShape           unitSquare;
        TransSquare         shapeSquare;
        TransEllipse        shapeEllipse;
        primShape           unitTriangle;
        TransTriangle       shapeTriangle;
    
        pathIterator pathSource;
        
        agg::rasterizer_scanline_aa<>   rasterizer;
        agg::scanline_p8                scanline;

        agg::trans_affine offset;
        int offsetX;
        int offsetY;
        int cropWidth;
        int cropHeight;
        
        std::set<agg::int64u> pixelSet;
        
        impl(aggCanvas* canvas)
            : buffer(), mCanvas(canvas), unitSquare(primShape::square),
              shapeSquare(unitSquare, unitTrans), 
              shapeEllipse(unitEllipse, unitTrans), unitTriangle(primShape::triangle),
              shapeTriangle(unitTriangle, unitTrans), 
              cropWidth(0), cropHeight(0)
        {
//            rasterizer.gamma(agg::gamma_power(1.0));
        }
        virtual ~impl() = default;

        virtual void reset() = 0;
        virtual void clear(const agg::rgba& bk) = 0;
        virtual void fill(RGBA8 bk) = 0;
        virtual void draw(RGBA8 c, agg::filling_rule_e fr = agg::fill_non_zero) = 0;
        
        virtual bool colorCount256() = 0;
        
        virtual void copy(void* data, unsigned width, unsigned height,
                          int stride, PixelFormat format) = 0;
};


template <class pixel_fmt> class aggPixelPainter : public aggCanvas::impl {
    public:
        typedef agg::renderer_base<pixel_fmt>                   renderer_base;
        typedef agg::renderer_scanline_aa_solid<renderer_base>  renderer_solid;

        pixel_fmt               pixFmt;
        renderer_base           rendBase;
        renderer_solid          rendSolid;
        
        aggPixelPainter(aggCanvas* canvas)
        : aggCanvas::impl(canvas), pixFmt(buffer), 
          rendBase(pixFmt), rendSolid(rendBase)
            { }
        ~aggPixelPainter() = default;
    
        void reset()
        {
            rendBase.reset_clipping(true);
        }

        void clear(const agg::rgba& bk);
        void fill(RGBA8 bk);
        void draw(RGBA8 c, agg::filling_rule_e fr = agg::fill_non_zero);

        bool colorCount256();
        
        void copy(void* data, unsigned width, unsigned height,
                  int stride, aggCanvas::PixelFormat format);
};

template <class pixel_fmt>
bool
aggPixelPainter<pixel_fmt>::colorCount256()
{
    return pixelSet.size() < PNG8Limit;
}

template <class pixel_fmt>
void
aggPixelPainter<pixel_fmt>::clear(const agg::rgba& bk)
{
    typedef typename pixel_fmt::color_type color_type;
    agg::rgba bk_pre = bk;
    bk_pre.premultiply();
    rendBase.clear(color_type(bk_pre));
}

template <class pixel_fmt>
void
aggPixelPainter<pixel_fmt>::fill(RGBA8 bk)
{
    typedef typename pixel_fmt::color_type color_type;
    typedef agg::ColorConverter<RGBA8, color_type> Converter_type;
    color_type c = Converter_type::f(bk);
    rendBase.fill(c.premultiply());
}

template <class pixel_fmt>
void
aggPixelPainter<pixel_fmt>::draw(RGBA8 col, agg::filling_rule_e fr)
{
    typedef typename pixel_fmt::color_type color_type;
    typedef agg::ColorConverter<RGBA8, color_type> Converter_type;
    if (pixelSet.size() < PNG8Limit) {
        agg::int64u pixel = 
            static_cast<agg::int64u>(col.r) << 48 |
            static_cast<agg::int64u>(col.g) << 32 |
            static_cast<agg::int64u>(col.b) << 16 |
            static_cast<agg::int64u>(col.a);
        pixelSet.insert(pixel);
    }
    
    color_type c = Converter_type::f(col);
    rendSolid.color(c.premultiply());
    rasterizer.filling_rule(fr);
    agg::render_scanlines(rasterizer, scanline, rendSolid);
    rasterizer.reset();
}

template <class  pixel_fmt>
void
aggPixelPainter<pixel_fmt>::copy(void* data, unsigned width, unsigned height,
                                 int stride, aggCanvas::PixelFormat format)
{
    agg::rendering_buffer srcBuffer(reinterpret_cast<agg::int8u*>(data), width, height, -stride);
    
    switch (format) {
        case aggCanvas::Gray8_Blend: {
            gray_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::Gray16_Blend: {
            gray16_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::RGBA8_Blend: {
            color32_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::RGBA16_Blend: {
            color64_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::RGB8_Blend: {
            color24_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::RGB16_Blend: {
            color48_pixel_fmt srcPixFmt(srcBuffer);
            agg::copy_rect(srcPixFmt, pixFmt);
            break;
        }
        
        case aggCanvas::FF_Blend:
        case aggCanvas::FF24_Blend:
        case aggCanvas::QT_Blend:
            assert(false);
            break;
            
        default:
            break;
    }
    
}


aggCanvas::aggCanvas(PixelFormat pixfmt) : Canvas(0, 0) { 
    switch (pixfmt) {
        case Gray8_Blend:   m.reset(new aggPixelPainter<gray_pixel_fmt>(this)); break;
        case RGBA8_Blend:   m.reset(new aggPixelPainter<color32_pixel_fmt>(this)); break;
        case RGB8_Blend:    m.reset(new aggPixelPainter<color24_pixel_fmt>(this)); break;
        case Gray16_Blend:  m.reset(new aggPixelPainter<gray16_pixel_fmt>(this)); break;
        case RGBA16_Blend:  m.reset(new aggPixelPainter<color64_pixel_fmt>(this)); break;
        case RGB16_Blend:   m.reset(new aggPixelPainter<color48_pixel_fmt>(this)); break;
        case FF_Blend:      m.reset(new aggPixelPainter<ff_pixel_fmt>(this)); break;
        case FF24_Blend:    m.reset(new aggPixelPainter<ff24_pixel_fmt>(this)); break;
        case QT_Blend:      m.reset(new aggPixelPainter<qt_pixel_fmt>(this)); break;
        default: break;
    }
}

aggCanvas::~aggCanvas() = default;

void
aggCanvas::start(bool clear, const agg::rgba& bk, int width, int height)
{
    Canvas::start(clear, bk, width, height);
    if (clear) {
        m->pixelSet.clear();
        m->cropWidth = width;
        m->cropHeight = height;
        m->offsetX = (mWidth - width) / 2;
        m->offsetY = (mHeight - height) / 2;
        agg::trans_affine_translation off(m->offsetX, m->offsetY);
        m->offset = off;
        m->clear(bk);
    }
}

void
aggCanvas::end()
{ Canvas::end(); }

void
aggCanvas::circle(RGBA8 c, agg::trans_affine tr)
{
    double size = adjustCircleSize(tr) / 2.0;
    tr *= m->offset;
    
    m->shapeEllipse.transformer(tr);
    m->unitEllipse.init(0.0, 0.0, 0.5, 0.5, int(size)+8);

    m->rasterizer.add_path(m->shapeEllipse);
    m->draw(c);
}

void
aggCanvas::square(RGBA8 c, agg::trans_affine tr)
{
    adjustSquareSize(tr);
    tr *= m->offset;
    
    m->shapeSquare.transformer(tr);
    
    m->rasterizer.add_path(m->shapeSquare);
    m->draw(c);
}

void
aggCanvas::triangle(RGBA8 c, agg::trans_affine tr)
{
    adjustTriangleSize(tr);
    tr *= m->offset;
    
    m->shapeTriangle.transformer(tr);
 
    m->rasterizer.add_path(m->shapeTriangle);
    m->draw(c);
}

void
aggCanvas::fill(RGBA8 c)
{
    m->fill(c);
}

void
aggCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo& attr)
{
    tr *= m->offset;    // already multiplied by attr->mTransform
    
    agg::filling_rule_e rule =  (attr.mFlags & (AST::CF_EVEN_ODD | AST::CF_FILL)) == (AST::CF_EVEN_ODD | AST::CF_FILL) ?
        agg::fill_even_odd : agg::fill_non_zero;
    
    m->pathSource.addPath(m->rasterizer, tr, attr);
    m->draw(c, rule);
}

void
aggCanvas::attach(void* data, unsigned width, unsigned height, int stride, bool invert)
{
    m->buffer.attach(reinterpret_cast<agg::int8u*>(data), width, height, invert ? -stride : stride);
    m->cropWidth = width;
    m->cropHeight = height;
    mWidth = width;
    mHeight = height;
    m->offsetX = 0;
    m->offsetY = 0;
    m->reset();
}


void
aggCanvas::copy(void* data, unsigned width, unsigned height,
                int stride, PixelFormat format)
{
    m->copy(data, width, height, stride, format);
}

bool    aggCanvas::colorCount256()  { return m->colorCount256(); }
int     aggCanvas::cropX()          { return m->offsetX; }
int     aggCanvas::cropY()          { return m->offsetY; }
int     aggCanvas::cropWidth()      { return m->cropWidth; }
int     aggCanvas::cropHeight()     { return m->cropHeight; }

aggCanvas::PixelFormat aggCanvas::SuggestPixelFormat(CFDG* engine)
{
    if (engine == nullptr) 
        return RGBA8_Blend;
    
    int ret = Gray8_Blend;
    
    if (engine->usesAlpha)
        ret = RGBA8_Blend;
    else if (engine->usesColor)
        ret = RGB8_Blend;

    if (engine->uses16bitColor)
        ret += Has_16bit_Color;
    
    return static_cast<PixelFormat>(ret);
}


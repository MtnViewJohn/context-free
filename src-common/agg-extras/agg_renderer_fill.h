//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
// Copyright (C) 2009 John Horigan ( john@glyphic.com )
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: john@glyphic.com
//          mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//          
//----------------------------------------------------------------------------
//
// class renderer_fill: extends class renderer_base by adding a fill() method
//
//----------------------------------------------------------------------------
#ifndef AGG_RENDERER_FILL_INCLUDED
#define AGG_RENDERER_FILL_INCLUDED

#include "agg_renderer_base.h"

namespace agg
{
    
    //-----------------------------------------------------------renderer_fill
    template<class PixelFormat> class renderer_fill : public renderer_base<PixelFormat>
    {
    public:
        typedef PixelFormat pixfmt_type;
        typedef typename pixfmt_type::color_type color_type;
        typedef typename pixfmt_type::row_data row_data;
        
        //--------------------------------------------------------------------
        renderer_fill() : renderer_base<pixfmt_type>() {}
        explicit renderer_fill(pixfmt_type& ren) :
        renderer_base<pixfmt_type>(ren)
        {}
        
        //--------------------------------------------------------------------
        void fill(const color_type& c)
        {
            unsigned y;
            if(this->width())
            {
                for(y = 0; y < this->height(); y++)
                {
                    this->ren().blend_hline(0, y, this->width(), c, cover_mask);
                }
            }
        }
        
    };
}



#endif  // AGG_RENDERER_FILL_INCLUDED

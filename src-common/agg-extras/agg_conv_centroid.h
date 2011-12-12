//----------------------------------------------------------------------------
// agg_conv_centroid.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//
//----------------------------------------------------------------------------
//
// class conv_centroid
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_CENTROID_INCLUDED
#define AGG_CONV_CENTROID_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //----------------------------------------------------------conv_centroid
    template<class VertexSource> class conv_centroid
    {
    public:
        conv_centroid(VertexSource& source) : m_source(&source) { reset(); }
        void attach(VertexSource& source) { m_source = &source; }
        
        void reset() {
            m_first_poly = true;
            m_p0.x = m_p0.y = m_plast.x = m_plast.y = 0.0;
            m_area = 0.0;
            m_centroid.x = m_centroid.y = 0.0;
            m_average.x = m_average.y = 0.0;
            m_count = 0;
        }

        void rewind(unsigned path_id) 
        { 
            m_source->rewind(path_id); 
            reset();
        }

        unsigned vertex(double* x, double* y)
        {
            unsigned cmd = m_source->vertex(x, y) & path_cmd_mask;
            if (is_vertex(cmd)) {
                m_average.x += *x; m_average.y += *y;
                ++m_count;
                if (m_first_poly) {
                    m_first_poly = false;
                    m_p0.x = m_plast.x = *x;
                    m_p0.y = m_plast.y = *y;
                } else {
                    double term = *y * m_plast.x - *x * m_plast.y;
                    m_area += 0.5 * term;
                    m_centroid.x += (*x + m_plast.x) * term;
                    m_centroid.y += (*y + m_plast.y) * term;
                    m_plast.x = *x; m_plast.y = *y;
                }
            } else if (is_end_poly(cmd)) {
                m_first_poly = true;
                double term = m_p0.y * m_plast.x - m_p0.x * m_plast.y;
                m_area += 0.5 * term;
                m_centroid.x += (m_p0.x + m_plast.x) * term;
                m_centroid.y += (m_p0.y + m_plast.y) * term;
            } else if (is_stop(cmd)) {
                if (fabs(m_area) < 1e-34) {
                    if (m_count) {
                        m_centroid.x = m_average.x / m_count;
                        m_centroid.y = m_average.y / m_count;
                    } else {
                        m_centroid.x = m_centroid.y = 0.0;
                    }
                } else {
                    m_centroid.x = m_centroid.x / (6.0 * m_area);
                    m_centroid.y = m_centroid.y / (6.0 * m_area);
                }
                m_area = fabs(m_area);
            }
                
            return cmd;
        }
        
        double             m_area;
        point_d            m_centroid;

    private:
        conv_centroid(const conv_centroid<VertexSource>&);
        const conv_centroid<VertexSource>& 
            operator = (const conv_centroid<VertexSource>&);

        VertexSource*      m_source;
        bool               m_first_poly;
        point_d            m_p0, m_plast, m_average;
        unsigned           m_count;
    };


}

#endif

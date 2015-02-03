// agg_fast_ellipse.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2015 John Horigan - john@glyphic.com
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

//----------------------------------------------------------------------------
//
// class fast_ellipse
//
//----------------------------------------------------------------------------

#ifndef AGG_FAST_ELLIPSE_INCLUDED
#define AGG_FAST_ELLIPSE_INCLUDED

#include "agg_basics.h"
#include <math.h>
#include <memory>

#ifdef _WIN32
#pragma warning( disable : 4146 )
#endif

namespace agg
{

    class fast_ellipse
    {
    public:
        fast_ellipse()
            : m_x(0.0), m_y(0.0), m_rx(0.0), m_ry(0.0), m_num(0), m_step(0),
              m_size(0)
        {
            init_num(0);
        }
        fast_ellipse(double x, double y, double rx, double ry, unsigned num_steps) 
            : m_x(x), m_y(y), m_rx(rx), m_ry(ry), m_num(0), m_step(0),
              m_size(0)
        {
            init_num(num_steps);
        }
        ~fast_ellipse() = default;
        
        void init(double x, double y, double rx, double ry, unsigned num_steps);
        void rewind(unsigned);
        unsigned vertex(double* x, double* y);
        
    private:
        double m_x;
        double m_y;
        double m_rx;
        double m_ry;
        unsigned m_num;
        unsigned m_step;

        std::unique_ptr<double[]> m_cosine;
        std::unique_ptr<double[]> m_sine;
        unsigned m_size;
        void init_num(unsigned num_steps);
    };

    inline void fast_ellipse::init(double x, double y, double rx, double ry, unsigned num_steps)
    {
        init_num(num_steps);
        m_x = x;
        m_y = y;
        m_rx = rx;
        m_ry = ry;
        m_step = 0;
    }

    inline void fast_ellipse::init_num(unsigned num_steps)
    {
        unsigned old_num = m_num;
        m_num = num_steps + ((-num_steps) & 7);     // round to next highest 8
        if (!m_num || m_num == old_num) return;
        if (m_num/4 > m_size) {
            m_size = m_num / 2 > 25 ? m_num / 2 : 25;
            m_cosine.reset(new double[m_size]);
            m_sine.reset(new double[m_size]);
        }
        for (unsigned i = 0; i < m_num/8; i++) {
            double angle = (double(i) + 0.5) / double(m_num) * 2.0 * pi;
            m_sine[(m_num / 4) - i - 1] = m_cosine[i] = cos(angle);
            m_cosine[(m_num / 4) - i - 1] = m_sine[i] = sin(angle);
        }
    }
            

    inline void fast_ellipse::rewind(unsigned)
    {
        m_step = 0;
    }

    inline unsigned fast_ellipse::vertex(double* x, double* y)
    {
        if(m_step == m_num) 
        {
            ++m_step;
            return path_cmd_end_poly | path_flags_close | path_flags_ccw;
        }
        if(m_step > m_num) return path_cmd_stop;
        int quadrant = m_step / (m_num / 4);
        int step = m_step % (m_num / 4);
        if (quadrant & 1)
            step = (m_num / 4) - step - 1;
        int ref_x = ((quadrant + 1) & 2) - 1;
        int ref_y = (quadrant & 2) - 1;
        *x = m_x + m_cosine[step] * ref_x * m_rx;
        *y = m_y + m_sine[step] * ref_y * m_ry;
        m_step++;
        return ((m_step == 1) ? path_cmd_move_to : path_cmd_line_to);
    }
}

#endif



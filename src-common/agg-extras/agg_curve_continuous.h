// agg::curve_continuous.h


#pragma once

#include "agg2/agg_path_storage.h"
#include <climits>

namespace agg
{
    //============================================================curve4_continuous
    //
    // Reconnects the end-point of a sequence of curves and arcs back to the
    // beginning using a curve4. Both control points are set to match the
    // curvature of the adjacent curve segments. Only produces a curve4 if the
    // most recent vertices in the path_storage are a move or line, follwed by
    // one or more curves and/or arcs.
    //
    //----------------------------------------------------------------------
    void curve4_continuous(path_storage& path);
    void curve4_continuous(path_storage& path)
    {
        double x_to;
        double y_to;
        double x_ctrl2;
        double y_ctrl2;
        if (is_curve(path.last_vertex(&x_to, &y_to)))
        {
            for (unsigned idx = path.total_vertices() - 1; idx != UINT_MAX && is_vertex(path.command(idx)); --idx)
            {
                unsigned cmd = path.vertex(idx, &x_to, &y_to);
                if (is_curve(cmd))
                {
                    x_ctrl2 = x_to;
                    y_ctrl2 = y_to;
                    continue;
                }
                if (is_move_to(cmd) || is_line_to(cmd))
                {
                    x_ctrl2 = x_to + x_to - x_ctrl2;
                    y_ctrl2 = y_to + y_to - y_ctrl2;
                    path.curve4(x_ctrl2, y_ctrl2, x_to, y_to);
                    break;
                }
            }
        }
    }

}

#pragma once

namespace CppWrapper {
    public value class RenderStats
    {
    public:
        bool    updateRender;   // stat pointer was null
        int     shapeCount;     // finished shapes in image
        int     toDoCount;      // unfinished shapes still to expand

        bool    inOutput;       // true if we are in the output loop
        bool    fullOutput;     // not an incremental output
        bool    finalOutput;    // the last output
        bool    showProgress;
        int     outputCount;    // number to be output
        int     outputDone;     // number output so far
        __int64 outputTime;

        bool    animating;      // inside the animation loop
    };
}

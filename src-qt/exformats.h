#ifndef EXFORMATS_H
#define EXFORMATS_H

#include <limits>
#include <string>
#include <memory>
#include <aggCanvas.h>

#include <QSpinBox>
#include <QDoubleSpinBox>

class QWidget;
class Canvas;
class Renderer;

// Uncomment to enable quicktime export
// #define QUICKTIME

std::shared_ptr<Canvas> ex_svg (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);
std::shared_ptr<Canvas> ex_png (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);
#ifdef QUICKTIME
std::shared_ptr<Canvas> ex_qtime (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);
#endif /* QUICKTIME */
namespace exfmt {

    using FileExporter = std::shared_ptr<Canvas> (*)(int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer>);

    struct ExFmt {
        public:
            FileExporter ex;
    };

    const ExFmt svg = (ExFmt) { &ex_svg };
    const ExFmt png = (ExFmt) { &ex_png };
#ifdef QUICKTIME
    const ExFmt qtime = (ExFmt) { &ex_qtime, (std::vector<std::shared_ptr<Option>>) {std::make_shared<IntOption>("FPS", 0, std::numeric_limits<double>::max(), "output_fps"),
            std::make_shared<IntOption>("Minimum size", 0, std::numeric_limits<double>::max(), "output_minsize")} };
#endif

}

#endif // EXFORMATS_H

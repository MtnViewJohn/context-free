#include "exformats.h"

#include <SVGCanvas.h>
#include <pngCanvas.h>
#include <cfdg.h>

#include <QDoubleSpinBox>
#include <memory>
#include <string>

std::shared_ptr<Canvas> ex_svg (int frames, int w, int h, const char *ofile, std::shared_ptr<Renderer> rend) {
    return std::make_shared<SVGCanvas>(ofile, w, h, false);
}
const exfmt::FileExporter svg_fex = &ex_svg;

std::shared_ptr<Canvas> ex_png (int frames, int w, int h, const char *ofile, std::shared_ptr<Renderer> rend) {

    // If a static output file name is provided then generate an output
    // file name format string by escaping any '%' characters. If this is
    // an animation run with PNG output then add "_%f" before the extension
    std::string pngOutput;
    std::string fname(ofile);
    pngOutput.reserve(fname.length());
    for (char c: fname) {
        pngOutput.append(c == '%' ? 2 : 1, c);
    }
    size_t ext = pngOutput.find_last_of('.');
    size_t dir = pngOutput.find_last_of('/');
    if(frames > 1)
    if (ext != std::string::npos && (dir == std::string::npos || ext > dir)) {
        pngOutput.insert(ext, "_%f");
    } else {
        pngOutput.append("_%f");
    }
    return std::make_shared<pngCanvas>(ofile, false, w, h, aggCanvas::PixelFormat::RGB16_Blend, false, frames, 294, true, rend.get(), 1, 1);
}
const exfmt::FileExporter png_fex = &ex_png;

std::string exfmt::Option::getName() {
    return name;
}

void exfmt::Option::setName(const std::string s) {
    name = s;
}

exfmt::DblOption::DblOption(const std::string name, const double min, const double max): min(min), max(max) {
    this->setName(name);
}

QWidget *exfmt::DblOption::getWidget() {
    QDoubleSpinBox *w = new QDoubleSpinBox();
    w->setRange(min, max);
    return w;
}

exfmt::IntOption::IntOption (const std::string name, const int min, const int max): min(min), max(max) {
    this->setName(name);
}

QWidget *exfmt::IntOption::getWidget() {
    QDoubleSpinBox *w = new QDoubleSpinBox();
    w->setRange(min, max);
    return w;
}

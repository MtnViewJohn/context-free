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


std::shared_ptr<Canvas> ex_svg (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);
std::shared_ptr<Canvas> ex_png (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);
std::shared_ptr<Canvas> ex_qtime (int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer> rend);

namespace exfmt {

    class Option {
        public:
            virtual QWidget *getWidget() = 0;
            std::string getName();
        protected:
            void setName(const std::string s);
        private:
            std::string name;
    };

    class DblOption: public Option {
        public:
            DblOption(const std::string name, const double min = 0, const double max = std::numeric_limits<double>::max());
            QWidget *getWidget() override;
        private:
            double min, max;
    };

    class IntOption: public Option {
        public:
            IntOption(const std::string name, const int min = 0, const int max = std::numeric_limits<int>::max());
            QWidget *getWidget() override;
        private:
            int min, max;
    };

    using FileExporter = std::shared_ptr<Canvas> (*)(int frames, int w, int h, char *ofile, aggCanvas::PixelFormat &fmt, std::shared_ptr<Renderer>);

    struct ExFmt {
        public:
            FileExporter ex;
            std::vector<std::shared_ptr<Option>> opts;
    };

    const ExFmt svg = (ExFmt) { &ex_svg, (std::vector<std::shared_ptr<Option>>) {std::make_shared<DblOption>("test.svg")} };
    const ExFmt png = (ExFmt) { &ex_png, (std::vector<std::shared_ptr<Option>>) {std::make_shared<DblOption>("test.png")} };
    const ExFmt qtime = (ExFmt) { &ex_qtime, (std::vector<std::shared_ptr<Option>>) {std::make_shared<DblOption>("test.qtime")} };

}

#endif // EXFORMATS_H

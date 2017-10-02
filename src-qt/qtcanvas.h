#ifndef QTCANVAS_H
#define QTCANVAS_H
#include <cfdg.h>
#include <aggCanvas.h>
#include <QGraphicsScene>
#include <vector>
#include <QThread>
#include <QStatusBar>
#include <queue>
#include "primShape.h"

using namespace std;

class ShapeSpec {
    public:
        ShapeSpec(int type, QTransform qtr, QColor fill): type(type), qtr(qtr), fill(fill) {}
        void drawOnScene(QGraphicsScene *scene);
        int type;
        QTransform qtr;
        QColor fill;
};

class QtCanvas: public Canvas {
        int frameIndex;
    public:
        virtual ~QtCanvas();
        QtCanvas(int w, int h);
        void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) override;
        void primitive(int shape, RGBA8 c, agg::trans_affine tr) override;
        void start(bool b, const agg::rgba &r, int i1, int i2) override;
        queue<queue<ShapeSpec> > specs;
};

#endif // QTCANVAS_H


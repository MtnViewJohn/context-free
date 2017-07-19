#ifndef QTCANVAS_H
#define QTCANVAS_H
#include <cfdg.h>
#include <aggCanvas.h>
#include <QGraphicsScene>

class QtCanvas : public Canvas {
    public:
        QtCanvas(int w, int h, QGraphicsScene *scene): Canvas(w, h), scene(scene) {}
        virtual ~QtCanvas();
        void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) override;
        void primitive(int shape, RGBA8 c, agg::trans_affine tr) override;
        QGraphicsScene *scene;
        int mWidth;
        int mHeight;
        bool mError;
};

#endif // QTCANVAS_H


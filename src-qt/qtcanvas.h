#ifndef QTCANVAS_H
#define QTCANVAS_H
#include <cfdg.h>
#include <aggCanvas.h>
#include <QGraphicsScene>
#include <vector>
#include <QThread>
#include "primShape.h"
using namespace std;

class ShapeSpec {
    public:
        ShapeSpec(int type, QTransform qtr, QColor fill): type(type), qtr(qtr), fill(fill) {}
        void drawOnScene(QGraphicsScene &scene);
        int type;
        QTransform qtr;
        QColor fill;
};

class QtCanvas : public Canvas {
    public:
        QtCanvas(int w, int h): Canvas(w, h) {}
        virtual ~QtCanvas();
        void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) override;
        void primitive(int shape, RGBA8 c, agg::trans_affine tr) override;
        vector<ShapeSpec*> specs;
};
class ParseWorker: public QThread {
        Q_OBJECT

    public:
        ParseWorker(int w, int h, shared_ptr<QtCanvas> canv, QObject *parent): w(w), h(h), canv(canv), QThread(parent) {}
        void run() override;
    signals:
        void done();
    private:
        int w, h;
        shared_ptr<QtCanvas> canv;
        ParseWorker();
};
class AsyncRenderer: public QObject {
        Q_OBJECT

    public:
        AsyncRenderer(int w, int h, shared_ptr<QtCanvas> canv, QGraphicsScene *scene);
        ~AsyncRenderer();
    public slots:
        void render();
    signals:
        void done();
    private:
        int w, h;
        shared_ptr<QtCanvas> canv;
        QGraphicsScene *scene;
        ParseWorker p;
};

#endif // QTCANVAS_H


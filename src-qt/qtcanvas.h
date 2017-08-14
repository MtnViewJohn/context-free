#ifndef QTCANVAS_H
#define QTCANVAS_H
#include <cfdg.h>
#include <aggCanvas.h>
#include <QGraphicsScene>
#include <vector>
#include <QThread>
#include <QStatusBar>
#include "primShape.h"
#include "mainwindow.h"
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
        ParseWorker(int w, int h, int frames, shared_ptr<QtCanvas> canv, MainWindow *mw);
        ~ParseWorker();
        void requestStop();
    public:
        void run();
    signals:
        void done();
    private:
        int w, h, frames;
        shared_ptr<QtCanvas> canv;
        shared_ptr<Renderer> rend;
        MainWindow *mw;
};
class AsyncRenderer: public QObject {
        Q_OBJECT

    public:
        AsyncRenderer(int w, int h, int frames, shared_ptr<QtCanvas> canv, QGraphicsScene *scene, MainWindow *mw);
        void cleanup();
        ~AsyncRenderer();
    public slots:
        void render();
    signals:
        void done();
        void abortRender();
        void aborted();
        void updateRect();
    private:
        int w, h, frames;
        shared_ptr<QtCanvas> canv;
        QGraphicsScene *scene;
        ParseWorker *p;
        QThread t;
        bool parsing = true;
        bool rendering = false;
        bool shouldExit = false;
};

#endif // QTCANVAS_H


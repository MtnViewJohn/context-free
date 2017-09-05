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
        int frameIndex;
    public:
        virtual ~QtCanvas();
        QtCanvas(int w, int h);
        void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) override;
        void primitive(int shape, RGBA8 c, agg::trans_affine tr) override;
        void start(bool b, const agg::rgba &r, int i1, int i2) override;
        queue<queue<ShapeSpec> > specs;
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
        void earlyAbort();
    private:
        int w, h, frames;
        shared_ptr<QtCanvas> canv;
        shared_ptr<Renderer> rend;
        MainWindow *mw;
};
class AsyncRenderer: public QObject {
        Q_OBJECT
    public:
        AsyncRenderer(int w, int h, int frames, shared_ptr<QtCanvas> canv, MainWindow *mw);
        void cleanup();
        vector<unique_ptr<QGraphicsScene> > &getScenes();
        int frameCount();
        int frameIndex;
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
        vector<unique_ptr<QGraphicsScene> > scenes;
        ParseWorker *p;
        QThread t;
        bool parsing = true;
        bool rendering = false;
        union {
                bool shouldExit;
                bool stillWorking;
        };
};

#endif // QTCANVAS_H


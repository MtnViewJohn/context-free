#ifndef ASYNCRENDERER_H
#define ASYNCRENDERER_H
#include <QThread>
#include <memory>
#include <cfdg.h>

class QGraphicsScene;
class QtCanvas;
class MainWindow;
class Renderer;

using namespace std;

class ParseWorker: public QThread {
        Q_OBJECT

    public:
        ParseWorker(int frames, shared_ptr<Canvas> canv, MainWindow *mw, cfdg_ptr design, shared_ptr<Renderer> rend);
        ~ParseWorker();
        void requestStop();
    public:
        void run();
    signals:
        void done();
        void earlyAbort();
    private:
        int frames;
        shared_ptr<Canvas> canv;
        shared_ptr<Renderer> rend;
        cfdg_ptr design;
        MainWindow *mw;
};
class AsyncRendQt: public QObject {
        Q_OBJECT
    public:
        AsyncRendQt(int w, int h, int frames, MainWindow *mw);
        void cleanup();
        vector<unique_ptr<QGraphicsScene> > &getScenes();
        int frameCount();
        int frameIndex;
        ~AsyncRendQt();
    public slots:
        void render();
    signals:
        void done();
        void abortRender();
        void aborted();
        void updateRect();
    private:
        int w, h, frames;
        vector<unique_ptr<QGraphicsScene> > scenes;
        shared_ptr<Renderer> rend;
        shared_ptr<QtCanvas> canv;
        ParseWorker *p;
//        QThread t;
        bool parsing = true;
        bool rendering = false;
        union {
                bool shouldExit;
                bool stillWorking;
        };
};
class AsyncRendPNG: public QObject {
        Q_OBJECT
    public:
        AsyncRendPNG(int frames, MainWindow *mw, string ifile, string ofile);
    private:
        ParseWorker *p;
        shared_ptr<Canvas> canv;
        shared_ptr<Renderer> rend;
};

#endif // ASYNCRENDERER_H

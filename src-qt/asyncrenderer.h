#ifndef ASYNCRENDERER_H
#define ASYNCRENDERER_H
#include <QThread>
#include <memory>

class QGraphicsScene;
class QtCanvas;
class MainWindow;
class Renderer;

using namespace std;

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

#endif // ASYNCRENDERER_H

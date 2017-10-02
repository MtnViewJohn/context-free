#include "asyncrenderer.h"
#include "qtcanvas.h"
#include "qtsystem.h"
#include "mainwindow.h"
#include <QSettings>
#include <QtDebug>
#include <QtConcurrent/QtConcurrent>
#include <QApplication>

AsyncRenderer::AsyncRenderer(int w, int h, int frames, shared_ptr<QtCanvas> canv, MainWindow *mw): w(w),
    h(h),
    canv(canv),
    t(this) {
    p = new ParseWorker(w, h, frames, canv, mw);
    qDebug() << "Beginning AsyncRenderer constructor" << endl;
    connect(p, SIGNAL(finished() ), p, SLOT(deleteLater() ));
    connect(p, SIGNAL(earlyAbort() ), mw, SLOT(abortRender() ));
    connect(p, SIGNAL(earlyAbort() ), p, SLOT(deleteLater() ));
    connect(p, SIGNAL(done() ), this, SLOT(render() ));
    p->start();
    parsing = true;
    qDebug() << "Done AsyncRenderer constructor" << endl;
    shouldExit = false;
}

AsyncRenderer::~AsyncRenderer() {
}

vector<unique_ptr<QGraphicsScene> > &AsyncRenderer::getScenes() {
    if (scenes.size() == 0)
        scenes.emplace_back(new QGraphicsScene());
    return scenes;
}

void AsyncRenderer::cleanup() {
    qDebug() << "AsyncRenderer being destroyed!";
    if(parsing) {
        p->requestStop();
        p->quit();
        qDebug() << "Waiting for ParseWorker...";
        p->wait();
        qDebug() << "Done waiting";
    } else if (rendering) {
        shouldExit = true;
        qDebug() << "Should exit";
        QtConcurrent::run([=] () {
            while(stillWorking) {
                //qDebug() << "Processing events waiting for aborted signal";
                QApplication::processEvents();
            }
            delete this;
        });
    }
}

void AsyncRenderer::render() {
    parsing = false;
    rendering = true;
    qDebug() << "Beginning render";
    //QSignalSpy spy(this, SIGNAL(abortRender()) );
    frameIndex = 0;
    while(!canv->specs.empty()) {
        queue<ShapeSpec> q = canv->specs.front();
        scenes.push_back(make_unique<QGraphicsScene>(Q_NULLPTR));
        qDebug() << "Scene count: " << scenes.size();
        qDebug() << "Processing events for render";
        QApplication::processEvents();
        while(!q.empty()) {
            if(shouldExit) {
                qDebug() << "Yes, I should";
                stillWorking = false;
                return;
            } else {
                q.front().drawOnScene(scenes[frameIndex].get());
                q.pop();
                emit updateRect();
            }
        }
        canv->specs.pop();
        frameIndex++;
    }
    qDebug() << "Done render; setting rendering flag to false";

    rendering = false;
    emit updateRect();
    emit done();
}

int AsyncRenderer::frameCount() {
    return scenes.size();
}

void ParseWorker::run() {
    qDebug() << "Beginning parsing" << endl;

    QtSystem sys;
    connect(&sys, SIGNAL(showmsg(const char*)), mw, SLOT(showmsg(const char*)));

    cfdg_ptr design(CFDG::ParseFile(mw->currentFile.toStdString().c_str(), &sys, 7394));
    if(design.get() == nullptr) {
        sys.catastrophicError("Design evaluated to null");
        emit earlyAbort();
        return;
    }
    QSettings s("contextfreeart.org", "ContextFree");
    rend = shared_ptr<Renderer>(design->renderer(design,
                                w,
                                h,
                                s.value("output_minsize", 0.3).toDouble(),
                                4,
                                2));
    if(rend == nullptr) {
        emit done();
        return;
    }
    rend->animate(this->canv.get(), frames, 0, false);
    //rend->run(this->canv.get(), false);
    qDebug() << "Done parsing" << endl;
    emit done();
}

void ParseWorker::requestStop() {
    if(rend != nullptr)
       rend->requestStop = true;
}

ParseWorker::ParseWorker(int w, int h, int frames, shared_ptr<QtCanvas> canv, MainWindow *mw): w(w), h(h), frames(frames), canv(canv), rend(nullptr), mw(mw) {}

ParseWorker::~ParseWorker() {
}

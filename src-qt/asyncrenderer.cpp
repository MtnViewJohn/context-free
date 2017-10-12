#include "asyncrenderer.h"
#include "qtcanvas.h"
#include "qtsystem.h"
#include "mainwindow.h"

#include <makeCFfilename.h>
#include <pngCanvas.h>
#include <QSettings>
#include <QtDebug>
#include <QtConcurrent/QtConcurrent>
#include <QApplication>

AsyncRendQt::AsyncRendQt(int w, int h, int frames, MainWindow *mw): w(w),
    h(h) {

    QtSystem* sys = new QtSystem();
    connect(sys, SIGNAL(showmsg(const char*)), mw, SLOT(showmsg(const char*)));

    cfdg_ptr design(CFDG::ParseFile(mw->currentFile.toStdString().c_str(), sys, 7394));
    if(design.get() == nullptr) {
        sys->catastrophicError("Design evaluated to null");
        emit aborted();
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
        emit aborted();
        return;
    }
    canv = make_unique<QtCanvas>(mw->ui->output->width(), mw->ui->output->height());

    p = new ParseWorker(frames, canv, mw, design, rend);
    qDebug() << "Beginning AsyncRendQt constructor" << endl;
    connect(p, SIGNAL( done() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( earlyAbort() ), mw, SLOT( abortRender() ));
    connect(p, SIGNAL( earlyAbort() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( done() ), this, SLOT( render() ));
    p->start();
    parsing = true;
    qDebug() << "Done AsyncRendQt constructor" << endl;
    shouldExit = false;
}

AsyncRendQt::~AsyncRendQt() {
}

vector<unique_ptr<QGraphicsScene> > &AsyncRendQt::getScenes() {
    if (scenes.size() == 0)
        scenes.emplace_back(new QGraphicsScene());
    return scenes;
}

void AsyncRendQt::cleanup() {
    qDebug() << "AsyncRendQt being destroyed!";
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

void AsyncRendQt::render() {
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

int AsyncRendQt::frameCount() {
    return scenes.size();
}

AsyncRendPNG::AsyncRendPNG(int frames, MainWindow *mw, string ifile, string ofile) {

    QtSystem *sys = new QtSystem();
    connect(sys, SIGNAL(showmsg(const char*)), this, SLOT(showmsg(const char*)));

    cfdg_ptr design(CFDG::ParseFile(ifile.c_str(), sys, 4));
    if(design.get() == nullptr) {
        sys->catastrophicError("Design evaluated to null");
        return;
    }

    QSettings s("contextfreeart.org", "ContextFree");
    shared_ptr<Renderer> rend(design->renderer(design,
                              1920,
                              1080,
                              s.value("output_minsize", 0.3).toDouble(),
                              4,
                              2));

    qDebug() << "Sensible filename:" << ofile.c_str();

    // If a static output file name is provided then generate an output
    // file name format string by escaping any '%' characters. If this is
    // an animation run with PNG output then add "_%f" before the extension.
    string pngOutput;
    pngOutput.reserve(ofile.length());
    for (char c: ofile) {
        pngOutput.append(c == '%' ? 2 : 1, c);
    }
    size_t ext = pngOutput.find_last_of('.');
    size_t dir = pngOutput.find_last_of('/');
    if (ext != string::npos && (dir == string::npos || ext > dir)) {
        pngOutput.insert(ext, "_%f");
    } else {
        pngOutput.append("_%f");
    }

    char *pngOutputC = new char[strlen(pngOutput.c_str()) + 1];
    strcpy(pngOutputC, pngOutput.c_str());

    shared_ptr<pngCanvas> canv = make_unique<pngCanvas>(pngOutputC, false, 1920, 1080, aggCanvas::PixelFormat::RGB16_Blend, false, 1, 294, true, rend.get(), 1, 1);

    p = new ParseWorker(frames, canv, mw, design, rend);
    qDebug() << "Beginning AsyncRendGeneric constructor" << endl;
    connect(p, SIGNAL( done() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( earlyAbort() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( done() ), this, SLOT( deleteLater() ));
    connect(p, SIGNAL( earlyAbort() ), this, SLOT( deleteLater() ));
    p->start();
    qDebug() << "Done AsyncRendGeneric constructor" << endl;
}

void ParseWorker::run() {
    qDebug() << "Beginning parsing" << endl;
    rend->animate(canv.get(), frames, 0, false);
    //rend->run(this->canv.get(), false);
    qDebug() << "Done parsing" << endl;
    emit done();
}

void ParseWorker::requestStop() {
    if(rend != nullptr)
       rend->requestStop = true;
}

ParseWorker::ParseWorker(int frames, shared_ptr<Canvas> canv, MainWindow *mw, cfdg_ptr design, shared_ptr<Renderer> rend): frames(frames), canv(canv), mw(mw), design(design), rend(rend) {}

ParseWorker::~ParseWorker() {
}

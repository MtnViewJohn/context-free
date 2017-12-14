#include "asyncrenderer.h"
#include "qtcanvas.h"
#include "qtsystem.h"
#include "mainwindow.h"
#include "exformats.h"

#include <variation.h>
#include <makeCFfilename.h>
#include <pngCanvas.h>
#include <SVGCanvas.h>
#include <QSettings>
#include <QtDebug>
#include <QtConcurrent/QtConcurrent>
#include <QApplication>

AsyncRendQt::AsyncRendQt(int w, int h, int frames, MainWindow *mw): w(w),
    h(h) {

    QtSystem* sys = new QtSystem();
    connect(sys, SIGNAL(showmsg(const char*)), mw, SLOT(showmsg(const char*)));

    int variation = Variation::fromString(mw->ui->varBox->text().toStdString().c_str());

    cfdg_ptr design(CFDG::ParseFile(mw->currentFile.toStdString().c_str(), sys, variation));
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
                                variation   ,
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

AsyncRendGeneric::AsyncRendGeneric(int frames, int w, int h, MainWindow *mw, string ifile, string ofile, exfmt::ExFmt e) {
    qDebug() << "Beginning AsyncRendGeneric constructor" << endl;

    sys = new QtSystem();
    connect(sys, &QtSystem::showmsg, mw, &MainWindow::showmsg);

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
                              Variation::fromString(mw->ui->varBox->text().toStdString().c_str()),
                              2));

    char *ofile_copy = new char[ofile.length() + 1];
    strcpy(ofile_copy, ofile.c_str());

    aggCanvas::PixelFormat fmt = aggCanvas::SuggestPixelFormat(design.get());

    shared_ptr<Canvas> canv = e.ex(frames, w, h, ofile_copy, fmt, rend);

    p = new ParseWorker(frames, canv, mw, design, rend);
    connect(p, SIGNAL( done() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( earlyAbort() ), p, SLOT( deleteLater() ));
    connect(p, SIGNAL( done() ), this, SLOT( deleteLater() ));
    connect(p, SIGNAL( earlyAbort() ), this, SLOT( deleteLater() ));
    p->start();
    qDebug() << "Done AsyncRendGeneric constructor" << endl;
}

AsyncRendGeneric::~AsyncRendGeneric() {
    QtConcurrent::run([] (ParseWorker *p, QtSystem *sys) {
        p->wait();
        delete sys;
    }, p, sys);
}

void ParseWorker::run() {
    qDebug() << "Beginning parsing" << endl;
    rend->animate(canv.get(), frames, 0, true);
    //rend->run(this->canv.get(), false);
    qDebug() << "Done parsing" << endl;
    emit done();
}

void ParseWorker::requestStop() {
    if(rend != nullptr)
       rend->requestStop = true;
}

AsyncRendSvg::~AsyncRendSvg() {}

ParseWorker::ParseWorker(int frames, shared_ptr<Canvas> canv, MainWindow *mw, cfdg_ptr design, shared_ptr<Renderer> rend): frames(frames), canv(canv), mw(mw), design(design), rend(rend) {}

ParseWorker::~ParseWorker() {
}

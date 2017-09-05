#include "qtcanvas.h"
#include "qtsystem.h"
#include <primShape.h>
#include <QObject>
#include <QTransform>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include <QApplication>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QtDebug>
#include <QSettings>

using namespace std;

void QtCanvas::primitive(int shape, RGBA8 c, agg::trans_affine tr) {
    //cout << "Primitive shape!" << endl;
    QApplication::processEvents();
    double* mat = new double[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    delete[] mat;
    specs.back().emplace(shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8));
}

void QtCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) {
    cout << "PATHological error!" << endl;
    return;
}

void QtCanvas::start(bool b, const agg::rgba &r, int i1, int i2) {
    specs.emplace();
    qDebug() << "New frame, now have " << specs.size() << " frames";
    this->Canvas::start(b, r, i1, i2);
}

QtCanvas::QtCanvas(int w, int h): Canvas(w, h) {}

QtCanvas::~QtCanvas() {

}

void ShapeSpec::drawOnScene(QGraphicsScene *scene) {
    QGraphicsItem *item;
    QBrush br(this->fill);
    QPen pe;
    pe.setStyle(Qt::NoPen);
    switch(this->type) {
    case primShape::circleType:
        item = scene->addEllipse(-0.5, -0.5, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::squareType:
        item = scene->addRect(-0.5, -0.5, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::fillType:
        scene->addRect(-scene->height()/2, -scene->width()/2, scene->height(), scene->width(), pe, br);
        break;
    case primShape::triangleType:
        QPainterPath *path = new QPainterPath(QPoint(0, 0));
        path->moveTo(-0.5, - sqrt(0.75) / 2 + 1 / sqrt(48));
        path->lineTo(0.5, - sqrt(0.75) / 2 + 1 / sqrt(48));
        path->lineTo(0, sqrt(0.75) / 2 + 1 / sqrt(48));
        path->lineTo(-0.5, - sqrt(0.75) / 2 + 1 / sqrt(48));
        item = scene->addPath(*path, pe, br);
        item->setTransform(this->qtr);
        delete path;
        break;
    }
}

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

#include "qtcanvas.h"
#include "qtcanvas-async.h"
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
#include <QSignalSpy>
#include <unistd.h>

using namespace std;

void QtCanvas::primitive(int shape, RGBA8 c, agg::trans_affine tr) {
    //cout << "Primitive shape!" << endl;
    QApplication::processEvents();
    double* mat = new double[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    delete[] mat;
    specs.push_back(new ShapeSpec(shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8)));
//    item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

void QtCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) {
    cout << "PATHological error!" << endl;
    return;
}

QtCanvas::~QtCanvas() {

}

void ShapeSpec::drawOnScene(QGraphicsScene *scene) {
    QGraphicsItem *item;
    QBrush br(this->fill);
    QPen pe;
    pe.setStyle(Qt::NoPen);
    switch(this->type) {
    case primShape::circleType:
        cout << "Circle!" << endl;
        item = scene->addEllipse(0, 0, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::squareType:
        cout << "Square!" << endl;
        item = scene->addRect(0, 0, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::fillType:
        cout << "Fill!" << endl;
        scene->addRect(-scene->height()/2, -scene->width()/2, scene->height(), scene->width(), pe, br);
        break;
    default:
        cout << "Shape " << this->type << " not recognized." << endl
             << "Circle: " << primShape::circleType << endl
             << "Square: " << primShape::squareType << endl
             << "Fill: " << primShape::fillType << endl
             << "Triangle: " << primShape::triangleType << endl;
        break;
    case primShape::triangleType:
        cout << "Triangle!" << endl;
        QPainterPath *path = new QPainterPath(QPoint(0, 0));
        path->lineTo(1, 0);
        path->lineTo(0.5, 0.8660254037844386);
        path->lineTo(0, 0);

        item = scene->addPath(*path, pe, br);
        item->setTransform(this->qtr);
        delete path;
        break;
    }
}

AsyncRenderer::AsyncRenderer(int w, int h, shared_ptr<QtCanvas> canv, QGraphicsScene *scene, MainWindow *mw): w(w),
    h(h),
    canv(canv),
    scene(scene),
    t(this) {
    p = new ParseWorker(w, h, canv, mw);
    qDebug() << "Beginning AsyncRenderer constructor" << endl;
    connect(p, SIGNAL(finished() ), p, SLOT(deleteLater() ));
    connect(p, SIGNAL(done() ), this, SLOT(render() ));
    p->start();
    parsing = true;
    qDebug() << "Done AsyncRenderer constructor" << endl;
}

AsyncRenderer::~AsyncRenderer() {
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
        shared_ptr<QSignalSpy> s(new QSignalSpy(this, SIGNAL(aborted()) ));
        emit abortRender();
        QtConcurrent::run([=] () {
            while(s->isEmpty()) {
                //qDebug() << "Processing events waiting for aborted signal";
            }
            delete this;
        });
    }
}

void AsyncRenderer::render() {
    parsing = false;
    rendering = true;
    qDebug() << "Beginning render";
    QSignalSpy spy(this, SIGNAL(abortRender()) );
    foreach(ShapeSpec *s, canv->specs) {
        qDebug() << "Processing events for render";
        QApplication::processEvents();
        if(!spy.isEmpty()) {
            qDebug() << "Yes, I should";
            emit aborted();
            return;
        } else {
                s->drawOnScene(scene);
        }
    }
    qDebug() << "Done render; setting rendering flag to false";
    rendering = false;
    emit done();
}

void ParseWorker::run() {
    qDebug() << "Beginning parsing" << endl;

    QtSystem sys;
    connect(&sys, SIGNAL(showmsg(const char*)), mw, SLOT(showmsg(const char*)));

    cfdg_ptr design(CFDG::ParseFile("/tmp/tmp.cfdg", &sys, 7394));
    if(design.get() == nullptr) {
        std::cerr << "Design evaluated to null; do you have a startshape?" << std::endl;
        if(unlink("/tmp/tmp.cfdg"))
            perror("Unlinking tempfile");
        return;
    }
    rend = shared_ptr<Renderer>(design->renderer(design,
                                w,
                                h,
                                1,
                                4,
                                2));
    if(rend == nullptr) {
        if(unlink("/tmp/tmp.cfdg"))
            perror("Unlinking tempfile");
        emit done();
        return;
    }
    rend->run(this->canv.get(), false);
    qDebug() << "Done parsing" << endl;
    emit done();
}

void ParseWorker::requestStop() {
    if(rend != nullptr)
       rend->requestStop = true;
}

ParseWorker::ParseWorker(int w, int h, shared_ptr<QtCanvas> canv, MainWindow *mw): w(w), h(h), canv(canv), rend(nullptr), mw(mw) {}

ParseWorker::~ParseWorker() {
}

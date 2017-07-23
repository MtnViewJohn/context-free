#include "qtcanvas.h"
#include <primShape.h>
#include <commandLineSystem.h>
#include <QObject>
#include <QTransform>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include <QApplication>
#include <QThread>
#include <QtDebug>
#include <unistd.h>

using namespace std;

void QtCanvas::primitive(int shape, RGBA8 c, agg::trans_affine tr) {
    cout << "Primitive shape!" << endl;
    QApplication::processEvents();
    double* mat = new double[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    delete[] mat;
    qtr.scale(1, -1);
    specs.push_back(new ShapeSpec(shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8)));
//    item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

void QtCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) {
    cout << "PATHological error!" << endl;
    return;
}

QtCanvas::~QtCanvas() {

}

void ShapeSpec::drawOnScene(QGraphicsScene &scene) {
    QGraphicsItem *item;
    QBrush br(this->fill);
    QPen pe;
    pe.setStyle(Qt::NoPen);
    switch(this->type) {
    case primShape::circleType:
        cout << "Circle!" << endl;
        item = scene.addEllipse(0, 0, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::squareType:
        cout << "Square!" << endl;
        item = scene.addRect(0, 0, 1, 1, pe, br);
        item->setTransform(this->qtr);
        break;
    case primShape::fillType:
        cout << "Fill!" << endl;
        scene.addRect(-scene.height()/2, -scene.width()/2, scene.height(), scene.width(), pe, br);
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

        item = scene.addPath(*path, pe, br);
        item->setTransform(this->qtr);
        delete path;
        break;
    }
}

AsyncRenderer::AsyncRenderer(int w, int h, shared_ptr<QtCanvas> canv, QGraphicsScene *scene): w(w),
    h(h),
    canv(canv),
    scene(scene),
    p(w, h, canv, this) {
    qDebug() << "Beginning AsyncRenderer constructor" << endl;
    connect(&p, &QThread::finished, &p, &QObject::deleteLater);
    p.start();
    connect(&p, &ParseWorker::done, this, &AsyncRenderer::render);
    qDebug() << "Done AsyncRenderer constructor" << endl;
}

AsyncRenderer::~AsyncRenderer() {
    qDebug() << "AsyncRenderer being destroyed!" << endl;
    p.quit();
    p.wait();
}

void AsyncRenderer::render() {
    qDebug() << "Beginning render";
    foreach(ShapeSpec *s, canv->specs)
        s->drawOnScene(*scene);
    qDebug() << "Done render";
    emit done();
    delete this;
}

void ParseWorker::run() {
    qDebug() << "Beginning parsing" << endl;
    CommandLineSystem sys;
    cfdg_ptr design(CFDG::ParseFile("/tmp/tmp.cfdg", &sys, 7394));
    if(design.get() == nullptr) {
        std::cerr << "OH NOES!" << std::endl;
        if(unlink("/tmp/tmp.cfdg"))
            perror("Unlinking tempfile");
        return;
    }
    shared_ptr<Renderer> rend(design->renderer(design,
                                               w,
                                               h,
                                               0.0001,
                                               4,
                                               2.0));
    rend->run(this->canv.get(), false);
    qDebug() << "Done parsing" << endl;
    emit done();
}

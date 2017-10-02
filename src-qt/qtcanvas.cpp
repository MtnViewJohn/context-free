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


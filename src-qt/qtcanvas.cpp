#include "qtcanvas.h"
#include "primShape.h"
#include <QObject>
#include <QTransform>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include <QApplication>
#include <QtDebug>

using namespace std;

void QtCanvas::primitive(int shape, RGBA8 c, agg::trans_affine tr) {
    cout << "Primitive shape!" << endl;
    QApplication::processEvents();
    double* mat = new double[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    qtr.scale(1, -1);
    QGraphicsItem *item;
    QBrush br(QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8));
    QPen pe;
    pe.setStyle(Qt::NoPen);
    switch(shape) {
    case primShape::circleType:
        cout << "Circle!" << endl;
        item = scene->addEllipse(0, 0, 1, 1, pe, br);
        item->setTransform(qtr);
        break;
    case primShape::squareType:
        cout << "Square!" << endl;
        item = scene->addRect(0, 0, 1, 1, pe, br);
        item->setTransform(qtr);
        break;
    case primShape::fillType:
        cout << "Fill!" << endl;
        scene->addRect(-scene->height()/2, -scene->width()/2, scene->height(), scene->width(), pe, br);
        break;
    case primShape::triangleType:
        cout << "Triangle!" << endl;
        QPainterPath *path = new QPainterPath(QPoint(0, 0));
        path->lineTo(1, 0);
        path->lineTo(0.5, 0.8660254037844386);
        path->lineTo(0, 0);

        item = scene->addPath(*path, pe, br);
        item->setTransform(qtr);
        delete path;
        break;
    }
    item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    //scene->addItem(item);
}

void QtCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) {
    cout << "PATHological error!" << endl;
    return;
}

QtCanvas::~QtCanvas() {

}

#include "qtcanvas.h"
#include "qtsystem.h"

#include <primShape.h>
#include <CmdInfo.h>
#include <agg2/agg_basics.h>
#include <cfdg.h>

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
    QApplication::processEvents();
    double mat[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    ShapeSpec spec(path_shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8));
    agg::vertex_block_storage<double> vertices = attr.mPath->vertices();
    for (unsigned i = 0; i < vertices.total_vertices(); ++i) {
        qDebug() << "Start vertex #" << i;
        // vertices.index(int idx, double* x, double* y) stores the coordinates of the vertex at index idx in *x and *y.
        // Why they couldn't use a vertex struct type and overload operator[] is beyond me.

        PathNode cur_node;
        vertices.vertex(i, &(cur_node.x), &(cur_node.y));
        unsigned cmd = vertices.command(i);
        if(agg::is_next_poly(cmd)) {
            qDebug() << "Next poly";
            cur_node.cmdt = CmdType::next_poly;
        }
        else if(agg::is_line_to(cmd)) {
            qDebug() << "Line to";
            cur_node.cmdt = CmdType::next_poly;
        }
        else if(agg::is_curve3(cmd)) {
            qDebug() << "Curve3";
            cur_node.cmdt = CmdType::curve3;

        }
        else if(agg::is_curve4(cmd)) {
            qDebug() << "Curve4";
            cur_node.cmdt = CmdType::curve4;
        }
        else if(agg::is_close(cmd)) {
            cur_node.cmdt = CmdType::close_path;
        }
    }
}

void QtCanvas::start(bool b, const agg::rgba &r, int i1, int i2) {
    specs.emplace();
    qDebug() << "New frame, now have " << specs.size() << " frames";
    this->Canvas::start(b, r, i1, i2);
}

QtCanvas::QtCanvas(int w, int h): Canvas(w, h) {}

QtCanvas::~QtCanvas() {

}

// Returns false if parsing fails
bool ShapeSpec::parsePath(QGraphicsScene *scene, QPen &pe, QBrush &br, QPainterPath *path) {
    double curvenodes[2][2];
    int cn_index = 0;
    foreach (PathNode n, nodes) {
        // vertices.index(int idx, double* x, double* y) stores the coordinates of the vertex at index idx in *x and *y.
        // Why they couldn't use a vertex struct type and overload operator[] is beyond me.
        switch(n.cmdt) {
            case CmdType::next_poly:
                qDebug() << "Next poly";
                path->moveTo(n.x, n.y);
                break;
            case CmdType::line_to:
                qDebug() << "Line to";
                path->lineTo(n.x, n.y);
                break;
            case CmdType::curve3:
                qDebug() << "Curve3";
                if(cn_index < 1) {
                    curvenodes[cn_index++][0] = n.x;
                    curvenodes[cn_index++][1] = n.y;
                } else {
                    path->quadTo(n.x,              n.y,
                                 curvenodes[0][0], curvenodes[0][1]);
                    cn_index = 0;
                }
                break;

            case CmdType::curve4:
                if(cn_index < 2) {
                    curvenodes[cn_index++][0] = n.x;
                    curvenodes[cn_index++][1] = n.y;
                } else {
                    path->cubicTo(n.x,              n.y,
                                  curvenodes[0][0], curvenodes[0][1],
                                  curvenodes[1][0], curvenodes[1][1]);
                    cn_index = 0;
                }
                break;
            case CmdType::close_path:
                qDebug() << "Close path";
                path->closeSubpath();
                break;
        }
    }
    QGraphicsItem *item = scene->addPath(*path, pe, br);
    item->setTransform(this->qtr);
    delete path;
}

void ShapeSpec::drawOnScene(QGraphicsScene *scene) {
    QGraphicsItem *item;
    QBrush br(this->fill);
    QPen pe;
    pe.setStyle(Qt::NoPen);
    QPainterPath *path;
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
    case path_shape:
        path = new QPainterPath(QPoint(0, 0));
        parsePath(scene, pe, br, path);
        break;
    case primShape::triangleType:
        path = new QPainterPath(QPoint(0, 0));
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


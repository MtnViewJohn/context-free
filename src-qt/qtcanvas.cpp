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
    QApplication::processEvents();
    double* mat = new double[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    delete[] mat;
    qDebug() << "RGBA:" << (c.r >> 8) << (c.g >> 8) << (c.b >> 8) << (c.a >> 8);
    specs.back().emplace(shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8));
}

void QtCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) {
    QApplication::processEvents();
    double mat[6];
    tr.store_to(mat);
    QTransform qtr(mat[0], mat[1], mat[2], mat[3], mat[4], mat[5]);
    ShapeSpec spec(path_shape, qtr, QColor(c.r >> 8, c.g >> 8, c.b >> 8, c.a >> 8));
    PathNode cur_node;
    attr.mPath->rewind(attr.mIndex);
    unsigned cmd;
    while (!agg::is_stop(cmd = attr.mPath->vertex(&cur_node.x, &cur_node.y))) {
        // vertices.index(int idx, double* x, double* y) stores the coordinates of the vertex at index idx in *x and *y.
        // Why they couldn't use a vertex struct type and overload operator[] is beyond me.

        switch(cmd & agg::path_cmd_mask) {
            case agg::path_cmd_move_to:
                qDebug() << "Move to";
                if(cmd & agg::path_flags_close)
                    cur_node.cmdt = CmdType::close_path;
                else
                    cur_node.cmdt = CmdType::move_to;
                break;
            case agg::path_cmd_line_to:
                qDebug() << "Line to";
                cur_node.cmdt = CmdType::line_to;
                break;

            case agg::path_cmd_curve3:
                qDebug() << "Curve3";
                cur_node.cmdt = CmdType::curve3;
                break;
            case agg::path_cmd_curve4:
                qDebug() << "Curve4";
                cur_node.cmdt = CmdType::curve4;
                break;
            case agg::path_cmd_end_poly:
                qDebug() << "Next poly";
                if(cmd & agg::path_flags_close)
                    cur_node.cmdt = CmdType::close_path;
                else
                    cur_node.cmdt = CmdType::move_to;
                break;
            default:
                qDebug() << "Warning: Couldn't parse agg node type";
                break;
        }

        spec.nodes.push_back(cur_node);
    }
    spec.cmd_info = attr;
    specs.back().push(spec);
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
    for (int i = 0; i < nodes.size(); i++) {
        PathNode n = nodes[i];
        switch(n.cmdt) {
            case CmdType::move_to:
                qDebug() << "Move to (node index" << i << ")";
                path->moveTo(n.x, n.y);
                break;
            case CmdType::line_to:
                //if(cn_index == 0) {
                //    cn_index++;
                //    path->moveTo(n.x, n.y);
                //} else {
                //    cn_index = 0;
                path->lineTo(n.x, n.y);
                //}
                break;
            case CmdType::curve3:
                if(i + 1 >= nodes.size()) {
                    qDebug() << "Not enough nodes for a Curve3!";
                    break;
                }
                path->quadTo(n.x         , n.y             ,
                             nodes[i + 1].x, nodes[i + 1].y);
                ++i;
                cn_index = 0;
                break;
            case CmdType::curve4:
                if(i + 2 >= nodes.size()) {
                    qDebug() << "Not enough nodes for a Curve4!";
                    break;
                }
                path->cubicTo(n.x         , n.y             ,
                              nodes[i + 1].x, nodes[i + 1].y,
                              nodes[i + 2].x, nodes[i + 2].y);
                i += 2;
                cn_index = 0;
                break;
            case CmdType::close_path:
                path->closeSubpath();
                path->moveTo(n.x, n.y);
                break;
            default:
                qDebug() << "Warning: Unsupported node type";
                break;
        }
    }
    if(!(cmd_info.mFlags & AST::CF_FILL)) {
        pe = QPen(shapeColor);
        pe.setWidthF(cmd_info.mStrokeWidth);
        br = QBrush(Qt::NoBrush);
        switch (cmd_info.mFlags & 15) {
            case agg::bevel_join:
                pe.setJoinStyle(Qt::BevelJoin);
                break;
            case agg::round_join:
                pe.setJoinStyle(Qt::RoundJoin);
                break;
            default:
                pe.setJoinStyle(Qt::MiterJoin);
                break;
        }
        switch ((cmd_info.mFlags >> 4) & 15) {
            case agg::square_cap:
                pe.setCapStyle(Qt::SquareCap);
                break;
            case agg::round_cap:
                pe.setCapStyle(Qt::RoundCap);
                break;
            default:
                pe.setCapStyle(Qt::FlatCap);
                break;
        }
    }
    if(cmd_info.mFlags & AST::CF_EVEN_ODD) {
        qDebug() << "Odd-even filling";
        path->setFillRule(Qt::OddEvenFill);
    }
    QGraphicsItem *item = scene->addPath(*path, pe, br);
    item->setTransform(this->qtr);
    delete path;
}

void ShapeSpec::drawOnScene(QGraphicsScene *scene) {
    QGraphicsItem *item;
    QBrush br(this->shapeColor);
    QPen pe;
    pe.setStyle(Qt::NoPen);
    QPainterPath *path;
    switch(this->type) {
    case primShape::circleType:
        qDebug() << "Drawing circle";
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
        qDebug() << "Drawing path";
        path = new QPainterPath(QPoint(0, 0));
        path->setFillRule(Qt::FillRule::WindingFill);
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


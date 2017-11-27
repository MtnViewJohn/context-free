#ifndef QTCANVAS_H
#define QTCANVAS_H
#include <cfdg.h>
#include <aggCanvas.h>
#include <QGraphicsScene>
#include <vector>
#include <QThread>
#include <QStatusBar>
#include <queue>
#include <primShape.h>
#include <CmdInfo.h>

using namespace std;

enum CmdType {
    move_to,
    line_to,
    curve3,
    curve4,
    close_path
};

struct PathNode {
        double x, y;
        CmdType cmdt;
};

class ShapeSpec {
        bool parsePath(QGraphicsScene *scene, QPen &pe, QBrush &br, QPainterPath *path);
    public:
        ShapeSpec(int type, QTransform qtr, QColor fill): type(type), qtr(qtr), shapeColor(fill) {}
        void drawOnScene(QGraphicsScene *scene);
        int type;
        vector<PathNode> nodes;
        QTransform qtr;
        QColor shapeColor;
        AST::CommandInfo cmd_info;
};

const int path_shape = -1;

class QtCanvas: public Canvas {
        int frameIndex;
    public:
        virtual ~QtCanvas();
        QtCanvas(int w, int h);
        void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo &attr) override;
        void primitive(int shape, RGBA8 c, agg::trans_affine tr) override;
        void start(bool b, const agg::rgba &r, int i1, int i2) override;
        queue<queue<ShapeSpec> > specs;
};

#endif // QTCANVAS_H


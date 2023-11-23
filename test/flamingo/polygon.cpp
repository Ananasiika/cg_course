#include "polygon.h"

polygon::polygon() {}

polygon::polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
}

polygon::polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &col) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
    _c = col;
}

QVector3D * polygon::get_points() { return _points; }

QColor polygon::get_color() {return _c;}

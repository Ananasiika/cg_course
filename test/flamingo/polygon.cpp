#include "polygon.h"

polygon::polygon() {}

polygon::polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
}

polygon::polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &col, std::vector<int> num) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
    _c = col;
    _num = num;
}

polygon::polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &col) {
    _points[0] = a;
    _points[1] = b;
    _points[2] = c;
    _c = col;
}

QVector3D * polygon::get_points() { return _points; }

QVector3D *polygon::get_points() const {
    return const_cast<QVector3D *>(_points);
}

QColor polygon::get_color() const {
    return _c;
}



QColor polygon::get_color() {return _c;}

std::vector<int> polygon::get_num() {return _num;}

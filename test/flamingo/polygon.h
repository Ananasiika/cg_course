#ifndef POLYGON_H
#define POLYGON_H

#include <QPainter>
#include <QVector3D>
#include <stddef.h>
#include <vector>

#define SIZE 3

class polygon {
public:
    polygon();
    polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c);
    polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &color, std::vector<int> num);
    polygon(const QVector3D &a, const QVector3D &b, const QVector3D &c, QColor &color);

    QVector3D *get_points();
    QVector3D *get_points() const;
    std::vector<int> get_num();
    QColor get_color();
    QColor get_color() const;

private:
    QVector3D _points[SIZE];
    std::vector<int> _num;
    QColor _c = QColor(120, 255, 150);
};

#endif // POLYGON_H

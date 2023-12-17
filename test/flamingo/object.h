#pragma once

#include <polygon.h>
#include <QColor>
#include <QPoint>
#include <QVector3D>

class object
{
public:
    object();
    object(std::vector<polygon> polygons, QVector3D center);
    object(std::vector<polygon> polygons);

    std::vector<polygon> get_polygons();
    QVector3D get_center();

private:
    std::vector<polygon> _polygons;
    QVector3D _center;
};

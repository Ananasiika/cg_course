#include "object.h"

object::object() {}

object::object(std::vector<polygon> polygons, QVector3D center)
    : _polygons(polygons), _center(center) {}

object::object(std::vector<polygon> polygons)
    : _polygons(polygons), _center(QVector3D(0, 0, 0)) {}

std::vector<polygon> object::get_polygons() { return _polygons; }

void object::set_polygons(std::vector<polygon> polys) { _polygons = polys; }

QVector3D object::get_center() { return _center; }

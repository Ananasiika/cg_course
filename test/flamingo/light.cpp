#include "light.h"

light::light() {}

light::light(QVector3D pos, double intensity)
    : _pos(pos), _intens(intensity) {}

QVector3D light::get_pos() { return _pos; }

QVector3D light::get_pos() const { return _pos; }

double light::get_intensity() { return _intens; }

double light::get_intensity() const { return _intens; }

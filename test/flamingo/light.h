#pragma once

#include <QColor>
#include <QVector3D>

class light {
public:
    light();
    light(QVector3D pos, double intensity);

    QVector3D get_pos();
    QVector3D get_pos() const;
    double get_intensity();
    void set_intensity(double intensity);
    void set_pos(QVector3D pos);
    double get_intensity() const;

private:
    QVector3D _pos;
    double _intens;
};

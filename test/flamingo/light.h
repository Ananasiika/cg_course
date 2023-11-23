#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>
#include <QVector3D>

class light {
public:
    light();
    light(QVector3D pos, double intensity);

    QVector3D get_pos();
    double get_intensity();

private:
    QVector3D _pos;
    double _intens;
};

#endif // LIGHT_H

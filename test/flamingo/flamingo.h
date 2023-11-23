#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <polygon.h>
#include <QColor>
#include <QPoint>
#include <QVector3D>

class flamingo
{
public:
    flamingo();
    flamingo(std::vector<polygon> polygons);

    std::vector<polygon> get_polygons();

private:
    std::vector<polygon> _polygons;
};

#endif // FLAMINGO_H

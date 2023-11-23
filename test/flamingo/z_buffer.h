#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include "light.h"
#include "flamingo.h"
#include <QColor>
#include <vector>
#include "math.h"
#include <stdlib.h>

struct Cell {
    double z;
    QColor c;
};

class z_buffer {
public:
    z_buffer(size_t x, size_t y);
    z_buffer();
    ~z_buffer();

    size_t sX();
    size_t sY();
    QColor getColorCell(int x, int y);
    void setSize(size_t x, size_t y);

    void put_flamingos(std::vector<flamingo> &flamingos, std::vector<light> &ls);
    void put_polygon(std::vector<QVector3D> &points, std::vector<light> &ls,
                                    QColor c, std::vector<std::vector<std::vector<double>>> &shadows);

    void show(QPainter &painter);
    void reflect(std::vector<flamingo> &flamingos);
    void shadows_on_lake(std::vector<flamingo> &flamingos, std::vector<light> &ls);


private:
    int _sX, _sY;
    std::vector<std::vector<Cell>> _buf;
};



#endif // z_buffer_H

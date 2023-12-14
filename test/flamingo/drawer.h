#ifndef DRAWER_H
#define DRAWER_H

#include "light.h"
#include "object.h"
#include <QColor>
#include <vector>
#include "math.h"
#include <thread>
#include <future>
#include <stdlib.h>

struct Cell {
    double z;
    QColor c;
    size_t obj;
};

class drawer {
public:
    drawer(size_t x, size_t y);
    drawer();
    ~drawer();

    size_t sX();
    size_t sY();
    QColor getColorCell(int x, int y);
    void setSize(size_t x, size_t y);

    void put_objects(std::vector<object> &objects, const std::vector<light> &ls);
    void put_polygon(std::vector<QVector3D> &points, const std::vector<light> &ls,
                                    QColor c, int obj);

    void show(std::shared_ptr<QImage> &image);
    void reflect(std::vector<object> &objects);
    void shadows(std::vector<object> &objects, const std::vector<light> &ls);
    std::tuple<int, int, int, int> border(std::vector<QVector3D> points);
    void putShadowPolygon(std::vector<std::vector<double>> &zb, std::vector<QVector3D> &points, const light &ls);
    void putShadowBuffer(std::vector<std::vector<double>> &zb, std::vector<object> &objects, const light &ls);
    QColor calculateColor(int x, int y, double z, QVector3D N, const std::vector<light> ls, QColor c);
    void reset_zb(std::vector<std::vector<double>> &zb);
    void set_factors(double scat, double dif, double spec, double tran, double ref);


private:
    int f = 1;
    int _sX, _sY, count_flamingo = 2;
    std::vector<std::vector<std::vector<double>>> _shadows;
    std::vector<std::vector<Cell>> _buf;
    double _scat, _dif, _spec, _tran, _ref;
};



#endif // drawer_H

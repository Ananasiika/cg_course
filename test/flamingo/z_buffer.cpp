#include "z_buffer.h"
#include <QDebug>

#define EPS 1e-8

bool isInside(int x, int y, std::vector<QVector3D> &points);
double calculateZ(int x, int y, std::tuple<int, int, int, int> coef);
std::tuple<int, int, int, int> planeCoef(std::vector<QVector3D> points);

z_buffer::z_buffer(size_t x, size_t y) : _sX(x), _sY(y) {
    for (size_t i = 0; i < x; i++) {
        std::vector<Cell> v;
        _buf.push_back(v);
        for (size_t j = 0; j < y; j++) {
            Cell value;
            if (j < _sY / 4)
                value = Cell{.z = INT_MIN, .c = QColor(153, 204, 255)};
            else
                value = Cell{.z = INT_MIN, .c = QColor(Qt::white)};
            _buf[i].push_back(value);
        }
    }
}

z_buffer::z_buffer() {}

z_buffer::~z_buffer() {}

std::tuple<int, int, int, int> planeCoef(std::vector<QVector3D> points) {
    int x1 = points[0].x();
    int y1 = points[0].y();
    int z1 = points[0].z();

    int x2 = points[1].x();
    int y2 = points[1].y();
    int z2 = points[1].z();

    int x3 = points[2].x();
    int y3 = points[2].y();
    int z3 = points[2].z();

    int a = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    int b = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
    int c = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    int d = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) +
                        x3 * (y1 * z2 - y2 * z1));
    return std::tuple<int, int, int, int>(a, b, c, d);
}

void z_buffer::setSize(size_t x, size_t y)
{
        _sX = x;
        _sY = y;
        _buf.clear();
        for (size_t i = 0; i < x; i++) {
            std::vector<Cell> v;
            _buf.push_back(v);
            for (size_t j = 0; j < y; j++) {
                Cell value;
                if (j < y / 4)
                    value = Cell{.z = INT_MIN, .c = QColor(153, 204, 255)};
                else
                    value = Cell{.z = INT_MIN, .c = QColor(Qt::white)};
                _buf[i].push_back(value);
            }
        }
}

void reset_zb(std::vector<std::vector<double>> &zb, size_t x, size_t y)
{
        zb.clear();
        for(size_t i = 0; i < x; i++)
        {
                std::vector<double> v;
                zb.push_back(v);
                for (size_t j = 0; j < y; j++) {
                    zb[i].push_back(INT_MAX);
                }
        }
}

void putShadowPolygon(std::vector<std::vector<double>> &zb, std::vector<QVector3D> &points,
                                                 light &ls) {
    if (points.size() < 3)
        return;
    int ymax, ymin, xmax, xmin;

    ymax = ymin = points[0].y();
    xmax = xmin = points[0].x();
    for (size_t i = 1; i < points.size(); i++) {
        int x = points[i].x();
        int y = points[i].y();
        if (y > ymax)
            ymax = y;
        else if (y < ymin)
            ymin = y;
        if (x > xmax)
            xmax = x;
        else if (x < xmin)
            xmin = x;
    }

    // от 0 до макс буфер
    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < zb[0].size()) ? ymax : zb[0].size() - 1;
    xmin = (xmin < 0) ? 0 : xmin;
    xmax = (xmax < zb.size()) ? xmax : zb.size() - 1;

    std::tuple<int, int, int, int> coef = planeCoef(points);


    for (int i = xmin; i <= xmax; i++)
        for (int j = ymin; j <= ymax; j++) {
            if (isInside(i, j, points)) {
                double z = calculateZ(i, j, coef);
                double light_dist = (QVector3D(i, j, z) - ls.get_pos()).length();
                if (light_dist < zb[i][j]) {
                    zb[i][j] = light_dist;
                }
            }
        }
}

void putShadowBuffer(std::vector<std::vector<double>> &zb, std::vector<flamingo> &flamingos, light &ls)
{
        for(size_t i = 0; i < flamingos.size(); i++)
        {
                std::vector<polygon> polygons = flamingos[i].get_polygons();
                for (size_t j = 0; j < polygons.size(); j++)
                {
                        QVector3D* pv = polygons[j].get_points();
                        std::vector<QVector3D> pointsPolygon = {pv[0], pv[1], pv[2]};
                        putShadowPolygon(zb, pointsPolygon, ls);
                }
        }
}


void z_buffer::reflect(std::vector<flamingo> &flamingos)
{
    for (size_t i = 0; i < flamingos.size() - 1; i++)
    {

        std::vector<polygon> polygons = flamingos[i].get_polygons();

        float min_y = std::numeric_limits<float>::min();
        float min_x, min_z;

        for (polygon &poly : polygons)
        {
            for (int i = 0; i < 3; i++)
            {
                float y = poly.get_points()[i].y();
                if (y > min_y)
                {
                    min_x = poly.get_points()[i].x();
                    min_y = y;
                    min_z = poly.get_points()[i].z();
                }
            }
        }

        std::vector<polygon> reflected_polygons;

        QVector3D plane_normal(0, -1, 0);
        QVector3D plane_point(min_x, min_y, min_z);

        for (polygon &poly : polygons)
        {
            std::vector<QVector3D> points = {poly.get_points()[0], poly.get_points()[1], poly.get_points()[2]};

            for (int i = 0; i < 3; i++)
            {
                QVector3D reflected_point = points[i] - (2 * QVector3D::dotProduct(points[i] - plane_point, plane_normal) * plane_normal);
                points[i] = reflected_point;
            }

            int ymax, ymin, xmax, xmin;
            ymax = ymin = points[0].y();
            xmax = xmin = points[0].x();
            for (size_t i = 1; i < 3; i++) {
                int x = points[i].x();
                int y = points[i].y();
                if (y > ymax)
                    ymax = y;
                else if (y < ymin)
                    ymin = y;
                if (x > xmax)
                    xmax = x;
                else if (x < xmin)
                    xmin = x;
            }

            // от 0 до макс буфер
            ymin = (ymin < 0) ? 0 : ymin;
            ymax = (ymax < _sY) ? ymax : _sY - 1;
            xmin = (xmin < 0) ? 0 : xmin;
            xmax = (xmax < _sX) ? xmax : _sX - 1;

            std::tuple<int, int, int, int> coef = planeCoef(points);
            for (int i = xmin; i <= xmax; i++)
                for (int j = ymin; j <= ymax; j++) {
                    if (isInside(i, j, points)) {
                        double z = calculateZ(i, j, coef);
                        if (z > _buf[i][j].z) {
                            _buf[i][j].z = z;
                            QColor c = getColorCell(poly.get_points()[0].x(), poly.get_points()[0].y());
                            c.setAlpha(200);
                            _buf[i][j].c = c;
                        }
                    }
                }

        }
    }


}

void z_buffer::shadows_on_lake(std::vector<flamingo> &flamingos, std::vector<light> &ls)
{

    for (size_t i = 0; i < flamingos.size() - 1; i++)
    {

        for (polygon& polygon_flam : flamingos[i].get_polygons())
        {
            QVector3D *points = polygon_flam.get_points();
            std::vector<QVector3D> new_points;
            for (size_t i = 0; i < 3; i++)
            {
                QVector3D direction = ls[0].get_pos() - points[i];
                direction.normalize();
                //float z_cur = calculateZ(int(points[i].x()), int(points[i].y()), coef);
                float t = -points[i].z() / direction.z();
                QVector3D intersection = points[i] + t * direction;
                new_points.push_back(intersection);
            }

            int ymax, ymin, xmax, xmin;

            ymax = ymin = new_points[0].y();
            xmax = xmin = new_points[0].x();
            for (size_t i = 1; i < new_points.size(); i++) {
                int x = new_points[i].x();
                int y = new_points[i].y();
                if (y > ymax)
                    ymax = y;
                else if (y < ymin)
                    ymin = y;
                if (x > xmax)
                    xmax = x;
                else if (x < xmin)
                    xmin = x;
            }

            // от 0 до макс буфер
            ymin = (ymin < 0) ? 0 : ymin;
            ymax = (ymax < _sY) ? ymax : _sY - 1;
            xmin = (xmin < 0) ? 0 : xmin;
            xmax = (xmax < _sX) ? xmax : _sX - 1;


            for (int i = xmin; i <= xmax; i++)
                for (int j = ymin; j <= ymax; j++)
                    if (isInside(i, j, new_points) && _buf[i][j].z == 0)
                         _buf[i][j].c.setAlpha(100);
        }
    }
}

void z_buffer::put_flamingos(std::vector<flamingo> &flamingos, std::vector<light> &ls) {
        std::vector<std::vector<std::vector<double>>> shadows;
        std::vector<std::vector<double>> zb;
        for(int i = 0; i < ls.size(); i++)
        {
                reset_zb(zb, _sX, _sY);
                putShadowBuffer(zb, flamingos, ls[i]);
                shadows.push_back(zb);
        }

        for (size_t i = 0; i < flamingos.size(); i++)
        {
                std::vector<polygon> polygons = flamingos[i].get_polygons();
                for (size_t j = 0; j < polygons.size(); j++)
                {
                        QVector3D* pv = polygons[j].get_points();
                        std::vector<QVector3D> pointsPolygon = {pv[0], pv[1], pv[2]};
                        put_polygon(pointsPolygon, ls, polygons[j].get_color(), shadows);
                }
        }

        //reflect(flamingos);
        shadows_on_lake(flamingos, ls);

}

QColor z_buffer::getColorCell(int x, int y) { return _buf[x][y].c; }

size_t z_buffer::sX() { return _sX; }
size_t z_buffer::sY() { return _sY; }

QColor calculateColor(int x, int y, double z,
                                            QVector3D N,
                                            std::vector<light> ls, QColor c,
                                            std::vector<std::vector<std::vector<double>>> &shadows) {
        QVector3D point(x,y,z);
        double diffuse_light_intensity = 0;
            for (size_t i = 0; i < ls.size(); i++) {
                    QVector3D light_dir = (ls[i].get_pos() - point);

                    if (light_dir.length() <= shadows[i][x][y])
                    {
                        light_dir.normalize();
                        QVector3D R = 2 * QVector3D::dotProduct(light_dir, N) * N - light_dir;
                        diffuse_light_intensity += ls[i].get_intensity() * (std::max(0.f, QVector3D::dotProduct(light_dir, N)) * 0.8 + 0.5 * (QVector3D::dotProduct(QVector3D(0, 0, 1), R)));
                    }
            }

     QVector3D cv(c.red() / 255.0, c.green() / 255.0, c.blue() / 255.0);
     cv = cv * diffuse_light_intensity;
     QColor color = QColor(255 * std::max(0.f, std::min(1.f, cv.x())), 255 * std::max(0.f, std::min(1.f, cv.y())), 255 * std::max(0.f, std::min(1.f, cv.z())), c.alpha());

    return color;
}

double calculateZ(int x, int y, std::tuple<int, int, int, int> coef) {
    int a = std::get<0>(coef);
    int b = std::get<1>(coef);
    int c = std::get<2>(coef);
    int d = std::get<3>(coef);

    if (c == 0)
        return 0;
    double z = -1.0 * (a * x + b * y + d) / c;
    return z;
}

bool isInside(int x, int y, std::vector<QVector3D> &points) {
    if (points.size() < 3)
        return false;
    QPoint a(points[0].x(), points[0].y());
    QPoint b(points[1].x(), points[1].y());
    QPoint c(points[2].x(), points[2].y());

    int abp =
            x * (b.y() - a.y()) + y * (a.x() - b.x()) + a.y() * b.x() - a.x() * b.y();
    int bcp =
            x * (c.y() - b.y()) + y * (b.x() - c.x()) + b.y() * c.x() - b.x() * c.y();
    int cap =
            x * (a.y() - c.y()) + y * (c.x() - a.x()) + c.y() * a.x() - c.x() * a.y();

    return ((abp <= 0 && bcp <= 0 && cap <= 0) ||
                    (abp >= 0 && bcp >= 0 && cap >= 0));
}

void z_buffer::put_polygon(std::vector<QVector3D> &points,
                                                 std::vector<light> &ls, QColor c,
                                                 std::vector<std::vector<std::vector<double>>> &shadows) {
    if (points.size() < 3)
        return;
    int ymax, ymin, xmax, xmin;

    ymax = ymin = points[0].y();
    xmax = xmin = points[0].x();
    for (size_t i = 1; i < points.size(); i++) {
        int x = points[i].x();
        int y = points[i].y();
        if (y > ymax)
            ymax = y;
        else if (y < ymin)
            ymin = y;
        if (x > xmax)
            xmax = x;
        else if (x < xmin)
            xmin = x;
    }

    // от 0 до макс буфер
    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < _sY) ? ymax : _sY - 1;
    xmin = (xmin < 0) ? 0 : xmin;
    xmax = (xmax < _sX) ? xmax : _sX - 1;


    std::tuple<int, int, int, int> coef = planeCoef(points);
    QVector3D N(std::get<0>(coef), std::get<1>(coef), std::get<2>(coef));
    N.normalize();
    if (QVector3D::dotProduct(N,QVector3D(0, 0, 5000)) < 0)
            N *= (-1);

    for (int i = xmin; i <= xmax; i++)
        for (int j = ymin; j <= ymax; j++) {
            if (isInside(i, j, points)) {
                double z = calculateZ(i, j, coef);
                if (z > _buf[i][j].z) {
                    _buf[i][j].z = z;
                    _buf[i][j].c = calculateColor(i, j, z, N, ls, c, shadows);
                }
            }
        }
}

void z_buffer::show(QPainter &painter) {
    for (size_t i = 0; i < _sX; i++)
        for (size_t j = 0; j < _sY; j++) {
            painter.setPen(getColorCell(i, j));
            painter.drawPoint(i, j);
        }
}





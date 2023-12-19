#include "drawer.h"
#include <QDebug>

#define EPS 1e-8

bool is_inside(int x, int y, std::vector<QVector3D> &points);
double calculateZ(int x, int y, std::tuple<int, int, int, int> coef);
std::tuple<int, int, int, int> plane_coef(std::vector<QVector3D> points);

drawer::drawer(size_t x, size_t y) : _sX(x), _sY(y) {
    _buf.clear();
    for (size_t i = 0; i < x; i++) {
        std::vector<Cell> v;
        _buf.push_back(v);
        for (size_t j = 0; j < y; j++) {
            Cell value;
            value = Cell{.z = INT_MIN, .c = QColor(Qt::white), .obj = INT_MAX};
            _buf[i].push_back(value);
        }
    }
}

drawer::drawer() {}

drawer::~drawer() {}

std::tuple<int, int, int, int> drawer::border(std::vector<QVector3D> points) {
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

    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < _sY) ? ymax : _sY - 1;
    xmin = (xmin < 0) ? 0 : xmin;
    xmax = (xmax < _sX) ? xmax : _sX - 1;
    return std::tuple<int, int, int, int>(ymax, ymin, xmax, xmin);
}

std::tuple<int, int, int, int> drawer::plane_coef(std::vector<QVector3D> points) {
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

void drawer::setSize(size_t x, size_t y)
{
    _shadows.clear();
    _sX = x;
    _sY = y;
    _buf.clear();
    for (size_t i = 0; i < x; i++) {
        std::vector<Cell> v;
        _buf.push_back(v);
        for (size_t j = 0; j < y; j++) {
            Cell value;
            value = Cell{.z = INT_MIN, .c = QColor(Qt::white), .obj = INT_MAX};
            _buf[i].push_back(value);
        }
    }
}

void drawer::reset_zb(std::vector<std::vector<double>> &zb)
{
    zb.clear();
    for(int i = 0; i < _sX; i++)
    {
        std::vector<double> v;
        zb.push_back(v);
        for (int j = 0; j < _sY; j++)
            zb[i].push_back(INT_MAX);
    }
}

void drawer::putShadowPolygon(std::vector<std::vector<double>> &zb, std::vector<QVector3D> &points, const light &ls) {
    if (points.size() < 3)
        return;

    std::tuple<int, int, int, int> bord = border(points);
    std::tuple<int, int, int, int> coef = plane_coef(points);

    for (int i = std::get<3>(bord); i <= std::get<2>(bord); i++)
        for (int j = std::get<1>(bord); j <= std::get<0>(bord); j++) {
            if (is_inside(i, j, points)) {
                double z = calculateZ(i, j, coef);
                double light_dist = (QVector3D(i, j, z) - ls.get_pos()).length();
                if (light_dist < zb[i][j]) {
                    zb[i][j] = light_dist;
                }
            }
        }
}

void drawer::putShadowBuffer(std::vector<std::vector<double>> &zb, std::vector<object> &objects, const light &ls)
{
    for(size_t i = 0; i < objects.size(); i++)
    {
        std::vector<polygon> polygons = objects[i].get_polygons();
        for (size_t j = 0; j < polygons.size(); j++)
        {
            QVector3D *pv = polygons[j].get_points();
            std::vector<QVector3D> pointsPolygon = {pv[0], pv[1], pv[2]};
            putShadowPolygon(zb, pointsPolygon, ls);
        }
    }
}

void drawer::reflect(std::vector<object> &objects)
{
    //QVector3D N(0, 0, 1);
    for (size_t o = objects.size() - 1; o >= 1; o--)
    {
        std::vector<polygon> polygons = objects[o].get_polygons();
        float y_max = 0, x, y;
        for (polygon &poly : polygons)
        {
            std::vector<QVector3D> points = {poly.get_points()[0], poly.get_points()[1], poly.get_points()[2]};
            for (auto &p : points)
                if (p.z() < 0.5 && p.y() > y_max)
                    y_max = p.y();
        }
        for (polygon &poly : polygons)
        {
            std::vector<QVector3D> points = {poly.get_points()[0], poly.get_points()[1], poly.get_points()[2]};
            std::tuple<int, int, int, int> bord = border(points);
            std::tuple<int, int, int, int> coef = plane_coef(points);
            for (int i = std::get<3>(bord); i <= std::get<2>(bord); i++)
                for (int j = std::get<1>(bord); j <= std::get<0>(bord); j++)
                    if (is_inside(i, j, points)) {
                        double z = calculateZ(i, j, coef);
                        if ((o >= 2 && _buf[i][j + 2 * (y_max - j)].z == 0 && j + 2 * (y_max - j) < _sY - 1 && j + 2 * (y_max - j) > 0) || (o == 1 && _buf[i][j + z * 2].z == 0 && j + 2 * z < _sY - 1 && j + 2 * z > 0))
                        {
                            x = (points[0].x() + points[1].x() + points[2].x()) / 3;
                            y = (points[0].y() + points[1].y() + points[2].y()) / 3;
                            if (o == 1)
                                y = std::fmax(points[1].y(), points[2].y()) - 2;
                            if (x <= 0 || y <= 0 || x >= _sX - 1 || y >= _sY - 1)
                                continue;
                            QColor c = getColorCell(x, y);
                            c.setAlpha(200);
                            if (o == 1)
                                _buf[i][j + z * 2].c = c;
                            else
                                _buf[i][j + 2 * (y_max - j)].c = c;
                        }
//                      QVector3D r =  QVector3D(i, j + z, z) + 2 * QVector3D::dotProduct(N, QVector3D(i, j + z, z)) / QVector3D::dotProduct(N, N) * N;
//                      if (_buf[r.x()][r.y()].z == 0 && r.y() < _sY)
//                            _buf[r.x()][r.y()].c = c;

                    }
        }
    }

}


void drawer::shadows(std::vector<object> &objects, const std::vector<light> &ls)
{

    for (size_t li = 0; li < ls.size(); li++)
    {
        double intens = ls[li].get_intensity();
        for (size_t o = 1; o < objects.size(); o++)
            for (polygon& poly : objects[o].get_polygons())
            {
                QVector3D *points = poly.get_points();
                std::vector<QVector3D> new_points;
                for (size_t i = 0; i < 3; i++)
                {
                    QVector3D direction = ls[li].get_pos() - points[i];
                    direction.normalize();
                    float t = -points[i].z() / direction.z();
                    QVector3D intersection = points[i] + t * direction;
                    new_points.push_back(intersection);
                }

                std::tuple<int, int, int, int> bord = border(new_points);
                for (int i = std::get<3>(bord); i <= std::get<2>(bord); i++)
                    for (int j = std::get<1>(bord); j <= std::get<0>(bord); j++)
                        if (is_inside(i, j, new_points) && (_buf[i][j].z == 0 || _buf[i][j].obj < o))
                             _buf[i][j].c = _buf[i][j].c.darker(150 + intens * 105);/*_buf[i][j].c.red() + 1 ? (_buf[i][j].c.red() + 1 <= 255) : 255, \
                                                 _buf[i][j].c.green() + 1 ? (_buf[i][j].c.green() + 1 <= 255) : 255, \
                                                 _buf[i][j].c.blue() + 1 ? (_buf[i][j].c.blue() + 1 <= 255) : 255);*/
            }
    }
}

void drawer::put_objects(std::vector<object> &objects, const std::vector<light> &ls)
{
    std::vector<std::vector<double>> zb;
    for(size_t i = 0; i < ls.size(); i++)
    {
        reset_zb(zb);
        putShadowBuffer(zb, objects, ls[i]);
        _shadows.push_back(zb);
    }

    for (size_t i = 0; i < objects.size(); i++)
    {

        std::vector<polygon> polygons = objects[i].get_polygons();

        int numThreads = 3;
        int polygonsPerThread = (polygons.size() + numThreads - 1) / numThreads;
        std::vector<std::future<void>> futures;

        for (int t = 0; t < numThreads; ++t)
        {
            int startIdx = t * polygonsPerThread;
            int endIdx = std::min((t + 1) * polygonsPerThread, int(polygons.size()));
            std::vector<polygon> threadPolygons(polygons.begin() + startIdx, polygons.begin() + endIdx);
            futures.push_back(std::async(std::launch::async, [=]() {
                    for (const polygon& poly : threadPolygons)
                    {
                        QVector3D* pv = poly.get_points();
                        std::vector<QVector3D> pointsPolygon = {pv[0], pv[1], pv[2]};
                        put_polygon(pointsPolygon, ls, poly.get_color(), i);
                    }
                }));
        }
        for (auto& future : futures)
        {
            future.wait();
        }
    }
    reflect(objects);
    shadows(objects, ls);
}

void drawer::set_factors(double scat, double dif, double spec, double tran, double ref)
{
    _scat = scat;
    _dif = dif;
    _spec = spec;
    _tran = tran;
    _ref = ref;
}

QColor drawer::getColorCell(int x, int y) { return _buf[x][y].c; }

size_t drawer::sX() { return _sX; }
size_t drawer::sY() { return _sY; }

QColor drawer::calculateColor(int x, int y, double z, QVector3D N, std::vector<light> ls, QColor c) {
    QVector3D point(x, y, z);
    double light_intensity = 0.2;
    for (size_t i = 0; i < ls.size(); i++) {
        QVector3D light_dir = (ls[i].get_pos() - point);

        if (light_dir.length() == _shadows[i][x][y])
        {
            light_dir.normalize();
            QVector3D R = 2 * QVector3D::dotProduct(light_dir, N) * N - light_dir;
            light_intensity += ls[i].get_intensity() * (std::max(0.f, QVector3D::dotProduct(light_dir, N)) * _dif + \
                                                                _spec * (QVector3D::dotProduct(QVector3D(0, 0, 1), R))) + \
                                                                std::max(0.f, QVector3D::dotProduct(light_dir, N)) * _dif * _scat;
        }
    }
    QVector3D cv(c.red() * c.alpha() / 255.0, c.green() * c.alpha() / 255.0, c.blue() * c.alpha() / 255.0);
    if (c.alpha() < 255)
        cv = cv + QVector3D(190.0 * (255 - c.alpha()) / 255.0, 245.0 * (255 - c.alpha()) / 255.0, 255.0 * (255 - c.alpha()) / 255.0);
    cv = cv * light_intensity;
    QColor color = QColor(std::max(0.f, std::min(255.f, cv.x())), std::max(0.f, std::min(255.f, cv.y())), \
                          std::max(0.f, std::min(255.f, cv.z())));

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

bool drawer::is_inside(int x, int y, std::vector<QVector3D> &points) {
    if (points.size() < 3)
        return false;

    float x1 = points[0].x();
    float y1 = points[0].y();
    float x2 = points[1].x();
    float y2 = points[1].y();
    float x3 = points[2].x();
    float y3 = points[2].y();

    float alpha = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    float beta = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    float gamma = 1.0f - alpha - beta;

    return (alpha >= 0.0f) && (beta >= 0.0f) && (gamma >= 0.0f);
}

void drawer::put_polygon(std::vector<QVector3D> &points,
                                                 const std::vector<light> &ls, QColor c, int obj) {
    if (points.size() < 3)
        return;

    std::tuple<int, int, int, int> coef = plane_coef(points);
    QVector3D N(std::get<0>(coef), std::get<1>(coef), std::get<2>(coef));
    N.normalize();
    if (QVector3D::dotProduct(N,QVector3D(0, 0, 5000)) < 0)
            N *= (-1);

    std::tuple<int, int, int, int> bord = border(points);
    for (int i = std::get<3>(bord); i <= std::get<2>(bord); i++)
        for (int j = std::get<1>(bord); j <= std::get<0>(bord); j++) {
            if (is_inside(i, j, points)) {
                double z = calculateZ(i, j, coef);
                if (z > _buf[i][j].z) {
                    _buf[i][j].z = z;
                    _buf[i][j].obj = obj;
                    _buf[i][j].c = calculateColor(i, j, z, N, ls, c);
                }
            }
        }
}

void drawer::show(std::shared_ptr<QImage> &image) {
    for (int i = 0; i < _sX; i++)
        for (int j = 0; j < _sY; j++) {
            image->setPixelColor(i, j, getColorCell(i, j));
        }
}





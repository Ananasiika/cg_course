#include "objects.h"
#include <QDebug>

objects::objects() {}

objects::objects(std::vector<light> lights, std::vector<object> objects,
               int canvas_height, int canvas_width)
    : _lights(lights), _objects(objects), _canvas_height(canvas_height), _canvas_width(canvas_width)
{
}

std::vector<light> objects::get_light() { return _lights; }

void objects::add_object(object &f)
{
    _objects.push_back(f);
}

void objects::delete_objects()
{
    while (_objects.size() > 2)
        _objects.pop_back();
}

void objects::delete_plant()
{
    while (_objects.size() > 1)
        _objects.pop_back();
}

void objects::set_density_plant(double density) {
    density_plant = density;
}

void objects::delete_lights()
{
    _lights.clear();
}

void objects::add_light(light &l)
{
    _lights.push_back(l);
}

void objects::set_size(size_t width, size_t height)
{
    _canvas_height = height;
    _canvas_width = width;
}

void objects::set_factors(QString scat, QString dif, QString spec, QString tran, QString ref)
{
    bool ok;
    double number = scat.toDouble(&ok);
    if (ok)
        _scat = number;
    number = dif.toDouble(&ok);
    if (ok)
        _dif = number;
    number = spec.toDouble(&ok);
    if (ok)
        _spec = number;
    number = tran.toDouble(&ok);
    if (ok)
        _tran = number;
    number = ref.toDouble(&ok);
    if (ok)
        _ref = number;
}


void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim))
    {
        out.push_back(s);
    }
}

void add_polygons_to_flamingo(std::vector<polygon> &polygons, std::vector<QVector3D> &verticies,
                  const std::vector<std::string> &out, QColor color)
{
    std::vector<int> a;
    for (size_t i = 0; i < 3; i++)
        a.push_back(std::stoi(out[i + 1]) - 1);
    QVector3D v1 = verticies[a[0]];
    QVector3D v2 = verticies[a[1]];
    QVector3D v3 = verticies[a[2]];

    polygons.push_back(polygon(v1, v2, v3, color, a));
}

void add_polygons(std::vector<polygon> &polygons, std::vector<QVector3D> &verticies, std::vector<int> a, QColor color, float tran, int x)
{
    QVector3D v1 = verticies[0];
    QVector3D v2 = verticies[1];
    QVector3D v3 = verticies[2];

    QVector3D right_knee_ch;
    QVector3D left_knee_ch;
    QVector3D right_sole_ch;
    QVector3D left_sole_ch;
    QVector3D left_toel_ch;
    QVector3D left_heel_ch;
    QVector3D left_h_heel_ch;

    float i = (x + 180) % 30;
    if (i <= 15)
    {
        left_knee_ch = QVector3D(i * 16 / 5 - 2, i * 5 / 4, -i * 22 / 15);
        left_sole_ch = QVector3D(i / 5, i * 10 / 3 - 4, -i * 25 / 15);
        right_knee_ch = QVector3D(-i, 0, 0);
        right_sole_ch = QVector3D(-i, 0, 0);
        left_toel_ch = QVector3D(0, i / 2, 0);
        left_heel_ch = QVector3D(-i / 4, 0, 0);
        left_h_heel_ch = QVector3D(0, -i / 4, 0);
    }
    else
    {

        left_toel_ch = QVector3D(0, 7.5, 0);
        left_heel_ch = QVector3D(-3.75, 0, 0);
        left_h_heel_ch = QVector3D(0, -3.75, 0);
        left_knee_ch = QVector3D(3 * 20 - i, 18.75, -22);
        left_sole_ch = QVector3D(18.5 - i, 46, -25);
        right_knee_ch = QVector3D(-i + 5 / 6 * (i - 15), -(i - 15) - 2, (i - 15) * 22 / 15);
        right_sole_ch = QVector3D(-15 + (i - 15) * 4 / 3, -(i - 15) * 4 - 2, (i - 15) * 25 / 15);
    }

    std::vector<int> left_toel = {445, 446, 447, 448};
    if (find(left_toel.begin(), left_toel.end(), a[0]) != left_toel.end())
        v1 += left_toel_ch;
    if (find(left_toel.begin(), left_toel.end(), a[1]) != left_toel.end())
        v2 += left_toel_ch;
    if (find(left_toel.begin(), left_toel.end(), a[2]) != left_toel.end())
        v3 += left_toel_ch;

    std::vector<int> left_heel = {407, 408, 409, 410, 411, 441, 442};
    if (find(left_heel.begin(), left_heel.end(), a[0]) != left_heel.end())
        v1 += left_heel_ch;
    if (find(left_heel.begin(), left_heel.end(), a[1]) != left_heel.end())
        v2 += left_heel_ch;
    if (find(left_heel.begin(), left_heel.end(), a[2]) != left_heel.end())
        v3 += left_heel_ch;

    std::vector<int> left_h_heel = {137, 138, 139, 140, 143, 144, 262, 263, 264, 267, 268, 386, 387, 388, 391, 392, 395, 396, 397, 399, 400, 401, 402, 403, 404, 405, 406};
    if (find(left_h_heel.begin(), left_h_heel.end(), a[0]) != left_h_heel.end())
        v1 += left_h_heel_ch;
    if (find(left_h_heel.begin(), left_h_heel.end(), a[1]) != left_h_heel.end())
        v2 += left_h_heel_ch;
    if (find(left_h_heel.begin(), left_h_heel.end(), a[2]) != left_h_heel.end())
        v3 += left_h_heel_ch;

    std::vector<int> right_knee = {413, 414, 415, 416};
    if (find(right_knee.begin(), right_knee.end(), a[0]) != right_knee.end())
        v1 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[1]) != right_knee.end())
        v2 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[2]) != right_knee.end())
        v3 += right_knee_ch;

    std::vector<int> left_knee = {133, 134, 135, 136, 258, 259, 260, 261, 382, 383, 384, 385, 398};
    if (find(left_knee.begin(), left_knee.end(), a[0]) != left_knee.end())
        v1 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[1]) != left_knee.end())
        v2 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[2]) != left_knee.end())
        v3 += left_knee_ch;

    std::vector<int> right_sole = {417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436};
    if (find(right_sole.begin(), right_sole.end(), a[0]) != right_sole.end())
        v1 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[1]) != right_sole.end())
        v2 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[2]) != right_sole.end())
        v3 += right_sole_ch;

    std::vector<int> left_sole = {137, 138, 139, 140, 143, 144, 262, 263, 264, 267, 268, 386, 387, 388, 391, 392, 395, 396, 397, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 441, 442, 443, 444, 445, 446, 447, 448};
    if (find(left_sole.begin(), left_sole.end(), a[0]) != left_sole.end())
        v1 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[1]) != left_sole.end())
        v2 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[2]) != left_sole.end())
        v3 += left_sole_ch;
    color.setAlpha((1 - tran) * 255);
    polygons.push_back(polygon(v1, v2, v3, color));

    /*if (v1.x() >= 294 && v1.x() <= 298 && v1.y() >= 476 && v1.y() <= 480)
        qDebug() << a[0];
    if (v2.x() >= 294 && v2.x() <= 298 && v2.y() >= 476 && v2.y() <= 480)
        qDebug() << a[1];
    if (v3.x() >= 294 && v3.x() <= 298 && v3.y() >= 476 && v3.y() <= 480)
        qDebug() << a[2];*/
}

QVector3D rotatePoint(const QVector3D& point)
{
    return point - QVector3D(0, point.z(), 0);
}

bool compareBySecondColumn(const std::vector<float>& a, const std::vector<float>& b) {
    return a[1] < b[1];
}


void objects::add_flamingo_coord(float x, float y)
{
    count_flamingo++;
    std::vector<float> coord = {x, y};
    coord_flamingos.push_back(coord);
    sort(coord_flamingos.begin(), coord_flamingos.end(), compareBySecondColumn);
}

int objects::get_count_flamingos()
{
    return count_flamingo;
}

std::vector<float> objects::get_coord_flamingo(int ind)
{
    return coord_flamingos[ind];
}

void objects::add_flamingo(float x, float y)
{
    QVector3D centre = flamingo.get_center() + QVector3D(x, -y, 0);
    std::vector<polygon> polygons;
    for (auto poly: flamingo.get_polygons())
    {
        QVector3D *vs = poly.get_points();
        for (size_t i = 0; i < 3; i++)
        {
            vs[i] += QVector3D(x, -y, 0);
            vs[i] = rotatePoint(vs[i]);
        }
        QColor color = poly.get_color();
        std::vector<QVector3D> points = {vs[0], vs[1], vs[2]};
        add_polygons(polygons, points, poly.get_num(), color, _tran, x);
    }
    _objects.push_back(object(polygons, centre));
}

bool objects::load_file(const char *filename)
{
    std::string s;
    std::ifstream f, f_m;

    const char *file = "/home/larisa/cg_course/flamingo.mtl";
    f_m.open(file);
    if (!f_m.is_open())
    {
        std::cout << "Ошибка открытия файла\n\n";
        return 0;
    }

    std::vector<QColor> colors;
    while (getline(f_m, s))
    {
        std::vector<std::string> out;
        tokenize(s, ' ', out);
        if (out.size() == 4 && out[0] == "Kd")
        {
            colors.push_back(QColor(int(255 * stod(out[1])), int(255 * stod(out[2])), int(255 * stod(out[3]))));
        }
    }
    f_m.close();

    f.open(filename);
    if (!f.is_open())
    {
        std::cout << "Ошибка открытия файла\n\n";
        return 0;
    }
    std::vector<polygon> polygons;
    std::vector<QVector3D> verticies;
    QColor color = QColor(1, 1, 1);
    QColor color_cur = QColor(100, 100, 100);
    size_t i = 0;
    while (getline(f, s))
    {
        std::vector<std::string> out;
        tokenize(s, ' ', out);

        if (out[0] == "v")
            verticies.push_back(QVector3D(stod(out[1]) * 2 * 0.6, 0.6 * (stod(out[2]) - stod(out[3])), 0.6 * stod(out[3])));
        if (out[0] == "usemtl")
        {
            color_cur = colors[i++];
            color = color_cur;
        }
        if (out[0] == "f")
        {
            add_polygons_to_flamingo(polygons, verticies, out, color);
        }
    }
    flamingo = object(polygons, verticies[0]);
    f.close();
    _objects.push_back(object(generate_lake()));
    generate_plant();
    return 1;
}

std::vector<polygon> objects::generate_lake()
{
    std::vector<polygon> lake;
    QVector3D v1(0, 0, 0);
    QVector3D v2(_canvas_width, 0, 0);
    QVector3D v3(0, _canvas_height, 0);
    QVector3D v4(_canvas_width, _canvas_height, 0);
    QColor color(190, 245, 255, 255);
    lake.push_back(polygon(v1, v2, v3, color));
    lake.push_back(polygon(v4, v2, v3, color));

    return lake;
}

void objects::generate_plant()
{
    srand(time(NULL));
    std::vector<polygon> plant;
    for (int i = 0; i < 100 * density_plant; i++)
    {
        int x = rand() % 1050;
        int y  = rand() % 800 + 30;
        int z1 = rand() % 30 + 10;
        int z2 = rand() % 30 + 10;
        int z3 = rand() % 30 + 10;

        QVector3D v1(x, y, 0);
        QVector3D v2(x + 10, y, 0);
        QVector3D v3(x + 8, y, 0);
        QVector3D v4(x + 16, y, 0);
        QVector3D v5(x + 14, y, 0);
        QVector3D v6(x + 24, y, 0);

        QVector3D v7(x + 4, y - 8, 0);
        QVector3D v8(x + 12, y - 8, 0);
        QVector3D v9(x + 20, y - 8, 0);

        QVector3D v10(x + 4, y - 4 - z1, z1);
        QVector3D v11(x + 12, y - 4 - z2, z2);
        QVector3D v12(x + 20, y - 4 - z3, z3);
        QColor color(Qt::green);
        color.setAlpha(255 * (1 - _tran));
        plant.push_back(polygon(v1, v2, v7, color));
        plant.push_back(polygon(v3, v4, v8, color));
        plant.push_back(polygon(v5, v6, v9, color));

        plant.push_back(polygon(v1, v7, v10, color));
        plant.push_back(polygon(v1, v2, v10, color));
        plant.push_back(polygon(v2, v7, v10, color));

        plant.push_back(polygon(v3, v4, v11, color));
        plant.push_back(polygon(v3, v8, v11, color));
        plant.push_back(polygon(v4, v8, v11, color));

        plant.push_back(polygon(v5, v6, v12, color));
        plant.push_back(polygon(v5, v9, v12, color));
        plant.push_back(polygon(v6, v9, v12, color));
    }
    _objects.push_back(object(plant));
}

std::shared_ptr<QImage> objects::draw()
{
    std::shared_ptr<QImage> image = std::make_shared<QImage>(
        _canvas_width, _canvas_height, QImage::Format_RGBA64);

    dr.setSize(_canvas_width, _canvas_height);
    dr.set_factors(_scat, _dif, _spec, _tran, _ref);

    dr.put_objects(_objects, _lights);

    dr.show(image);

    return image;
}

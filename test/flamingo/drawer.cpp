#include "drawer.h"
#include <QDebug>

drawer::drawer() {}

drawer::drawer(std::vector<light> lights, std::vector<object> objects,
               int canvas_height, int canvas_width)
    : _lights(lights), _objects(objects), _canvas_height(canvas_height), _canvas_width(canvas_width)
{
}

std::vector<light> drawer::get_light() { return _lights; }

void drawer::add_object(object &f)
{
    _objects.push_back(f);
}

void drawer::delete_objects()
{
    while (_objects.size() > 2)
        _objects.pop_back();
}

void drawer::delete_lights()
{
    _lights.clear();
}

void drawer::add_light(light &l)
{
    _lights.push_back(l);
}

void drawer::set_size(size_t width, size_t height)
{
    _canvas_height = height;
    _canvas_width = width;
}

void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out)
{
    // строим поток из строки
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

void add_polygons(std::vector<polygon> &polygons, std::vector<QVector3D> &verticies, std::vector<int> a, QColor color, int x)
{
    QVector3D v1 = verticies[0];
    QVector3D v2 = verticies[1];
    QVector3D v3 = verticies[2];

    QVector3D right_knee_ch;
    QVector3D left_knee_ch;
    QVector3D right_sole_ch;
    QVector3D left_sole_ch;

    float i = (x + 180) % 30;
    if (i <= 15)
    {
        left_knee_ch = QVector3D(i * 16 / 5 - 2, i * 5 / 4, -i * 22 / 15);
        left_sole_ch = QVector3D(i / 5, i * 10 / 3 - 4, -i * 25 / 15);
        right_knee_ch = QVector3D(-i, 0, 0);
        right_sole_ch = QVector3D(-i, 0, 0);
    }
    else
    {
        left_knee_ch = QVector3D(3 * 20 - i, 18.75, -22);
        left_sole_ch = QVector3D(18.5 - i, 46, -25);
        right_knee_ch = QVector3D(-i + 5 / 6 * (i - 15), -(i - 15) - 2, (i - 15) * 22 / 15);
        right_sole_ch = QVector3D(-15 + (i - 15) * 4 / 3, -(i - 15) * 4 - 2, (i - 15) * 25 / 15);
    }

    std::vector<int> right_knee = {413, 414, 415, 416};
    //std::vector<int> right_knee = {427, 428, 429, 430};
    if (find(right_knee.begin(), right_knee.end(), a[0]) != right_knee.end())
        v1 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[1]) != right_knee.end())
        v2 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[2]) != right_knee.end())
        v3 += right_knee_ch;

    std::vector<int> left_knee = {133, 134, 135, 136, 258, 259, 260, 261, 382, 383, 384, 385, 398};
    //std::vector<int> left_knee = {133, 134, 135, 136, 262, 263, 264, 265, 389, 390, 391, 392, 408};
    if (find(left_knee.begin(), left_knee.end(), a[0]) != left_knee.end())
        v1 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[1]) != left_knee.end())
        v2 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[2]) != left_knee.end())
        v3 += left_knee_ch;

    std::vector<int> right_sole = {417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436};
    //std::vector<int> right_sole = {431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450};
    if (find(right_sole.begin(), right_sole.end(), a[0]) != right_sole.end())
        v1 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[1]) != right_sole.end())
        v2 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[2]) != right_sole.end())
        v3 += right_sole_ch;

    std::vector<int> left_sole = {137, 138, 139, 140, 143, 144, 262, 263, 264, 267, 268, 386, 387, 388, 391, 392, 395, 396, 397, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 441, 442, 443, 444, 445, 446, 447, 448};
    //std::vector<int> left_sole = {137, 138, 139, 140, 145, 146, 266, 267, 268, 272, 273, 393, 394, 395, 399, 400, 405, 406, 407, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425};
    if (find(left_sole.begin(), left_sole.end(), a[0]) != left_sole.end())
        v1 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[1]) != left_sole.end())
        v2 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[2]) != left_sole.end())
        v3 += left_sole_ch;
    polygons.push_back(polygon(v1, v2, v3, color));
}

QVector3D rotatePoint(const QVector3D& point)
{
    return point - QVector3D(0, point.z(), 0);
}

void drawer::add_flamingo(float x, float y, double c)
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
        add_polygons(polygons, points, poly.get_num(), color, x);
    }
    _objects.push_back(object(polygons, centre));
}

bool drawer::load_file(const char *filename)
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
    _objects.push_back(object(generate_plant(1)));
    return 1;
}

//bool drawer::load_file_flower(const char *filename)
//{
//    std::string s;
//    std::ifstream f, f_m;

//    const char *file = "/home/larisa/cg_course/rose.mtl";
//    f_m.open(file);
//    if (!f_m.is_open())
//    {
//        std::cout << "Ошибка открытия файла\n\n";
//        return 0;
//    }

//    std::vector<QColor> colors;
//    while (getline(f_m, s))
//    {
//        std::vector<std::string> out;
//        tokenize(s, ' ', out);
//        if (out.size() == 4 && out[0] == "Kd")
//        {
//            colors.push_back(QColor(int(255 * stod(out[1])), int(255 * stod(out[2])), int(255 * stod(out[3]))));
//        }
//    }
//    f_m.close();

//    f.open(filename);
//    if (!f.is_open())
//    {
//        std::cout << "Ошибка открытия файла\n\n";
//        return 0;
//    }
//    std::vector<polygon> polygons;
//    std::vector<QVector3D> verticies;
//    QColor color = QColor(1, 1, 1);
//    QColor color_cur = QColor(100, 100, 100);
//    size_t i = 0;
//    while (getline(f, s))
//    {
//        std::vector<std::string> out;
//        tokenize(s, ' ', out);

//        if (out[0] == "v")
//            verticies.push_back(QVector3D(stod(out[1]) * 2 + 100, stod(out[2]) * 2 + 500 - stod(out[3]) * 20, stod(out[3]) * 20));
//        if (out[0] == "usemtl")
//        {
//            color_cur = colors[i++];
//            color = color_cur;
//        }
//        if (out[0] == "f")
//        {
//            add_polygons_to_flamingo(polygons, verticies, out, color);
//        }
//    }
//    flower = object(polygons, verticies[0]);

//    //add_flowers(1);
//    f.close();
//    return 1;
//}

//void drawer::add_flowers(int p)
//{
//    std::vector<polygon> flowers;
//    QVector3D v1, v2, v3;
//    for (size_t i = 0; i < 20; i++)
//    {
//        int x = random() % 1100 - 100;
//        int y  = random() % 500 - 200;
//        for (auto &poly : flower.get_polygons())
//        {
//            QVector3D *points = poly.get_points();
//            v1 = points[0] + QVector3D(x, y, 0);
//            v2 = points[1] + QVector3D(x, y, 0);
//            v3 = points[2] + QVector3D(x, y, 0);
//            QColor color = poly.get_color();
//            flowers.push_back(polygon(v1, v2, v3, color));
//        }
//    }
//    _objects.push_back(object(flowers));
//}

std::vector<polygon> drawer::generate_lake()
{
    std::vector<polygon> lake;
    QVector3D v1(_canvas_width, _canvas_height / 4, 0);
    QVector3D v2(0, _canvas_height, 0);
    QVector3D v3(0, _canvas_height / 4, 0);
    QVector3D v4(_canvas_width, _canvas_height, 0);
    QColor color(204, 255, 255, 255);
    lake.push_back(polygon(v1, v2, v3, color));
    lake.push_back(polygon(v4, v2, v1, color));
    return lake;
}

std::vector<polygon> drawer::generate_plant(int p)
{
    std::vector<polygon> plant;
    for (int i = 0; i < 50; i++)
    {
        int x = random() % 1050;
        int y  = random() % 500 + 300;
        int z1 = random() % 30 + 10;
        int z2 = random() % 30 + 10;
        int z3 = random() % 30 + 10;

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
        plant.push_back(polygon(v1, v2, v7));
        plant.push_back(polygon(v3, v4, v8));
        plant.push_back(polygon(v5, v6, v9));

        plant.push_back(polygon(v1, v7, v10));
        plant.push_back(polygon(v1, v2, v10));
        plant.push_back(polygon(v2, v7, v10));

        plant.push_back(polygon(v3, v4, v11));
        plant.push_back(polygon(v3, v8, v11));
        plant.push_back(polygon(v4, v8, v11));

        plant.push_back(polygon(v5, v6, v12));
        plant.push_back(polygon(v5, v9, v12));
        plant.push_back(polygon(v6, v9, v12));
    }
    return plant;
}

std::shared_ptr<QImage> drawer::draw()
{
    std::shared_ptr<QImage> image = std::make_shared<QImage>(
        _canvas_width, _canvas_height, QImage::Format_RGB32);
    QPainter painter(image.get());
    image->fill(Qt::black);

    zb.setSize(_canvas_width, _canvas_height);
    zb.put_objects(_objects, _lights);
    zb.show(painter);

    painter.end();
    return image;
}

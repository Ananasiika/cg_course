#include "drawer.h"
#include <QDebug>

drawer::drawer() {}

drawer::drawer(std::vector<light> lights, std::vector<flamingo> flamingos,
               int canvas_height, int canvas_width)
    : _lights(lights), _flamingos(flamingos), _canvas_height(canvas_height), _canvas_width(canvas_width)
{
}

std::vector<light> drawer::get_light() { return _lights; }

void drawer::add_flamingo(flamingo &f)
{
    _flamingos.push_back(f);
}

void drawer::delete_flamingos()
{
    _flamingos.clear();
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

void add_polygons(std::vector<polygon> &polygons, std::vector<QVector3D> &verticies,
                  const std::vector<std::string> &out, QColor color, int x, int y)
{
    int a[3];
    for (size_t i = 0; i < 3; i++)
        a[i] = std::stoi(out[i + 1]) - 1;
    QVector3D v1 = verticies[a[0]];
    QVector3D v2 = verticies[a[1]];
    QVector3D v3 = verticies[a[2]];

    QVector3D right_knee_ch;
    QVector3D left_knee_ch;
    QVector3D right_sole_ch;
    QVector3D left_sole_ch;

    float i = (x + 120) % 30;
    if (i <= 15)
    {
        left_knee_ch = QVector3D(i * 13 / 5, i, 0);
        left_sole_ch = QVector3D(i * 10.5 / 15, i * 5 / 3, 0);
        right_knee_ch = QVector3D(-i, i, 0);
        right_sole_ch = QVector3D(-i, i, 0);
    }
    else
    {
        left_knee_ch = QVector3D(3 * 18 - i, i, 0);
        left_sole_ch = QVector3D(25.5 - i, 15 * 2 / 3 + i, 0);
        right_knee_ch = QVector3D(-i + 5 / 6 * (i - 15), 15 - (i - 15) , 0);
        right_sole_ch = QVector3D(-15 + (i - 15) * 4 / 3, 15 - (i - 15) * 3 , 0);
    }

    std::vector<int> right_knee = {427, 428, 429, 430};
    if (find(right_knee.begin(), right_knee.end(), a[0]) != right_knee.end())
        v1 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[1]) != right_knee.end())
        v2 += right_knee_ch;
    if (find(right_knee.begin(), right_knee.end(), a[2]) != right_knee.end())
        v3 += right_knee_ch;

    std::vector<int> left_knee = {133, 134, 135, 136, 262, 263, 264, 265, 389, 390, 391, 392, 408};
    if (find(left_knee.begin(), left_knee.end(), a[0]) != left_knee.end())
        v1 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[1]) != left_knee.end())
        v2 += left_knee_ch;
    if (find(left_knee.begin(), left_knee.end(), a[2]) != left_knee.end())
        v3 += left_knee_ch;

    std::vector<int> right_sole = {431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450};
    if (find(right_sole.begin(), right_sole.end(), a[0]) != right_sole.end())
        v1 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[1]) != right_sole.end())
        v2 += right_sole_ch;
    if (find(right_sole.begin(), right_sole.end(), a[2]) != right_sole.end())
        v3 += right_sole_ch;

    std::vector<int> left_sole = {137, 138, 139, 140, 145, 146, 266, 267, 268, 272, 273, 393, 394, 395, 399, 400, 405, 406, 407, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425};
    if (find(left_sole.begin(), left_sole.end(), a[0]) != left_sole.end())
        v1 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[1]) != left_sole.end())
        v2 += left_sole_ch;
    if (find(left_sole.begin(), left_sole.end(), a[2]) != left_sole.end())
        v3 += left_sole_ch;
    polygons.push_back(polygon(v1, v2, v3, color));
}
#include <QtGui/QMatrix4x4>

QVector3D rotatePoint(const QVector3D& point)
{
    float z = point.z();
    float y = point.y();
    float x = point.x();
    QMatrix4x4 transformationMatrix;
    transformationMatrix.setToIdentity();
    //transformationMatrix.translate(-x, -y, 0);
    transformationMatrix.rotate(90, 1, 0, 0);

    transformationMatrix.translate(x, y, 0);

    QVector3D rotatedPoint = transformationMatrix.map(point);
    rotatedPoint.setZ(z);
    return point - QVector3D(0, point.z(), 0);
}

bool drawer::load_file(const char *filename, float x, float y, double c)
{
    std::ifstream f_legs;
    const char *file_legs = "/home/larisa/cg_course/legs.txt";
    f_legs.open(file_legs);
    if (!f_legs.is_open())
    {
        std::cout << "Ошибка открытия файла\n\n";
        return 0;
    }
    std::vector<int> legs_numbers;
    std::string s;
    while (getline(f_legs, s))
    {
        legs_numbers.push_back(stoi(s));
    }
    f_legs.close();

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
        {
            verticies.push_back(QVector3D(stod(out[1]), stod(out[2]), stod(out[3])) + QVector3D(x, -y, 0));
            QVector3D temp = verticies[verticies.size() - 1];
            QVector3D centre = verticies[0];
            QVector3D scaledPoint = centre + (temp - centre) * c;
            if (verticies.size() != 1)
                scaledPoint.setZ(scaledPoint.z() * c);
            verticies[verticies.size() - 1] = rotatePoint(scaledPoint);
        }
        if (out[0] == "usemtl")
        {
            color_cur = colors[i++];
            color = color_cur;
        }
        if (out[0] == "g")
        {
            //            if (out[1] == "off")
            //                k = 0;
            //            else if (out[1] == "Группа.001")
            //                std::cout << 1;
        }
        if (out[0] == "f")
        {
            add_polygons(polygons, verticies, out, color, x, y);
        }
    }
    _flamingos.push_back(flamingo(polygons));
    f.close();
    return 1;
}

std::vector<polygon> drawer::reflect_polygons()
{
    std::vector<polygon> polygons = _flamingos[0].get_polygons();

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
        QVector3D points[3] = {poly.get_points()[0], poly.get_points()[1], poly.get_points()[2]};
        QColor color = poly.get_color();

        // Отражаем каждую вершину относительно плоскости перпендикулярной объекту
        for (int i = 0; i < 3; i++)
        {
            QVector3D reflected_point = points[i] - (2 * QVector3D::dotProduct(points[i] - plane_point, plane_normal) * plane_normal);
            points[i] = reflected_point;
        }

        // Создаем отраженный полигон
        color.setAlpha(200);
        polygon reflected_polygon(points[0], points[1], points[2], color);

        // Добавляем отраженный полигон в вектор отраженных полигонов
        reflected_polygons.push_back(reflected_polygon);
    }

    return reflected_polygons;
}

std::vector<polygon> drawer::generate_lake()
{
    std::vector<polygon> lake;
    for (float x = 0; x < _canvas_width - 10; x += 10)
        for (float y = _canvas_height / 4; y < _canvas_height - 10; y += 10)
        {
            QVector3D v1(x, y, 0);
            QVector3D v2(x + 10, y, 0);
            QVector3D v3(x, y + 10, 0);
            QVector3D v4(x + 10, y + 10, 0);
            QColor color(204, 255, 255);
            lake.push_back(polygon(v1, v2, v3, color));
            lake.push_back(polygon(v4, v2, v3, color));
        }
    return lake;
}

std::vector<polygon> drawer::generate_plant(int p)
{
    std::vector<polygon> plant;
    for (int i = 0; i < 100; i++)
    {
        int x = random() % 1000;
        int y  = random() % 500 + 300;
        int z = random() % 40;

        QVector3D v1(x - 7, y, 0);
        QVector3D v2(x + 7, y, 0);
        QVector3D v3(x, y - 7, 0);
        QVector3D v4(x, y - 3 - z, z);
        QColor color(Qt::green);
        plant.push_back(polygon(v1, v2, v3));
        plant.push_back(polygon(v1, v2, v4));
        plant.push_back(polygon(v1, v3, v4));
        plant.push_back(polygon(v2, v3, v4));
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


    _flamingos.push_back(flamingo(generate_plant(1)));
    _flamingos.push_back(flamingo(generate_lake()));
    zb.put_flamingos(_flamingos, _lights);
    zb.show(painter);

    painter.end();
    return image;
}

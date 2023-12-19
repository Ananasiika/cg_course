#pragma once

#include "object.h"
#include "light.h"
#include "drawer.h"
#include <QImage>
#include <QPainter>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include <sstream>

class objects
{
public:
  objects();
  objects(std::vector<light> lights,
         std::vector<object> objects, int canvas_height, int canvas_width);

  std::vector<light> get_light();
  void delete_objects();
  void delete_plant();
  void delete_lights();
  void add_object(object &f);
  void add_light(light &l);
  void set_size(size_t width, size_t height);

  bool load_file(const char *filename);
  void add_flamingo(float x, float y);
  std::vector<polygon> generate_lake();
  void generate_plant();
  void set_density_plant(double density);
  int get_count_flamingos();
  void set_factors(QString scat, QString dif, QString spec, QString tran, QString ref);
  std::vector<float> get_coord_flamingo(int ind);
  QVector3D translatePoint(const QVector3D& point);
  void move(int x, int y, double k);
  void move_plant(int x, int y, double k);

  void add_flamingo_coord(float x, float y);
  std::shared_ptr<QImage> draw();

private:
  std::vector<light> _lights;
  std::vector<object> _objects;
  object flamingo;
  int count_flamingo = 0;
  std::vector<std::vector<float>> coord_flamingos;
  int _canvas_height, _canvas_width;
  double density_plant = 0.5;
  int x_tran = 5, y_tran = 10;
  double coef_tran = 1;
  double _scat = 0.2, _dif = 0.8, _spec = 0.5, _tran = 0, _ref = 1;
  drawer dr;
};

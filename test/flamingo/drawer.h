#ifndef DRAWER_H
#define DRAWER_H

#include "flamingo.h"
#include "light.h"
#include "z_buffer.h"
#include <QImage>
#include <QPainter>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include <sstream>

#define HEIGHT_SCREEN 800
#define WIDTH_SCREEN 1200

class drawer
{
public:
  drawer();
  drawer(std::vector<light> lights,
         std::vector<flamingo> flamingos, int canvas_height, int canvas_width);

  std::vector<light> get_light();
  void delete_flamingos();
  void delete_lights();
  void add_flamingo(flamingo &f);
  void add_light(light &l);
  void set_size(size_t width, size_t height);

  bool load_file(const char *filename, float x, float y, double c);
  std::vector<polygon> generate_lake();
  std::vector<polygon> generate_plant(int p);
  std::vector<polygon> reflect_polygons();

  std::shared_ptr<QImage> draw();

private:
  std::vector<light> _lights;
  std::vector<flamingo> _flamingos;
  int _canvas_height;
  int _canvas_width;
  z_buffer zb;
};

#endif // DRAWER_H

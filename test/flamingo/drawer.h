#ifndef DRAWER_H
#define DRAWER_H

#include "object.h"
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
         std::vector<object> objects, int canvas_height, int canvas_width);

  std::vector<light> get_light();
  void delete_objects();
  void delete_lights();
  void add_object(object &f);
  void add_light(light &l);
  void set_size(size_t width, size_t height);

  bool load_file(const char *filename);
  //bool load_file_flower(const char *filename);
  void add_flamingo(float x, float y, double c);
  //void add_flowers(int p);
  std::vector<polygon> generate_lake();
  std::vector<polygon> generate_plant(int p);
  std::vector<polygon> reflect_polygons();

  std::shared_ptr<QImage> draw();

private:
  std::vector<light> _lights;
  std::vector<object> _objects;
  object flamingo;
  //object flower;
  int count_flamingo;
  int _canvas_height;
  int _canvas_width;
  z_buffer zb;
};

#endif // DRAWER_H

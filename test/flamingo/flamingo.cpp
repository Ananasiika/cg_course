#include "flamingo.h"

flamingo::flamingo() {}

flamingo::flamingo(std::vector<polygon> polygons)
    : _polygons(polygons) {}

std::vector<polygon> flamingo::get_polygons() { return _polygons; }

#ifndef LIGHT_H
#define LIGHT_H

#include <raytracer/core/colors.hpp>
#include <raytracer/core/matrices/matrix.hpp>

struct PointLight
{
    Color intensity;
    Point position;

    PointLight(Point position, Color intensity) : position(position), intensity(intensity) {}
};

#endif
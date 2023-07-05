#ifndef SPHERES_H
#define SPHERES_H

#include <raytracer/core/shapes/shape.hpp>

struct Sphere : public IShape
{
    Sphere(std::string id) : IShape(id)
    {
    }
};

#endif
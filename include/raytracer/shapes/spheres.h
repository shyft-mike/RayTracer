#ifndef SPHERES_H
#define SPHERES_H

#include "raytracer/shapes/shapes.h"

struct Sphere : public IShape
{
    Sphere(std::string id) : IShape(id)
    {
    }
};

#endif
#ifndef SPHERES_H
#define SPHERES_H

#include "shapes.h"

struct Sphere : public IShape
{
    Sphere(std::string id) : IShape(id)
    {
    }
};

#endif
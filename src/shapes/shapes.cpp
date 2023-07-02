#include "raytracer/shapes/shapes.h"
#include "raytracer/matrices/transformations.h"

IShape IShape::translate(float x, float y, float z)
{
    this->transform = this->transform * translation(x, y, z);

    return *this;
}

bool IShape::operator==(const IShape &other) const
{
    return this->id == other.id;
}
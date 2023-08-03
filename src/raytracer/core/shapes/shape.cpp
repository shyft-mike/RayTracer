#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>
#include <raytracer/core/rays.hpp>

IShape IShape::translate(float x, float y, float z)
{
    this->transform = this->transform * translation(x, y, z);

    return *this;
}

IShape IShape::scale(float x, float y, float z)
{
    this->transform = this->transform * scaling(x, y, z);

    return *this;
}

IShape IShape::rotate_x(float radians)
{
    this->transform = this->transform * rotation_x(radians);

    return *this;
}

IShape IShape::rotate_y(float radians)
{
    this->transform = this->transform * rotation_y(radians);

    return *this;
}

IShape IShape::rotate_z(float radians)
{
    this->transform = this->transform * rotation_z(radians);

    return *this;
}

bool IShape::operator==(const IShape &other) const
{
    if (this == &other)
    {
        return true;
    }

    return this->id == other.id;
}

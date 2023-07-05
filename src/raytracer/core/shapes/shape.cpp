#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>

Vector IShape::normal_at(float x, float y, float z)
{
    Point object_point = MatrixHelper(inverse(this->transform) * Point(x, y, z)).to_point();
    Vector object_normal = object_point - Point(0, 0, 0);
    Vector world_normal = MatrixHelper(transpose(inverse(this->transform)) * object_normal).to_vector();
    return world_normal.normalize();
}

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
    return this->id == other.id;
}
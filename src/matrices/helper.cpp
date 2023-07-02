#include "raytracer/matrices/matrices.h"
#include "raytracer/matrices/helper.h"
#include "raytracer/matrices/transformations.h"

MatrixHelper MatrixHelper::identity()
{
    return MatrixHelper({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}

Point MatrixHelper::to_point()
{
    return Point(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0]);
}

Vector MatrixHelper::to_vector()
{
    return Vector(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0]);
}

MatrixHelper MatrixHelper::transpose()
{
    return MatrixHelper(::transpose(this->matrix));
}

MatrixHelper MatrixHelper::invert()
{
    return ::inverse(this->matrix);
}

MatrixHelper MatrixHelper::translate(float x, float y, float z)
{
    return MatrixHelper(this->matrix * ::translation(x, y, z));
}

MatrixHelper MatrixHelper::rotate_x(float radians)
{
    return MatrixHelper(this->matrix * ::rotation_x(radians));
}

MatrixHelper MatrixHelper::rotate_y(float radians)
{
    return MatrixHelper(this->matrix * ::rotation_y(radians));
}

MatrixHelper MatrixHelper::rotate_z(float radians)
{
    return MatrixHelper(this->matrix * ::rotation_z(radians));
}

MatrixHelper MatrixHelper::scale(float x, float y, float z)
{
    return MatrixHelper(this->matrix * ::scaling(x, y, z));
}

#include "matrices.h"
#include "transformations.h"
#include "cartesia.h"

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

Matrix translation(float x, float y, float z)
{
    return {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}};
}

Matrix translation(const Point &point)
{
    return translation(point.x, point.y, point.z);
}

Matrix scaling(float x, float y, float z)
{
    return {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1}};
}

Matrix scaling(const Point &point)
{
    return scaling(point.x, point.y, point.z);
}

Matrix rotation_x(float radians)
{
    return {
        {1, 0, 0, 0},
        {0, std::cos(radians), -std::sin(radians), 0},
        {0, std::sin(radians), std::cos(radians), 0},
        {0, 0, 0, 1}};
}

Matrix rotation_y(float radians)
{
    return {
        {std::cos(radians), 0, std::sin(radians), 0},
        {0, 1, 0, 0},
        {-std::sin(radians), 0, std::cos(radians), 0},
        {0, 0, 0, 1}};
}

Matrix rotation_z(float radians)
{
    return {
        {std::cos(radians), -std::sin(radians), 0, 0},
        {std::sin(radians), std::cos(radians), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};
}

Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
{
    return {
        {1, x_y, x_z, 0},
        {y_x, 1, y_z, 0},
        {z_x, z_y, 1, 0},
        {0, 0, 0, 1}};
}
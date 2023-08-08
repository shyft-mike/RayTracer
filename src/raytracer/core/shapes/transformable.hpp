#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>
#include <raytracer/core/matrices/transformations.hpp>

struct ITransformable
{
    Matrix transform;

    ITransformable()
    {
        this->transform = MatrixHelper::identity();
    }

    ITransformable *translate(float x, float y, float z)
    {
        this->transform = this->transform * translation(x, y, z);
        return this;
    }

    ITransformable *scale(float x, float y, float z)
    {
        this->transform = this->transform * scaling(x, y, z);
        return this;
    }

    ITransformable *rotate_x(float radians)
    {
        this->transform = this->transform * rotation_x(radians);

        return this;
    }

    ITransformable *rotate_y(float radians)
    {
        this->transform = this->transform * rotation_y(radians);

        return this;
    }

    ITransformable *rotate_z(float radians)
    {
        this->transform = this->transform * rotation_z(radians);

        return this;
    }
};

#endif
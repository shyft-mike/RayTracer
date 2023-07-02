#ifndef RAYS_H
#define RAYS_H

#include "cartesia.h"
#include "matrices.h"
#include "transformations.h"

struct Ray
{
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction) : origin(origin), direction(direction)
    {
    }

    Point get_position(float time)
    {
        return this->origin + this->direction * time;
    }

    Ray translate(float x, float y, float z)
    {
        return Ray(
            MatrixHelper(this->origin).translate(x, y, z).to_point(),
            MatrixHelper(this->direction).translate(x, y, z).to_vector());
    }

    Ray scale(float x, float y, float z)
    {
        return Ray(
            MatrixHelper(this->origin).scale(x, y, z).to_point(),
            MatrixHelper(this->direction).scale(x, y, z).to_vector());
    }
};

inline Ray operator*(const Ray ray, const Matrix matrix)
{
    return Ray(
        MatrixHelper(ray.origin * matrix).to_point(),
        MatrixHelper(ray.direction * matrix).to_vector());
}

#endif
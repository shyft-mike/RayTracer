#ifndef PLANE_H
#define PLANE_H

#include <algorithm>
#include <cfloat>
#include <raytracer/common/constants.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/matrices/matrix.hpp>

const Vector PLANE_NORMAL = Vector(0, 1, 0);

struct Plane : public IShape
{
    std::vector<float> intersect(const Ray &ray) const override
    {
        if (std::abs(ray.direction.y) < FLT_EPSILON)
        {
            return {};
        }

        return {-ray.origin.y / ray.direction.y};
    }

    Vector normal_at(float x, float y, float z) const override
    {
        return PLANE_NORMAL;
    }
};

#endif
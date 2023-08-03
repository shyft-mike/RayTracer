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
    Plane(std::string id) : IShape(id)
    {
    }

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
        Point object_point = MatrixHelper(inverse(this->transform) * Point(x, y, z)).to_point();
        Vector object_normal = object_point - Point(0, 0, 0);
        Vector world_normal = MatrixHelper(transpose(inverse(this->transform)) * object_normal).to_vector();

        return world_normal.normalize();
    }
};

#endif
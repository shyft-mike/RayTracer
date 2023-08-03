#ifndef SPHERES_H
#define SPHERES_H

#include <algorithm>
#include <raytracer/core/shapes/shape.hpp>

struct Sphere : public IShape
{
    Sphere(std::string id) : IShape(id)
    {
    }

    std::vector<float> intersect(const Ray &ray) const override
    {
        Vector sphere_to_ray = ray.origin - Point(0, 0, 0);

        float a = dot(ray.direction, ray.direction);
        float b = 2 * dot(ray.direction, sphere_to_ray);
        float c = dot(sphere_to_ray, sphere_to_ray) - 1;

        float discriminant = (b * b) - 4 * a * c;

        if (discriminant < 0)
        {
            return std::vector<float>{};
        }

        return std::vector<float>{
            (-b - std::sqrt(discriminant)) / (2 * a),
            (-b + std::sqrt(discriminant)) / (2 * a)};
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
#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <optional>
#include <algorithm>
#include "raytracer/shapes/shapes.h"
#include "raytracer/rays.h"

struct Intersection
{
    float t;
    IShape object;

    Intersection(float t, IShape object) : t(t), object(object)
    {
    }

    bool operator==(const Intersection &other) const
    {
        return (this->object == other.object) && (this->t == other.t);
    }
};

struct Intersections : std::vector<Intersection>
{
    Intersections(std::vector<Intersection> intersections) : std::vector<Intersection>(intersections)
    {
    }
};

inline Intersections get_intersections(const IShape &shape, const Ray ray)
{
    Vector sphere_to_ray = ray.origin - Point(0, 0, 0);

    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(ray.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    float discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0)
    {
        return Intersections({});
    }

    return Intersections(
        {Intersection((-b - std::sqrt(discriminant)) / (2 * a), shape),
         Intersection((-b + std::sqrt(discriminant)) / (2 * a), shape)});
}

inline bool compareIntersection(Intersection i1, Intersection i2)
{
    return (i1.t < i2.t);
}

inline std::optional<Intersection> hit(Intersections &intersections)
{
    std::sort(intersections.begin(), intersections.end(), compareIntersection);

    for (int i = 0; i < intersections.size(); i++)
    {
        if (intersections[i].t >= 0)
        {
            return intersections[i];
        }
    }

    return std::nullopt;
}

#endif
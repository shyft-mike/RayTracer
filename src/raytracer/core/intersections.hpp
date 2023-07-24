#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <optional>
#include <algorithm>
#include <raytracer/common/constants.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/matrices/matrix.hpp>

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

struct ComputedIntersection : Intersection
{
    Point position;
    Vector eye_direction;
    Vector normal_direction;
    Point over_position;
    bool inside{false};

    ComputedIntersection(float t, IShape object, Point position, Vector eye_direction, Vector normal_direction)
        : Intersection(t, object),
          position(position),
          eye_direction(eye_direction),
          normal_direction(normal_direction),
          over_position(position)
    {
        if (dot(this->normal_direction, this->eye_direction) < 0)
        {
            this->inside = true;
            this->normal_direction = -this->normal_direction;
        }

        this->over_position = this->position + this->normal_direction * EPSILON;
    }

    ComputedIntersection(Intersection &in, Point position, Vector eye_direction, Vector normal_direction)
        : ComputedIntersection(in.t, in.object, position, eye_direction, normal_direction)
    {
    }
};

struct Intersections : std::vector<Intersection>
{
    Intersections(std::vector<Intersection> intersections) : std::vector<Intersection>(intersections)
    {
    }
};

inline bool compareIntersection(const Intersection &i1, const Intersection &i2)
{
    return (i1.t < i2.t);
}

inline std::optional<Intersection> hit(Intersections &intersections)
{
    for (int i = 0; i < intersections.size(); i++)
    {
        if (intersections[i].t >= 0)
        {
            return intersections[i];
        }
    }

    return std::nullopt;
}

inline Intersections intersect_shape(const IShape &shape, const Ray &ray)
{
    Ray transformed_ray = ray * inverse(shape.transform);
    Vector sphere_to_ray = transformed_ray.origin - Point(0, 0, 0);

    float a = dot(transformed_ray.direction, transformed_ray.direction);
    float b = 2 * dot(transformed_ray.direction, sphere_to_ray);
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

inline ComputedIntersection compute_intersection(Intersection &intersection, const Ray &ray)
{
    Point position = ray.get_position(intersection.t);

    return ComputedIntersection(
        intersection,
        position,
        -ray.direction,
        intersection.object.normal_at(position.x, position.y, position.z));
}

#endif
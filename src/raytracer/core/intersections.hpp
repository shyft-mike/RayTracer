#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <optional>
#include <raytracer/common/constants.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/shapes/shape.hpp>

struct Intersection
{
    float t;
    IShape *object;

    Intersection(float t, IShape *object) : t(t), object(object)
    {
    }

    bool operator==(const Intersection &other) const
    {
        return (this->object == other.object) && (this->t == other.t);
    }

    Intersection &operator=(const Intersection &in)
    {
        if (this != &in)
        {
            this->t = in.t;

            if (this->object != in.object)
            {
                this->object = in.object;
            }
        }

        return *this;
    }
};

struct ComputedIntersection : Intersection
{
    Point position;
    Vector eye_direction;
    Vector normal_direction;
    Point over_position;
    bool inside{false};

    ComputedIntersection(float t, IShape *object, Point position, Vector eye_direction, Vector normal_direction)
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

        this->over_position = this->position + this->normal_direction * ACNE_EPSILON;
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

inline Intersections intersect(IShape &shape, const Ray &ray)
{
    Intersections results = Intersections({});

    Ray transformed_ray = ray * inverse(shape.transform);
    std::vector<float> intersection_ts = shape.intersect(transformed_ray);

    if (intersection_ts.size() == 0)
    {
        return results;
    }

    results.reserve(intersection_ts.size());

    for (int i = 0; i < intersection_ts.size(); i++)
    {
        results.push_back(Intersection(intersection_ts.at(i), &shape));
    }

    return results;
}

inline bool compare_intersection(const Intersection &i1, const Intersection &i2)
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

inline ComputedIntersection compute_intersection(Intersection &intersection, const Ray &ray)
{
    Point position = ray.get_position(intersection.t);

    return ComputedIntersection(
        intersection,
        position,
        -ray.direction,
        intersection.object->normal_at(position.x, position.y, position.z));
}

#endif
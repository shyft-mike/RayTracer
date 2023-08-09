#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <memory>
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
    Vector reflect_direction;
    Point over_position;
    Point under_position;
    float n1{1};
    float n2{1};
    bool inside{false};

    ComputedIntersection(float t, IShape *object, Point position, Vector eye_direction, Vector normal_direction)
        : Intersection(t, object),
          position(position),
          eye_direction(eye_direction),
          normal_direction(normal_direction),
          reflect_direction(eye_direction),
          over_position(position),
          under_position(position)
    {
        if (dot(this->normal_direction, this->eye_direction) < 0)
        {
            this->inside = true;
            this->normal_direction = -this->normal_direction;
        }

        this->over_position = this->position + this->normal_direction * ACNE_EPSILON;
        this->under_position = this->position - this->normal_direction * ACNE_EPSILON;
        this->reflect_direction = reflect(-this->eye_direction, this->normal_direction);
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

inline ComputedIntersection compute_intersection(Intersection &intersection, const Ray &ray, const std::optional<Intersections> &intersections = std::nullopt)
{
    std::vector<IShape *> containers = {};
    Intersections local_intersections = Intersections({intersection});

    if (intersections && intersections.value().size() != 0)
    {
        local_intersections = intersections.value();
    }

    Point position = ray.get_position(intersection.t);

    ComputedIntersection result = ComputedIntersection(
        intersection,
        position,
        -ray.direction,
        intersection.object->normal_at(position.x, position.y, position.z));

    for (Intersection &related_intersection : local_intersections)
    {
        if (related_intersection == intersection)
        {
            if (containers.size() == 0)
            {
                result.n1 = 1;
            }
            else
            {
                result.n1 = containers.back()->material.refractive_index;
            }
        }

        if (std::find(containers.begin(), containers.end(), related_intersection.object) != containers.end())
        {
            containers.erase(std::find(containers.begin(), containers.end(), related_intersection.object));
        }
        else
        {
            containers.push_back(related_intersection.object);
        }

        if (related_intersection == intersection)
        {
            if (containers.size() == 0)
            {
                result.n2 = 1;
            }
            else
            {
                result.n2 = containers.back()->material.refractive_index;
            }
        }
    }

    return result;
}

#endif
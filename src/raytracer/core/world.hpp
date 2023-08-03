#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/intersections.hpp>

struct World
{
    std::vector<PointLight> lights;
    std::vector<IShape *> shapes;
};

inline World create_default_world()
{
    World result = World();

    IShape *s1 = new Sphere("1");
    s1->material.color = Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    IShape *s2 = new Sphere("2");
    s2->scale(0.5, 0.5, 0.5);

    result.lights = {PointLight(Point(-10, 10, -10), Color(1, 1, 1))};

    result.shapes = {s1, s2};

    return result;
}

inline Intersections intersect_world(World &world, const Ray &ray)
{
    Intersections results = Intersections({});

    for (int i = 0; i < world.shapes.size(); i++)
    {
        Intersections intersections = intersect(*world.shapes[i], ray);

        if (intersections.size() == 2)
        {
            results.push_back(intersections[0]);
            results.push_back(intersections[1]);
        }
    }

    std::sort(results.begin(), results.end(), compare_intersection);

    return results;
}

inline bool is_shadowed(World &world, const Point &point)
{
    for (int i = 0; i < world.lights.size(); i++)
    {
        Vector point_to_light = world.lights[i].position - point;
        float distance = point_to_light.magnitude;
        Vector direction = point_to_light.normalize();

        Ray r = Ray(point, direction);
        Intersections intersections = intersect_world(world, r);

        std::optional<Intersection> h = hit(intersections);

        if (h.has_value() && h.value().t < distance)
        {
            return true;
        }
    }

    return false;
}

inline Color shade_hit(World &world, ComputedIntersection &computed_intersection)
{
    Color result = BLACK;

    for (int i = 0; i < world.lights.size(); i++)
    {
        bool shadowed = is_shadowed(world, computed_intersection.over_position);

        Color shade = lighting(
            computed_intersection.object->material,
            world.lights[i],
            computed_intersection.over_position,
            computed_intersection.eye_direction,
            computed_intersection.normal_direction,
            shadowed);

        result = result + shade;
    }

    return result;
}

inline Color color_at(World &world, const Ray &ray)
{
    Intersections intersections = intersect_world(world, ray);
    std::optional<Intersection> potential_hit = hit(intersections);

    if (potential_hit.has_value())
    {
        ComputedIntersection computed_intersection = compute_intersection(potential_hit.value(), ray);

        return shade_hit(world, computed_intersection);
    }

    return BLACK;
}

#endif
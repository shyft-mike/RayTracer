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
    std::vector<IShape> shapes;
};

inline World create_default_world()
{
    World result = World();

    Sphere s1 = Sphere("1");
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    Sphere s2 = Sphere("2");
    s2.scale(0.5, 0.5, 0.5);

    result.lights = {PointLight(Point(-10, 10, -10), Color(1, 1, 1))};

    result.shapes = {s1, s2};

    return result;
}

inline Intersections intersect_world(const World &world, const Ray &ray)
{
    Intersections results = {{}};

    for (int i = 0; i < world.shapes.size(); i++)
    {
        Intersections intersections = intersect_shape(world.shapes[i], ray);

        if (intersections.size() == 2)
        {
            results.push_back(intersections[0]);
            results.push_back(intersections[1]);
        }
    }

    std::sort(results.begin(), results.end(), compareIntersection);

    return results;
}

inline Color shade_hit(const World &world, const ComputedIntersection &computed_intersection)
{
    Color result = Color(0, 0, 0);

    for (int i = 0; i < world.lights.size(); i++)
    {
        Color shade = lighting(
            computed_intersection.object.material,
            world.lights[i],
            computed_intersection.position,
            computed_intersection.eye_direction,
            computed_intersection.normal_direction);

        result = result + shade;
    }

    return result;
}

inline Color color_at(const World &world, const Ray &ray)
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
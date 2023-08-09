#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/rays.hpp>

struct World
{
    std::vector<PointLight> lights;
    std::vector<IShape *> shapes;
};

World create_default_world();
Intersections intersect_world(const World &world, const Ray &ray);
bool is_shadowed(const World &world, const Point &point);
Color color_at(const World &world, const Ray &ray, int remaining = 5);
Color get_reflected_color(const World &world, const ComputedIntersection &computed_intersection, int remaining = 5);
Color get_refracted_color(const World &world, const ComputedIntersection &computed_intersection, int remaining = 5);
Color shade_hit(const World &world, ComputedIntersection &computed_intersection, int remaining = 5);

#endif
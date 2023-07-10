#ifndef CHAPTER6_H
#define CHAPTER6_H

#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/intersections.hpp>

namespace Chapter6
{
    struct Program
    {
        float wall_size = 7;
        float wall_z = 10;

        void execute(Canvas &canvas)
        {
            Point origin = Point(0, 0, -5);
            Sphere sphere = Sphere("1");
            sphere.material.color = Color(0.9, 0.1, 0.1);
            sphere.scale(0.75, 0.75, 0.75);

            Point light_position = Point(-5, 5, -5);
            Color light_color = WHITE;
            PointLight light = PointLight(light_position, light_color);

            float pixel_size = wall_size / canvas.width;
            float half = wall_size / 2;

            for (int y = 0; y < canvas.height; y++)
            {
                float world_y = half - pixel_size * y;

                for (int x = 0; x < canvas.width; x++)
                {
                    float world_x = -half + pixel_size * x;

                    Point position = Point(world_x, world_y, wall_z);
                    Ray r = Ray(origin, (position - origin).normalize());

                    Intersections xs = intersect_shape(sphere, r);

                    std::optional<Intersection> potential_hit = hit(xs);

                    if (potential_hit.has_value())
                    {
                        Intersection actual_hit = potential_hit.value();
                        Point hit_point = r.get_position(actual_hit.t);
                        Vector hit_normal = actual_hit.object.normal_at(hit_point.x, hit_point.y, hit_point.z);
                        Vector eye_vector = -r.direction;

                        Color color = lighting(actual_hit.object.material, light, hit_point, eye_vector, hit_normal);

                        canvas.setPixel(x, y, color);
                    }
                }
            }
        }
    };
}

#endif
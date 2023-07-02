#ifndef CHAPTER5_H
#define CHAPTER5_H

#include "canvas.h"
#include "cartesia.h"
#include "spheres.h"
#include "rays.h"
#include "intersections.h"

namespace Chapter5
{
    struct Program
    {
        float wall_size = 7;
        float wall_z = 10;

        void execute(Canvas &canvas)
        {
            Point origin = Point(0, 0, -5);
            Color color = Color(1, 0, 0);
            Point center = Point(0, 0, 0);
            Sphere sphere = Sphere("1");
            sphere.scale(0.75, 0.75, 0.75).translate(-1, 0, 5);

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

                    Intersections xs = get_intersections(sphere, r);

                    if (hit(xs).has_value())
                    {
                        canvas.setPixel(x, canvas.height - y, color);
                    }
                }
            }
        }
    };
}

#endif
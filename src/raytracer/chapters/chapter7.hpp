#ifndef CHAPTER7_H
#define CHAPTER7_H

#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/world.hpp>
#include <raytracer/core/camera.hpp>

namespace Chapter7
{
    struct Program
    {
        Canvas execute()
        {
            IShape floor = Sphere("floor");
            floor.transform = scaling(10, 0.01, 10);
            floor.material.color = Color(1, 0.9, 0.9);
            floor.material.specular = 0;

            IShape left_wall = Sphere("left_wall");
            left_wall.transform = MatrixHelper(left_wall.transform)
                                      .translate(0, 0, 5)
                                      .rotate_y(-M_PI_4)
                                      .rotate_x(M_PI_2)
                                      .scale(10, 0.01, 10);
            left_wall.material = floor.material;

            IShape right_wall = Sphere("right_wall");
            right_wall.transform = MatrixHelper(right_wall.transform)
                                       .translate(0, 0, 5)
                                       .rotate_y(M_PI_4)
                                       .rotate_x(M_PI_2)
                                       .scale(10, 0.01, 10);
            right_wall.material = floor.material;

            IShape middle = Sphere("middle");
            middle.transform = middle.transform * translation(-0.5, 1, 0.5);
            middle.material.color = Color(0.1, 1, 0.5);
            middle.material.diffuse = 0.7;
            middle.material.specular = 0.3;

            IShape right = Sphere("right");
            right.transform = MatrixHelper(right.transform)
                                  .translate(1.5, 0.5, -0.5)
                                  .scale(0.5, 0.5, 0.5);
            right.material.color = Color(0.5, 1, 0.1);
            right.material.diffuse = 0.7;
            right.material.specular = 0.3;

            IShape left = Sphere("left");
            left.transform = MatrixHelper(left.transform)
                                 .translate(-1.5, 0.33, -0.75)
                                 .scale(0.33, 0.33, 0.33);
            left.material.color = Color(1, 0.8, 0.1);
            left.material.diffuse = 0.7;
            left.material.specular = 0.3;

            World world = World();
            world.lights = {
                PointLight(Point(-10, 10, -10), Color(1, 1, 1))};
            world.shapes = {
                floor,
                left_wall,
                right_wall,
                middle,
                left,
                right};

            Camera camera = Camera(100, 50, M_PI / 3);
            camera.transform = view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

            return render(camera, world);
        }
    };
}

#endif
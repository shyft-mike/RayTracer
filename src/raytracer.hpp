#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/shapes/plane.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/world.hpp>
#include <raytracer/core/camera.hpp>

class RayTracer
{
public:
    void run()
    {
        World world = build_world();

        Camera camera = Camera(100, 100, M_PI / 4);
        camera.transform = view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(1, 1.5, 0));

        Canvas canvas = render(camera, world);

        this->save_canvas(canvas);
    }

private:
    World build_world()
    {
        IShape *floor = new Plane("floor");
        floor->transform = scaling(10, 0.01, 10);
        floor->material.color = Color(1, 0.9, 0.9);
        floor->material.specular = 0;

        IShape *background = new Plane("background");
        background->scale(10, 10, 1).translate(0, 0, -15);

        IShape *middle = new Sphere("middle");
        middle->translate(-0.5, 1, 0.5);
        middle->material.color = Color(1, 1, 0.45);
        middle->material.diffuse = 0.9;
        middle->material.specular = 0.5;

        IShape *right = new Sphere("right");
        right->translate(1, 0, 0.5).scale(0.3, 0.2, 0.3);
        right->material.color = Color(0.5, 0.6, 0.1);
        right->material.diffuse = 0.5;
        right->material.specular = 0.3;

        IShape *left = new Sphere("left");
        left->translate(-1.5, 0.33, -0.75).scale(0.66, 0.66, 0.66);
        left->material.color = Color(0.9, 0.9, 0.9);
        left->material.diffuse = 0.7;
        left->material.specular = 0.3;

        World world = World();
        world.lights = {
            PointLight(Point(-10, 10, -10), Color(1, 1, 1))};
        world.shapes = {
            floor,
            background,
            middle,
            left,
            right};

        return world;
    }

    void save_canvas(const Canvas &canvas)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        std::filesystem::create_directory("../output");
        std::ofstream out("../output/canvas_" + std::to_string(timestamp.count()) + ".ppm");
        out << canvas.to_ppm();
        out.close();
    }
};

#endif
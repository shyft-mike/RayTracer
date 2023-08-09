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

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

class RayTracer
{

public:
    void run()
    {
        World world = build_world();

        Camera camera = Camera(600, 600, M_PI / 3);
        camera.transform = view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

        auto start = high_resolution_clock::now();

        Canvas canvas = render(camera, world);

        auto end = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(end - start);
        std::cerr << "render() time: " << ms_int.count() << std::endl;

        start = high_resolution_clock::now();

        this->save_canvas(canvas);

        end = high_resolution_clock::now();
        ms_int = duration_cast<milliseconds>(end - start);
        std::cerr << "save_canvas() time: " << ms_int.count() << std::endl;
    }

private:
    World build_world()
    {
        IShape *floor = new Plane("floor");
        floor->material.pattern = new CheckerPattern(WHITE, BLACK);
        floor->material.reflective = 0.3;

        IShape *middle = new Sphere("middle");
        middle->translate(-0.5, 5, 10)->rotate_y(M_PI / 3)->scale(2.3, 2.3, 2.3);
        middle->material.pattern = new StripePattern(WHITE, Color(0.2, 0.3, 0.4));
        middle->material.pattern->scale(0.1, 0.1, 0.1);
        middle->material.diffuse = 0.9;
        middle->material.specular = 0.5;
        middle->material.reflective = 0.8;

        IShape *right = new Sphere("right");
        right->translate(1.5, 0.5, -0.5)->rotate_z(M_PI_4)->scale(0.5, 0.5, 0.5);
        right->material.pattern = new RadialGradientPattern(RED, BLUE);
        right->material.pattern->scale(0.25, 0.25, 0.25);
        right->material.diffuse = 0.5;
        right->material.specular = 0.3;

        // IShape *left = new Sphere("left");
        // left->scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75);
        // left->material.pattern = new CheckerPattern(Color(0.9, 0.9, 0.9), Color(1, 0, 0));
        // left->material.diffuse = 0.7;
        // left->material.specular = 0.3;

        World world = World();
        world.lights = {
            PointLight(Point(-1, 5, -5), WHITE)};
        world.shapes = {
            floor,
            middle,
            // left,
            right};

        return world;
    }

    void save_canvas(const Canvas &canvas)
    {
        auto output = canvas.to_ppm();

        auto now = high_resolution_clock::now();
        auto timestamp = duration_cast<milliseconds>(now.time_since_epoch());

        std::filesystem::create_directory("../output");

        std::ofstream out("../output/canvas_" + std::to_string(timestamp.count()) + ".ppm");
        out << output;
        out.close();

        std::ofstream static_out("../output/canvas_static.ppm");
        static_out << output;
        static_out.close();
    }
};

#endif
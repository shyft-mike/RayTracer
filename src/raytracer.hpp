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

        Camera camera = Camera(200, 200, M_PI / 3);
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
        World world = World();

        PointLight light = PointLight(Point(-10, 10, -10), WHITE);
        world.lights = {light};

        IShape *wall = new Plane();
        wall->translate(0, 0, 100)->rotate_x(M_PI_2);
        wall->material.pattern = new CheckerPattern(WHITE, BLACK);

        IShape *floor = new Plane();
        floor->translate(0, -1, 0);
        floor->material.pattern = new CheckerPattern(WHITE, BLACK);

        IShape *water = new Plane();
        water->translate(0, -0.2, 0);
        water->material.pattern = new SolidPattern(BLUE);
        water->material.reflective = 0.9;
        water->material.transparency = 0.9;
        water->material.diffuse = 0.5;
        water->material.specular = 1;
        water->material.shininess = 369;

        IShape *ball = new Sphere();
        ball->translate(0, 0, 4)->scale(2, 2, 2);
        ball->material.pattern = new SolidPattern(RED);
        ball->material.transparency = 1;
        ball->material.reflective = 1;
        ball->material.diffuse = 0.5;

        IShape *inner = new Sphere();
        inner->translate(0, 0, 4);
        inner->material.pattern = new CheckerPattern(WHITE, BLACK);

        world.shapes = {
            floor,
            water,
            wall,
            ball,
            inner};

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
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/chapters/chapter6.hpp>

class RayTracer
{
public:
    struct Environment
    {
        Vector gravity;
        Vector wind;

        Environment(Vector gravity, Vector wind) : gravity(gravity), wind(wind)
        {
        }
    };

    struct Projectile
    {
        Point position;
        Vector velocity;

        Projectile(Point position, Vector velocity) : position(position), velocity(velocity)
        {
        }
    };

    Environment env;
    Projectile proj;
    Canvas canvas;

    RayTracer(Environment env, Projectile proj, Canvas canvas) : env(env), proj(proj), canvas(canvas)
    {
    }

public:
    void run()
    {
        Chapter6::Program program = Chapter6::Program();

        program.execute(this->canvas);

        this->saveCanvas();
    }

private:
    void saveCanvas()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        std::filesystem::create_directory("../output");
        std::ofstream out("../output/canvas_" + std::to_string(timestamp.count()) + ".ppm");
        out << this->canvas.toPPM();
        out.close();
    }
};

#endif
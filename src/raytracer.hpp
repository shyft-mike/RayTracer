#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/chapters/chapter5.hpp>

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
        Chapter5::Program program = Chapter5::Program();

        program.execute(this->canvas);

        this->saveCanvas();
    }

private:
    void saveCanvas()
    {
        std::filesystem::create_directory("../output");
        std::ofstream out("../output/canvas.ppm");
        out << this->canvas.toPPM();
        out.close();
    }
};

#endif
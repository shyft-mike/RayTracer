#include <iostream>
#include <fstream>
#include <filesystem>
#include "raytracer/cartesia.h"
#include "raytracer/canvas.h"
#include "raytracer/matrices/matrices.h"
#include "raytracer/chapter4.h"

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
        Chapter4::Program program = Chapter4::Program();

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

int main()
{
    RayTracer::Environment env = RayTracer::Environment(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));
    RayTracer::Projectile proj = RayTracer::Projectile(Point(0, 1, 0), Vector(1, 1.8, 0).normalize() * 11.25);
    Canvas canvas = Canvas(100, 100);

    RayTracer(env, proj, canvas).run();

    return 0;
}

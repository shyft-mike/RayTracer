#include <iostream>
#include <fstream>
#include <filesystem>
#include "cartesia.h"
#include "canvas.h"

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
    short runs = 0;

    RayTracer(Environment env, Projectile proj, Canvas canvas) : env(env), proj(proj), canvas(canvas)
    {
    }

public:
    void run()
    {
        Color pointColor = Color(0.75, 0.1, 0.1);
        this->canvas.setPixel(this->proj.position.x, this->canvas.height - this->proj.position.y, pointColor);

        while (this->proj.position.y > 0 && this->runs < 1000)
        {
            this->proj = tick();
            this->canvas.setPixel(this->proj.position.x, this->canvas.height - this->proj.position.y, pointColor);
            this->runs++;
        }

        this->saveCanvas();
    }

private:
    Projectile tick()
    {
        Point newPosition = this->proj.position + this->proj.velocity;
        Vector newVelocity = this->proj.velocity + this->env.gravity + this->env.wind;
        return Projectile(newPosition, newVelocity);
    }

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
    Canvas canvas = Canvas(900, 550);

    RayTracer(env, proj, canvas).run();

    return 0;
}

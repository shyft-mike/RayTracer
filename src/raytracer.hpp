#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/chapters/chapter7.hpp>

class RayTracer
{
public:
    void run()
    {
        Chapter7::Program program = Chapter7::Program();

        Canvas canvas = program.execute();

        this->saveCanvas(canvas);
    }

private:
    void saveCanvas(const Canvas &canvas)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        std::filesystem::create_directory("../output");
        std::ofstream out("../output/canvas_" + std::to_string(timestamp.count()) + ".ppm");
        out << canvas.toPPM();
        out.close();
    }
};

#endif
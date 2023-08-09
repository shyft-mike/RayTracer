#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>
#include <math.h>
#include <future>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/world.hpp>

struct Camera
{
    float h_size;
    float v_size;
    float field_of_view;
    float half_width;
    float half_height;
    float pixel_size;
    Matrix transform;

    Camera(float h_size, float v_size, float field_of_view) : h_size(h_size), v_size(v_size), field_of_view(field_of_view)
    {
        this->transform = MatrixHelper::identity();

        float half_view = tan(this->field_of_view / 2);
        float aspect = this->h_size / this->v_size;

        if (aspect >= 1)
        {
            this->half_width = half_view;
            this->half_height = half_view / aspect;
        }
        else
        {
            this->half_width = half_view * aspect;
            this->half_height = half_view;
        }

        this->pixel_size = (this->half_width * 2) / this->h_size;
    }
};

inline Ray ray_for_pixel(const Camera &camera, int pixel_x, int pixel_y)
{
    float offset_x = (pixel_x + 0.5) * camera.pixel_size;
    float offset_y = (pixel_y + 0.5) * camera.pixel_size;

    float world_x = camera.half_width - offset_x;
    float world_y = camera.half_height - offset_y;

    Point pixel = MatrixHelper(inverse(camera.transform) * Point(world_x, world_y, -1)).to_point();
    Point origin = MatrixHelper(inverse(camera.transform) * Point(0, 0, 0)).to_point();
    Vector direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

inline Canvas render(const Camera &camera, World &world)
{
    Canvas result = Canvas(camera.h_size, camera.v_size);

    int pixel_count = camera.v_size * camera.h_size;

    int thread_count = 100; // hehe
    int start_index = -1;
    int end_index = -1;

    if (config::is_async)
    {
        do
        {
            start_index = end_index + 1;
            end_index += thread_count;

            if (end_index > pixel_count)
            {
                end_index = pixel_count;
                thread_count = end_index - start_index;
            }

            // First step: Do all the rays at once
            std::vector<std::future<Ray>> ray_threads = std::vector<std::future<Ray>>();
            ray_threads.reserve(thread_count);

            for (int i = 0; i < thread_count; i++)
            {
                auto [x, y] = result.index_to_xy(start_index + i);

                ray_threads.push_back(std::async(std::launch::async, ray_for_pixel, camera, x, y));
            }

            // Second step: Generate all the colors
            std::vector<std::future<Color>> color_threads = std::vector<std::future<Color>>();
            color_threads.reserve(pixel_count);

            for (std::future<Ray> &ray_thread : ray_threads)
            {
                Ray ray = ray_thread.get();
                color_threads.push_back(std::async(std::launch::async, color_at, world, ray, 4));
            }

            // Third step: set the colors in the world
            int color_index = 0;
            for (std::future<Color> &color_thread : color_threads)
            {
                auto [x, y] = result.index_to_xy(start_index + color_index);

                Color color = color_threads.at(color_index).get();
                result.set_pixel(x, y, color);

                color_index++;
            }

        } while (pixel_count > end_index);
    }
    else
    {
        for (int y = 0; y < camera.v_size; y++)
        {
            for (int x = 0; x < camera.h_size; x++)
            {
                Ray ray = ray_for_pixel(camera, x, y);
                Color color = color_at(world, ray);
                result.set_pixel(x, y, color);
            }
        }
    }

    return result;
};

#endif
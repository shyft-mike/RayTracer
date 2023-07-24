#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
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

inline Canvas render(const Camera &camera, const World &world)
{
    Canvas result = Canvas(camera.h_size, camera.v_size);

    for (int y = 0; y < camera.v_size; y++)
    {
        for (int x = 0; x < camera.h_size; x++)
        {
            Ray ray = ray_for_pixel(camera, x, y);
            Color color = color_at(world, ray);
            result.setPixel(x, y, color);
        }
    }

    return result;
};

#endif
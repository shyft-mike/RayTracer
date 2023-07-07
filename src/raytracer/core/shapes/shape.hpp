#ifndef SHAPES_H
#define SHAPES_H

#include <string>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>
#include <raytracer/core/materials/material.hpp>

struct IShape
{
    std::string id;
    Matrix transform;
    Material material;

    IShape(std::string id) : id(id)
    {
        this->transform = MatrixHelper::identity();
        this->material = Material();
    }

    Vector normal_at(float x, float y, float z);

    IShape translate(float x, float y, float z);

    IShape scale(float x, float y, float z);

    IShape rotate_x(float radians);
    IShape rotate_y(float radians);
    IShape rotate_z(float radians);

    bool operator==(const IShape &other) const;
};

#endif
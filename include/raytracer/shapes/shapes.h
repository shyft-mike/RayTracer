#ifndef SHAPES_H
#define SHAPES_H

#include <string>
#include "raytracer/matrices/matrices.h"
#include "raytracer/matrices/helper.h"

struct IShape
{
    std::string id;
    Matrix transform;

    IShape(std::string id) : id(id)
    {
        this->transform = MatrixHelper::identity();
    }

    IShape translate(float x, float y, float z);

    bool operator==(const IShape &other) const;
};

#endif
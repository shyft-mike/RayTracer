#ifndef SHAPES_H
#define SHAPES_H

#include "matrices.h"

struct IShape
{
    std::string id;
    Matrix transform;

    IShape(std::string id) : id(id)
    {
        this->transform = MatrixHelper::identity();
    }

    IShape translate(float x, float y, float z)
    {
        this->transform *= translation(x,y,z);

        return *this;
    }
};

inline bool operator==(const IShape &self, const IShape &other)
{
    return self.id == other.id;
}

#endif
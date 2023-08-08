#ifndef MATERIAL_H
#define MATERIAL_H

#include <raytracer/core/materials/material.models.hpp>

inline bool operator==(const Material &mat1, const Material &mat2)
{
    if (&mat1 == &mat2)
    {
        return true;
    }

    return (mat1.ambient == mat2.ambient) && (mat1.diffuse == mat2.diffuse) && (mat1.shininess == mat2.shininess) && (mat1.specular == mat2.specular) && (mat1.pattern == mat2.pattern);
}

#endif
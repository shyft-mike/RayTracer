#ifndef MATERIAL_MODELS_H
#define MATERIAL_MODELS_H

#include <memory>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/patterns/pattern.hpp>

const std::unique_ptr<IPattern> DEFAULT_PATTERN = std::make_unique<IPattern>(SolidPattern(WHITE));

/// @brief The base for a Phong reflection-based material.
struct Material
{
    IPattern *pattern{DEFAULT_PATTERN.get()}; /// @brief The pattern of the material. Defaults to SolidPattern(White).
    float ambient{0.1};                       /// @brief Background or light reflected from other objects reflectivity. Defaults to 0.1.
    float diffuse{0.9};                       /// @brief Matte surface reflectivity. Defaults to 0.9.
    float specular{0.9};                      /// @brief Light source reflectivity (works with shininess). Defaults to 0.9.
    float shininess{200};                     /// @brief Controls the specular highlight. Defaults to 200.
};

struct ISkinnable
{
    Material material;

    ISkinnable()
    {
        this->material = Material();
    }
};

#endif
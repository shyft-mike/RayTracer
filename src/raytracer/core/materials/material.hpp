#ifndef MATERIAL_H
#define MATERIAL_H

#include <raytracer/core/colors.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/patterns/pattern.hpp>

/// @brief The base for a Phong reflection-based material.
struct Material
{
    IPattern *pattern{new SolidPattern(WHITE)}; /// @brief The pattern of the material. Defaults to SolidPattern(White).
    float ambient{0.1};                         /// @brief Background or light reflected from other objects reflectivity. Defaults to 0.1.
    float diffuse{0.9};                         /// @brief Matte surface reflectivity. Defaults to 0.9.
    float specular{0.9};                        /// @brief Light source reflectivity (works with shininess). Defaults to 0.9.
    float shininess{200};                       /// @brief Controls the specular highlight. Defaults to 200.
};

inline bool operator==(const Material &mat1, const Material &mat2)
{
    if (&mat1 == &mat2)
    {
        return true;
    }

    return (mat1.ambient == mat2.ambient) && (mat1.diffuse == mat2.diffuse) && (mat1.shininess == mat2.shininess) && (mat1.specular == mat2.specular) && (mat1.pattern == mat2.pattern);
}

inline Color lighting(const Material &material, const PointLight &light, const Point &position, const Vector &eye_vector, const Vector &normal_vector, const bool in_shadow)
{
    Color ambient = {};
    Color diffuse = {};
    Color specular = {};

    Color effective_color = material.pattern->at(position.x, position.y, position.z) * light.intensity;

    Vector direction_to_light = (light.position - position).normalize();

    ambient = effective_color * material.ambient;

    // light_dot_normal represents the cosine of the angle between the light vector and normal vector
    // negative means the light is on the other side of the surface
    float light_dot_normal = dot(direction_to_light, normal_vector);

    if (light_dot_normal < 0)
    {
        diffuse = BLACK;
        specular = BLACK;
    }
    else
    {
        diffuse = effective_color * material.diffuse * light_dot_normal;

        // reflect_dot_eye represents the cosine of the angle between the
        // reflection vector and the eye vector. A negative number means the
        // light reflects away from the eye.
        Vector reflect_vector = reflect(-direction_to_light, normal_vector);
        float reflect_dot_eye = dot(reflect_vector, eye_vector);

        if (reflect_dot_eye <= 0)
        {
            specular = BLACK;
        }
        else
        {
            float specular_factor = std::pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * specular_factor;
        }
    }

    if (in_shadow)
    {
        return ambient;
    }
    else
    {
        return ambient + diffuse + specular;
    }
}

#endif
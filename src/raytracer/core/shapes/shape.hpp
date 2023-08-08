#ifndef SHAPES_H
#define SHAPES_H

#include <algorithm>
#include <string>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/shapes/transformable.hpp>

struct IShape : public ITransformable, ISkinnable
{
    std::string id;

    IShape(std::string id) : ITransformable(), ISkinnable(), id(id)
    {
    }
    virtual ~IShape() = default;

    virtual std::vector<float> intersect(const Ray &ray) const
    {
        return {};
    }

    virtual Vector normal_at(float x, float y, float z) const
    {
        return Vector(0, 0, 0);
    }

    Color color_at(float x, float y, float z)
    {
        Point object_point = MatrixHelper(inverse(this->transform) * Point(x, y, z)).to_point();
        Point pattern_point = MatrixHelper(inverse(this->material.pattern->transform) * object_point).to_point();

        return this->material.pattern->at(pattern_point.x, pattern_point.y, pattern_point.z);
    }

    bool operator==(const IShape &other) const
    {
        if (this == &other)
        {
            return true;
        }

        return this->id == other.id;
    }
};

inline Color lighting(IShape *object, const PointLight &light, const Point &position, const Vector &eye_vector, const Vector &normal_vector, const bool in_shadow)
{
    Material material = object->material;

    Color ambient = {};
    Color diffuse = {};
    Color specular = {};

    Color effective_color = object->color_at(position.x, position.y, position.z) * light.intensity;

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
#include <vector>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/world.hpp>

World create_default_world()
{
    World result = World();

    IShape *s1 = new Sphere();
    s1->material.pattern = new SolidPattern(Color(0.8, 1.0, 0.6));
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    IShape *s2 = new Sphere();
    s2->scale(0.5, 0.5, 0.5);

    result.lights = {PointLight(Point(-10, 10, -10), Color(1, 1, 1))};

    result.shapes = {s1, s2};

    return result;
}

Intersections intersect_world(const World &world, const Ray &ray)
{
    Intersections results = Intersections({});

    for (int i = 0; i < world.shapes.size(); i++)
    {
        Intersections intersections = intersect(*world.shapes[i], ray);

        for (Intersection &intersection : intersections)
        {
            results.push_back(intersection);
        }
    }

    std::sort(results.begin(), results.end(), compare_intersection);

    return results;
}

bool is_shadowed(const World &world, const Point &point)
{
    for (int i = 0; i < world.lights.size(); i++)
    {
        Vector point_to_light = world.lights[i].position - point;
        float distance = point_to_light.magnitude;
        Vector direction = point_to_light.normalize();

        Ray r = Ray(point, direction);
        Intersections intersections = intersect_world(world, r);

        std::optional<Intersection> h = hit(intersections);

        if (h.has_value() && h.value().t < distance)
        {
            return true;
        }
    }

    return false;
}

Color color_at(const World &world, const Ray &ray, int remaining)
{
    Intersections intersections = intersect_world(world, ray);
    std::optional<Intersection> potential_hit = hit(intersections);

    if (potential_hit.has_value())
    {
        ComputedIntersection computed_intersection = compute_intersection(potential_hit.value(), ray, intersections);

        return shade_hit(world, computed_intersection, remaining);
    }

    return BLACK;
}

Color get_reflected_color(const World &world, const ComputedIntersection &computed_intersection, int remaining)
{
    // No more reflection attempts left
    if (remaining <= 0)
    {
        return BLACK;
    }

    if (computed_intersection.object->material.reflective == 0)
    {
        return BLACK;
    }

    Ray reflect_ray = Ray(computed_intersection.over_position, computed_intersection.reflect_direction);
    Color color = color_at(world, reflect_ray, remaining - 1);

    return color * computed_intersection.object->material.reflective;
}

Color get_refracted_color(const World &world, const ComputedIntersection &computed_intersection, int remaining)
{
    if (remaining <= 0)
    {
        return BLACK;
    }

    if (computed_intersection.object->material.transparency == 0)
    {
        return BLACK;
    }

    // Find the ratio of first index of refraction to the second.
    // (Yup, this is inverted from the definition of Snell's Law.)
    float n_ratio = computed_intersection.n1 / computed_intersection.n2;

    // cos(theta_i) is the same as the dot product of the two vectors
    float cos_i = dot(computed_intersection.eye_direction, computed_intersection.normal_direction);

    // Find sin(theta_t) ^ 2 via trigonometric identity
    float sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));

    if (sin2_t > 1)
    {
        return BLACK;
    }

    // Find cos(theta_t) via trigonometric identity
    float cos_t = std::sqrt(1.0 - sin2_t);

    // Compute direction of refracted ray
    Vector refracted_direction = computed_intersection.normal_direction * (n_ratio * cos_i - cos_t) - computed_intersection.eye_direction * n_ratio;

    Ray refract_ray = Ray(computed_intersection.under_position, refracted_direction);

    // Find the color of the refracted ray, making sure to account for transparency
    return color_at(world, refract_ray, remaining - 1) * computed_intersection.object->material.transparency;
}

Color shade_hit(const World &world, ComputedIntersection &computed_intersection, int remaining)
{
    Color result = BLACK;

    for (int i = 0; i < world.lights.size(); i++)
    {
        bool shadowed = is_shadowed(world, computed_intersection.over_position);

        Color surface = lighting(
            computed_intersection.object,
            world.lights[i],
            computed_intersection.over_position,
            computed_intersection.eye_direction,
            computed_intersection.normal_direction,
            shadowed);

        Color reflected = get_reflected_color(world, computed_intersection, remaining);
        Color refracted = get_refracted_color(world, computed_intersection, remaining);

        result = result + surface + reflected + refracted;
    }

    return result;
}
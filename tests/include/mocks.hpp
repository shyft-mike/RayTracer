#ifndef MOCKS_H
#define MOCKS_H

#include <memory>
#include <raytracer/core/shapes/transformable.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/patterns/pattern.models.hpp>

struct TestTransformable : ITransformable
{
};

struct TestPattern : IPattern
{
    TestPattern() : IPattern({})
    {
    }

    Color at(float x, float y, float z) const override
    {
        return Color(x, y, z);
    }
};

inline std::unique_ptr<ITransformable> get_test_transformable()
{
    return std::make_unique<TestTransformable>();
}

inline std::unique_ptr<Sphere> get_test_sphere()
{
    return std::make_unique<Sphere>();
}

inline std::unique_ptr<Plane> get_test_plane()
{
    return std::make_unique<Plane>();
}

inline std::unique_ptr<IPattern> get_test_pattern()
{
    return std::make_unique<TestPattern>();
}

inline std::unique_ptr<Sphere> TEST_SPHERE = get_test_sphere();

inline std::unique_ptr<Plane> TEST_PLANE = get_test_plane();

inline const StripePattern TEST_STRIPE_PATTERN = StripePattern(WHITE, BLACK);

inline std::unique_ptr<IPattern> TEST_PATTERN = get_test_pattern();

#endif
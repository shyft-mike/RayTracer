#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <helpers.hpp>
#include <raytracer/core/shapes/plane.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/intersections.hpp>

namespace PlaneTest
{
    const Plane *PLANE = new Plane("test");

    TEST(PlaneTest, IntersectRayParallel)
    {
        Ray r = Ray(Point(0, 10, 0), Vector(0, 0, 1));
        std::vector<float> results = PLANE->intersect(r);

        ASSERT_EQ(results.size(), 0);
    }

    TEST(PlaneTest, IntersectCoplanar)
    {
        Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
        std::vector<float> results = PLANE->intersect(r);

        ASSERT_EQ(results.size(), 0);
    }

    TEST(PlaneTest, IntersectFromAbove)
    {
        Ray r = Ray(Point(0, 1, 0), Vector(0, -1, 0));
        std::vector<float> results = PLANE->intersect(r);

        ASSERT_EQ(results.size(), 1);
        ASSERT_EQ(results.at(0), 1);
    }

    TEST(PlaneTest, IntersectFromBelow)
    {
        Ray r = Ray(Point(0, -1, 0), Vector(0, 1, 0));
        std::vector<float> results = PLANE->intersect(r);

        ASSERT_EQ(results.size(), 1);
        ASSERT_EQ(results.at(0), 1);
    }
}
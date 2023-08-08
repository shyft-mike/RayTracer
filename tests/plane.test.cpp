#include <gtest/gtest.h>
#include <algorithm>
#include <raytracer.tests.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/rays.hpp>

TEST(PlaneTest, IntersectRayParallel)
{
    Ray r = Ray(Point(0, 10, 0), Vector(0, 0, 1));
    std::vector<float> results = TEST_PLANE->intersect(r);

    ASSERT_EQ(results.size(), 0);
}

TEST(PlaneTest, IntersectCoplanar)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    std::vector<float> results = TEST_PLANE->intersect(r);

    ASSERT_EQ(results.size(), 0);
}

TEST(PlaneTest, IntersectFromAbove)
{
    Ray r = Ray(Point(0, 1, 0), Vector(0, -1, 0));
    std::vector<float> results = TEST_PLANE->intersect(r);

    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results.at(0), 1);
}

TEST(PlaneTest, IntersectFromBelow)
{
    Ray r = Ray(Point(0, -1, 0), Vector(0, 1, 0));
    std::vector<float> results = TEST_PLANE->intersect(r);

    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results.at(0), 1);
}
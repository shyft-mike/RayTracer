#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/intersections.hpp>

const Sphere SPHERE = Sphere("test");

TEST_P(IntersectionsTestFixture, Hit)
{
    auto [intersections, expectedResult] = GetParam();

    std::optional<Intersection> result = hit(intersections);

    if (result.has_value())
    {
        EXPECT_EQ(result.value(), expectedResult.value());
    }
    else
    {
        EXPECT_TRUE(!expectedResult);
    }
}

INSTANTIATE_TEST_SUITE_P(
    IntersectionsTest_Hit,
    IntersectionsTestFixture,
    ::testing::Values(
        std::make_tuple(Intersections({Intersection(1, SPHERE), Intersection(2, SPHERE)}), Intersection(1, SPHERE)),
        std::make_tuple(Intersections({Intersection(-1, SPHERE), Intersection(2, SPHERE)}), Intersection(2, SPHERE)),
        std::make_tuple(Intersections({Intersection(-2, SPHERE), Intersection(-1, SPHERE)}), std::optional<Intersection>()),
        std::make_tuple(Intersections({Intersection(5, SPHERE), Intersection(7, SPHERE), Intersection(-3, SPHERE), Intersection(2, SPHERE)}), Intersection(2, SPHERE))));

TEST(IntersectionsTest, Precompute)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i = Intersection(4, SPHERE);

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_FLOAT_EQ(result.t, i.t);
    EXPECT_EQ(result.object, i.object);
    EXPECT_EQ(result.position, Point(0, 0, -1));
    EXPECT_EQ(result.eye_direction, Vector(0, 0, -1));
    EXPECT_EQ(result.normal_direction, Vector(0, 0, -1));
}

TEST(IntersectionsTest, IntersectionOutside)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i = Intersection(4, SPHERE);

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_EQ(result.inside, false);
}

TEST(IntersectionsTest, IntersectionInside)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersection i = Intersection(1, SPHERE);

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_EQ(result.inside, true);
    EXPECT_EQ(result.position, Point(0, 0, 1));
    EXPECT_EQ(result.eye_direction, Vector(0, 0, -1));
    EXPECT_EQ(result.normal_direction, Vector(0, 0, -1));
}
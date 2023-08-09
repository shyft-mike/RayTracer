#include <gtest/gtest.h>
#include <raytracer.tests.hpp>
#include <raytracer/common/constants.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/intersections.hpp>

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
        std::make_tuple(Intersections({Intersection(1, TEST_SPHERE.get()), Intersection(2, TEST_SPHERE.get())}), Intersection(1, TEST_SPHERE.get())),
        std::make_tuple(Intersections({Intersection(-1, TEST_SPHERE.get()), Intersection(2, TEST_SPHERE.get())}), Intersection(2, TEST_SPHERE.get())),
        std::make_tuple(Intersections({Intersection(-2, TEST_SPHERE.get()), Intersection(-1, TEST_SPHERE.get())}), std::optional<Intersection>())));

TEST(IntersectionsTest, Precompute)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i = Intersection(4, TEST_SPHERE.get());

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_FLOAT_EQ(result.t, i.t);
    EXPECT_EQ(result.object, i.object);
    EXPECT_EQ(result.position, Point(0, 0, -1));
    EXPECT_EQ(result.eye_direction, Vector(0, 0, -1));
    EXPECT_EQ(result.normal_direction, Vector(0, 0, -1));
}

TEST(IntersectionsTest, PrecomputeReflection)
{
    Ray r = Ray(Point(0, 1, -1), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    Intersection i = Intersection(std::sqrt(2), TEST_PLANE.get());

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_EQ(result.reflect_direction, Vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
}

TEST(IntersectionsTest, IntersectionOutside)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i = Intersection(4, TEST_SPHERE.get());

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_EQ(result.inside, false);
}

TEST(IntersectionsTest, IntersectionInside)
{
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersection i = Intersection(1, TEST_SPHERE.get());

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_EQ(result.inside, true);
    EXPECT_EQ(result.position, Point(0, 0, 1));
    EXPECT_EQ(result.eye_direction, Vector(0, 0, -1));
    EXPECT_EQ(result.normal_direction, Vector(0, 0, -1));
}

TEST(IntersectionsTest, HitShouldOffsetPoint)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    IShape *shape = new Sphere("1");
    shape->translate(0, 0, 1);
    Intersection i = Intersection(5, shape);

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_TRUE(result.over_position.z < -ACNE_EPSILON / 2);
    EXPECT_TRUE(result.position.z > result.over_position.z);
}
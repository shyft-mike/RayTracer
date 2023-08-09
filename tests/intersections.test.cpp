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
    IShape *shape = TEST_SPHERE.get();
    shape->translate(0, 0, 1);
    Intersection i = Intersection(5, shape);

    ComputedIntersection result = compute_intersection(i, r);

    EXPECT_TRUE(result.over_position.z < -ACNE_EPSILON / 2);
    EXPECT_TRUE(result.position.z > result.over_position.z);
}

TEST_P(IntersectionsNTestFixture, FindN)
{
    auto [index, expected_n1, expected_n2] = GetParam();

    Sphere *a = Sphere::glass_sphere();
    a->scale(2, 2, 2);
    a->material.refractive_index = 1.5;

    Sphere *b = Sphere::glass_sphere();
    b->translate(0, 0, -0.25);
    b->material.refractive_index = 2;

    Sphere *c = Sphere::glass_sphere();
    c->translate(0, 0, 0.25);
    c->material.refractive_index = 2.5;

    Ray r = Ray(Point(0, 0, -4), Vector(0, 0, 1));
    Intersections xs = Intersections({
        Intersection(2.00, a),
        Intersection(2.75, b),
        Intersection(3.25, c),
        Intersection(4.75, b),
        Intersection(5.25, c),
        Intersection(6, a),
    });

    ComputedIntersection result = compute_intersection(xs.at(index), r, xs);
    EXPECT_FLOAT_EQ(result.n1, expected_n1);
    EXPECT_FLOAT_EQ(result.n2, expected_n2);
}

INSTANTIATE_TEST_SUITE_P(
    IntersectionsTest_FindN,
    IntersectionsNTestFixture,
    ::testing::Values(
        std::make_tuple(0, 1.0, 1.5),
        std::make_tuple(1, 1.5, 2.0),
        std::make_tuple(2, 2.0, 2.5),
        std::make_tuple(3, 2.5, 2.5),
        std::make_tuple(4, 2.5, 1.5),
        std::make_tuple(5, 1.5, 1.0)));

TEST(IntersectionsTest, UnderPosition)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    IShape *shape = Sphere::glass_sphere();
    shape->translate(0, 0, 1);
    Intersection i = Intersection(5, shape);
    Intersections xs = Intersections({i});

    ComputedIntersection result = compute_intersection(i, r, xs);

    EXPECT_TRUE(result.under_position.z > ACNE_EPSILON / 2);
    EXPECT_TRUE(result.position.z < result.under_position.z);
}
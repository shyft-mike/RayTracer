#include <gtest/gtest.h>
#include "spheres.h"
#include "fixtures.h"
#include "intersections.h"

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

#include <gtest/gtest.h>
#include "spheres.h"
#include "fixtures.h"
#include "intersections.h"
#include "matrices.h"

const Sphere SPHERE = Sphere("test");

TEST_P(SpheresTestFixture, Intersect)
{
    auto [origin, direction, expectedResult] = GetParam();

    Ray ray = Ray(origin, direction);
    Intersections results = get_intersections(SPHERE, ray);

    EXPECT_EQ(results.size(), expectedResult.size());

    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_FLOAT_EQ(results[i].t, expectedResult[i].t);
        EXPECT_EQ(results[i].object, expectedResult[i].object);
    }
}

INSTANTIATE_TEST_SUITE_P(
    SpheresTest_Intersect,
    SpheresTestFixture,
    ::testing::Values(
        std::make_tuple(Point(0, 0, -5), Vector(0, 0, 1), Intersections({Intersection(4, SPHERE), Intersection(6, SPHERE)})),
        std::make_tuple(Point(0, 2, -5), Vector(0, 0, 1), Intersections({})),
        std::make_tuple(Point(0, 0, 0), Vector(0, 0, 1), Intersections({Intersection(-1, SPHERE), Intersection(1, SPHERE)})),
        std::make_tuple(Point(0, 0, 5), Vector(0, 0, 1), Intersections({Intersection(-6, SPHERE), Intersection(-4, SPHERE)}))));

TEST(SpheresTest, Default)
{
    Sphere result = Sphere("test");

    EXPECT_EQ(result.id, "test");
    EXPECT_EQ(result.transform, MatrixHelper::identity().matrix);
}

TEST(SpheresTest, IntersectScaledSphere)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere("test");
    s.transform = scaling(2, 2, 2);

    Intersections results = get_intersections(s, r);

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].t, 3);
    EXPECT_EQ(results[1].t, 7);
}

TEST(SpheresTest, IntersectTranslatedSphere)
{
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere("test");
    s.transform = translation(5, 0, 0);

    Intersections results = get_intersections(s, r);

    EXPECT_EQ(results.size(), 0);
}
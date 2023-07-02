#include <gtest/gtest.h>
#include "raytracer/rays.h"
#include "raytracer/matrices/matrices.h"
#include "raytracer/matrices/transformations.h"

TEST(RaysTest, Basic)
{
    Point origin = Point(1, 2, 3);
    Vector direction = Vector(4, 5, 6);

    Ray result = Ray(origin, direction);

    EXPECT_EQ(result.origin, origin);
    EXPECT_EQ(result.direction, direction);
}

TEST(RaysTest, Position)
{
    Point origin = Point(2, 3, 4);
    Vector direction = Vector(1, 0, 0);
    Ray ray = Ray(origin, direction);

    EXPECT_EQ(ray.get_position(0), Point(2, 3, 4));
    EXPECT_EQ(ray.get_position(1), Point(3, 3, 4));
    EXPECT_EQ(ray.get_position(-1), Point(1, 3, 4));
    EXPECT_EQ(ray.get_position(2.5), Point(4.5, 3, 4));
}

TEST(RaysTest, Scale)
{
    Ray ray = Ray(Point(1, 2, 3), Vector(0, 1, 0));

    Ray result = ray.scale(2, 3, 4);

    EXPECT_EQ(result.origin, Point(2, 6, 12));
    EXPECT_EQ(result.direction, Vector(0, 3, 0));
}

TEST(RaysTest, Translate)
{
    Ray ray = Ray(Point(1, 2, 3), Vector(0, 1, 0));

    Ray result = ray.translate(3, 4, 5);

    EXPECT_EQ(result.origin, Point(4, 6, 8));
    EXPECT_EQ(result.direction, Vector(0, 1, 0));
}
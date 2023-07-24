#include <gtest/gtest.h>
#include <helpers.hpp>
#include <raytracer/core/world.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/intersections.hpp>

TEST(WorldTest, Default)
{
    World result = create_default_world();

    EXPECT_EQ(result.lights.size(), 1);
    EXPECT_EQ(result.shapes.size(), 2);
}

TEST(WorldTest, Intersect)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));

    Intersections results = intersect_world(w, r);

    EXPECT_EQ(results.size(), 4);
    EXPECT_FLOAT_EQ(results[0].t, 4);
    EXPECT_FLOAT_EQ(results[1].t, 4.5);
    EXPECT_FLOAT_EQ(results[2].t, 5.5);
    EXPECT_FLOAT_EQ(results[3].t, 6);
}

TEST(WorldTest, ShadingIntersection)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i = Intersection(4, w.shapes[0]);
    ComputedIntersection c_i = compute_intersection(i, r);

    Color result = shade_hit(w, c_i);

    check_color(result, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionInside)
{
    World w = create_default_world();
    w.lights[0] = PointLight(Point(0, 0.25, 0), Color(1, 1, 1));
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersection i = Intersection(0.5, w.shapes[1]);
    ComputedIntersection c_i = compute_intersection(i, r);

    Color result = shade_hit(w, c_i);

    check_color(result, Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldTest, ShadeHitInShadow)
{
    World w = World();
    w.lights = {PointLight(Point(0, 0, -10), Color(1, 1, 1))};
    Sphere s1 = Sphere("s1");
    Sphere s2 = Sphere("s2");
    s2.transform = MatrixHelper(s2.transform).translate(0, 0, 10);
    w.shapes = {s1, s2};

    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Intersection i = Intersection(4, s2);
    ComputedIntersection c_i = compute_intersection(i, r);

    Color result = shade_hit(w, c_i);

    check_color(result, Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, ColorWhenMissed)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 1, 0));

    Color result = color_at(w, r);

    check_color(result, BLACK);
}

TEST(WorldTest, ColorHit)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));

    Color result = color_at(w, r);

    check_color(result, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorHitBehind)
{
    World w = create_default_world();
    IShape &outer = w.shapes[0];
    outer.material.ambient = 1;
    IShape &inner = w.shapes[1];
    inner.material.ambient = 1;
    Ray r = Ray(Point(0, 0, 0.75), Vector(0, 0, -1));

    Color result = color_at(w, r);

    check_color(result, inner.material.color);
}

TEST(WorldTest, ShadowNothingCollinearWithPointAndLight)
{
    World w = create_default_world();
    Point p = Point(0, 10, 0);

    bool result = is_shadowed(w, p);

    EXPECT_EQ(result, false);
}

TEST(WorldTest, ShadowObjectBetweenPointAndLight)
{
    World w = create_default_world();
    Point p = Point(10, -10, 10);

    bool result = is_shadowed(w, p);

    EXPECT_EQ(result, true);
}

TEST(WorldTest, ShadowWhenObjectBehindLight)
{
    World w = create_default_world();
    Point p = Point(-20, 20, -20);

    bool result = is_shadowed(w, p);

    EXPECT_EQ(result, false);
}

TEST(WorldTest, ShadowObjectBehindPoint)
{
    World w = create_default_world();
    Point p = Point(-2, 2, -2);

    bool result = is_shadowed(w, p);

    EXPECT_EQ(result, false);
}
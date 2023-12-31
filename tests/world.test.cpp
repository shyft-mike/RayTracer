#include <gtest/gtest.h>
#include <raytracer.tests.hpp>
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

// TEST(WorldTest, ShadingIntersectionInside)
// {
//     World w = create_default_world();
//     w.lights[0] = PointLight(Point(0, 0.25, 0), Color(1, 1, 1));
//     Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
//     Intersection i = Intersection(0.5, w.shapes[1]);
//     ComputedIntersection c_i = compute_intersection(i, r);

//     Color result = shade_hit(w, c_i);

//     check_color(result, Color(0.90498, 0.90498, 0.90498));
// }

TEST(WorldTest, ShadeHitInShadow)
{
    World w = World();
    w.lights = {PointLight(Point(0, 0, -10), Color(1, 1, 1))};
    IShape *s1 = new Sphere();
    IShape *s2 = new Sphere();
    s2->translate(0, 0, 10);
    w.shapes = {s1, s2};

    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Intersection i = Intersection(4, s2);
    ComputedIntersection c_i = compute_intersection(i, r);

    Color result = shade_hit(w, c_i);

    check_color(result, Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, ShadeHitReflective)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    IShape *shape = new Plane();
    shape->material.reflective = 0.5;
    shape->translate(0, -1, 0);
    w.shapes.push_back(shape);
    Intersection i = Intersection(std::sqrt(2), shape);
    ComputedIntersection computed = compute_intersection(i, r);

    Color result = shade_hit(w, computed);

    check_color(result, Color(0.87677, 0.92436, 0.82918));
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
    IShape &outer = *w.shapes[0];
    outer.material.ambient = 1;
    IShape &inner = *w.shapes[1];
    inner.material.ambient = 1;
    Ray r = Ray(Point(0, 0, 0.75), Vector(0, 0, -1));

    Color result = color_at(w, r);

    check_color(result, inner.material.pattern->colors.at(0));
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

TEST(WorldTest, ReflectedColor)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    IShape *shape = new Plane();
    shape->material.reflective = 0.5;
    shape->translate(0, -1, 0);
    w.shapes.push_back(shape);
    Intersection i = Intersection(std::sqrt(2), shape);
    ComputedIntersection computed = compute_intersection(i, r);

    Color result = get_reflected_color(w, computed);

    check_color(result, Color(0.19032, 0.2379, 0.14274));
}

TEST(WorldTest, ReflectedColorNonreflectiveMaterial)
{
    World w = create_default_world();
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    IShape *shape = w.shapes.at(1);
    shape->material.ambient = 1;
    Intersection i = Intersection(1, shape);
    ComputedIntersection computed = compute_intersection(i, r);

    Color result = get_reflected_color(w, computed);

    check_color(result, BLACK);
}

TEST(WorldTest, ReflectedColorMirrors)
{
    World w = World();
    w.lights.push_back(PointLight(Point(0, 0, 0), WHITE));
    IShape *lower = new Plane();
    lower->material.reflective = 1;
    lower->translate(0, -1, 0);
    IShape *upper = new Plane();
    upper->material.reflective = 1;
    upper->translate(0, 1, 0);
    w.shapes.push_back(lower);
    w.shapes.push_back(upper);
    Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));

    EXPECT_NO_THROW(color_at(w, r));
}

TEST(WorldTest, GetRefractedColorOpaqueSurface)
{
    World w = create_default_world();
    IShape *shape = w.shapes.at(0);
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersections xs = Intersections({Intersection(4, shape), Intersection(6, shape)});
    ComputedIntersection computed_intersection = compute_intersection(xs.at(0), r, xs);

    Color result = get_refracted_color(w, computed_intersection, 5);

    check_color(result, BLACK);
}

TEST(WorldTest, GetRefractedColorMaxRecursion)
{
    World w = create_default_world();
    IShape *shape = w.shapes.at(0);
    shape->material.transparency = 1;
    shape->material.refractive_index = 1.5;
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersections xs = Intersections({Intersection(4, shape), Intersection(6, shape)});
    ComputedIntersection computed_intersection = compute_intersection(xs.at(0), r, xs);

    Color result = get_refracted_color(w, computed_intersection, 0);

    check_color(result, BLACK);
}

TEST(WorldTest, GetRefractedColorTotalInternalReflection)
{
    World w = create_default_world();
    IShape *shape = w.shapes.at(0);
    shape->material.transparency = 1;
    shape->material.refractive_index = 1.5;
    Ray r = Ray(Point(0, 0, std::sqrt(2) / 2), Vector(0, 1, 0));
    Intersections xs = Intersections({Intersection(-std::sqrt(2) / 2, shape),
                                      Intersection(std::sqrt(2) / 2, shape)});
    ComputedIntersection computed_intersection = compute_intersection(xs.at(1), r, xs);

    Color result = get_refracted_color(w, computed_intersection, 5);

    check_color(result, BLACK);
}

TEST(WorldTest, GetRefractedColorHit)
{
    World w = create_default_world();
    IShape *s1 = w.shapes.at(0);
    s1->material.ambient = 1;
    s1->material.pattern = TEST_PATTERN.get();
    IShape *s2 = w.shapes.at(1);
    s2->material.transparency = 1;
    s2->material.refractive_index = 1.5;
    Ray r = Ray(Point(0, 0, 0.1), Vector(0, 1, 0));
    Intersections xs = Intersections({Intersection(-0.9899, s1),
                                      Intersection(-0.4899, s2),
                                      Intersection(0.4899, s2),
                                      Intersection(0.9899, s1)});
    ComputedIntersection computed_intersection = compute_intersection(xs.at(2), r, xs);

    Color result = get_refracted_color(w, computed_intersection, 5);

    check_color(result, Color(0, 0.99888, 0.04725));
}

TEST(WorldTest, ShadeHitTransparent)
{
    World w = create_default_world();
    IShape *floor = TEST_PLANE.get();
    floor->translate(0, -1, 0);
    floor->material.transparency = 0.5;
    floor->material.refractive_index = 1.5;
    IShape *ball = TEST_SPHERE.get();
    ball->translate(0, -3.5, -0.5);
    ball->material.pattern = new SolidPattern(RED);
    ball->material.ambient = 0.5;
    w.shapes.push_back(floor);
    w.shapes.push_back(ball);
    Ray r = Ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
    Intersections xs = Intersections({Intersection(std::sqrt(2), floor)});
    ComputedIntersection computed_intersection = compute_intersection(xs.at(0), r, xs);

    Color result = shade_hit(w, computed_intersection, 5);

    check_color(result, Color(0.93642, 0.68642, 0.68642));
}

#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <helpers.hpp>
#include <raytracer/core/shapes/sphere.hpp>
#include <raytracer/core/shapes/shape.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/intersections.hpp>

namespace SphereTest
{
    Sphere *SPHERE = new Sphere("test");

    TEST_P(SpheresTestFixture, Intersect)
    {
        auto [origin, direction, expectedResult] = GetParam();

        Ray ray = Ray(origin, direction);
        Intersections results = intersect(*SPHERE, ray);

        EXPECT_EQ(results.size(), expectedResult.size());

        for (int i = 0; i < results.size(); i++)
        {
            EXPECT_FLOAT_EQ(results[i].t, expectedResult[i].t);
            EXPECT_EQ(results[i].object, expectedResult[i].object);
        }
    }

    INSTANTIATE_TEST_SUITE_P(
        SphereTest_Intersect,
        SpheresTestFixture,
        ::testing::Values(
            std::make_tuple(Point(0, 0, -5), Vector(0, 0, 1), Intersections({Intersection(4, SPHERE), Intersection(6, SPHERE)})),
            std::make_tuple(Point(0, 2, -5), Vector(0, 0, 1), Intersections({})),
            std::make_tuple(Point(0, 0, 0), Vector(0, 0, 1), Intersections({Intersection(-1, SPHERE), Intersection(1, SPHERE)})),
            std::make_tuple(Point(0, 0, 5), Vector(0, 0, 1), Intersections({Intersection(-6, SPHERE), Intersection(-4, SPHERE)}))));

    TEST(SphereTest, Default)
    {
        Sphere result = Sphere("test");

        EXPECT_EQ(result.id, "test");
        EXPECT_EQ(result.transform, MatrixHelper::identity().matrix);
    }

    TEST(SphereTest, IntersectScaledSphere)
    {
        Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
        Sphere s = Sphere("test");
        s.transform = scaling(2, 2, 2);

        Intersections results = intersect(s, r);

        EXPECT_EQ(results.size(), 2);
        EXPECT_EQ(results[0].t, 3);
        EXPECT_EQ(results[1].t, 7);
    }

    TEST(SphereTest, IntersectTranslatedSphere)
    {
        Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
        Sphere s = Sphere("test");
        s.transform = translation(5, 0, 0);

        Intersections results = intersect(s, r);

        EXPECT_EQ(results.size(), 0);
    }

    TEST(SphereTest, NormalX)
    {
        Sphere s = Sphere("test");

        Vector result = s.normal_at(1, 0, 0);

        EXPECT_EQ(result, Vector(1, 0, 0));
    }

    TEST(SphereTest, NormalY)
    {
        Sphere s = Sphere("test");

        Vector result = s.normal_at(0, 1, 0);

        EXPECT_EQ(result, Vector(0, 1, 0));
    }

    TEST(SphereTest, NormalZ)
    {
        Sphere s = Sphere("test");

        Vector result = s.normal_at(0, 0, 1);

        EXPECT_EQ(result, Vector(0, 0, 1));
    }

    TEST(SphereTest, IsNormal)
    {
        Sphere s = Sphere("test");

        Vector result = s.normal_at(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3);

        check_matrix(result, result.normalize());
    }

    TEST(SphereTest, NormalTranslated)
    {
        Sphere s = Sphere("test");
        s.translate(0, 1, 0);

        Vector result = s.normal_at(0, 1.70711, -0.70711);

        check_matrix(result, Vector(0, 0.70711, -0.70711));
    }

    TEST(SphereTest, NormalTransformed)
    {
        Sphere s = Sphere("test");
        s.scale(1, 0.5, 1).rotate_z(M_PI / 5);

        Vector result = s.normal_at(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);

        check_matrix(result, Vector(0, 0.97014, -0.24254));
    }

    TEST(SphereTest, DefaultMaterial)
    {
        Sphere result = Sphere("test");

        EXPECT_EQ(result.material, Material());
    }

    TEST(SphereTest, AssignedMaterial)
    {
        Sphere result = Sphere("test");
        Material m = Material();
        m.ambient = 1;
        result.material = m;

        EXPECT_EQ(result.material, m);
    }
}
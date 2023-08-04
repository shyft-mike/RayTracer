#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/patterns/pattern.hpp>

namespace MaterialTest
{
    TEST(MaterialTest, Default)
    {
        Material m = Material();

        EXPECT_EQ(m.pattern->color, Color(1, 1, 1));
        EXPECT_FLOAT_EQ(m.ambient, 0.1);
        EXPECT_FLOAT_EQ(m.diffuse, 0.9);
        EXPECT_FLOAT_EQ(m.specular, 0.9);
        EXPECT_FLOAT_EQ(m.shininess, 200);
    }

    TEST_P(MaterialLightingTestFixture, Lighting)
    {
        auto [eye_vector, normal_vector, light, expectedResult, is_shadow] = GetParam();

        Color result = lighting(this->m, light, this->position, eye_vector, normal_vector, is_shadow);

        EXPECT_NEAR(result.blue, expectedResult.blue, 0.0001);
        EXPECT_NEAR(result.green, expectedResult.green, 0.0001);
        EXPECT_NEAR(result.red, expectedResult.red, 0.0001);
    }

    INSTANTIATE_TEST_CASE_P(
        MaterialTest,
        MaterialLightingTestFixture,
        ::testing::Values(
            std::make_tuple(Vector(0, 0, -1), Vector(0, 0, -1), PointLight(Point(0, 0, -10), Color(1, 1, 1)), Color(1.9, 1.9, 1.9), false),
            std::make_tuple(Vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2), Vector(0, 0, -1), PointLight(Point(0, 0, -10), Color(1, 1, 1)), Color(1.0, 1.0, 1.0), false),
            std::make_tuple(Vector(0, 0, -1), Vector(0, 0, -1), PointLight(Point(0, 10, -10), Color(1, 1, 1)), Color(0.7364, 0.7364, 0.7364), false),
            std::make_tuple(Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2), Vector(0, 0, -1), PointLight(Point(0, 10, -10), Color(1, 1, 1)), Color(1.6364, 1.6364, 1.6364), false),
            std::make_tuple(Vector(0, 0, -1), Vector(0, 0, -1), PointLight(Point(0, 0, 10), Color(1, 1, 1)), Color(0.1, 0.1, 0.1), false),
            std::make_tuple(Vector(0, 0, -1), Vector(0, 0, -1), PointLight(Point(0, 0, -10), Color(1, 1, 1)), Color(0.1, 0.1, 0.1), true)));

    TEST(MaterialTest, LightingWithPattern)
    {
        Material m = Material();
        m.pattern = new StripePattern(WHITE, BLACK);
        m.ambient = 1;
        m.diffuse = 0;
        m.specular = 0;

        Vector eye = Vector(0, 0, -1);
        Vector normal = Vector(0, 0, -1);
        PointLight light = PointLight(Point(0, 0, -10), WHITE);

        Color result_1 = lighting(m, light, Point(0.9, 0, 0), eye, normal, false);
        Color result_2 = lighting(m, light, Point(1.1, 0, 0), eye, normal, false);

        ASSERT_EQ(result_1, WHITE);
        ASSERT_EQ(result_2, BLACK);
    }

}

#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/patterns/pattern.hpp>

TEST(MaterialTest, Default)
{
    Material m = Material();

    EXPECT_EQ(m.pattern->colors.at(0), WHITE);
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
}

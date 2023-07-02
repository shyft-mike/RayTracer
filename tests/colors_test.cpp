#include <gtest/gtest.h>
#include "raytracer/colors.h"

TEST(ColorsTest, Constructor)
{
    Color result = Color(-0.5, 0.4, 1.7);

    EXPECT_FLOAT_EQ(result.red, -0.5);
    EXPECT_FLOAT_EQ(result.green, 0.4);
    EXPECT_FLOAT_EQ(result.blue, 1.7);
}

TEST(ColorsTest, Add)
{
    Color color1 = Color(0.9, 0.6, 0.75);
    Color color2 = Color(0.7, 0.1, 0.25);

    Color result = color1 + color2;

    EXPECT_FLOAT_EQ(result.red, 1.6);
    EXPECT_FLOAT_EQ(result.green, 0.7);
    EXPECT_FLOAT_EQ(result.blue, 1.0);
}

TEST(ColorsTest, Subtract)
{
    Color color1 = Color(0.9, 0.6, 0.75);
    Color color2 = Color(0.7, 0.1, 0.25);

    Color result = color1 - color2;

    EXPECT_FLOAT_EQ(result.red, 0.2);
    EXPECT_FLOAT_EQ(result.green, 0.5);
    EXPECT_FLOAT_EQ(result.blue, 0.5);
}

TEST(ColorsTest, Multiply)
{
    Color color1 = Color(1, 0.2, 0.4);
    Color color2 = Color(0.9, 1, 0.1);

    Color result = color1 * color2;

    EXPECT_FLOAT_EQ(result.red, 0.9);
    EXPECT_FLOAT_EQ(result.green, 0.2);
    EXPECT_FLOAT_EQ(result.blue, 0.04);
}

TEST(ColorsTest, MultiplyByScalar)
{
    Color color1 = Color(0.2, 0.3, 0.4);

    Color result = color1 * 2;

    EXPECT_FLOAT_EQ(result.red, 0.4);
    EXPECT_FLOAT_EQ(result.green, 0.6);
    EXPECT_FLOAT_EQ(result.blue, 0.8);
}
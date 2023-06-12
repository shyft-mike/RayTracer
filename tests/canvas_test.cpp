#include <gtest/gtest.h>
#include "canvas.h"
#include "helpers.h"

TEST(CanvasTest, Constructor)
{
    Canvas result = Canvas(10, 20);

    EXPECT_FLOAT_EQ(result.width, 10);
    EXPECT_FLOAT_EQ(result.height, 20);

    for (const Color &pixel : result.pixels)
    {
        EXPECT_FLOAT_EQ(pixel.red, 0);
        EXPECT_FLOAT_EQ(pixel.green, 0);
        EXPECT_FLOAT_EQ(pixel.blue, 0);
    }
}

TEST(CanvasTest, SetPixel)
{
    Canvas canvas = Canvas(10, 20);
    Color pixel = Color(1, 0, 0);

    canvas.setPixel(2, 3, pixel);

    Color result = canvas.getPixel(2, 3);

    EXPECT_FLOAT_EQ(result.red, pixel.red);
    EXPECT_FLOAT_EQ(result.green, pixel.green);
    EXPECT_FLOAT_EQ(result.blue, pixel.blue);
}

TEST(CanvasTest, PPM)
{
    Canvas canvas = Canvas(5, 3);

    auto ppm = canvas.toPPM();
    auto result = split(ppm, "\n");

    EXPECT_EQ(result[0], "P3");
    EXPECT_EQ(result[1], "5 3");
    EXPECT_EQ(result[2], "255");
}

TEST(CanvasTest, PPMPixelCheck)
{
    Canvas canvas = Canvas(5, 3);
    canvas.setPixel(0, 0, Color(1.5, 0, 0));
    canvas.setPixel(2, 1, Color(0, 0.5, 0));
    canvas.setPixel(4, 2, Color(-0.5, 0, 1));

    auto ppm = canvas.toPPM();
    auto result = split(ppm, "\n");

    EXPECT_EQ(result[3], "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    EXPECT_EQ(result[4], "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    EXPECT_EQ(result[5], "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}
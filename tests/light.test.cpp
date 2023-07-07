#include <gtest/gtest.h>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/matrices/matrix.hpp>

TEST(LightTest, DefaultPointLight)
{
    Color intensity = Color(1, 1, 1);
    Point position = Point(1, 1, 1);

    PointLight result = PointLight(position, intensity);

    EXPECT_EQ(result.intensity, intensity);
    EXPECT_EQ(result.position, position);
}
#include <gtest/gtest.h>
#include <math.h>
#include <helpers.hpp>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/camera.hpp>
#include <raytracer/core/matrices/helper.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/rays.hpp>
#include <raytracer/core/world.hpp>
#include <raytracer/core/matrices/transformations.hpp>

TEST(CameraTest, Default)
{
    int h_size = 160;
    int v_size = 120;
    float field_of_view = M_PI_2;

    Camera result = Camera(h_size, v_size, field_of_view);

    EXPECT_EQ(result.h_size, h_size);
    EXPECT_EQ(result.v_size, v_size);
    EXPECT_EQ(result.field_of_view, field_of_view);
    EXPECT_EQ(result.transform, MatrixHelper::identity().matrix);
}

TEST(CameraTest, HorizontalPixelSize)
{
    Camera c = Camera(200, 125, M_PI_2);

    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTest, VerticalPixelSize)
{
    Camera c = Camera(125, 200, M_PI_2);

    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTest, RayThroughCenter)
{
    Camera c = Camera(201, 101, M_PI_2);
    Ray result = ray_for_pixel(c, 100, 50);

    check_matrix(result.origin, Point(0, 0, 0));
    check_matrix(result.direction, Vector(0, 0, -1));
}

TEST(CameraTest, RayThroughCorner)
{
    Camera c = Camera(201, 101, M_PI_2);
    Ray result = ray_for_pixel(c, 0, 0);

    check_matrix(result.origin, Point(0, 0, 0));
    check_matrix(result.direction, Vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayWhenTransformed)
{
    Camera c = Camera(201, 101, M_PI_2);
    c.transform = MatrixHelper(c.transform).rotate_y(M_PI_4).translate(0, -2, 5);
    Ray result = ray_for_pixel(c, 100, 50);

    check_matrix(result.origin, Point(0, 2, -5));
    check_matrix(result.direction, Vector(std::sqrt(2) / 2, 0, -std::sqrt(2) / 2));
}

TEST(CameraTest, Render)
{
    World w = create_default_world();
    Camera c = Camera(11, 11, M_PI_2);
    Point from = Point(0, 0, -5);
    Point to = Point(0, 0, 0);
    Vector up = Vector(0, 1, 0);
    c.transform = view_transform(from, to, up);

    Canvas result = render(c, w);

    check_color(result.get_pixel(5, 5), Color(0.38066, 0.47583, 0.2855));
}
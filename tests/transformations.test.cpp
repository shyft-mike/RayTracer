#include <gtest/gtest.h>
#include <fixtures.hpp>
#include <helpers.hpp>
#include <math.h>
#include <raytracer/core/matrices/transformations.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/matrices/helper.hpp>

TEST_P(TransformationsTestFixture, Common)
{
    auto [transform, point, expectedResult] = GetParam();

    Matrix result = point * transform;

    check_matrix(result, expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Translation,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(translation(Point(5, -3, 2)), Point(-3, 4, 5), Point(2, 1, 7)),
        std::make_tuple(inverse(translation(Point(5, -3, 2))), Point(-3, 4, 5), Point(-8, 7, 3)),
        std::make_tuple(translation(Point(5, -3, 2)), Vector(-3, 4, 5), Vector(-3, 4, 5))));

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Scaling,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(scaling(Point(2, 3, 4)), Point(-4, 6, 8), Point(-8, 18, 32)),
        std::make_tuple(scaling(Point(2, 3, 4)), Vector(-4, 6, 8), Vector(-8, 18, 32)),
        std::make_tuple(scaling(Point(-1, 1, 1)), Point(2, 3, 4), Point(-2, 3, 4)),
        std::make_tuple(inverse(scaling(Point(2, 3, 4))), Vector(-4, 6, 8), Vector(-2, 2, 2))));

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Rotation_X,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(rotation_x(M_PI / 4), Point(0, 1, 0), Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2)),
        std::make_tuple(rotation_x(M_PI / 2), Point(0, 1, 0), Point(0, 0, 1)),
        std::make_tuple(inverse(rotation_x(M_PI / 4)), Point(0, 1, 0), Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2))));

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Rotation_Y,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(rotation_y(M_PI / 4), Point(0, 0, 1), Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2)),
        std::make_tuple(rotation_y(M_PI / 2), Point(0, 0, 1), Point(1, 0, 0))));

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Rotation_Z,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(rotation_z(M_PI / 4), Point(0, 1, 0), Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0)),
        std::make_tuple(rotation_z(M_PI / 2), Point(0, 1, 0), Point(-1, 0, 0))));

INSTANTIATE_TEST_SUITE_P(
    TransformationsTest_Shearing,
    TransformationsTestFixture,
    ::testing::Values(
        std::make_tuple(shearing(1, 0, 0, 0, 0, 0), Point(2, 3, 4), Point(5, 3, 4)),
        std::make_tuple(shearing(0, 1, 0, 0, 0, 0), Point(2, 3, 4), Point(6, 3, 4)),
        std::make_tuple(shearing(0, 0, 1, 0, 0, 0), Point(2, 3, 4), Point(2, 5, 4)),
        std::make_tuple(shearing(0, 0, 0, 1, 0, 0), Point(2, 3, 4), Point(2, 7, 4)),
        std::make_tuple(shearing(0, 0, 0, 0, 1, 0), Point(2, 3, 4), Point(2, 3, 6)),
        std::make_tuple(shearing(0, 0, 0, 0, 0, 1), Point(2, 3, 4), Point(2, 3, 7))));

TEST(TransformationsTest, IndividualTransforms)
{
    Point p = Point(1, 0, 1);
    Matrix A = rotation_x(M_PI_2);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);

    Matrix p2 = A * p;

    check_matrix(p2, Point(1, -1, 0));

    Matrix p3 = B * p2;

    check_matrix(p3, Point(5, -5, 0));

    Matrix p4 = C * p3;

    check_matrix(p4, Point(15, 0, 7));
}

TEST(TransformationsTest, ChainedTransforms)
{
    Point p = Point(1, 0, 1);
    Matrix A = rotation_x(M_PI_2);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);

    Matrix T = C * B * A;

    check_matrix(T * p, Point(15, 0, 7));
}

TEST(TransformationsTest, ViewTransformDefault)
{
    Point from = Point(0, 0, 0);
    Point to = Point(0, 0, -1);
    Vector up = Vector(0, 1, 0);

    Matrix result = view_transform(from, to, up);

    check_matrix(result, MatrixHelper::identity());
}

TEST(TransformationsTest, ViewTransformZ)
{
    Point from = Point(0, 0, 0);
    Point to = Point(0, 0, 1);
    Vector up = Vector(0, 1, 0);

    Matrix result = view_transform(from, to, up);

    check_matrix(result, scaling(-1, 1, -1));
}

TEST(TransformationsTest, ViewTransformWorld)
{
    Point from = Point(0, 0, 8);
    Point to = Point(0, 0, 0);
    Vector up = Vector(0, 1, 0);

    Matrix result = view_transform(from, to, up);

    check_matrix(result, translation(0, 0, -8));
}

TEST(TransformationsTest, ViewTransform)
{
    Point from = Point(1, 3, 2);
    Point to = Point(4, -2, 8);
    Vector up = Vector(1, 1, 0);

    Matrix result = view_transform(from, to, up);

    check_matrix(result, Matrix({{-0.50709, 0.50709, 0.67612, -2.36643},
                                 {0.76772, 0.60609, 0.12122, -2.82843},
                                 {-0.35857, 0.59761, -0.71714, 0},
                                 {0, 0, 0, 1}}));
}
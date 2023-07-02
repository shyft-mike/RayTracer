#include <gtest/gtest.h>
#include "raytracer/cartesia.h"
#include "fixtures.h"

TEST(CartesiaTest, PointBasics)
{
    Point result = Point(1, 2, 3);

    EXPECT_EQ(result.x, 1);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.z, 3);
}

TEST(CartesiaTest, VectorBasics)
{
    Vector result = Vector(1, 2, 3);

    EXPECT_EQ(result.x, 1);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.z, 3);
}

// parameterize
TEST(CartesiaTest, VectorMagnitude)
{
    float result = Vector(1, 0, 0).magnitude;

    EXPECT_FLOAT_EQ(result, 1);

    result = Vector(0, 1, 0).magnitude;

    EXPECT_FLOAT_EQ(result, 1);

    result = Vector(0, 0, 1).magnitude;

    EXPECT_FLOAT_EQ(result, 1);

    result = Vector(1, 2, 3).magnitude;

    EXPECT_FLOAT_EQ(result, sqrt(14));

    result = Vector(-1, -2, -3).magnitude;

    EXPECT_FLOAT_EQ(result, sqrt(14));
}

TEST(CartesiaTest, PointPlusVector)
{
    Point point = Point(1, 2, 3);
    Vector vector = Vector(6, 4, 2);

    Point result = point + vector;

    EXPECT_EQ(result.x, 7);
    EXPECT_EQ(result.y, 6);
    EXPECT_EQ(result.z, 5);
}

TEST(CartesiaTest, PointPlusPoint)
{
    Point point1 = Point(3, 2, 1);
    Point point2 = Point(5, 6, 7);

    Vector result = point1 - point2;

    EXPECT_EQ(result.x, -2);
    EXPECT_EQ(result.y, -4);
    EXPECT_EQ(result.z, -6);
}

TEST(CartesiaTest, PointMinusVector)
{
    Point point1 = Point(3, 2, 1);
    Vector vector1 = Vector(5, 6, 7);

    Point result = point1 - vector1;

    EXPECT_EQ(result.x, -2);
    EXPECT_EQ(result.y, -4);
    EXPECT_EQ(result.z, -6);
}

TEST(CartesiaTest, VectorMinusVector)
{
    Vector vector1 = Vector(3, 2, 1);
    Vector vector2 = Vector(5, 6, 7);

    Vector result = vector1 - vector2;

    EXPECT_EQ(result.x, -2);
    EXPECT_EQ(result.y, -4);
    EXPECT_EQ(result.z, -6);
}

TEST(CartesiaTest, NegatePoint)
{
    Point point1 = Point(1, -2, 3);

    Point result = -point1;

    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.z, -3);
}

TEST(CartesiaTest, NegateVector)
{
    Vector vector1 = Vector(1, -2, 3);

    Vector result = -vector1;

    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.z, -3);
}

TEST(CartesiaTest, MultiplyPoint)
{
    Point point1 = Point(1, -2, 3);

    Point result = point1 * 3.5;

    EXPECT_EQ(result.x, 3.5);
    EXPECT_EQ(result.y, -7);
    EXPECT_EQ(result.z, 10.5);
}

TEST(CartesiaTest, MultiplyVector)
{
    Vector vector1 = Vector(1, -2, 3);

    Vector result = vector1 * 3.5;

    EXPECT_EQ(result.x, 3.5);
    EXPECT_EQ(result.y, -7);
    EXPECT_EQ(result.z, 10.5);
}

TEST(CartesiaTest, DividePoint)
{
    Point point1 = Point(1, -2, 3);

    Point result = point1 / 2;

    EXPECT_EQ(result.x, 0.5);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.z, 1.5);
}

TEST(CartesiaTest, DivideVector)
{
    Vector vector1 = Vector(1, -2, 3);

    Vector result = vector1 / 2;

    EXPECT_EQ(result.x, 0.5);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.z, 1.5);
}

TEST_P(CartesiaVectorTestFixture, NormalizeVectors)
{
    auto [vector, expectedResult] = GetParam();

    Vector result = vector.normalize();

    EXPECT_FLOAT_EQ(result.x, expectedResult.x);
    EXPECT_FLOAT_EQ(result.y, expectedResult.y);
    EXPECT_FLOAT_EQ(result.z, expectedResult.z);
    EXPECT_FLOAT_EQ(result.magnitude, expectedResult.magnitude);
}

INSTANTIATE_TEST_CASE_P(
    CartesiaTest,
    CartesiaVectorTestFixture,
    ::testing::Values(
        std::make_tuple(Vector(4, 0, 0), Vector(1, 0, 0)),
        std::make_tuple(Vector(1, 2, 3), Vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)))));

TEST_P(CartesiaVectorDotProductTestFixture, DotProduct)
{
    auto [vector1, vector2, expectedResult] = GetParam();

    float result = dot(vector1, vector2);

    EXPECT_FLOAT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_CASE_P(
    CartesiaTest,
    CartesiaVectorDotProductTestFixture,
    ::testing::Values(
        std::make_tuple(Vector(1, 2, 3), Vector(2, 3, 4), 20)));

TEST_P(CartesiaVectorCrossProductTestFixture, CrossProduct)
{
    auto [vector1, vector2, expectedResult] = GetParam();

    Vector result = cross(vector1, vector2);

    EXPECT_FLOAT_EQ(result.x, expectedResult.x);
    EXPECT_FLOAT_EQ(result.y, expectedResult.y);
    EXPECT_FLOAT_EQ(result.z, expectedResult.z);
}

INSTANTIATE_TEST_CASE_P(
    CartesiaTest,
    CartesiaVectorCrossProductTestFixture,
    ::testing::Values(
        std::make_tuple(Vector(1, 2, 3), Vector(2, 3, 4), Vector(-1, 2, -1)),
        std::make_tuple(Vector(2, 3, 4), Vector(1, 2, 3), Vector(1, -2, 1))));
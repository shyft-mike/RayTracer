#ifndef FIXTURES_H
#define FIXTURES_H
#include <gtest/gtest.h>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/intersections.hpp>
#include <raytracer/core/materials/material.hpp>
#include <raytracer/core/lights/light.hpp>
#include <raytracer/core/shapes/plane.hpp>

class CartesiaPointTestFixture : public testing::TestWithParam<std::tuple<Point, float, float, float>>
{
};

class CartesiaVectorTestFixture : public testing::TestWithParam<std::tuple<Vector, Vector>>
{
};

class CartesiaVectorDotProductTestFixture : public testing::TestWithParam<std::tuple<Vector, Vector, float>>
{
};

class CartesiaVectorCrossProductTestFixture : public testing::TestWithParam<std::tuple<Vector, Vector, Vector>>
{
};

class MatricesEqualityTestFixture : public testing::TestWithParam<std::tuple<Matrix, Matrix, bool>>
{
};

class MatricesMathTestFixture : public testing::TestWithParam<std::tuple<Matrix, Matrix, Matrix>>
{
};

class MatricesTransposeTestFixture : public testing::TestWithParam<std::tuple<Matrix, Matrix>>
{
};

class TransformationsTestFixture : public testing::TestWithParam<std::tuple<Matrix, Matrix, Matrix>>
{
};

class SpheresTestFixture : public testing::TestWithParam<std::tuple<Point, Vector, Intersections>>
{
};

class IntersectionsTestFixture : public testing::TestWithParam<std::tuple<Intersections, std::optional<Intersection>>>
{
};

class IntersectionsNTestFixture : public testing::TestWithParam<std::tuple<int, float, float>>
{
};

class ShapeLightingTestFixture : public testing::TestWithParam<std::tuple<Vector, Vector, PointLight, Color, bool>>
{
public:
    IShape *shape = new Plane();
    Point position = Point(0, 0, 0);
};

#endif
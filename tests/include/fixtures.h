#ifndef FIXTURES_H
#define FIXTURES_H
#include <gtest/gtest.h>
#include "cartesia.h"
#include "matrices.h"

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

#endif
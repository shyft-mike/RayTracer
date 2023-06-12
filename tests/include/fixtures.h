#ifndef FIXTURES_H
#define FIXTURES_H
#include <gtest/gtest.h>
#include "cartesia.h"

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

#endif
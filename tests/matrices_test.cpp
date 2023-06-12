#include <gtest/gtest.h>
#include "fixtures.h"

TEST_P(MatricesEqualityTestFixture, Equality)
{
    auto [matrix1, matrix2, expectedResult] = GetParam();

    bool result = matrix1 == matrix2;

    EXPECT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_CASE_P(
    MatricesTest,
    MatricesEqualityTestFixture,
    ::testing::Values(
        std::make_tuple(Matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}), Matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}), true),
        std::make_tuple(Matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}), Matrix({{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}}), false)));

TEST_P(MatricesMathTestFixture, Multiply)
{
    auto [matrix1, matrix2, expectedResult] = GetParam();

    Matrix result = (matrix1 * matrix2);

    EXPECT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_CASE_P(
    MatricesTest,
    MatricesMathTestFixture,
    ::testing::Values(
        std::make_tuple(Matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}), Matrix({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}), Matrix({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}}))));
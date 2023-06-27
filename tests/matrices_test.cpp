#include <gtest/gtest.h>
#include "fixtures.h"
#include "helpers.h"

TEST_P(MatricesEqualityTestFixture, Equality)
{
    auto [matrix1, matrix2, expectedResult] = GetParam();

    bool result = matrix1 == matrix2;

    EXPECT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_SUITE_P(
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
        std::make_tuple(Matrix({{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}}), Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}), Matrix({{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}})),
        std::make_tuple(Matrix({{1}, {2}, {3}, {4}}), Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}), Matrix({{1}, {2}, {3}, {4}})),
        std::make_tuple(Matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}), Matrix({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}), Matrix({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}})),
        std::make_tuple(Matrix({{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}), Matrix({{1}, {2}, {3}, {1}}), Matrix({{18}, {24}, {33}, {1}}))));

TEST_P(MatricesTransposeTestFixture, Transpose)
{
    auto [matrix, expectedResult] = GetParam();

    Matrix result = MatrixHelper(matrix).transpose();

    EXPECT_EQ(result, expectedResult);
}

INSTANTIATE_TEST_CASE_P(
    MatricesTest,
    MatricesTransposeTestFixture,
    ::testing::Values(
        std::make_tuple(Matrix({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}}), Matrix({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}})),
        std::make_tuple(Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}), Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}))));

TEST(MatricesTest, Determinant)
{
    Matrix matrix = {{1, 5}, {-3, 2}};

    float result = determinant(matrix);

    EXPECT_FLOAT_EQ(result, 17);
}

TEST(MatricesTest, SubMatrix)
{
    Matrix matrix = {{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}};

    Matrix result = submatrix(matrix, 0, 2);

    EXPECT_EQ(result, Matrix({{-3, 2}, {0, 6}}));
}

TEST(MatricesTest, Minor)
{
    Matrix matrix = {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};

    float result = minor(matrix, 1, 0);

    EXPECT_FLOAT_EQ(result, 25);
}

TEST(MatricesTest, Cofactor)
{
    Matrix matrix = {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};

    float resultMinor1 = minor(matrix, 0, 0);
    float resultCofactor1 = cofactor(matrix, 0, 0);

    float resultMinor2 = minor(matrix, 1, 0);
    float resultCofactor2 = cofactor(matrix, 1, 0);

    EXPECT_FLOAT_EQ(resultMinor1, -12);
    EXPECT_FLOAT_EQ(resultCofactor1, -12);
    EXPECT_FLOAT_EQ(resultMinor2, 25);
    EXPECT_FLOAT_EQ(resultCofactor2, -25);
}

TEST(MatricesTest, Determinant3x3)
{
    Matrix matrix = {{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}};

    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 0), 56);
    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 1), 12);
    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 2), -46);
    EXPECT_FLOAT_EQ(determinant(matrix), -196);
}

TEST(MatricesTest, Determinant4x4)
{
    Matrix matrix = {{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}};

    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 0), 690);
    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 1), 447);
    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 2), 210);
    EXPECT_FLOAT_EQ(cofactor(matrix, 0, 3), 51);
    EXPECT_FLOAT_EQ(determinant(matrix), -4071);
}

TEST(MatricesTest, Invertable)
{
    Matrix matrix = {{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}};

    EXPECT_FLOAT_EQ(determinant(matrix), -2120);
}

TEST(MatricesTest, NonInvertable)
{
    Matrix matrix = {{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}};

    EXPECT_FLOAT_EQ(determinant(matrix), 0);
}

TEST(MatricesTest, Invert)
{
    Matrix matrix = {{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}};

    Matrix result = inverse(matrix);

    Matrix expectedResult = {{0.21805, 0.45113, 0.24060, -0.04511}, {-0.80827, -1.45677, -0.44361, 0.52068}, {-0.07895, -0.22368, -0.05263, 0.19737}, {-0.52256, -0.81391, -0.30075, 0.30639}};

    EXPECT_FLOAT_EQ(determinant(matrix), 532);
    EXPECT_FLOAT_EQ(cofactor(matrix, 2, 3), -160);
    EXPECT_FLOAT_EQ(cofactor(matrix, 3, 2), 105);

    checkMatrix(result, expectedResult);
}

TEST(MatricesTest, InvertToOriginal)
{
    Matrix matrix1 = {{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}};
    Matrix matrix2 = {{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}};

    Matrix result = (matrix1 * matrix2);
    Matrix inv = inverse(matrix2);
    result = result * inv;

    checkMatrix(result, matrix1);
}
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <raytracer.tests.hpp>
#include <raytracer/core/shapes/transformable.hpp>

TEST(TransformableTest, Default)
{
    ASSERT_EQ(get_test_transformable()->transform, MatrixHelper::identity().matrix);
}

TEST(TransformableTest, Scale)
{
    Matrix result = get_test_transformable()->scale(2, 3, 4)->transform;

    Matrix expected_result = {
        {2, 0, 0, 0},
        {0, 3, 0, 0},
        {0, 0, 4, 0},
        {0, 0, 0, 1}};

    ASSERT_EQ(result, expected_result);
}
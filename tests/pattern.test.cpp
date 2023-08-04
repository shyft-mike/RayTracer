#include <gtest/gtest.h>
#include <raytracer/core/patterns/pattern.hpp>

namespace PatternTest
{
    const StripePattern pattern = StripePattern(WHITE, BLACK);

    TEST(PatternTest, CreateStripePattern)
    {
        StripePattern result = StripePattern(WHITE, BLACK);

        ASSERT_EQ(result.a, WHITE);
        ASSERT_EQ(result.b, BLACK);
    }

    TEST(PatternTest, StripePatternX)
    {
        ASSERT_EQ(pattern.at(0, 0, 0), WHITE);
        ASSERT_EQ(pattern.at(0.9, 0, 0), WHITE);
        ASSERT_EQ(pattern.at(1, 0, 0), BLACK);
        ASSERT_EQ(pattern.at(-0.1, 0, 0), BLACK);
        ASSERT_EQ(pattern.at(-1, 0, 0), BLACK);
        ASSERT_EQ(pattern.at(-1.1, 0, 0), WHITE);
    }

    TEST(PatternTest, StripePatternY)
    {
        ASSERT_EQ(pattern.at(0, 0, 0), WHITE);
        ASSERT_EQ(pattern.at(0, 1, 0), WHITE);
        ASSERT_EQ(pattern.at(0, 2, 0), WHITE);
    }

    TEST(PatternTest, StripePatternZ)
    {
        ASSERT_EQ(pattern.at(0, 0, 0), WHITE);
        ASSERT_EQ(pattern.at(0, 0, 1), WHITE);
        ASSERT_EQ(pattern.at(0, 0, 2), WHITE);
    }

}
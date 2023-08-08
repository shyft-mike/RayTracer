#include <gtest/gtest.h>
#include <raytracer.tests.hpp>
#include <raytracer/core/patterns/pattern.hpp>
#include <raytracer/core/shapes/sphere.hpp>

TEST(PatternTest, PatternWithObjectTransform)
{
    Sphere s = Sphere("test");
    s.scale(2, 2, 2);
    s.material.pattern = new TestPattern();

    Color result = s.color_at(2, 3, 4);

    check_color(result, Color(1, 1.5, 2));
}

TEST(PatternTest, PatternWithPatternTransform)
{
    Sphere s = Sphere("test");
    s.material.pattern = new TestPattern();
    s.material.pattern->scale(2, 2, 2);

    Color result = s.color_at(2, 3, 4);

    check_color(result, Color(1, 1.5, 2));
}

TEST(PatternTest, PatternWithObjectAndPatternTransform)
{
    Sphere s = Sphere("test");
    s.scale(2, 2, 2);
    s.material.pattern = new TestPattern();
    s.material.pattern->translate(0.5, 1, 1.5);

    Color result = s.color_at(2.5, 3, 3.5);

    check_color(result, Color(0.75, 0.5, 0.25));
}

TEST(PatternTest, CreateStripePattern)
{
    StripePattern result = StripePattern(WHITE, BLACK);

    ASSERT_EQ(result.a, WHITE);
    ASSERT_EQ(result.b, BLACK);
}

TEST(PatternTest, StripePatternX)
{
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 0, 0), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0.9, 0, 0), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(1, 0, 0), BLACK);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(-0.1, 0, 0), BLACK);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(-1, 0, 0), BLACK);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(-1.1, 0, 0), WHITE);
}

TEST(PatternTest, StripePatternY)
{
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 0, 0), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 1, 0), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 2, 0), WHITE);
}

TEST(PatternTest, StripePatternZ)
{
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 0, 0), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 0, 1), WHITE);
    ASSERT_EQ(TEST_STRIPE_PATTERN.at(0, 0, 2), WHITE);
}

TEST(PatternTest, StripeWithObjectTransform)
{
    Sphere s = Sphere("test");
    s.scale(2, 2, 2);
    s.material.pattern = new StripePattern(WHITE, BLACK);

    Color result = s.color_at(1.5, 0, 0);

    check_color(result, WHITE);
}

TEST(PatternTest, StripeWithPatternTransform)
{
    Sphere s = Sphere("test");
    s.material.pattern = new StripePattern(WHITE, BLACK);
    s.material.pattern->scale(2, 2, 2);

    Color result = s.color_at(1.5, 0, 0);

    check_color(result, WHITE);
}

TEST(PatternTest, StripeWithObjectAndPatternTransform)
{
    Sphere s = Sphere("test");
    s.scale(2, 2, 2);
    s.material.pattern = new StripePattern(WHITE, BLACK);
    s.material.pattern->translate(0.5, 0, 0);

    Color result = s.color_at(2.5, 0, 0);

    check_color(result, WHITE);
}

TEST(PatternTest, GradientLinearlyInterpolates)
{
    GradientPattern pattern = GradientPattern(WHITE, BLACK);

    Color result1 = pattern.at(0.25, 0, 0);
    Color result2 = pattern.at(0.5, 0, 0);
    Color result3 = pattern.at(0.75, 0, 0);

    check_color(result1, Color(0.75, 0.75, 0.75));
    check_color(result2, Color(0.5, 0.5, 0.5));
    check_color(result3, Color(0.25, 0.25, 0.25));
}

TEST(PatternTest, RingExtendsXandZ)
{
    RingPattern pattern = RingPattern(WHITE, BLACK);

    check_color(pattern.at(0, 0, 0), WHITE);
    check_color(pattern.at(1, 0, 0), BLACK);
    check_color(pattern.at(0, 0, 1), BLACK);
    check_color(pattern.at(0.708, 0, 0.708), BLACK);
    check_color(pattern.at(1.708, 0, 1.708), WHITE);
}

TEST(PatternTest, CheckersRepeatX)
{
    CheckerPattern pattern = CheckerPattern(WHITE, BLACK);

    check_color(pattern.at(0, 0, 0), WHITE);
    check_color(pattern.at(0.99, 0, 0), WHITE);
    check_color(pattern.at(1.01, 0, 0), BLACK);
}

TEST(PatternTest, CheckersRepeatY)
{
    CheckerPattern pattern = CheckerPattern(WHITE, BLACK);

    check_color(pattern.at(0, 0, 0), WHITE);
    check_color(pattern.at(0, 0.99, 0), WHITE);
    check_color(pattern.at(0, 1.01, 0), BLACK);
}

TEST(PatternTest, CheckersRepeatZ)
{
    CheckerPattern pattern = CheckerPattern(WHITE, BLACK);

    check_color(pattern.at(0, 0, 0), WHITE);
    check_color(pattern.at(0, 0, 0.99), WHITE);
    check_color(pattern.at(0, 0, 1.01), BLACK);
}
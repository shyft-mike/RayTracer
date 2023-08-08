#ifndef PATTERN_MODELS_H
#define PATTERN_MODELS_H

#include <algorithm>
#include <math.h>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/shapes/transformable.hpp>

enum PatternType
{
    NONE,
    SOLID,
    STRIPE,
    GRADIENT
};

struct IPattern : public ITransformable
{
    std::vector<Color> colors;

    IPattern(std::vector<Color> colors) : ITransformable(), colors(colors)
    {
    }
    virtual ~IPattern() = default;

    virtual Color at(float x, float y, float z) const
    {
        return WHITE;
    }
};

struct SolidPattern : IPattern
{
    SolidPattern(Color color) : IPattern({color})
    {
    }

    Color at(float x, float y, float z) const override
    {
        return this->colors.at(0);
    }
};

struct StripePattern : IPattern
{
    Color a;
    Color b;

    StripePattern(Color a, Color b) : IPattern({a, b})
    {
        this->a = this->colors.at(0);
        this->b = this->colors.at(1);
    }

    Color at(float x, float y, float z) const override
    {
        if (static_cast<int>(std::floor(x)) % 2 == 0)
        {
            return this->a;
        }

        return this->b;
    }
};

struct GradientPattern : IPattern
{
    Color a;
    Color b;

    GradientPattern(Color a, Color b) : IPattern({a, b})
    {
        this->a = this->colors.at(0);
        this->b = this->colors.at(1);
    }

    Color at(float x, float y, float z) const override
    {
        Color color_diff = this->b - this->a;
        float fraction = x - std::floor(x);

        return this->a + color_diff * fraction;
    }
};

struct RingPattern : IPattern
{
    Color a;
    Color b;

    RingPattern(Color a, Color b) : IPattern({a, b})
    {
        this->a = this->colors.at(0);
        this->b = this->colors.at(1);
    }

    Color at(float x, float y, float z) const override
    {
        float distance = std::sqrt((x * x) + (z * z));
        int distance_rounded = std::floor(distance);

        if (distance_rounded % 2 == 0)
        {
            return this->a;
        }

        return this->b;
    }
};

struct CheckerPattern : IPattern
{
    Color a;
    Color b;

    CheckerPattern(Color a, Color b) : IPattern({a, b})
    {
        this->a = this->colors.at(0);
        this->b = this->colors.at(1);
    }

    Color at(float x, float y, float z) const override
    {
        int sum = std::floor(x) + std::floor(y) + std::floor(z);

        if (sum % 2 == 0)
        {
            return this->a;
        }

        return this->b;
    }
};

struct BlendedPattern : IPattern
{
    std::unique_ptr<IPattern> a;
    std::unique_ptr<IPattern> b;

    BlendedPattern(IPattern *a, IPattern *b) : IPattern({}), a(a), b(b)
    {
    }

    Color at(float x, float y, float z) const override
    {
        Point pattern_a_point = MatrixHelper(inverse(this->a->transform) * Point(x, y, z)).to_point();
        Point pattern_b_point = MatrixHelper(inverse(this->b->transform) * Point(x, y, z)).to_point();

        return this->a->at(pattern_a_point.x, pattern_a_point.y, pattern_a_point.z) + this->b->at(pattern_b_point.x, pattern_b_point.y, pattern_b_point.z);
    }
};

struct RadialGradientPattern : IPattern
{
    Color a;
    Color b;

    RadialGradientPattern(Color a, Color b) : IPattern({a, b})
    {
        this->a = this->colors.at(0);
        this->b = this->colors.at(1);
    }

    Color at(float x, float y, float z) const override
    {
        Color color_diff = this->b - this->a;
        float distance = std::sqrt((x * x) + (z * z));
        float fraction = distance - std::floor(distance);

        return this->a + color_diff * fraction;
    }
};

#endif
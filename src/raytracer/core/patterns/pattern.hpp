#ifndef PATTERN_H
#define PATTERN_H

#include <algorithm>
#include <math.h>
#include <raytracer/core/colors.hpp>

struct IPattern
{
    Color color;
    std::vector<Color> colors;

    IPattern(std::vector<Color> colors) : colors(colors)
    {
        this->color = this->colors.at(0);
    }
    virtual ~IPattern() = default;

    virtual Color at(float x, float y, float z) const
    {
        return this->color;
    }
};

struct SolidPattern : public IPattern
{
    SolidPattern(Color color) : IPattern({color})
    {
    }
};

struct StripePattern : public IPattern
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

inline bool operator==(const IPattern &lhs, const IPattern &rhs)
{
    if (lhs.colors.size() != rhs.colors.size())
    {
        return false;
    }

    for (int i = 0; i < lhs.colors.size(); i++)
    {
        Color lcolor = lhs.colors.at(i);
        Color rcolor = rhs.colors.at(i);

        if (lcolor == rcolor)
        {
            return true;
        }
    }

    return false;
}

inline bool operator==(const SolidPattern &lhs, const SolidPattern &rhs)
{
    if (lhs.colors.size() != rhs.colors.size())
    {
        return false;
    }

    for (int i = 0; i < lhs.colors.size(); i++)
    {
        Color lcolor = lhs.colors.at(i);
        Color rcolor = rhs.colors.at(i);

        if (lcolor == rcolor)
        {
            return true;
        }
    }

    return false;
}

#endif
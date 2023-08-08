#ifndef PATTERN_H
#define PATTERN_H

#include <algorithm>
#include <math.h>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/patterns/pattern.models.hpp>

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
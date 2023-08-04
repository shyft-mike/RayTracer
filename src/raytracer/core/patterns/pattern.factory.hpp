#ifndef PATTERN_FACTORY_H
#define PATTERN_FACTORY_H

#include <raytracer/core/colors.hpp>
#include <raytracer/core/patterns/pattern.hpp>

namespace PatternFactory
{
    struct PatternFactoryResult
    {
        IPattern *result;
    };

    struct PatternFactoryRequest
    {
        int type{-1};
    };

    struct StripePatternFactoryRequest : public PatternFactoryRequest
    {
        int type = 1;
        Color a;
        Color b;

        StripePatternFactoryRequest(Color a, Color b) : a(a), b(b)
        {
        }
    };

    inline PatternFactoryResult generate()
    {
        return PatternFactoryResult()
    }

}
#endif
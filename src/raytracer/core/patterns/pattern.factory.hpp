#ifndef PATTERN_FACTORY_H
#define PATTERN_FACTORY_H

#include <memory>
#include <raytracer/core/colors.hpp>
#include <raytracer/core/patterns/pattern.models.hpp>

namespace PatternFactory
{
    struct PatternFactoryResult
    {
        std::unique_ptr<IPattern> result;
    };

    struct PatternFactoryRequest
    {
        PatternType type = PatternType.NONE;
    };

    struct StripePatternFactoryRequest : public PatternFactoryRequest
    {
        Color a;
        Color b;

        StripePatternFactoryRequest(Color a, Color b) : a(a), b(b)
        {
            this->type = PatternType.STRIPE;
        }
    };

    struct StripePatternFactoryRequest : public PatternFactoryRequest
    {
        Color a;
        Color b;

        StripePatternFactoryRequest(Color a, Color b) : a(a), b(b)
        {
            this->type = PatternType.STRIPE;
        }
    };

    inline PatternFactoryResult generate()
    {
        return PatternFactoryResult();
    }

}

#endif
#ifndef HELPERS_H
#define HELPERS_H

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer/core/colors.hpp>

inline std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

inline void check_matrix(const Matrix &result, const Matrix &expected)
{
    short rowSize = result.size();
    short colSize = result[0].size();

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            EXPECT_NEAR(result[i][j], expected[i][j], 0.0001);
        }
    }
}

inline void check_color(const Color &result, const Color &expected)
{
    EXPECT_NEAR(result.blue, expected.blue, 0.0001);
    EXPECT_NEAR(result.green, expected.green, 0.0001);
    EXPECT_NEAR(result.red, expected.red, 0.0001);
}

#endif
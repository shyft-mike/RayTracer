#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <raytracer/core/colors.hpp>
#include <raytracer/common/config.hpp>

class Canvas
{
public:
    short width;
    short height;
    std::vector<Color> pixels;

    Canvas(short width, short height) : width(width), height(height)
    {
        this->pixels.assign((width * height), Color(0, 0, 0));
    }

    Color get_pixel(int x, int y) const
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            return Color(0, 0, 0);
        }

        int position = this->get_position_index(x, y);

        return this->pixels.at(position);
    }

    void set_pixel(int x, int y, const Color &pixel)
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            if (config::is_debug)
            {
                std::cerr << "COULDN'T SET PIXEL AT (" << x << "," << y << ")" << std::endl;
            }

            return;
        }

        int position = this->get_position_index(x, y);

        this->pixels.at(position) = pixel;

        if (config::is_debug)
        {
            std::cerr << "SET PIXEL AT (" << x << "," << y << ") TO " << pixel << std::endl;
        }
    }

    std::string to_ppm() const
    {
        std::string ppm = "";
        ppm += "P3\n";

        ppm += std::to_string(this->width);
        ppm += " ";
        ppm += std::to_string(this->height);
        ppm += "\n";

        ppm += "255";
        ppm += "\n";

        ppm += this->generate_ppm_pixels();

        return ppm;
    }

    int get_position_index(int x, int y) const
    {
        return (y * this->width) + x;
    }

    std::array<int, 2> index_to_xy(int index) const
    {
        return {index % this->width, index / this->width};
    }

private:
    std::string generate_ppm_pixels() const
    {
        std::string result = "";

        for (int y = 0; y < this->height; y++)
        {
            std::string line = "";

            for (int x = 0; x < this->width; x++)
            {
                Color pixel = this->get_pixel(x, y);
                this->write_result(result, line, pixel.red);
                this->write_result(result, line, pixel.green);
                this->write_result(result, line, pixel.blue);
            }

            // Remove the final whitespace character
            if (line.size() > 0)
            {
                line.pop_back();
            }

            result += line;
            result += "\n";
        }

        return result;
    }

    void write_result(std::string &result, std::string &line, float colorValue) const
    {
        short maxLineLength = 70;

        std::string colorPPM = this->color_to_ppm(colorValue);
        short newLineLength = line.length() + colorPPM.length();

        if (newLineLength < 70)
        {
            line += colorPPM;
            line += " ";
        }
        else if (newLineLength == 70)
        {
            line += colorPPM;
            line += "\n";
            result += line;
            line = "";
        }
        else
        {
            line.pop_back();
            line += "\n";
            result += line;
            line = "";

            line += colorPPM;
            line += " ";
        }
    }

    std::string color_to_ppm(float colorValue) const
    {
        int adjustedColorValue = std::ceil(colorValue * 255);
        std::string result = std::to_string(std::clamp(adjustedColorValue, 0, 255));

        return result;
    }
};

#endif
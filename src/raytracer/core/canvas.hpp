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

    Color getPixel(short x, short y)
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            return Color(0, 0, 0);
        }

        int position = this->getPositionIndex(x, y);

        return this->pixels.at(position);
    }

    void setPixel(short x, short y, const Color &pixel)
    {
        if (x >= this->width || x < 0 || y >= this->height || y < 0)
        {
            if (config::is_debug)
            {
                std::cerr << "COULDN'T SET PIXEL AT (" << x << "," << y << ")" << std::endl;
            }

            return;
        }

        int position = this->getPositionIndex(x, y);

        this->pixels.at(position) = pixel;

        if (config::is_debug)
        {
            std::cerr << "SET PIXEL AT (" << x << "," << y << ") TO " << pixel << std::endl;
        }
    }

    std::string toPPM()
    {
        std::string ppm = "";
        ppm += "P3\n";

        ppm += std::to_string(this->width);
        ppm += " ";
        ppm += std::to_string(this->height);
        ppm += "\n";

        ppm += "255";
        ppm += "\n";

        ppm += this->generatePPMPixels();

        return ppm;
    }

private:
    std::string generatePPMPixels()
    {
        std::string result = "";

        for (int y = 0; y < this->height; y++)
        {
            std::string line = "";

            for (int x = 0; x < this->width; x++)
            {
                Color pixel = this->getPixel(x, y);
                this->writeResult(result, line, pixel.red);
                this->writeResult(result, line, pixel.green);
                this->writeResult(result, line, pixel.blue);
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

    void writeResult(std::string &result, std::string &line, float colorValue)
    {
        short maxLineLength = 70;

        std::string colorPPM = this->colorToPPM(colorValue);
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

    std::string colorToPPM(float colorValue)
    {
        int adjustedColorValue = std::ceil(colorValue * 255);
        std::string result = std::to_string(std::clamp(adjustedColorValue, 0, 255));

        return result;
    }

    int getPositionIndex(short x, short y)
    {
        return (y * this->width) + x;
    }
};

#endif
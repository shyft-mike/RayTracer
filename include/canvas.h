#ifndef CANVAS_H
#define CANVAS_H
#include <vector>
#include <cmath>
#include <algorithm>
#include "colors.h"

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
            return;
        }

        int position = this->getPositionIndex(x, y);

        this->pixels.at(position) = pixel;
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
        short maxLineLength = 70;

        for (int y = 0; y < this->height; y++)
        {
            std::string line = "";

            for (int x = 0; x < this->width; x++)
            {
                Color pixel = this->getPixel(x, y);
                line += this->colorToPPM(pixel.red);
                line += " ";
                line += this->colorToPPM(pixel.green);
                line += " ";
                line += this->colorToPPM(pixel.blue);

                if (x < this->width - 1)
                {
                    line += " ";
                }
            }

            result += line;
            result += "\n";
        }

        return result;
    }

    std::string colorToPPM(float colorValue)
    {
        int adjustedColorValue = std::ceil(colorValue * 255);
        std::string result = std::to_string(std::clamp(adjustedColorValue, 0, 255));

        return result;
    }

    int getPositionIndex(short x, short y)
    {
        return (y * this->height) + x;
    }
};

#endif
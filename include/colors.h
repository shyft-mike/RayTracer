#ifndef COLORS_H
#define COLORS_H

struct Color
{
    float red;
    float green;
    float blue;

    Color(float red, float green, float blue) : red(red), green(green), blue(blue)
    {
    }
};

inline Color operator+(const Color &color1, const Color &color2)
{
    return Color(
        color1.red + color2.red,
        color1.green + color2.green,
        color1.blue + color2.blue);
}

inline Color operator-(const Color &color1, const Color &color2)
{
    return Color(
        color1.red - color2.red,
        color1.green - color2.green,
        color1.blue - color2.blue);
}

inline Color operator*(const Color &color1, const Color &color2)
{
    return Color(
        color1.red * color2.red,
        color1.green * color2.green,
        color1.blue * color2.blue);
}

inline Color operator*(const Color &color, const float &value)
{
    return Color(
        color.red * value,
        color.green * value,
        color.blue * value);
}

inline std::ostream &operator<<(std::ostream &os, const Color &c)
{
    return (os << "Color(" << c.red << "," << c.green << "," << c.blue << ")");
}

#endif
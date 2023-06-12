#ifndef CARTESIA_H
#define CARTESIA_H
#include <iostream>
#include <cmath>

struct Point
{
    float x;
    float y;
    float z;

    Point(float x, float y, float z) : x(x), y(y), z(z)
    {
    }
};

struct Vector
{
    float x;
    float y;
    float z;
    float magnitude;

    Vector(float x, float y, float z) : x(x), y(y), z(z)
    {
        this->magnitude = sqrt((x * x) + (y * y) + (z * z));
    }

    Vector normalize()
    {
        return Vector(
            this->x / this->magnitude,
            this->y / this->magnitude,
            this->z / this->magnitude);
    }
};

inline Point operator-(const Point &point)
{
    return Point(-point.x, -point.y, -point.z);
}

inline Point operator-(const Point &point, const Vector &vector)
{
    return Point(
        point.x - vector.x,
        point.y - vector.y,
        point.z - vector.z);
}

inline Vector operator-(const Vector &vector)
{
    return Vector(-vector.x, -vector.y, -vector.z);
}

inline Vector operator-(const Point &point1, const Point &point2)
{
    return Vector(
        point1.x - point2.x,
        point1.y - point2.y,
        point1.z - point2.z);
}

inline Vector operator-(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.x - vector2.x,
        vector1.y - vector2.y,
        vector1.z - vector2.z);
}

inline Point operator+(const Point &point, const Vector &vector)
{
    return Point(
        point.x + vector.x,
        point.y + vector.y,
        point.z + vector.z);
}

inline Vector operator+(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.x + vector2.x,
        vector1.y + vector2.y,
        vector1.z + vector2.z);
}

inline Point operator*(const Point &point, const float &value)
{
    return Point(
        point.x * value,
        point.y * value,
        point.z * value);
}

inline Vector operator*(const Vector &vector, const float &value)
{
    return Vector(
        vector.x * value,
        vector.y * value,
        vector.z * value);
}

inline Point operator/(const Point &point, const float &value)
{
    return Point(
        point.x / value,
        point.y / value,
        point.z / value);
}

inline Vector operator/(const Vector &vector, const float &value)
{
    return Vector(
        vector.x / value,
        vector.y / value,
        vector.z / value);
}

inline float dot(const Vector &vector1, const Vector &vector2)
{
    return vector1.x * vector2.x +
           vector1.y * vector2.y +
           vector1.z * vector2.z;
}

inline Vector cross(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.y * vector2.z - vector1.z * vector2.y,
        vector1.z * vector2.x - vector1.x * vector2.z,
        vector1.x * vector2.y - vector1.y * vector2.x);
}

inline std::ostream &operator<<(std::ostream &os, const Point &p)
{
    return (os << "(" << p.x << "," << p.y << "," << p.z << ")");
}

#endif
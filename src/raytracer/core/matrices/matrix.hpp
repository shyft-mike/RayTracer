#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <ostream>
#include <vector>

typedef std::vector<std::vector<float>> Matrix;

struct Point : Matrix
{
    float x;
    float y;
    float z;

    Point(float x, float y, float z) : x(x), y(y), z(z)
    {
        this->assign(4, {{1}});
        this->at(0).at(0) = x;
        this->at(1).at(0) = y;
        this->at(2).at(0) = z;
    }
};

struct Vector : Matrix
{
    float x;
    float y;
    float z;
    float magnitude;

    Vector(float x, float y, float z) : x(x), y(y), z(z)
    {
        this->assign(4, {{0}});
        this->at(0).at(0) = x;
        this->at(1).at(0) = y;
        this->at(2).at(0) = z;

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

Matrix operator*(const Matrix &m1, const Matrix &m2);
Matrix transpose(const Matrix &matrix);
Matrix submatrix(const Matrix &matrix, short rowToRemove, short colToRemove);
Vector reflect(const Vector &vector, const Vector &normal);
float determinant(const Matrix &matrix);
float minor(const Matrix &matrix, short row, short col);
float cofactor(const Matrix &matrix, short row, short col);
Matrix inverse(const Matrix &matrix);
Point operator-(const Point &point);
Point operator-(const Point &point, const Vector &vector);
Vector operator-(const Vector &vector);
Vector operator-(const Point &point1, const Point &point2);
Vector operator-(const Vector &vector1, const Vector &vector2);
Point operator+(const Point &point, const Vector &vector);
Vector operator+(const Vector &vector1, const Vector &vector2);
Point operator*(const Point &point, const float &value);
Vector operator*(const Vector &vector, const float &value);
Point operator/(const Point &point, const float &value);
Vector operator/(const Vector &vector, const float &value);
float dot(const Vector &vector1, const Vector &vector2);
Vector cross(const Vector &vector1, const Vector &vector2);

std::ostream &operator<<(std::ostream &os, const Point &p);

#endif
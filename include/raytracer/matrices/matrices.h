#ifndef MATRICES_H
#define MATRICES_H

#include <math.h>
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

Matrix transpose(const Matrix matrix);

Matrix submatrix(const Matrix matrix, short rowToRemove, short colToRemove);

float determinant(const Matrix matrix);

float minor(const Matrix matrix, short row, short col);

float cofactor(const Matrix matrix, short row, short col);

Matrix inverse(const Matrix matrix);

#endif
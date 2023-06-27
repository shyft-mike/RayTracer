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

struct MatrixHelper
{
    Matrix matrix;

    MatrixHelper(const Matrix matrix) : matrix(matrix)
    {
    }

    static MatrixHelper identity();

    Point to_point();

    MatrixHelper transpose();
    MatrixHelper submatrix(short rowToRemove, short colToRemove);
    MatrixHelper invert();

    MatrixHelper translate(float x, float y, float z);
    MatrixHelper scale(float x, float y, float z);
    MatrixHelper rotate_x(float radians);
    MatrixHelper rotate_y(float radians);
    MatrixHelper rotate_z(float radians);
    MatrixHelper shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

    operator Matrix() { return this->matrix; }
};

Matrix operator*(const Matrix &m1, const Matrix &m2);

Matrix transpose(const Matrix matrix);

Matrix submatrix(const Matrix matrix, short rowToRemove, short colToRemove);

float determinant(const Matrix matrix);

float minor(const Matrix matrix, short row, short col);

float cofactor(const Matrix matrix, short row, short col);

Matrix inverse(const Matrix matrix);

#endif
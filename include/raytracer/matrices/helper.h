#ifndef MATRICES_HELPER_H
#define MATRICES_HELPER_H

#include "raytracer/matrices/matrices.h"

struct MatrixHelper
{
    Matrix matrix;

    MatrixHelper(const Matrix matrix) : matrix(matrix)
    {
    }

    static MatrixHelper identity();

    Point to_point();
    Vector to_vector();

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

#endif
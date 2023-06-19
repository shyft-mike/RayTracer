#ifndef MATRICES_H
#define MATRICES_H

#include <vector>

typedef std::vector<std::vector<float>> Matrix;

Matrix operator*(const Matrix &m1, const Matrix &m2);

Matrix transpose(const Matrix matrix);

Matrix submatrix(const Matrix matrix, short rowToRemove, short colToRemove);

float determinant(const Matrix matrix);

float minor(const Matrix matrix, short row, short col);

float cofactor(const Matrix matrix, short row, short col);

Matrix inverse(const Matrix matrix);

#endif
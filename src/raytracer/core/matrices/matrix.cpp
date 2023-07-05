#include <ostream>
#include <stdexcept>
#include <raytracer/core/matrices/matrix.hpp>

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix main, other;

    if (m1[0].size() >= m2[0].size())
    {
        main = m1;
        other = m2;
    }
    else
    {
        main = m2;
        other = m1;
    }

    short mainRowSize = main.size();
    short mainColSize = main[0].size();
    short otherRowSize = other.size();
    short otherColSize = other[0].size();

    if (mainRowSize == otherRowSize)
    {
        if (mainColSize == otherColSize || otherColSize == 1)
        {
            Matrix result = Matrix(mainRowSize, std::vector<float>(otherColSize));

            for (int row = 0; row < mainRowSize; row++)
            {
                for (int col = 0; col < otherColSize; col++)
                {
                    float product = 0;

                    for (int i = 0; i < mainRowSize; i++)
                    {
                        product += main[row][i] * other[i][col];
                    }

                    result[row][col] = product;
                }
            }

            return result;
        }
        else
        {
            throw std::invalid_argument("Mismatched column sizes in matrix operation");
        }
    }
    else
    {
        throw std::invalid_argument("Mismatched row sizes in matrix operation");
    }
}

Matrix transpose(const Matrix &matrix)
{
    Matrix result = Matrix(matrix);

    short rowSize = matrix.size();
    short colSize = matrix[0].size();

    for (int row = 0; row < rowSize; row++)
    {
        for (int col = 0; col < colSize; col++)
        {
            result[col][row] = matrix[row][col];
        }
    }

    return result;
}

Matrix submatrix(const Matrix &matrix, short rowToRemove, short colToRemove)
{
    short rowSize = matrix.size();
    short colSize = matrix[0].size();

    if (rowToRemove > rowSize - 1)
    {
        throw std::invalid_argument("Invalid row index");
    }

    if (colToRemove > colSize - 1)
    {
        throw std::invalid_argument("Invalid column index");
    }

    Matrix result = Matrix(rowSize - 1, std::vector<float>(colSize - 1));

    int i = 0;

    for (int row = 0; row < rowSize; row++)
    {
        int j = 0;

        if (row == rowToRemove)
        {
            continue;
        }

        for (int col = 0; col < colSize; col++)
        {
            if (col == colToRemove)
            {
                continue;
            }

            result[i][j] = matrix[row][col];

            j++;
        }

        i++;
    }

    return result;
}

Vector reflect(const Vector &vector, const Vector &normal)
{
    return vector - normal * 2 * dot(vector, normal);
}

/// @brief Determine if there is a solution for the system.
/// @param matrix The matrix to get the determinant for.
/// @return The value of the determinant.
float determinant(const Matrix &matrix)
{
    float result = 0;
    short size = matrix.size();

    if (size == 2)
    {
        result = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    else
    {
        for (int col = 0; col < size; col++)
        {
            result += matrix[0][col] * cofactor(matrix, 0, col);
        }
    }

    return result;
}

float minor(const Matrix &matrix, short row, short col)
{
    Matrix subMatrix = submatrix(matrix, row, col);

    return determinant(subMatrix);
}

float cofactor(const Matrix &matrix, short row, short col)
{
    float matrixMinor = minor(matrix, row, col);

    // if row + column is odd, then the minor gets negated
    if ((row + col) % 2 == 1)
    {
        return -(matrixMinor);
    }

    return matrixMinor;
}

Matrix inverse(const Matrix &matrix)
{
    if (determinant(matrix) == 0)
    {
        throw std::invalid_argument("Matrix is not invertible");
    }

    Matrix result = Matrix(matrix);
    short size = matrix.size();

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            result[col][row] = cofactor(matrix, row, col) / determinant(matrix);
        }
    }

    return result;
}

Point operator-(const Point &point)
{
    return Point(-point.x, -point.y, -point.z);
}

Point operator-(const Point &point, const Vector &vector)
{
    return Point(
        point.x - vector.x,
        point.y - vector.y,
        point.z - vector.z);
}

Vector operator-(const Vector &vector)
{
    return Vector(-vector.x, -vector.y, -vector.z);
}

Vector operator-(const Point &point1, const Point &point2)
{
    return Vector(
        point1.x - point2.x,
        point1.y - point2.y,
        point1.z - point2.z);
}

Vector operator-(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.x - vector2.x,
        vector1.y - vector2.y,
        vector1.z - vector2.z);
}

Point operator+(const Point &point, const Vector &vector)
{
    return Point(
        point.x + vector.x,
        point.y + vector.y,
        point.z + vector.z);
}

Vector operator+(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.x + vector2.x,
        vector1.y + vector2.y,
        vector1.z + vector2.z);
}

Point operator*(const Point &point, const float &value)
{
    return Point(
        point.x * value,
        point.y * value,
        point.z * value);
}

Vector operator*(const Vector &vector, const float &value)
{
    return Vector(
        vector.x * value,
        vector.y * value,
        vector.z * value);
}

Point operator/(const Point &point, const float &value)
{
    return Point(
        point.x / value,
        point.y / value,
        point.z / value);
}

Vector operator/(const Vector &vector, const float &value)
{
    return Vector(
        vector.x / value,
        vector.y / value,
        vector.z / value);
}

float dot(const Vector &vector1, const Vector &vector2)
{
    return vector1.x * vector2.x +
           vector1.y * vector2.y +
           vector1.z * vector2.z;
}

Vector cross(const Vector &vector1, const Vector &vector2)
{
    return Vector(
        vector1.y * vector2.z - vector1.z * vector2.y,
        vector1.z * vector2.x - vector1.x * vector2.z,
        vector1.x * vector2.y - vector1.y * vector2.x);
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    return (os << "Point(" << p.x << "," << p.y << "," << p.z << ")");
}

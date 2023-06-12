#ifndef MATRICES_H
#define MATRICES_H

typedef std::vector<std::vector<float>> Matrix;

inline Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    short rowSize = m1.size();
    short colSize = m1[0].size();

    Matrix result = Matrix(rowSize, std::vector<float>(colSize));

    for (int row = 0; row < rowSize; row++)
    {
        for (int col = 0; col < colSize; col++)
        {
            float product = 0;

            for (int i = 0; i < colSize; i++)
            {
                product += m1[row][i] * m2[i][col];
            }

            result[row][col] = product;
        }
    }

    return result;
}

#endif
#ifndef MATRIX_A_LIB_H
#define MATRIX_A_LIB_H
#include <vector>
#include <iostream>



namespace ALib{
    class Matrix{
    public:
        Matrix();
        Matrix(const std::vector<std::vector<float>> &newMatrix);
        Matrix& operator=(const Matrix& b);
        Matrix& operator=(const std::vector<std::vector<float>>& b);
        Matrix operator*(const float &b);
        Matrix& operator*=(const float &b);
        Matrix operator/(const float &b);
        Matrix& operator/=(const float &b);
        Matrix operator*(const Matrix& b);
        Matrix operator+(const Matrix& b);
        Matrix operator-(const Matrix& b);
        Matrix operator->*(const Matrix& b);
        friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);
        Matrix Transpose() const;
        std::vector<float>& operator[](unsigned index);
        const std::vector<float>& operator[](unsigned index)const;
        unsigned Width() const;
        unsigned Height() const;
    private:
        void SetSize(unsigned x, unsigned y);
        std::vector<std::vector<float>> matrixData;
        unsigned width=0,height=0;
    };
};






#endif //MATRIX_A_LIB_H
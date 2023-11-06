#include "Matrix.h"

#include <utility>
#include <stdexcept>
#include "immintrin.h"

//TODO: Implement SIMD, Multi threading, Test cache optimization, Local sub functions


using namespace ALib;

Matrix::Matrix(const std::vector<std::vector<double>> &newMatrix) {
    unsigned a=newMatrix[0].size();
    for(int i=0;i<newMatrix.size();i++){
        if(a!=newMatrix[i].size()){
            throw std::invalid_argument("Matrix rows are not the same size");
        }
    }
    width=newMatrix[0].size();
    height=newMatrix.size();
    matrixData=newMatrix;
}
Matrix::Matrix() = default;

Matrix &Matrix::operator=(const ALib::Matrix &b) {
    matrixData=b.matrixData;
    width=b.width;
    height=b.height;
    return *this;
}

Matrix &Matrix::operator=(const std::vector<std::vector<double>> &b) {
    unsigned a=b[0].size();
    for(int i=0;i<b.size();i++){
        if(a!=b[i].size()){
            throw std::invalid_argument("Matrix rows are not the same size");
        }
    }
    width=b[0].size();
    height=b.size();
    matrixData=b;
    return *this;
}

Matrix Matrix::operator*(const double &b) {
    //TODO: Optimize
    Matrix result;
    result.SetSize(width,height);
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            result[y][x]=this->matrixData[y][x]*b;
        }
    }
    return result;
}

void Matrix::SetSize(unsigned int x, unsigned int y) {
    if(!x||!y)return;
    matrixData.resize(y);
    for(int i=0;i<y;i++){
        matrixData[i].resize(x);
    }
    width=x;
    height=y;
}

Matrix &Matrix::operator/=(const double &b) {
    //TODO: Optimize
    for(int y=0;y<matrixData.size();y++){
        for(int x=0;x<matrixData[y].size();x++){
            matrixData[y][x]/=b;
        }
    }
    return *this;
}

Matrix Matrix::operator/(const double &b) {
    //TODO: Optimize
    Matrix result;
    result.SetSize(width,height);
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            result[y][x]=this->matrixData[y][x]/b;
        }
    }
    return result;
}

std::vector<double> &Matrix::operator[](unsigned int index){
    return matrixData[index];
}

const std::vector<double> &Matrix::operator[](unsigned int index) const {
    return matrixData[index];
}

Matrix &Matrix::operator*=(const double &b) {
    //TODO: Optimize
    for(int y=0;y<matrixData.size();y++){
        for(int x=0;x<matrixData[y].size();x++){
            matrixData[y][x]*=b;
        }
    }
    return *this;
}

Matrix Matrix::operator*(const ALib::Matrix &b) {
    //TODO: Optimize
    if(width!=b.height){
        throw std::invalid_argument("Width of first matrix is not matching height for second matrix");
    }
    Matrix result;
    result.SetSize(b.width,height);


    //VeryBasic GEMM, transpose optimization

    //Matrix tempMatrix=b.Transpose();

    for(int y=0;y<result.height;y++){
        for(int x=0;x<result.width;x++){
            double temp=0;
            for(int z=0;z<width;z++){
                temp+=matrixData[y][z]*b.matrixData[z][x];//*tempMatrix[x][z];
            }
            result[y][x]=temp;
        }
    }


    return result;
}



Matrix Matrix::operator+(const ALib::Matrix &b) {
    if(width!=b.width||height!=b.height){
        throw std::invalid_argument("Size of first matrix is not matching size of second matrix");
    }
    Matrix result;
    result.SetSize(width,height);
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            result[y][x]=matrixData[y][x]+b.matrixData[y][x];
        }
    }

    return result;
}

Matrix Matrix::operator-(const ALib::Matrix &b) {
    if(width!=b.width||height!=b.height){
        throw std::invalid_argument("Size of first matrix is not matching size of second matrix");
    }
    Matrix result;
    result.SetSize(width,height);
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            result[y][x]=matrixData[y][x]+b.matrixData[y][x];
        }
    }

    return result;
}

Matrix Matrix::Transpose() const {
    Matrix result;
    result.SetSize(height,width);
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            result[x][y]=matrixData[y][x];
        }
    }
    return  result;
}

Matrix Matrix::operator->*(const ALib::Matrix &b) {
    if(width!=1||b.width!=1){
        throw std::invalid_argument("Both matrix have to be column (1 width)");
    }

    Matrix result;
    result=(*this)*b.Transpose();

    return result;
}

unsigned int Matrix::Height() const {
    return height;
}

unsigned int Matrix::Width() const {
    return width;
}

std::ostream& ALib::operator<<(std::ostream& stream, const Matrix& matrix){
    for(int y=0;y<matrix.Height();y++){
        for(int x=0;x<matrix.Width();x++){
            stream<<matrix[y][x]<<" ";
        }
        stream<<std::endl;
    }
    return stream;
}
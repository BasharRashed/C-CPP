// Matrix.h


#include <iostream>
#include <cmath>

#ifndef MATRIX_H
#define MATRIX_H
#define MATRIX_DIMENSIONS_MSG "Matrix dimensions are not aligned."

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};


// Insert Matrix class here...
class Matrix{
private:
    int _rows,_cols;
    float* _data{};

public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int get_rows() const;
    int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(const Matrix& other) const;
    float norm() const;
    Matrix rref() const;
    int argmax() const;
    float sum() const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;
    float& operator[](int index);
    const float& operator[](int index) const;
    Matrix operator+(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(float scalar) const;
    friend Matrix operator*(float scalar, const Matrix& mat);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
    friend std::istream& operator>>(std::istream& is, Matrix& mat);

};


#endif //MATRIX_H
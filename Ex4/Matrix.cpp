//
// Created by bashar on 1/7/2025.
//
#include "Matrix.h"
#define DIM_ERR "Matrix dimensions must match for operation."
#define OUT_OF_RANGE "Accessing out of range of matrix index."
#define INPUT_STREAM_ERR "Input stream error to fill matrix"
Matrix::Matrix(): _rows{1},_cols{1}{
    _data = new float[_rows * _cols];
    _data[0] = 0;
}

Matrix::Matrix(int rows, int cols): _rows{rows},_cols{cols}{
    if(rows <= 0 || cols <= 0){
        throw std::invalid_argument(MATRIX_DIMENSIONS_MSG);
    }
    _data = new float[_rows * _cols];
}

Matrix::Matrix(const Matrix& m):_rows{m._rows},_cols{m._cols}
    ,_data{new float[_rows*_cols]} {
    for(int i =0;i< _rows * _cols ;i++){
        _data[i] = m._data[i];
    }

}

//destructor
Matrix::~Matrix(){
    delete[] _data;
}

//getters
int Matrix::get_rows() const{
    return _rows;
}
int Matrix::get_cols() const{
    return _cols;
}

//actions
Matrix& Matrix::transpose(){
    auto transposed_data = new float[_rows * _cols];
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            transposed_data[j * _rows + i] = _data[i * _cols + j];
        }
    }
    std::swap(_rows, _cols);

    delete[] _data;
    _data = transposed_data;

    return *this;
}

Matrix& Matrix::vectorize(){
    auto* newdata = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++) {
        newdata[i] = _data[i];
    }
    _rows = _rows * _cols;
    _cols = 1;
    delete[] _data;
    _data = newdata;
    return *this;
}

//operations
void Matrix::plain_print() const {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _data[i * _cols + j] << " ";
        }
        std::cout << std::endl;
    }
}
Matrix Matrix::dot(const Matrix& other) const{
    if(_rows != other._rows || _cols != other._cols){
        throw std::invalid_argument(MATRIX_DIMENSIONS_MSG);
    }
    Matrix dot_product(_rows,_cols);
    if(dot_product._data!= nullptr){
        for(int i=0;i<_rows;i++) {
            for (int j = 0; j < _cols; j++) {
                dot_product._data[i * _cols + j] = _data[i * _cols + j] *
                        other._data[i * _cols + j];
            }
        }
    }
    return dot_product;
}

float Matrix::norm() const{
    float sum = 0;
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++){
            sum+= _data[i*_cols +j] * _data[i*_cols +j];
        }
    }
    return sqrtf(sum);
}

Matrix Matrix::rref() const {
    Matrix copy(*this);
    int currPivot_index = 0;
    for (int row = 0; row < copy._rows; ++row) {
        if (currPivot_index >= copy._cols) {
            break;
        }

        int currentRow = row;
        while (copy._data[currentRow * copy._cols + currPivot_index] == 0) {
            ++currentRow;
            if (currentRow == copy._rows) {
                ++currPivot_index;
                if (currPivot_index == copy._cols) {
                    return copy;
                }
                currentRow = row;
            }
        }
        for (int col = 0; col < copy._cols; ++col) {
            std::swap(copy._data[row * copy._cols + col],
                      copy._data[currentRow * copy._cols + col]);
        }

        float pivot = copy._data[row * copy._cols + currPivot_index];
        if (pivot != 0) {
            for (int col = 0; col < copy._cols; ++col) {
                copy._data[row * copy._cols + col] /= pivot;
            }
        }
        for (int otherRow = 0; otherRow < copy._rows; ++otherRow) {
            if (otherRow != row) {
                float factor = copy._data[otherRow * copy._cols + currPivot_index];
                for (int col = 0; col < copy._cols; ++col) {
                    copy._data[otherRow * copy._cols + col] -= factor * copy._data[row * copy._cols + col];
                }
            }
        }
        ++currPivot_index;
    }
    for (int i = 0; i < _rows * _cols; ++i) {
        if (copy._data[i] == -0) {
            copy._data[i] = 0;
        }
    }

    return copy;
}



int Matrix::argmax() const {
    int maxindex = 0;
    float maxvalue = _data[0];
    for (int i = 1; i < _rows * _cols; ++i) {
        if (_data[i] > maxvalue) {
            maxvalue = _data[i];
            maxindex = i;
        }
    }
    return maxindex;
}

float Matrix::sum() const {
    float total = 0;
    for (int i = 0; i < _rows; i++) {
        for(int j =0; j < _cols;j++) {
            total += _data[i*_cols +j];
        }
    }
    return total;
}

//operators
Matrix& Matrix::operator=(const Matrix& other){
    if (this != &other) {
        _rows = other._rows;
        _cols = other._cols;
        auto *_new_data = new float[_rows * _cols];
        for(int i = 0; i <_rows*_cols; ++i)
        {
            _new_data[i] = other._data[i];
        }
        delete[] _data;
        _data = _new_data;
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& other) const{
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument(DIM_ERR);
    }
    Matrix result_add(_rows, _cols);
    if(result_add._data!= nullptr){
        for(int i=0;i<_rows;i++) {
            for (int j = 0; j < _cols; j++) {
                result_add._data[i * _cols + j] = _data[i * _cols + j]
                        + other._data[i * _cols + j];
            }
        }
    }
    return result_add;
}
Matrix& Matrix::operator+=(const Matrix& other){
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument(DIM_ERR);
    }
    for (int i = 0; i < _rows; i++) {
        for(int j=0;j< _cols;j++){
            _data[i*_cols +j] += other._data[i*_cols +j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if (_cols != other._rows) {
        throw std::invalid_argument(DIM_ERR);
    }
    Matrix result_mult(_rows, other._cols);
    if(result_mult._data!= nullptr) {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < other._cols; ++j) {
                result_mult._data[i * other._cols + j] = 0;
                for (int z = 0; z < _cols; ++z) {
                    result_mult._data[i * other._cols + j] +=
                            _data[i * _cols + z] * other._data[z * other._cols + j];
                }
            }
        }
    }
    return result_mult;
}
Matrix Matrix::operator*(float scalar) const{
    Matrix result_mult(_rows, _cols);
    for(int i =0;i<_rows;i++){
        for(int j =0;j<_cols;j++){
            result_mult._data[i*_cols + j] = _data[i*_cols +j]* scalar;
        }
    }
    return result_mult;
}

Matrix operator*(float scalar, const Matrix& mat){
    return mat*scalar;
}
float& Matrix::operator()(int row, int col){
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw std::out_of_range(OUT_OF_RANGE);
    }
    return _data[row * _cols + col];
}

const float& Matrix::operator()(int row, int col) const{
    if (row<0 || row >= _rows || col<0 ||col >= _cols) {
        throw std::out_of_range(OUT_OF_RANGE);
    }
    return _data[row * _cols + col];
}

float& Matrix::operator[] (int index){
    if (index < 0 || index >= _rows*_cols) {
        throw std::out_of_range(OUT_OF_RANGE);
    }
    return _data[index];
}
const float& Matrix::operator[](int index) const{
    if (index < 0 || index >= _rows * _cols) {
        throw std::out_of_range(OUT_OF_RANGE);
    }
    return _data[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat._rows; ++i) {
        for (int j = 0; j < mat._cols; ++j) {
            if (mat(i, j) > 0.1f) {
                os << "**";
            } else {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& mat) {

    for (int i = 0; i < mat._rows * mat._cols; ++i) {
        if (!is.read((char*)(&mat._data[i]), sizeof(float))) {
            throw std::runtime_error(INPUT_STREAM_ERR);
        }
    }
    return is;
}
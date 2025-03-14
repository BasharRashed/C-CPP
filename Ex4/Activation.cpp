//
// Created by bashar on 1/8/2025.
//
#include "Activation.h"

namespace activation {
    Matrix relu(const Matrix &mat) {
        Matrix relu_mat{mat.get_rows(), mat.get_cols()};
        for (int i = 0; i < mat.get_rows() * mat.get_cols(); i++) {
            if (mat[i] >= 0) {
                relu_mat[i] = mat[i];
            } else {
                relu_mat[i] = 0;
            }
        }
        return relu_mat;
    }

    Matrix softmax(const Matrix &mat) {
        Matrix vec{mat.get_rows(), mat.get_cols()};
        float sum = 0;
        for(int j=0;j<mat.get_rows();j++) {
            for (int i = 0; i < mat.get_cols() ;i++) {
                sum += std::exp(mat(j,i));
            }
        }
        sum = 1 / sum;
        for (int i = 0; i < mat.get_rows() * mat.get_cols(); i++) {
            vec[i] = std::exp(mat[i]) * sum;
        }
        return vec;
    }
}
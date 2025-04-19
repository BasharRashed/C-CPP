//
// Created by bashar on 1/8/2025.
//
#include "Dense.h"
Dense::Dense(const Matrix& weights,const Matrix& bias,activation_function af)
    : _weights(weights), _bias(bias), _af(af) {}

Matrix Dense::get_weights() const {
    return _weights;
}

Matrix Dense::get_bias() const {
    return _bias;
}

activation_function Dense::get_activation() const {
    return _af;
}

Matrix Dense::operator()(const Matrix& input) const {
    Matrix output = (_weights * input)+_bias;
    return _af(output);
}
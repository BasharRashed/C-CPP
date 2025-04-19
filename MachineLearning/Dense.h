// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
typedef Matrix (*activation_function)(const Matrix&);
// Insert Dense class here...
class Dense {
private:
    Matrix _weights;
    Matrix _bias;
    activation_function _af;

public:
    Dense(const Matrix& weights, const Matrix& bias, activation_function af);

    Matrix get_weights() const;
    Matrix get_bias() const;
    activation_function get_activation() const;

    Matrix operator()(const Matrix& input) const;
};

#endif //DENSE_H
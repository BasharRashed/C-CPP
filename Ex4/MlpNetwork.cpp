//
// Created by bashar on 1/8/2025.
//
#include "MlpNetwork.h"
MlpNetwork::MlpNetwork(const Matrix weights[MLP_SIZE],const Matrix biases[MLP_SIZE]): layers{
        Dense(weights[0],biases[0],activation::relu),
        Dense(weights[1],biases[1],activation::relu),
        Dense(weights[2],biases[2], activation::relu),
        Dense(weights[3], biases[3],activation::softmax)
} {}

digit MlpNetwork::operator()(const Matrix& input) const {
    Matrix copy = input;
    for(int i = 0; i <MLP_SIZE; i++) {
        copy = layers[i](copy);
    }
    unsigned int value = copy.argmax();
    float prob = copy[value];
    digit return_value = {value, prob};
    return return_value;
}
#pragma once

#include "cubes.h"


template <typename T>
Vector2DSquare<T>::Vector2DSquare(int length) : length(length) {
    vec = std::vector<std::vector<T>>(length, std::vector<T>(length));
}


template <typename T>
Vector2DSquare<T>::Vector2DSquare(int length, T defaultValue) : length(length) {
    vec = std::vector<std::vector<T>>(length, std::vector<T>(length, defaultValue));
}


template <typename T>
const T& Vector2DSquare<T>::at(int row, int col) const {
    return vec.at(row).at(col);
}


template <typename T>
T& Vector2DSquare<T>::at(int row, int col) {
    return vec.at(row).at(col);
}


template <typename T>
void Vector2DSquare<T>::set(int row, int col, T value) {
    vec[row][col] = value;
}


template <typename T>
void Vector2DSquare<T>::rot90() {
    // Code yoinked from 
    // https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/

    for (int i = 0; i < length / 2; i++) { 
        for (int j = i; j < length - i - 1; j++) { 
            // Swap elements of each cycle in clockwise direction 
            T temp = vec[i][j]; 
            vec[i][j]                             = vec[length - 1 - j][i]; 
            vec[length - 1 - j][i]                = vec[length - 1 - i][length - 1 - j]; 
            vec[length - 1 - i][length - 1 - j]   = vec[j][length - 1 - i]; 
            vec[j][length - 1 - i]                = temp; 
        } 
    } 
}


// See https://stackoverflow.com/questions/8848575/fastest-way-to-reset-every-value-of-stdvectorint-to-0
// for performance differences in `std::fill` vs. `std::vector::assign`.

template <typename T>
void Vector2DSquare<T>::reset(T defaultValue) {
    for (auto& row : vec) {
        std::fill(row.begin(), row.end(), defaultValue);
    }
}


template <typename T>
void Vector2DSquare<T>::resetAndResize(int newLength, T defaultValue) {
    for (std::vector<T>& row : vec) {
        row.clear();
    }
    vec.clear();
    vec = std::vector<std::vector<T>>(newLength, std::vector<T>(newLength, defaultValue));
}
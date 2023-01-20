#pragma once

#include "rubik/core/cube.h"

namespace rubik {

template<typename T>
constexpr Vector2DSquare<T>::Vector2DSquare(int length) : length(length) {
    vec = std::vector<std::vector<T>>(length, std::vector<T>(length));
}

template<typename T>
constexpr Vector2DSquare<T>::Vector2DSquare(int length, T defaultValue) : length(length) {
    vec = std::vector<std::vector<T>>(length, std::vector<T>(length, defaultValue));
}

template<typename T>
constexpr const T& Vector2DSquare<T>::at(int row, int col) const {
    return vec.at(row).at(col);
}

template<typename T>
constexpr T& Vector2DSquare<T>::at(int row, int col) {
    return vec.at(row).at(col);
}

template<typename T>
constexpr void Vector2DSquare<T>::set(int row, int col, T value) {
    vec[row][col] = value;
}

template<typename T>
constexpr void Vector2DSquare<T>::rot90() {
    // Code yoinked from 
    // https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/
    for (int i = 0; i < length / 2; i++) { 
        for (int j = i; j < length - i - 1; j++) { 
            // Swap elements of each cycle in clockwise direction 
            T temp = vec.at(i).at(j);
            vec.at(i).at(j) = vec.at(length - 1 - j).at(i);
            vec.at(length - 1 - j).at(i) = vec.at(length - 1 - i).at(length - 1 - j);
            vec.at(length - 1 - i).at(length - 1 - j) = vec.at(j).at(length - 1 - i);
            vec.at(j).at(length - 1 - i) = temp;
        } 
    } 
}

// See https://stackoverflow.com/questions/8848575/fastest-way-to-reset-every-value-of-stdvectorint-to-0
// for performance differences in `std::fill` vs. `std::vector::assign`.

template<typename T>
constexpr void Vector2DSquare<T>::reset(T defaultValue) {
    for (auto& row : vec) {
        std::fill(row.begin(), row.end(), defaultValue);
    }
}

template<typename T>
constexpr void Vector2DSquare<T>::resetAndResize(int newLength, T defaultValue) {
    length = newLength;
    vec.clear();
    vec.resize(length);
    std::fill(vec.begin(), vec.end(), std::vector<T>(length, defaultValue));
}

template<typename T>
void Vector2DSquare<T>::coutPrintArray() const {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            std::cout << at(i, j);
        }
        std::cout << '\n';
    }
}

}  // namespace rubik

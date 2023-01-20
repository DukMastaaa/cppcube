#pragma once

#include "rubik/core/move.h"

#include <array>
#include <cstdint>
#include <vector>

namespace rubik {

enum class CubeFace : uint8_t {
    Up,
    Front,
    Right,
    Left,
    Back,
    Down
};

// Alias for convenience
using StickerColour = CubeFace;

template <typename T>
class Vector2DSquare {
private:
    int length;
    std::vector<std::vector<T>> vec;
public:
    constexpr Vector2DSquare(int length = 3);
    constexpr Vector2DSquare(int length, T defaultValue);
    constexpr const T& at(int row, int col) const;
    constexpr T& at(int row, int col);
    constexpr void set(int row, int col, T value);
    constexpr void reset(T defaultValue);
    constexpr void resetAndResize(int newLength, T defaultValue);
    constexpr void rot90();
    void coutPrintArray() const;
};

class Cube {
private:
    int dim;
    std::array<Vector2DSquare<StickerColour>, 6> faces;
public:
    constexpr Cube(int dim_);
    constexpr void applyMove(Move move);
    constexpr void reset();
    constexpr void resetAndResize(int newDim);
    constexpr StickerColour getColourAtSticker(CubeFace face, int row, int col) const;
    // void coutDisplayNet() const;
};

}  // namespace rubik

#include "rubik/core/impl/vector2dsquare.tpp"
#include "rubik/core/impl/cube.tpp"

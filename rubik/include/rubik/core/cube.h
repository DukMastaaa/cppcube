#pragma once

#include "rubik/core/move.h"

#include <array>
#include <cstdint>
#include <vector>
#include <type_traits>

namespace rubik {

enum class CubeFace : uint8_t {
    Up = 0,
    Front = 1,
    Right = 2,
    Back = 3,
    Left = 4,
    Down = 5
};

// https://en.cppreference.com/w/cpp/utility/to_underlying
template< class Enum >
constexpr std::underlying_type_t<Enum> to_underlying( Enum e ) noexcept {
    return static_cast<std::underlying_type_t<Enum>>(e);
}

static_assert(
        (to_underlying(CubeFace::Up)    == to_underlying(Action::Up)    - 1) &&
        (to_underlying(CubeFace::Front) == to_underlying(Action::Front) - 1) &&
        (to_underlying(CubeFace::Right) == to_underlying(Action::Right) - 1) &&
        (to_underlying(CubeFace::Back)  == to_underlying(Action::Back)  - 1) &&
        (to_underlying(CubeFace::Left)  == to_underlying(Action::Left)  - 1) &&
        (to_underlying(CubeFace::Down)  == to_underlying(Action::Down)  - 1));

constexpr CubeFace actionFaceTurnToCubeFace(Action action) {
    using enum Action;
    switch (action) {
        case Up:
        case Front:
        case Right:
        case Back:
        case Left:
        case Down:
            return static_cast<CubeFace>(to_underlying(action) - 1);
        default:
            throw std::invalid_argument("action is not a face turn");
    }
}

constexpr CubeFace oppositeFace(CubeFace face) {
    using enum CubeFace;
    switch (face) {
        case Up: return Down;
        case Front: return Back;
        case Right: return Left;
        case Left: return Right;
        case Back: return Front;
        case Down: return Up;
    }
}

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
    constexpr ~Vector2DSquare() = default;
    constexpr const T& at(int row, int col) const;
    constexpr T& at(int row, int col);
    constexpr void set(int row, int col, T value);
    constexpr void reset(T defaultValue);
    constexpr void resetAndResize(int newLength, T defaultValue);
    constexpr void rot90Clockwise();
    constexpr void rot90Counterclockwise();
    void coutPrintArray() const;
};

class Cube {
private:
    int dim;
    std::array<Vector2DSquare<StickerColour>, 6> faces;
private:
    constexpr void applyFaceTurn(CubeFace face, Depth depth, std::int8_t signedRepeat);
    // constexpr void applyRotation(CubeFace clockwiseFace, CubeFace counterClock)
public:
    constexpr Cube(int dim_);

    // template <int N>
    // static constexpr Cube fromArray(const std::array<StickerColour, N*N*6>& arr);

    constexpr void applyMove(Move move);
    constexpr void reset();
    constexpr void resetAndResize(int newDim);
    constexpr StickerColour getColourAtSticker(CubeFace face, int row, int col) const;

    template <int N>
    constexpr std::array<StickerColour, N*N*6> exportAsArray() const;

    template <int N>
    static inline void printNetFromArray(
                const std::array<StickerColour, N*N*6>& arr,
                const std::array<char, 6>& colourChars);
    
    // void coutDisplayNet() const;
};

}  // namespace rubik

#include "rubik/core/impl/vector2dsquare.tpp"
#include "rubik/core/impl/cubehelper.tpp"
#include "rubik/core/impl/cube.tpp"

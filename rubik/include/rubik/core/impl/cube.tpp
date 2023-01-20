#pragma once

#include "rubik/core/cube.h"

namespace rubik {

constexpr Cube::Cube(int dim_)
    : dim(dim_), faces()
{
    reset();
}

constexpr void Cube::applyFaceTurn(CubeFace face, Depth depth, std::int8_t signedRepeat) {
    bool reverse = signedRepeat < 0;
    std::int8_t unsignedRepeat = reverse ? -signedRepeat : signedRepeat;
    if (depth.min == 0) {
        if (reverse) {
            faces[static_cast<size_t>(face)].rot90Counterclockwise();
        } else {
            faces[static_cast<size_t>(face)].rot90Clockwise();
        }
    }
    if (depth.max == dim - 1) {
        // Choose opposite face and switch rotation direction
        if (reverse) {
            faces[static_cast<size_t>(oppositeFace(face))].rot90Clockwise();
        } else {
            faces[static_cast<size_t>(oppositeFace(face))].rot90Counterclockwise();
        }
    }
    for (std::int8_t i = 0; i < unsignedRepeat; i++) {
        for (int layer = depth.min; layer <= depth.max; layer++) {
            cube_helper::cycle(faces, dim, face, reverse, layer);
        }
    }
}

constexpr void Cube::applyMove(Move move) {
    switch (move.action) {
        case Action::NOP:
            break;
        case Action::Up:
        case Action::Front:
        case Action::Right:
        case Action::Back:
        case Action::Left:
        case Action::Down:
            applyFaceTurn(actionFaceTurnToCubeFace(move.action), move.depth, move.signedRepeat);
        case Action::SliceM:
        case Action::SliceE:
        case Action::SliceS:
            break;  // not implemented
        case Action::RotX:
        case Action::RotY:
        case Action::RotZ:
            break;  // not implemented
    }
}

constexpr void Cube::reset() {
    for (int i = 0; i < 6; i++) {
        faces[i].reset(static_cast<StickerColour>(i));
    }
}

constexpr void Cube::resetAndResize(int newDim) {
    dim = newDim;
    for (int i = 0; i < 6; i++) {
        faces[i].resetAndResize(dim, static_cast<StickerColour>(i));
    }
}

constexpr StickerColour Cube::getColourAtSticker(CubeFace face, int row, int col) const {
    return faces[static_cast<size_t>(face)].at(row, col);
}

template <int N>
constexpr std::array<StickerColour, N*N*6> Cube::exportAsArray() const {
    if (dim != N) {
        throw std::invalid_argument("dim doesnt match N");
    }
    std::array<StickerColour, N*N*6> arr;
    size_t runningIndex = 0;
    for (int face = 0; face < 6; face++) {
        // Saved in standard face order (UFRBLD)
        for (int row = 0; row < dim; row++) {
            for (int col = 0; col < dim; col++) {
                arr.at(runningIndex) = faces[face].at(row, col);
                runningIndex++;
            }
        }
    }
    return arr;
}

template <int N>
inline void Cube::printNetFromArray(const std::array<StickerColour, N*N*6>& arr,
        const std::array<char, 6>& colourChars) {
    size_t runningIndex = 0;
    for (int face = 0; face < 6; face++) {
        std::cout << "face: " << face << '\n';
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                std::cout << colourChars[static_cast<size_t>(arr[runningIndex])];
                runningIndex++;
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}

}  // namespace rubik

#pragma once

#include "rubik/core/cube.h"

namespace rubik {

constexpr Cube::Cube(int dim_)
    : dim(dim_), faces()
{
    reset();
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


namespace cube_helper {

using enum CubeFace;

// Faces to swap

using FacesToSwap = std::array<std::array<CubeFace, 4>, 6>;

constexpr const FacesToSwap facesToSwap = {{  // double brace
    {Right, Back, Left, Front},  // Up
    {Left, Down, Right, Up},     // Front
    {Down, Back, Up, Front},     // Right
    {Right, Down, Left, Up},     // Back
    {Up, Back, Down, Front},     // Left
    {Left, Back, Right, Front},  // Down
}};

constexpr const FacesToSwap reverseFacesToSwap(const FacesToSwap& facesToSwap) {
    auto reversed = FacesToSwap();
    for (std::size_t faceIndex = 0; faceIndex < 6; faceIndex++) {
        for (std::size_t sideIndex = 0; sideIndex < 4; sideIndex++) {
            reversed[faceIndex][sideIndex] = facesToSwap[faceIndex][3 - sideIndex];
        }
    }
    return reversed;
}

constexpr const FacesToSwap reversedFacesToSwap = reverseFacesToSwap(facesToSwap);


// Swap instructions

enum class SwapInstruction : uint8_t {
    Depth,
    IterationCount,
    DimMinusOneMinusDepth,
    DimMinusOneMinusIterationCount
};

using D = SwapInstruction::Depth;
using I = SwapInstruction::IterationCount;
using M = SwapInstruction::DimMinusOneMinusDepth;
using F = SwapInstruction::DimMinusOneMinusIterationCount;

using SwapInstructions = std::array<std::array<std::array<SwapInstruction, 2>, 4>, 6>;

constexpr const SwapInstructions swapInstructions = {{
    {{  // Up
        {D, I},
        {D, I},
        {D, I},
        {D, I}
    }},
    {{  // Front
        {F, M},
        {D, F},
        {I, D},
        {M, I}
    }},
    {{  // Right
        {I, M},
        {F, D},
        {I, M},
        {I, M}
    }},
    {{  // Back
        {I, M},
        {M, F},
        {F, D},
        {D, I}
    }},
    {{  // Left
        {I, D},
        {F, M},
        {I, D},
        {I, D}
    }},
    {{  // Down
        {M, I},
        {M, I},
        {M, I},
        {M, I}
    }}
}};

constexpr const SwapInstructions reverseSwapInstructions(const SwapInstructions& swapInstructions) {
    auto reversed = SwapInstructions();
    for (std::size_t faceIndex = 0; faceIndex < 6; faceIndex++) {
        for (std::size_t sideIndex = 0; sideIndex < 4; sideIndex++) {
            // TODO: replace this with copy operation?
            for (std::size_t instructionIndex = 0; instructionIndex < 2; instructionIndex++) {
                reversed[faceIndex][sideIndex][instructionIndex] = swapInstructions[faceIndex][3 - sideIndex][instructionIndex];
            }
        }
    }
    return reversed;
}

constexpr const SwapInstructions reversedSwapInstructions = reverseSwapInstructions(swapInstructions);


}  // namespace cube_helper

}  // namespace rubik

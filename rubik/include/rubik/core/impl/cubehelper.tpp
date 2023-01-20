#pragma once

#include "rubik/core/cube.h"

namespace rubik {

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

enum class PositionCode : uint8_t {
    Depth,
    IterationCount,
    DimMinusOneMinusDepth,
    DimMinusOneMinusIterationCount
};

constexpr PositionCode D = PositionCode::Depth;
constexpr PositionCode I = PositionCode::IterationCount;
constexpr PositionCode M = PositionCode::DimMinusOneMinusDepth;
constexpr PositionCode F = PositionCode::DimMinusOneMinusIterationCount;

using SwapInstruction = std::array<PositionCode, 2>;
using SwapInstructions = std::array<std::array<SwapInstruction, 4>, 6>;

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


// Functions to help with cycles

constexpr int translatePositionCode(PositionCode code, int dim, int depth, int layer) {
    switch (code) {
        case D:
            return depth;
            break;
        case I:
            return layer;
            break;
        case M:
            return dim - 1 - depth;
            break;
        case F:
            return dim - 1 - layer;
            break;
    }
}

constexpr std::array<int, 2> getPosFromSwapInstruction(
            const SwapInstruction& insn,
            int dim, int depth, int layer) {
    int row = translatePositionCode(insn[0], dim, depth, layer);
    int col = translatePositionCode(insn[1], dim, depth, layer);
    return {row, col};
}

constexpr StickerColour* getStickerFromSwapInstruction(
        const SwapInstruction& insn,
        int dim, int depth, int layer,
        CubeFace thisFace,
        std::array<Vector2DSquare<StickerColour>, 6>& faces) {
    auto [row, col] = getPosFromSwapInstruction(insn, dim, depth, layer);
    return &(faces.at(static_cast<size_t>(thisFace)).at(row, col));
}

constexpr void cycle(
        std::array<Vector2DSquare<StickerColour>, 6>& faces,
        int dim, CubeFace face, bool reverse, int depth) {
    // index -1 is (dim - 1)

    int faceIndex = static_cast<size_t>(face);
    const auto& faceCycle = reverse ? reversedFacesToSwap[faceIndex] : facesToSwap[faceIndex];
    const auto& instructions = (reverse) ? reversedSwapInstructions[faceIndex] : swapInstructions[faceIndex];

    StickerColour* thisSticker;
    StickerColour* nextSticker;

    CubeFace nextFace;  // faces

    StickerColour bufferValue;  // Keeps track of the value at the buffer because it gets replaced.
    
    for (int layer = 0; layer < dim; layer++) {  // loops over stickers along each layer
        // get the initial value
        // store everything in "next" variables as the loop shunts the values to "this" variables
        nextFace = faceCycle[0];
        nextSticker = getStickerFromSwapInstruction(
                instructions[0],
                dim, depth, layer,
                nextFace, faces);
        bufferValue = *nextSticker;

        for (int cycleStep = 0; cycleStep < 4; cycleStep++) {  // loops over cycle replacements
            nextFace = faceCycle[(cycleStep+1) % 4];

            thisSticker = nextSticker;
            if (cycleStep == 3) {
                nextSticker = &bufferValue;
            } else {
                nextSticker = getStickerFromSwapInstruction(
                        instructions[(cycleStep+1)%4],
                        dim, depth, layer,
                        nextFace, faces);
            }
            
            *thisSticker = *nextSticker;
        }
    }
}





}  // namespace cube_helper

}  // namespace rubik

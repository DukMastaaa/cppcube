#include "models/cubes.h"

#include <iostream>
#include <array>
#include <vector>
#include <sstream>


int CycleHelper::translateOneSwapInstruction(char instruction, int dim, int depth, int layer) {
    switch (instruction) {
        case 'd':
            return depth;
            break;
        case 'i':
            return layer;
            break;
        case 'm':
            return dim - 1 - depth;
            break;
        case 'f':
            return dim - 1 - layer;
            break;
        default:
            return -1;
            break;
    }
}


std::array<int, 2> CycleHelper::getPosFromSwapInstruction(const std::array<char, 2>& instructions, int dim, int depth, int layer) {
    int row = translateOneSwapInstruction(instructions[0], dim, depth, layer);
    int col = translateOneSwapInstruction(instructions[1], dim, depth, layer);
    return {row, col};
}


void CycleHelper::cycle(std::vector<Vector2DSquare<StickerColour>>& faces, int dim, CubeFace face, bool reverse, int depth) {
    // index -1 is (dim - 1) 

    const auto& faceCycle = (reverse) ? facesToSwapReversed[face] : facesToSwap[face];
    const auto& instructions = (reverse) ? swapInstructionsReversed[face] : swapInstructions[face];

    StickerColour* thisSticker;
    StickerColour* nextSticker;

    CubeFace thisFace, nextFace;  // faces

    StickerColour bufferValue;  // Keeps track of the value at the buffer because it gets replaced.
    
    for (int layer = 0; layer < dim; layer++) {  // loops over stickers along each layer
        for (int cycleStep = 0; cycleStep < 4; cycleStep++) {  // loops over cycle replacements

            thisFace = faceCycle[cycleStep];
            if (cycleStep < 3) {  // if statement necessary as index error will be raised if cycleStep == 3
                nextFace = faceCycle[cycleStep+1];
            }

            // todo: refactor more??!
            auto [row, col] = getPosFromSwapInstruction(instructions[cycleStep], dim, depth, layer);
            thisSticker = &(faces[thisFace].at(row, col));

            // note: when cycleStep == 3, cycleStep+1 will cause index error
            if (cycleStep < 3) {
                // add 1 to look forward to next instruction.
                auto [row, col] = getPosFromSwapInstruction(instructions[cycleStep+1], dim, depth, layer);
                nextSticker = &(faces[nextFace].at(row, col));
            }
        
            if (cycleStep == 0) {
                bufferValue = *thisSticker;
            }

            if (cycleStep < 3) {
                // Now, thisSticker and nextSticker have been set, so we replace:
                *thisSticker = *nextSticker;
            } else {
                // Now we need to fix the cycle by putting the first element of the cycle (buffer)
                // in the last cycle position. There is no more nextSticker.
                *thisSticker = bufferValue;
            }
            // Cycle fixed.
        }
    }
}


// CubeModel method implementations
CubeModel::CubeModel(int dimension) : faces(6, Vector2DSquare<StickerColour>(dimension)), dim(dimension) {
    resetState();
}


void CubeModel::resetState() {
    for (int i = 0; i < 6; i++) {
        // does this cause memory leaks? what happens to the old Vector2DSquare?
        faces[i].reset(static_cast<StickerColour>(i));
    }
}


void CubeModel::resetState(int dimension) {
    dim = dimension;
    for (int i = 0; i < 6; i++) {
        faces[i].resetAndResize(dim, static_cast<StickerColour>(i));
    }
}


void CubeModel::makeTurn(CubeFace face, bool reverse, int depth) {
    if (depth == 0) {
        for (int i = 0; i < (reverse ? 3 : 1); i++) {
            faces[face].rot90(); 
        }
    }
    CycleHelper::cycle(faces, dim, face, reverse, depth);
}


const std::vector<Vector2DSquare<StickerColour>>& CubeModel::getFaces() const {
    return faces;
}


StickerColour CubeModel::getColourAtSticker(CubeFace face, int row, int col) const {
    return faces[face].at(row, col);
}


void CubeModel::coutRepeatChar(char character, int repetitions) const {
    for (int i = 0; i < repetitions; i++) {
        std::cout << character;
    }
}


void CubeModel::coutDisplayNet() const {
    /* Prints a net of the cube to std::cout. */
    // UP
    for (int row = 0; row < dim; row++) {
        coutRepeatChar(' ', dim + 1);
        for (int col = 0; col < dim; col++) {
            std::cout << COLOURS[faces[UP].at(row, col)];
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // LEFT, FRONT, RIGHT, BACK
    const int middleFaces[] = {LEFT, FRONT, RIGHT, BACK};
    for (int row = 0; row < dim; row++ ) {
        for (int face : middleFaces) {
            for (int col = 0; col < dim; col++) {
                std::cout << COLOURS[faces[face].at(row, col)];
            }
            std::cout << " ";
        }
        std::cout << "\n";
    } 
    std::cout << "\n";

    // DOWN
    for (int row = 0; row < dim; row++) {
        coutRepeatChar(' ', dim + 1);
        for (int col = 0; col < dim; col++) {
            std::cout << COLOURS[faces[DOWN].at(row, col)];
        }
        std::cout << "\n";
    }
}


void CubeModel::parseOneMove(std::string move) {
    // todo: inefficient since it searches multiple times
    int depth;
    CubeFace face;
    std::string depthAcc;

    bool doubleTurn = (move.back() == '2');
    bool reverseTurn = (move.back() == '\'');

    // find depth of wide turn
    bool wideSymbol = (move.find('w') != std::string::npos);
    if (wideSymbol) {
        for (const char& symbol : move) {
            if (std::isdigit(symbol)) {
                depthAcc += {symbol, '\0'};
            } else {
                break;
            }
        }
        depth = depthAcc.empty() ? 1 : std::stoi(depthAcc) - 1;  // top layer is depth 0, not 1
    } else {
        depth = 0;
    }

    std::cout << depth << '\n';

    for (int i = 0; i < 6; i++) {
        if (move.find(FACE_SYMBOLS[i]) != std::string::npos) {
            face = static_cast<CubeFace>(i);  // `i` will definitely be in enum range, static_cast acceptable
            break;  // this can't handle invalid input, but oh well
        }
    }
        
    for (int turnTwice = 0; turnTwice < (doubleTurn ? 2 : 1); turnTwice++) {
        for (int depthCount = 0; depthCount < depth + 1; depthCount++) {
            // for depth + 1, e.g. depth = 0 => loop once
            makeTurn(face, reverseTurn, depthCount);
        }
    }
}


void CubeModel::parseMovesReset(std::string moves) {
    /* Resets cube then parses moves. */
    resetState();
    parseMovesNoReset(moves);
}


void CubeModel::parseMovesNoReset(std::string moves) {
    std::string move;
    std::stringstream stream(moves);

    while (stream >> move) {
        parseOneMove(move);
    }
}
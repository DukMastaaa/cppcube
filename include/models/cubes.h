#pragma once

#include <array>
#include <vector>
#include <iostream>

#include "models/baseModel.h"


// Default colour of face is the face number itself.
enum CubeFace {
    UP, FRONT, RIGHT, BACK, LEFT, DOWN
};


enum StickerColour {
    WHITE, GREEN, RED, BLUE, ORANGE, YELLOW
};


template <typename T>
class Vector2DSquare {
    private:
        int length;
        std::vector<std::vector<T>> vec;

    public:
        Vector2DSquare(int length);
        Vector2DSquare(int length, T defaultValue);
        const T& at(int row, int col) const;
        T& at(int row, int col);
        void set(int row, int col, T value);
        void reset(T defaultValue);
        void resetAndResize(int newLength, T defaultValue);
        void rot90();
        void coutPrintArray() const;
};


#include "cubes.tpp"


// Provides constexpr functions to assist with reversing cycle instructions in `CycleHelper`.
class CycleCalculateReversed {
    public:
        static constexpr const std::array<std::array<CubeFace, 4>, 6> reverseFacesToSwap(const std::array<std::array<CubeFace, 4>, 6> facesToSwap) {
            auto reversed = std::array<std::array<CubeFace, 4>, 6>();
            for (std::size_t faceIndex = 0; faceIndex < 6; faceIndex++) {
                for (std::size_t sideIndex = 0; sideIndex < 4; sideIndex++) {
                    reversed[faceIndex][sideIndex] = facesToSwap[faceIndex][3 - sideIndex];
                }
            }
            return reversed;
        }

        static constexpr const std::array<std::array<std::array<char, 2>, 4>, 6> reverseSwapInstructions(const std::array<std::array<std::array<char, 2>, 4>, 6> swapInstructions) {
            auto reversed = std::array<std::array<std::array<char, 2>, 4>, 6>();
            for (std::size_t faceIndex = 0; faceIndex < 6; faceIndex++) {
                for (std::size_t sideIndex = 0; sideIndex < 4; sideIndex++) {
                    for (std::size_t instructionIndex = 0; instructionIndex < 2; instructionIndex++) {  // todo: replace this with copy operation?
                        reversed[faceIndex][sideIndex][instructionIndex] = swapInstructions[faceIndex][3 - sideIndex][instructionIndex];
                    }
                }
            }
            return reversed;
        }
};


class CycleHelper {
    private:
        static constexpr const std::array<std::array<CubeFace, 4>, 6> facesToSwap = {{  // double brace
            {RIGHT, BACK, LEFT, FRONT},  // UP
            {LEFT, DOWN, RIGHT, UP},     // FRONT
            {DOWN, BACK, UP, FRONT},     // RIGHT
            {RIGHT, DOWN, LEFT, UP},     // BACK
            {UP, BACK, DOWN, FRONT},     // LEFT
            {LEFT, BACK, RIGHT, FRONT},  // DOWN
        }};

        static constexpr const std::array<std::array<CubeFace, 4>, 6> facesToSwapReversed = CycleCalculateReversed::reverseFacesToSwap(facesToSwap);

        // d: depth, i: i, m: dim-1-depth, f: dim-1-i

        static constexpr const std::array<std::array<std::array<char, 2>, 4>, 6> swapInstructions = {{  // double brace
            {{  // UP, double brace
                {'d', 'i'},
                {'d', 'i'},
                {'d', 'i'},
                {'d', 'i'}
            }},
            {{  // FRONT
                {'f', 'm'},
                {'d', 'f'},  //  bug, used to be d m
                {'i', 'd'},
                {'m', 'i'}
            }},
            {{  // RIGHT
                {'i', 'm'},
                {'f', 'd'},
                {'i', 'm'},
                {'i', 'm'}
            }},
            {{  // BACK
                {'i', 'm'},
                {'m', 'f'},
                {'f', 'd'},
                {'d', 'i'}
            }},
            {{  // LEFT
                {'i', 'd'},
                {'f', 'm'},
                {'i', 'd'},
                {'i', 'd'}
            }},
            {{  // DOWN
                {'m', 'i'},
                {'m', 'i'},
                {'m', 'i'},
                {'m', 'i'}
            }}
        }};

        static constexpr const std::array<std::array<std::array<char, 2>, 4>, 6> swapInstructionsReversed = CycleCalculateReversed::reverseSwapInstructions(swapInstructions);

        static int translateOneSwapInstruction(char instruction, int dim, int depth, int layer);
        static std::array<int, 2> getPosFromSwapInstruction(const std::array<char, 2>& instructions, int dim, int depth, int layer);

    public:
        static void cycle(std::vector<Vector2DSquare<StickerColour>>& faces, int dim, CubeFace face, bool reverse, int depth = 0);
};


class CubeModel : public BaseModel {
    private:
        static constexpr std::array<char, 6> FACE_SYMBOLS = {'U', 'F', 'R', 'B', 'L', 'D'};
        static constexpr std::array<char, 6> COLOURS = {'W', 'G', 'R', 'B', 'O', 'Y'};
        
        // not doing this with `std::array<Vector2DSquare<StickerColour>, 6>>`.
        // that requires me to provide some default constructor for `Vector2DSquare<StickerColour>` which
        // i have no idea how to do.
        std::vector<Vector2DSquare<StickerColour>> faces;

        void cycle(int face, bool reverse, int depth = 0);
        void makeTurn(CubeFace face, bool reverse, int depth = 0);
        void parseOneMove(std::string move);
        void coutRepeatChar(char character, int repetitions) const;

    public:
        int dim;  // todo: should this be std::size_t instead of int?
        CubeModel(int dimension);
        void resetState();
        void resetState(int dimension);
        const std::vector<Vector2DSquare<StickerColour>>& getFaces() const;
        StickerColour getColourAtSticker(CubeFace face, int row, int col) const;
        void coutDisplayNet() const;
        void parseMovesReset(std::string moves);
        void parseMovesNoReset(std::string moves);
};
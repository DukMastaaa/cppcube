#pragma once

#include <array>
#include <vector>
#include <iostream>


// Default colour of face is the face number itself.
enum CubeFace {
    UP, FRONT, RIGHT, BACK, LEFT, DOWN
};


class Array2DSquare {
    private:
        std::vector<std::vector<int>> array;

    public:
        int length;
        Array2DSquare(int sideLength);
        Array2DSquare(int sideLength, int defaultValue);
        int& at(int row, int col);
        void set(int row, int col, int value);
        void rot90();
};


class CubeModel {
    private:
        static constexpr std::array<char, 6> FACE_SYMBOLS = {'U', 'F', 'R', 'B', 'L', 'D'};
        static constexpr std::array<char, 6> COLOURS = {'W', 'G', 'R', 'B', 'O', 'Y'};

        static constexpr std::array<std::array<CubeFace, 4>, 6> facesToSwap = {{
            {RIGHT, BACK, LEFT, FRONT},  // UP
            {LEFT, DOWN, RIGHT, UP},     // FRONT
            {DOWN, BACK, UP, FRONT},     // RIGHT
            {RIGHT, DOWN, LEFT, UP},     // BACK
            {UP, BACK, DOWN, FRONT},     // LEFT
            {LEFT, BACK, RIGHT, FRONT},  // DOWN
        }};

        static constexpr std::array<std::array<CubeFace, 4>, 6> reverseFacesToSwap() {
            std::array<std::array<CubeFace, 4>, 6> reversed = facesToSwap;
            for (std::size_t faceIndex = 0; faceIndex < 6; faceIndex++) {
                for (std::size_t sideIndex = 0; sideIndex < 4; sideIndex++) {
                    reversed[faceIndex][sideIndex] = facesToSwap[faceIndex][3 - sideIndex];
                }
            }
            return reversed;
        }

        // what on earth
        static constexpr std::array<std::array<CubeFace, 4>, 6> facesToSwapReversed = reverseFacesToSwap();

        static const std::vector<std::vector<int>> facesToSwapReversed;

        // d: depth, i: i, m: dim-1-depth, f: dim-1-i
        static const std::vector<std::vector<std::vector<char>>> swapInstructions;
        static const std::vector<std::vector<std::vector<char>>> swapInstructionsReversed;

        std::vector<Array2DSquare> faces;

        void cycle(int face, bool reverse, int depth = 0);
        void makeTurn(int face, bool reverse, int depth = 0);
        void parseOneMove(std::string move);
        void coutRepeatChar(char character, int repetitions);

    public:
        int dim;  // todo: should this be std::size_t instead of int?
        CubeModel(int dimension);
        void resetState();
        void resetState(int dimension);
        std::vector<Array2DSquare>& getFaces();
        int getColourAtSticker(int face, int row, int col);
        void coutDisplayNet();
        void parseMovesReset(std::string moves);
        void parseMovesNoReset(std::string moves);
};
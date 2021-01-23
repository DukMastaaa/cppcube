#pragma once

#include <vector>
#include <iostream>

/*
Faces order:
U F R B L D
0 1 2 3 4 5

Colours:
W G R B O Y
0 1 2 3 4 5

Default colour of face is the face number itself.
*/


static const int FACE_UP = 0;
static const int FACE_FRONT = 1;
static const int FACE_RIGHT = 2;
static const int FACE_BACK = 3;
static const int FACE_LEFT = 4;
static const int FACE_DOWN = 5;

static const char FACES[] = "UFRBLD";
static const char COLOURS[] = "WGRBOY";


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
        static const std::vector<std::vector<int>> facesToSwap;
        static const std::vector<std::vector<int>> facesToSwapReversed;

        // d: depth, i: i, m: dim-1-depth, f: dim-1-i
        static const std::vector<std::vector<std::vector<char>>> swapInstructions;
        static const std::vector<std::vector<std::vector<char>>> swapInstructionsReversed;

        std::vector<Array2DSquare> faces;
        void cycle(int face, bool reverse, int depth = 0);
        void makeTurn(int face, bool reverse, int depth = 0);
        void parseOneMove(std::string move);

    public:
        int dim;  // todo: should this be std::size_t instead of int?
        CubeModel(int dimension);
        void resetState();
        void resetState(int dimension);
        std::vector<Array2DSquare>& getFaces();
        int getColourAtSticker(int face, int row, int col);
        void coutDisplayNet();
        void parseMoves(std::string moves);
};


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

class Array2DSquare {
    private:
        std::vector<std::vector<int>> array;
        int length;

    public:
        Array2DSquare(int sideLength);
        Array2DSquare(int sideLength, int defaultValue);
        int& at(int row, int col);
        void set(int row, int col, int value);
        void rot90();  // oohhh boy
};

class CubeModel {
    private:
        static const int UP = 0;
        static const int FRONT = 1;
        static const int RIGHT = 2;
        static const int BACK = 3;
        static const int LEFT = 4;
        static const int DOWN = 5;

        static const char numToFace[];
        static const char numToColour[];

        static const std::vector<std::vector<int>> facesToSwap;
        static const std::vector<std::vector<int>> facesToSwapReversed;

        // d: depth, i: i, m: dim-1-depth, f: dim-1-i
        static const std::vector<std::vector<std::vector<char>>> swapInstructions;
        static const std::vector<std::vector<std::vector<char>>> swapInstructionsReversed;

        std::vector<Array2DSquare> faces;
        int dim;
        void cycle(int face, bool reverse, int depth = 0);
        void makeTurn(int face, bool reverse, int depth = 0);
        void repeatChar(char character, int repetitions);

    public:
        CubeModel(int dimension);
        void resetState();
        void resetState(int dimension);
        std::vector<Array2DSquare> getFaces();
        void display();
        void displayNet();
        void parseMoves(std::string moves);
};


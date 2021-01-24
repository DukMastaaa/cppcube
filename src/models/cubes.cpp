#include "models/cubes.h"

#include <iostream>
#include <vector>
#include <sstream>


Array2DSquare::Array2DSquare(int sideLength) {
    array = std::vector<std::vector<int>>(sideLength, std::vector<int>(sideLength));
    length = sideLength;
}


Array2DSquare::Array2DSquare(int sideLength, int defaultValue) {
    array = std::vector<std::vector<int>>(sideLength, std::vector<int>(sideLength, defaultValue));
    length = sideLength;
}


int& Array2DSquare::at(int row, int col) {
    return array[row][col];
}


void Array2DSquare::set(int row, int col, int value) {
    array[row][col] = value;
}


void Array2DSquare::rot90() {
    // Code yoinked from 
    // https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/

    for (int i = 0; i < length / 2; i++) { 
        for (int j = i; j < length - i - 1; j++) { 
            // Swap elements of each cycle in clockwise direction 
            int temp = array[i][j]; 
            array[i][j]                             = array[length - 1 - j][i]; 
            array[length - 1 - j][i]                = array[length - 1 - i][length - 1 - j]; 
            array[length - 1 - i][length - 1 - j]   = array[j][length - 1 - i]; 
            array[j][length - 1 - i]                = temp; 
        } 
    } 
}


const std::vector<std::vector<int>> CubeModel::facesToSwapReversed = {
    {FACE_FRONT, FACE_LEFT, FACE_BACK, FACE_RIGHT},  // FACE_UP
    {FACE_UP, FACE_RIGHT, FACE_DOWN, FACE_LEFT},     // FACE_FRONT
    {FACE_FRONT, FACE_UP, FACE_BACK, FACE_DOWN},     // FACE_RIGHT
    {FACE_UP, FACE_LEFT, FACE_DOWN, FACE_RIGHT},     // FACE_BACK
    {FACE_FRONT, FACE_DOWN, FACE_BACK, FACE_UP},     // FACE_LEFT
    {FACE_FRONT, FACE_RIGHT, FACE_BACK, FACE_LEFT},  // FACE_DOWN
};


const std::vector<std::vector<int>> CubeModel::facesToSwap = {
    {FACE_RIGHT, FACE_BACK, FACE_LEFT, FACE_FRONT},  // FACE_UP
    {FACE_LEFT, FACE_DOWN, FACE_RIGHT, FACE_UP},     // FACE_FRONT
    {FACE_DOWN, FACE_BACK, FACE_UP, FACE_FRONT},     // FACE_RIGHT
    {FACE_RIGHT, FACE_DOWN, FACE_LEFT, FACE_UP},     // FACE_BACK
    {FACE_UP, FACE_BACK, FACE_DOWN, FACE_FRONT},     // FACE_LEFT
    {FACE_LEFT, FACE_BACK, FACE_RIGHT, FACE_FRONT},  // FACE_DOWN
};


// d: depth, i: i, m: dim-1-depth, f: dim-1-i
const std::vector<std::vector<std::vector<char>>> CubeModel::swapInstructionsReversed = {
    {  // FACE_UP
        {'d', 'i'},
        {'d', 'i'},
        {'d', 'i'},
        {'d', 'i'}
    },
    {  // FACE_FRONT
        {'m', 'i'},
        {'i', 'd'},
        {'d', 'f'},
        {'f', 'm'}
    },
    {  // FACE_RIGHT
        {'i', 'm'},
        {'i', 'm'},
        {'f', 'd'},
        {'i', 'm'}
    },
    {  // FACE_BACK
        {'d', 'i'},
        {'f', 'd'},
        {'m', 'f'},
        {'i', 'm'}
    },
    {  // FACE_LEFT
        {'i', 'd'},
        {'i', 'd'},
        {'f', 'm'},
        {'i', 'd'}
    },
    {  // FACE_DOWN
        {'m', 'i'},
        {'m', 'i'},
        {'m', 'i'},
        {'m', 'i'}
    }
};


// d: depth, i: i, m: dim-1-depth, f: dim-1-i
const std::vector<std::vector<std::vector<char>>> CubeModel::swapInstructions = {
    {  // FACE_UP
        {'d', 'i'},
        {'d', 'i'},
        {'d', 'i'},
        {'d', 'i'}
    },
    {  // FACE_FRONT
        {'f', 'm'},
        {'d', 'f'},  //  bug, used to be d m
        {'i', 'd'},
        {'m', 'i'}
    },
    {  // FACE_RIGHT
        {'i', 'm'},
        {'f', 'd'},
        {'i', 'm'},
        {'i', 'm'}
    },
    {  // FACE_BACK
        {'i', 'm'},
        {'m', 'f'},
        {'f', 'd'},
        {'d', 'i'}
    },
    {  // FACE_LEFT
        {'i', 'd'},
        {'f', 'm'},
        {'i', 'd'},
        {'i', 'd'}
    },
    {  // FACE_DOWN
        {'m', 'i'},
        {'m', 'i'},
        {'m', 'i'},
        {'m', 'i'}
    }
};


// CubeModel method implementations
CubeModel::CubeModel(int dimension) {
    faces = std::vector<Array2DSquare>(6, Array2DSquare(dimension));
    dim = dimension;
    resetState();
}


void CubeModel::resetState() {
    for (int i = 0; i < 6; i++) {
        faces[i] = Array2DSquare(dim, i);
    }
}


void CubeModel::resetState(int dimension) {
    dim = dimension;
    resetState();
}


void CubeModel::cycle(int face, bool reverse, int depth) {
    // index -1 is (dim - 1) 

    const std::vector<int>* faceCycle;
    const std::vector<std::vector<char>>* instructions;
    if (reverse) {
        faceCycle = &(facesToSwapReversed[face]);
        instructions = &(swapInstructionsReversed[face]);
    } else {
        faceCycle = &(facesToSwap[face]);
        instructions = &(swapInstructions[face]);
    }

    int* stickers[2];
    int*& thisSticker = stickers[0];
    int*& nextSticker = stickers[1];

    int selectedFaces[2];

    // Keeps track of the value at the buffer because it gets replaced.
    int bufferValue;
    
    for (int layer = 0; layer < dim; layer++) {  // loops over stickers along each layer
        
        for (int cycleStep = 0; cycleStep < 4; cycleStep++) {  // loops over cycle replacements

            selectedFaces[0] = (*faceCycle)[cycleStep];
            if (cycleStep < 3) {  // if statement necessary as index error will be raised if cycleStep == 3
                selectedFaces[1] = (*faceCycle)[cycleStep+1];
            }

            for (int k = 0; k < 2; k++) {  // loops over `this` and `next` stickers
                int rowAndCol[2];

                for (int m = 0; m < 2; m++) {  // loops over row and col swap instructions

                    // this is ridiculous. cycleStep+k is because i need to increment
                    // cycleStep by 1 when looking forward to the next instruction.
                    switch ((*instructions)[cycleStep+k][m]) {
                        case 'd':
                            rowAndCol[m] = depth;
                            break;
                        case 'i':
                            rowAndCol[m] = layer;
                            break;
                        case 'm':
                            rowAndCol[m] = dim - 1 - depth;
                            break;
                        case 'f':
                            rowAndCol[m] = dim - 1 - layer;
                            break;
                    }
                }
                // i have a feeling the line below will cause bugs because 
                // at() returns a reference, and i'm using & on that.
                // note: for the loop where cycleStep == 3, k will only be 0.
                stickers[k] = &(faces[selectedFaces[k]].at(rowAndCol[0], rowAndCol[1]));

                if (cycleStep == 3) {
                    break;  // this is horrible.
                }
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


void CubeModel::makeTurn(int face, bool reverse, int depth) {
    if (depth == 0) {
        for (int i = 0; i < (reverse ? 3 : 1); i++) {
            faces[face].rot90(); 
        }
    }
    cycle(face, reverse, depth);
}


std::vector<Array2DSquare>& CubeModel::getFaces() {
    return faces;
}


int CubeModel::getColourAtSticker(int face, int row, int col) {
    return faces[face].at(row, col);
}


void CubeModel::coutRepeatChar(char character, int repetitions) {
    for (int i = 0; i < repetitions; i++) {
        std::cout << character;
    }
}


void CubeModel::coutDisplayNet() {
    /* Prints a net of the cube to std::cout. */
    // FACE_UP
    for (int row = 0; row < dim; row++) {
        coutRepeatChar(' ', dim + 1);
        for (int col = 0; col < dim; col++) {
            std::cout << COLOURS[faces[FACE_UP].at(row, col)];
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // FACE_LEFT, FACE_FRONT, FACE_RIGHT, FACE_BACK
    const int middleFaces[] = {FACE_LEFT, FACE_FRONT, FACE_RIGHT, FACE_BACK};
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

    // FACE_DOWN
    for (int row = 0; row < dim; row++) {
        coutRepeatChar(' ', dim + 1);
        for (int col = 0; col < dim; col++) {
            std::cout << COLOURS[faces[FACE_DOWN].at(row, col)];
        }
        std::cout << "\n";
    }
}


void CubeModel::parseOneMove(std::string move) {
    // todo: inefficient since it searches multiple times
    int depth, face;
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
        if (move.find(FACES[i]) != std::string::npos) {
            face = i;
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
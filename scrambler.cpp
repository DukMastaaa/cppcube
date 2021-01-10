#include "scrambler.h"
#include <iostream>
#include <stdexcept>
#include <random>


CubeScrambler::CubeScrambler() {
    std::random_device rd;
    std::mt19937 mersenneGenerator(rd());
    std::uniform_int_distribution<int> uniform6(0, 5);  // inclusive
}


const char CubeScrambler::FACES3X3[6] = {
    'U', 'D',      // axis 0
    'F', 'B',      // axis 1
    'R', 'L'       // axis 2
};


const char CubeScrambler::DIRECTIONS[2] = {
    PRIME, DOUBLE
};


int CubeScrambler::getNewAxis(int prevAxis) {
    int newNumber = uniform6(mersenneGenerator) % 2;  // 0 or 1
    switch (prevAxis) {
        case 0:
            return newNumber + 1;  // 1 or 2
            break;
        case 1:
            return newNumber * 2;  // 0 or 2
            break;
        case 2:
            return newNumber;
            break;
    }
}


std::string CubeScrambler::generateMove(int prevAxis, int dim, bool wideAllowed) {
    int newAxis = getNewAxis(prevAxis);
    int addOffset = (dim == 2) ? 0 : uniform6(mersenneGenerator) % 2;
    char faceChar = FACES3X3[newAxis * 2 + addOffset];
    std::string faceString = &faceChar;

    std::string wideTurnDepth;
    std::string wideIndicator;
    if (wideAllowed) {
        std::uniform_int_distribution<int> dist(1, dim / 2);  // int division
        int depth = dist(mersenneGenerator);

        if (depth == 1) {
            wideTurnDepth = "";
            wideIndicator = "";
        } else {
            wideIndicator = "w";
            if (depth > 2) {
                wideTurnDepth = depth;
            }
        }
    }

    int directionModifier = uniform6(mersenneGenerator) % 3;
    char dirChar;
    std::string dirStr;
    if (directionModifier < 2) {
        dirChar = DIRECTIONS[directionModifier];
        dirStr = &dirChar;
    } else {
        dirStr = "";
    }

    return wideTurnDepth + faceString + wideIndicator + dirStr;
}


std::string CubeScrambler::getScramble(int dim) {
    if (dim < 2) {
        throw std::runtime_error("CubeScrambler dim needs to be > 2");
    }



    
}
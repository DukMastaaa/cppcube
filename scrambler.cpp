#include "scrambler.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <utility>


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


std::pair<int, std::string> CubeScrambler::generateMove(int prevAxis, int dim, 
        std::uniform_int_distribution<int>& wideDist) {
    // generates a face on a new axis. dim == 2 restricts to {F, R, U}
    int newAxis = getNewAxis(prevAxis);
    int addOffset = (dim == 2) ? 0 : uniform6(mersenneGenerator) % 2;
    char faceChar = FACES3X3[newAxis * 2 + addOffset];
    std::string faceString = &faceChar;

    std::string wideTurnDepth;
    std::string wideIndicator;
    if (dim >= MIN_WIDE_THRESHOLD) {
        int depth = wideDist(mersenneGenerator);
        if (depth == 1) {
            wideTurnDepth = "";
            wideIndicator = "";
        } else {
            wideIndicator = "w";
            if (depth > 2) {
                wideTurnDepth = std::to_string(depth);
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

    std::string move = wideTurnDepth + faceString + wideIndicator + dirStr;
    return std::make_pair(newAxis, move);
}


std::string CubeScrambler::generateMoveSeq(int dim, 
        std::uniform_int_distribution<int>& wideDist, int moveCount) {
    std::string moves;
    int prevAxis = uniform6(mersenneGenerator) % 3;
    for (int i = 0; i < moveCount; ++i) {
        std::pair<int, std::string> movePair = generateMove(prevAxis, dim, wideDist);
        prevAxis = movePair.first;
        moves += movePair.second;
    }
    return moves;
}


std::string CubeScrambler::getScramble(int dim) {
    if (dim < 2) {
        throw std::runtime_error("CubeScrambler dim needs to be > 2");
    }

    std::uniform_int_distribution<int> wideDist(1, dim / 2);  // floor division
    switch (dim) {
        case 2:
            return generateMoveSeq(2, wideDist, 10);
            break;
        case 3:
            return generateMoveSeq(3, wideDist, 20);  // or 25?
            break;
        case 4:
            // 20 moves without wide moves, 25 moves with
            return generateMoveSeq(3, wideDist, 20) + generateMoveSeq(4, wideDist, 25);
            break;
        default:
            int moveCount = (dim - 2) * 20;
            return generateMoveSeq(dim, wideDist, moveCount);
            break;
    }
}
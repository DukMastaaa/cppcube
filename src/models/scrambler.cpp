#include "models/scrambler.h"

#include <iostream>
#include <stdexcept>
#include <random>
#include <utility>
#include <chrono>


CubeScrambler::CubeScrambler() {
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mersenneGenerator = std::mt19937(seed);
    std::uniform_int_distribution<int> uniform6(0, 5);  // inclusive
    mostRecentScramble = "";
}


const char CubeScrambler::FACES3X3[6] = {
    'U', 'D',      // axis 0
    'F', 'B',      // axis 1
    'R', 'L'       // axis 2
};


const char* CubeScrambler::WIDE = "w";
const char* CubeScrambler::PRIME = "\'";
const char* CubeScrambler::DOUBLE = "2";


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
        default:
            return -1;  // uh oh
    }
}


std::pair<int, std::string> CubeScrambler::generateMove(int prevAxis, int dim, 
        std::uniform_int_distribution<int>& wideDist) {
    // generates a face on a new axis. dim == 2 restricts to {F, R, U}
    int newAxis = getNewAxis(prevAxis);
    int addOffset = (dim == 2) ? 0 : uniform6(mersenneGenerator) % 2;
    char faceChar = FACES3X3[newAxis * 2 + addOffset];
    std::string faceString(1, faceChar);

    std::string wideTurnDepth = "";
    std::string wideIndicator = "";
    if (dim >= MIN_WIDE_THRESHOLD) {
        int depth = wideDist(mersenneGenerator);
        if (depth >= 2) {
            wideIndicator = WIDE;
            if (depth > 2) {
                wideTurnDepth = std::to_string(depth);
            }
        }
    }

    int directionModifier = uniform6(mersenneGenerator) % 3;
    std::string dirStr;
    switch (directionModifier) {
        case 0:
            dirStr = PRIME;
            break;
        case 1:
            dirStr = DOUBLE;
            break;
        default:
            dirStr = "";
            break;
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
        moves += std::string(" ");
    }
    return moves;
}


std::string CubeScrambler::generateScramble(int dim) {
    if (dim < 2) {
        throw std::runtime_error("CubeScrambler dim needs to be > 2");
    }

    std::uniform_int_distribution<int> wideDist(1, dim / 2);  // floor division
    switch (dim) {
        case 2:
            mostRecentScramble = generateMoveSeq(2, wideDist, 10);
            break;
        case 3:
            mostRecentScramble = generateMoveSeq(3, wideDist, 20);  // or 25?
            break;
        case 4:
            // 20 moves without wide moves, 25 moves with
            mostRecentScramble = generateMoveSeq(3, wideDist, 20) + generateMoveSeq(4, wideDist, 25);
            break;
        default:
            int moveCount = (dim - 2) * 20;
            mostRecentScramble = generateMoveSeq(dim, wideDist, moveCount);
            break;
    }

    return mostRecentScramble;
}


std::string& CubeScrambler::getLatestScramble() {
    return mostRecentScramble;
}
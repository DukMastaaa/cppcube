#pragma once
#include <iostream>
#include <random>
#include <utility>


class CubeScrambler {
    private:
        std::mt19937 mersenneGenerator;

        // will preserve uniform distribution of integers
        // using modulo 2 or 3 (since 6 is multiple of both)
        std::uniform_int_distribution<int> uniform6;

        static const char FACES3X3[6];
        static const char* WIDE;
        static const char* PRIME;
        static const char* DOUBLE;
        static const int MIN_WIDE_THRESHOLD = 4;

        std::string mostRecentScramble;  // saves most recent scramble so ScramblerViewModel can access

        int getNewAxis(int prevAxis);
        std::pair<int, std::string> generateMove(int prevAxis, int dim, std::uniform_int_distribution<int>& wideDist);
        std::string generateMoveSeq(int dim, std::uniform_int_distribution<int>& wideDist, int moveCount);

    public:
        CubeScrambler();
        std::string getScramble(int dim);
        std::string& getMostRecentScramble();
};
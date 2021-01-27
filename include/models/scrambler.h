#pragma once

#include <iostream>
#include <random>
#include <utility>


class CubeScrambler {
    private:
        struct MoveAndAxis {
            int axis;
            std::string move;
        };

        static std::mt19937 mersenneGenerator;

        // will preserve uniform distribution of integers
        // using modulo 2 or 3 (since 6 is multiple of both)
        static std::uniform_int_distribution<int> uniform6;

        static std::mt19937 getGenerator();
        static std::uniform_int_distribution<int> getDistribution();

        static const char FACES3X3[6];
        static const char* WIDE;
        static const char* PRIME;
        static const char* DOUBLE;
        static const int MIN_WIDE_THRESHOLD = 4;

        static int getNewAxis(int prevAxis);
        static MoveAndAxis generateMove(int prevAxis, int dim, std::uniform_int_distribution<int>& wideDist);
        static std::string generateMoveSeq(int dim, std::uniform_int_distribution<int>& wideDist, int moveCount);

    public:
        // this entire class can be static except for this member... unsatisfying
        std::string mostRecentScramble;  // saves most recent scramble so ScramblerViewModel can access
        CubeScrambler();
        std::string generateScramble(int dim);
        std::string getLatestScramble() const;
};
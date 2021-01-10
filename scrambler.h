#pragma once
#include <iostream>
#include <random>


class CubeScrambler {
    private:
        static std::mt19937 mersenneGenerator;

        // will preserve uniform distribution of integers
        // using modulo 2 or 3 (since 6 is multiple of both)
        static std::uniform_int_distribution<int> uniform6;

        static const char FACES3X3[6];
        static const char WIDE = 'w';
        static const char PRIME = '\'';
        static const char DOUBLE = '2';
        static const char DIRECTIONS[2];

        static int getNewAxis(int prevAxis);
        std::string generateMove(int prevAxis, int dim, bool wideAllowed);

    public:
        CubeScrambler();
        std::string getScramble(int dim);
};
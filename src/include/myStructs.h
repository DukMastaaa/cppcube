#pragma once

#include <chrono>
#include <iostream>


struct Pos2D {
    int y;  // y-pos or height
    int x;  // x-pos or width
};


enum Penalty {
    NO_PENALTY, PLUS_2_PENALTY, DNF_PENALTY
};


struct Record {
    std::chrono::milliseconds time;
    std::string scramble;
    Penalty penalty;
};
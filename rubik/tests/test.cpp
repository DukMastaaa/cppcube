#include "rubik/rubik.h"
#include "rubik/algs.h"

#include <array>
#include <iostream>

constexpr const std::array<char, 6> colourChars = {'W', 'G', 'R', 'B', 'O', 'Y'};

consteval std::array<rubik::StickerColour, 3*3*6> test() {
    rubik::Cube cube(3);
    cube.applyAlgorithm(rubik::PLL_T); 
    return cube.exportAsArray<3>();
}

int main() {
    auto arr = test();
    rubik::Cube::printNetFromArray<3>(arr, colourChars);
}

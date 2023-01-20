#include "rubik/rubik.h"

#include <array>
#include <iostream>

constexpr const std::array<char, 6> colourChars = {'W', 'G', 'R', 'B', 'O', 'Y'};

consteval std::array<rubik::StickerColour, 3*3*6> test() {
    rubik::Cube cube(3);
    return cube.exportAsArray<3>();
}

int main() {
    auto arr = test();
    rubik::Cube::printNetFromArray<3>(arr, colourChars);
}

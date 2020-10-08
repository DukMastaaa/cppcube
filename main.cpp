#include "cubes.h"
#include <iostream>

int main() {
    int dim;
    std::cout << "dim = ";
    std::cin >> dim;

    CubeModel cube(dim);
    std::string moves;

    while (true) {
        std::cout << "Enter in moves or 'quit':\n";
        std::getline(std::cin, moves);  // can't use cin here because cin separates by space
        if (moves == "quit") {
            break;
        }
        cube.parseMoves(moves);
        cube.displayNet();
    }
    return 0;
}
#include "cubes.h"

int main() {
    CubeModel cube(3);
    cube.parseMoves("");
    cube.display();
    return 0;
}
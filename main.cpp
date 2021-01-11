#include <ncurses.h>
#include <iostream>
#include <random>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"
#include "scrambler.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    startColours();

    // https://stackoverflow.com/a/15509942
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 mersenne(seed);    
    CubeScrambler cs(mersenne);

    CubeModel cube(4);
    std::string scramble = cs.getScramble(4);
    // std::string scramble = "Rw";
    cube.parseMoves(scramble);

    CubeView view(cube);
    view.draw();
    view.wnoutrefresh();
    doupdate();

    wgetch(view.viewWindow);
    endwin();

    std::cout << scramble << '\n';

    return 0;
}
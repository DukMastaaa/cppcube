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

    CubeScrambler cs;
    CubeModel cube(5);
    std::string scramble = cs.getScramble(5);
    cube.parseMoves(scramble);

    waddstr(stdscr, scramble.c_str());

    CubeView view(cube);
    view.draw();
    box(view.viewWindow, '|', '-');
    view.wnoutrefresh();
    doupdate();

    wgetch(view.viewWindow);
    endwin();

    std::cout << scramble << '\n';

    return 0;
}
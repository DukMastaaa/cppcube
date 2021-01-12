#include <ncurses.h>
#include <iostream>
#include <random>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"
#include "scrambler.h"
#include "windowClasses.h"

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

    // waddstr(stdscr, scramble.c_str());
    CubeView vm(cube);
    BottomRightWindow brwin(vm);
    brwin.draw();
    brwin.makeBox();
    brwin.wnoutrefresh();
    doupdate();

    wgetch(brwin.window);
    endwin();

    std::cout << scramble << '\n';

    return 0;
}
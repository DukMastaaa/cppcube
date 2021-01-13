#include <ncurses.h>
#include <iostream>
#include <random>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"
#include "scrambler.h"
#include "windowClasses.h"
#include "scramblerView.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    startColours();

    int dim = 6;

    CubeScrambler cs;
    CubeModel cube(dim);
    std::string scramble = cs.getScramble(dim);
    cube.parseMoves(scramble);


    CubeViewModel cubevm(cube);
    BottomRightWindow brwin(cubevm);
    brwin.draw();
    brwin.makeBox();
    brwin.wnoutrefresh();

    ScramblerViewModel scramblervm(cs);
    DefaultWindow dwin(scramblervm, 0, 0);
    dwin.draw();
    dwin.makeBox();
    dwin.wnoutrefresh();

    doupdate();

    char beans;
    do {
    beans = wgetch(brwin.window);
    } while (beans != 'q');
    endwin();
 
    // std::cout << scramble << '\n';

    return 0;
}
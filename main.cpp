#include <ncurses.h>
#include <iostream>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    startColours();
    /*
    int beforeX, beforeY;
    getmaxyx(stdscr, beforeY, beforeX);
    WINDOW* meow = newwin(5, 5, 0, 0);
    int afterX, afterY;
    getmaxyx(stdscr, afterY, afterX);
    int lolx, loly;
    getmaxyx(meow, lolx, loly);
    endwin();
    std::cout << beforeX << ' ' << beforeY << '\n';
    std::cout << afterX << ' ' << afterY << '\n';
    std::cout << lolx << ' ' << loly << '\n';
    */
    CubeModel cube(7);
    cube.parseMoves(std::string("R U R' U'"));
    CubeView view(cube);
    view.draw();
    view.wnoutrefresh();
    doupdate();

    wgetch(view.viewWindow);
    endwin();

    return 0;
}
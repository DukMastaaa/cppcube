#include <ncurses.h>
#include <iostream>
#include <utility>
#include "scramblerViewModel.h"
#include "scrambler.h"


Pos2D ScramblerViewModel::calcHeightWidth() {
    // currently constant return value, will adapt later for larger scramble size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxY;  // maxY unused - doesn't matter here
    return {4, maxX - 2};
}


ScramblerViewModel::ScramblerViewModel(CubeScrambler& scramblerRef) : scrambler(scramblerRef) {}


void ScramblerViewModel::draw(WINDOW* window) {
    // to be modified - format scramble properly, only break line on space
    std::string s = scrambler.getMostRecentScramble();
    mvwprintw(window, 0, 0, s.c_str());
}


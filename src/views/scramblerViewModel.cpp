#include "views/scramblerViewModel.h"

#include <iostream>
#include <utility>

#include <ncurses.h>

#include "models/scrambler.h"
#include "myStructs.h"


Pos2D ScramblerViewModel::calcHeightWidth() {
    // currently constant return value, will adapt later for larger scramble size
    unsigned maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxY;  // maxY unused - doesn't matter here
    return {4, maxX - 2};
}


ScramblerViewModel::ScramblerViewModel(CubeScrambler& scramblerRef) : scrambler(scramblerRef) {}


void ScramblerViewModel::draw(WINDOW* window) {
    std::string s = scrambler.getMostRecentScramble();
    smartStringDisplay(window, s);
}


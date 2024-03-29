#include "views/normal/scramblerViewModel.h"

#include <iostream>
#include <utility>

#include <ncurses.h>

#include "models/scrambler.h"
#include "myStructs.h"


Pos2D ScramblerViewModel::calcHeightWidth() const {
    // currently constant return value, will adapt later for larger scramble size
    unsigned maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxY;  // maxY unused - doesn't matter here
    return {6, 45};
}


ScramblerViewModel::ScramblerViewModel(const CubeScrambler& scramblerRef) : scrambler(scramblerRef) {}


void ScramblerViewModel::draw(WINDOW* window) const {
    /* Erases and draws scrambler window. */
    werase(window);
    std::string s = scrambler.getLatestScramble();
    smartStringDisplay(window, s);
}
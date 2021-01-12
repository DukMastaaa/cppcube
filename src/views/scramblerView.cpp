#include <ncurses.h>
#include <iostream>
#include <utility>
#include "scramblerView.h"
#include "scrambler.h"


std::pair<int, int> ScramblerViewModel::calcHeightWidth() {
    // currently constant return value, will adapt later for larger scramble size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    return std::make_pair(3 + 2 * BORDER_THICKNESS, maxX - 2 * BORDER_THICKNESS);
}


ScramblerViewModel::ScramblerViewModel(CubeScrambler& scramblerRef) : scrambler(scramblerRef) {}


void ScramblerViewModel::draw(WINDOW* window) {
    std::string& s = scrambler.getMostRecentScramble();
    mvwprintw(window, 1, 1, s.c_str());
    // waddstr(window, "beans");
}


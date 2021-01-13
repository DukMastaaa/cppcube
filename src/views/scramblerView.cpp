#include <ncurses.h>
#include <iostream>
#include <utility>
#include "scramblerView.h"
#include "scrambler.h"


std::pair<int, int> ScramblerViewModel::calcHeightWidth() {
    // currently constant return value, will adapt later for larger scramble size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxY;  // maxY unused - doesn't matter here
    return std::make_pair(3, maxX - 2);
}


ScramblerViewModel::ScramblerViewModel(CubeScrambler& scramblerRef) : scrambler(scramblerRef) {}


void ScramblerViewModel::draw(WINDOW* window) {
    std::string s = scrambler.getMostRecentScramble();
    // std::string s = scrambler.beans;
    // int max = s.length();
    // for (int h = 0; h < max; h++) {
    //     mvwaddch(window, 1, h + 1, s.at(h));
    // }
    mvwprintw(window, 0, 0, s.c_str());
    // waddstr(window, "beans");
}


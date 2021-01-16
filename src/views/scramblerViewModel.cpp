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
    std::string s = scrambler.mostRecentScramble;
    // smartStringDisplay(window, "a b c d e f gs d s df sdfsdfsdfs fsdfsdf sdf sdfs dfsdfsd fsdf sdf sdfsdfs fad as AAAA AA beans beans meow beans meows oh boy big ch ungus woo hoo");
    smartStringDisplay(window, s);
}


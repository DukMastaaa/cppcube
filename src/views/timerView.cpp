#include <ncurses.h>
#include <utility>
#include "timerView.h"
#include "cubeTimer.h"
#include "position.h"


const std::string TimerViewModel::NUM_BLOCK[10][5] = {
    {
        "###",
        "# #",
        "# #",
        "# #",
        "###",
    },
    {
        "## ",
        " # ",
        " # ",
        " # ",
        "###",
    },
    {
        "## ",
        "  #",
        " # ",
        "#  ",
        "###",
    },
    {
        "## ",
        "  #",
        "## ",
        "  #",
        "## ",
    },
    {
        "# #",
        "# #",
        "###",
        "  #",
        "  #",
    },
    {
        "###",
        "#  ",
        "###",
        "  #",
        "###",
    },
    {
        "###",
        "#  ",
        "###",
        "# #",
        "###",
    },
    {
        "###",
        "  #",
        "  #",
        "  #",
        "  #",
    },
    {
        "###",
        "# #",
        "###",
        "# #",
        "###",
    },
    {
        "###",
        "# #",
        "###",
        "  #",
        "  #",
    }
};


const std::string TimerViewModel::FULL_STOP[5] = {
    " ",
    " ",
    " ",
    " ",
    "#"
};


const std::string TimerViewModel::COLON[5] = {
    " ",
    "#",
    " ",
    "#",
    " "
};


const std::string TimerViewModel::PLUS[5] = {
    "   ",
    " # ",
    "###",
    " # ",
    "   "
};


Pos2D TimerViewModel::calcHeightWidth() {
    return {5, 31};  // hardcode for now
}


TimerViewModel::TimerViewModel(CubeTimer& timerRef) : timer(timerRef) {}


void TimerViewModel::draw(WINDOW* window) {
    return;
}
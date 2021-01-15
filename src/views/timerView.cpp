#include <ncurses.h>
#include <chrono>
#include <array>
#include "timerView.h"
#include "cubeTimer.h"
#include "position.h"
#include "colours.h"


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


std::array<int, 3> TimerViewModel::getTimesAsStr(std::chrono::milliseconds elapsedTime) {
    /* Changes milliseconds to string representation of equivalent minutes:seconds.centiseconds. */
    namespace chrono = std::chrono;
    static const int millisecToSec = 1000;

    int min = chrono::duration_cast<chrono::minutes>(elapsedTime).count();
    int sec, centisec;
    if (min >= 100) {  // wrap at 100 min
        min = 99;
        sec = 59;
        centisec = 99;
    } else {
        sec = chrono::duration_cast<chrono::seconds>(elapsedTime).count() % 60;
        centisec = (elapsedTime.count() % millisecToSec) / 10;  // round instead of floor div?
    }
    return {min, sec, centisec};
}


void TimerViewModel::drawCharMatrix(WINDOW* window, std::array<int, 3> times) {
    for (int row = 0; row < 5; row++) {
        int xPos = 0;
        for (int timeSelector = 0; timeSelector < 3; timeSelector++) {
            int time = times[timeSelector];
            int tens, ones;
            if (time < 10) {
                tens = 0;
                ones = time;
            } else {
                tens = time / 10;
                ones = time % 10;
            }
            int digits[2] = {tens, ones};

            // actual digits
            for (int placeVal = 0; placeVal < 2; placeVal++) {
                for (char block : NUM_BLOCK[digits[placeVal]][row]) {
                    // inverse colour - switch symbols around
                    block = (block == '#') ? ' ' : '█';
                    wattron(window, COLOR_PAIR(BLACK_ON_WHITE));
                    mvwaddch(window, row, xPos, block);
                    wattroff(window, COLOR_PAIR(BLACK_ON_WHITE));
                    xPos++;
                }
                mvwaddch(window, row, xPos, ' ');  // spacing
                xPos++;
            }

            // punctuation
            if (timeSelector < 2) {
                const std::string* punctuation = (timeSelector == 0) ? COLON : FULL_STOP;
                for (const char& symbol : punctuation[row]) {
                    mvwaddch(window, row, xPos, symbol);
                    xPos++;
                }
                mvwaddch(window, row, xPos, ' ');  // spacing
                xPos++;
            }
        }
    }
}


void TimerViewModel::draw(WINDOW* window) {
    std::array<int, 3> times = getTimesAsStr(timer.getTimeElapsed());
    drawCharMatrix(window, times);
}
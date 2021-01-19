#include "timerViewModel.h"

#include <chrono>
#include <array>

#include <ncurses.h>

#include "cubeTimer.h"
#include "myStructs.h"
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


const std::string TimerViewModel::DNF[5] = {
    "##      ###",
    "# # ### #  ",
    "# # # # ###",
    "# # # # #  ",  
    "##  # # #  ",
};


Pos2D TimerViewModel::calcHeightWidth() {
    return {5, 31};  // hardcode for now
}


TimerViewModel::TimerViewModel(CubeTimer& timerRef) : timer(timerRef) {}


std::array<int, 3> TimerViewModel::getTimeDivisions(std::chrono::milliseconds elapsedTime) {
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


void TimerViewModel::drawCharMatrix(WINDOW* window, std::array<int, 3> times, bool plus2) {
    for (int row = 0; row < 5; row++) {
        int xPos = (plus2) ? 0 : 2;  // aligns time properly
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
                    // block = (block == '#') ? ' ' : '█';
                    int colour = (block == '#') ? GREEN_ON_BLACK : WHITE_ON_BLACK;
                    wattron(window, COLOR_PAIR(colour));
                    mvwaddch(window, row, xPos, block);
                    wattroff(window, COLOR_PAIR(colour));
                    xPos++;
                }
                mvwaddch(window, row, xPos, ' ');  // spacing
                xPos++;
            }

            // punctuation
            const std::string* punctuation;
            switch (timeSelector) {
                case 0:
                    punctuation = COLON;
                    break;
                case 1:
                    punctuation = FULL_STOP;
                    break;
                case 2:
                    punctuation = PLUS;
                    break;
            }
            if (timeSelector != 2 || plus2) {
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


void TimerViewModel::drawEllipsis(WINDOW* window) {
    for (int col = 0; col < 5; col += 2) {
        mvwaddch(window, 4, col, '#');
    }
}


void TimerViewModel::drawDNF(WINDOW* window) {
    for (int row = 0; row < 5; row++) {
        mvwprintw(window, row, 0, DNF[row].c_str());
    }
}


void TimerViewModel::draw(WINDOW* window) {
    namespace chrono = std::chrono;
    if (!timer.isTiming) {
        if (timer.currentPenalty == DNF_PENALTY) {
            drawDNF(window);
        } else {
            bool plus2 = (timer.currentPenalty == PLUS_2_PENALTY);
            chrono::seconds offset = (plus2) ? chrono::seconds(2) : chrono::seconds(0);
            std::array<int, 3> times = getTimeDivisions(timer.getTimeElapsed() + offset);
            drawCharMatrix(window, times, plus2);
        }
    } else {
        drawEllipsis(window);
    }
}
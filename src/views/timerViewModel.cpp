#include "views/timerViewModel.h"

#include <chrono>
#include <array>

#include <ncurses.h>

#include "models/cubeTimer.h"
#include "myStructs.h"
#include "views/colours.h"


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


void TimerViewModel::drawCharMatrix(WINDOW* window, std::array<int, 3> times, bool plus2) {
    // todo: move RLVM::formatTime to CubeTimer::formatTime and iterate over char. this is partially duplicated code
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
    /* Erases and draws timer window. */
    if (!timer.isTiming) {
        wclear(window);  // clear instead of erase to prevent window corruption
        if (timer.currentPenalty == DNF_PENALTY) {
            drawDNF(window);
        } else {
            bool plus2 = (timer.currentPenalty == PLUS_2_PENALTY);
            auto offset = (plus2) ? std::chrono::seconds(2) : std::chrono::seconds(0);
            std::array<int, 3> times = CubeTimer::getTimeDivisions(timer.getTimeElapsed() + offset);
            drawCharMatrix(window, times, plus2);
        }
    } else {
        werase(window);  // full refresh not needed, erase will suffice
        drawEllipsis(window);
    }
}
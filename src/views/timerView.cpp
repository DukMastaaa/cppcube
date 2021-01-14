#include <ncurses.h>
#include <chrono>
#include <array>
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


std::array<std::string, 3> TimerViewModel::getTimesAsStr(std::chrono::milliseconds elapsedTime) {
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

    int timesAsInt[3] = {min, sec, centisec};
    std::array<std::string, 3> times;
    for (int i = 0; i < 3; i++) {
        int this_time = timesAsInt[i];
        if (this_time < 10) {
            times[i] = '0' + std::to_string(this_time);
        } else {
            times[i] = std::to_string(this_time);
        }
    }

    return times;
}


void TimerViewModel::drawCharMatrix(WINDOW* window, std::array<std::string, 3> times) {
    // wip
}


void TimerViewModel::draw(WINDOW* window) {
    std::array<std::string, 3> times = getTimesAsStr(timer.getTimeElapsed());
    std::string beans = times[0] + ':' + times[1] + '.' + times[2];  // just for now
    waddstr(window, beans.c_str());

    // drawCharMatrix(window, times);
}
/* No .cpp file for this header. */

#pragma once

#include <chrono>
#include <iostream>
#include <functional>


struct Pos2D {
    unsigned int y;  // y-pos or height
    unsigned int x;  // x-pos or width
};


enum Penalty {
    NO_PENALTY, PLUS_2_PENALTY, DNF_PENALTY
};


struct Record {
    std::chrono::milliseconds time;
    std::string scramble;
    Penalty penalty;
};


enum Direction {  // do i really need this
    UP_DIR = 'u', DOWN_DIR = 'd', LEFT_DIR = 'l', RIGHT_DIR = 'l'
};


// used to define what state a popup window is in after keyboard input.
enum PopupState {
    REFRESH, NOREFRESH, CLOSE, RESIZE
};


// typedef void (*PopupCallback)(std::string);
typedef std::function<void (std::string)> PopupCallback;


void dummyPopupCallback(std::string returnVal);
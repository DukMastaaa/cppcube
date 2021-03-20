/* No .cpp file for this header. */

#pragma once

#include <ncurses.h>

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
    public:
        std::chrono::milliseconds time;
        std::string scramble;
        Penalty penalty;

        static bool staticIsDNF(const Record& record);  // todo: is this needed over normal isDNF?
        bool isDNF() const;
        std::chrono::milliseconds getFinalTime() const;
        bool operator<(const Record& otherRecord) const;
        bool operator>(const Record& otherRecord) const;

        std::string getFormattedTime() const;
        static std::string getFormattedTime(std::chrono::milliseconds time, Penalty penalty);

    private:
        static std::array<int, 3> getTimeDivisions(std::chrono::milliseconds elapsedTime);
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


constexpr const int KEY_ESCAPE = 7;
#pragma once

#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <functional>


// if terminal supports, displays █, otherwise #
// i've never seen it display as the full block char.
#define BLOCK_CHAR ACS_BLOCK
// #define BLOCK_CHAR ACS_CKBOARD
// #define BLOCK_CHAR '█'



/**
 * @brief Represents a 2D position.
 */
struct Pos2D {
    unsigned int y;  ///< y-position or height
    unsigned int x;  ///< y-position or width
};


/**
 * @brief Represents a penalty applied to a solve.
 */
enum Penalty {
    NO_PENALTY, PLUS_2_PENALTY, DNF_PENALTY
};


/**
 * @brief Represents the results of a solve.
 */
struct Record {
    public:
        std::chrono::milliseconds time;  ///< Time taken for solve, ignoring penalties
        std::string scramble;  ///< Scramble used for the solve
        Penalty penalty;  ///< Penalty applied to solve

        /**
         * @brief Calculate the solve time accounting for penalties.
         * @return Solve time after penalties applied.
         */
        std::chrono::milliseconds getFinalTime() const;

        /**
         * @brief Returns if this record's solve time is less than the other, accounting for penalties.
         * @param otherRecord The other record to compare with.
         */
        bool operator<(const Record& otherRecord) const;

        /**
         * @brief Returns if this record's solve time is more than the other, accounting for penalties.
         * @param otherRecord The other record to compare with.
         */
        bool operator>(const Record& otherRecord) const;

        /**
         * @brief Checks if the supplied record has a DNF penalty.
         * @param record Record to check.
         */
        static bool isDNF(const Record& record);

        /**
         * @brief Returns the time and penalty formatted as a string.
         * @param time Solve time.
         * @param penalty Solve penalty.
         * @return Either the literal `"DNF"`, or `"mm:ss.cc"` with optional trailing + indicating +2. 
         */
        static std::string getFormattedTime(std::chrono::milliseconds time, Penalty penalty);

        /**
         * @brief Returns a penalty formatted as a string.
         * @param penalty 
         * @return std::string 
         */
        static std::string penaltyAsString(Penalty penalty);
        static std::chrono::milliseconds timeDivisionsToTime(int minutes, int seconds, int centiseconds);

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


constexpr const int KEY_ESCAPE = 27;
constexpr const int KEY_WEIRD_BACKSPACE = 127;  // weird
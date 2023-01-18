/**
 * @file myStructs.h
 * @brief Contains structs and enums used throughout the program.
 */


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
 * @brief Represents a 2D position. Used for either coordinates or heights/widths.
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
         * @brief Returns the time and penalty formatted as a string.
         * @return Either the literal `"DNF"`, or `"mm:ss.cc"` with optional trailing + indicating +2. 
         */
        std::string getFormattedTime();

        /**
         * @brief Returns a penalty formatted as a string.
         * @param penalty Solve penalty.
         * @return Either `"NONE"`, `"+2"` or `"DNF"`.
         */
        static std::string penaltyAsString(Penalty penalty);

        /**
         * @brief Converts minutes, seconds and centiseconds to milliseconds.
         * @param minutes Minutes portion of total time.
         * @param seconds Seconds portion of total time.
         * @param centiseconds Centiseconds portion of total time.
         * @return Total time in milliseconds.
         */
        static std::chrono::milliseconds timeDivisionsToMilliseconds(int minutes, int seconds, int centiseconds);

    private:

        /**
         * @brief Converts total time in milliseconds to minutes, seconds and centiseconds.
         * @param time Total time in milliseconds.
         * @return Array containing total time in minutes, seconds, centiseconds, rounded down to nearest unit.
         */
        static std::array<int, 3> millisecondsToTimeDivisions(std::chrono::milliseconds time);
};


/**
 * @brief Represents the external state of a popup window after some sort of input.
 * 
 * Popup view models return a `PopupState` value when:
 * - the window refreshes
 * - a button is pressed
 * - data is passed to the window
 */
enum PopupState {
    REFRESH, NOREFRESH, CLOSE, RESIZE
};


// typedef void (*PopupCallback)(std::string);

/**
 * @brief Typedef for functions that get called when popups close.
 * 
 * The ``std::string`` parameter contains data returned from the popup view model.
 */
typedef std::function<void (std::string)> PopupCallback;


/**
 * @brief A blank popup callback used when popups don't return anything needed.
 * @param returnVal Unused parameter.
 */
void dummyPopupCallback(std::string returnVal);


constexpr const int KEY_ESCAPE = 27;  ///< Key code for escape key
constexpr const int KEY_WEIRD_BACKSPACE = 127;  ///< Key code for backspace used by some terminals
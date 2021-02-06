#include "views/baseViewModel.h"

#include <iostream>
#include <sstream>

#include <ncurses.h>


void BaseViewModel::receiveKeyboardInput(int input) {
    /* Default behaviour is to do nothing. */
    (void) input;  // unused
    return;
}


void BaseViewModel::smartStringDisplay(WINDOW* window, const std::string& text) {
    /* Writes the text to window but breaks the line on a space, 
    not in the middle of a word, unlike `wprintw`. */
    std::stringstream stream(text);
    std::string word;
    int maxY, maxX;
    int row = 0;
    int col = 0;
    getmaxyx(window, maxY, maxX);
    (void) maxY;  // unused

    while (stream >> word) {
        if (word != " ") {
            int wordLen = word.length();
            if (col >= maxX || col + wordLen >= maxX) {
                row++;
                col = 0;
            }

            mvwaddstr(window, row, col, word.c_str());  // this may not work
            col += wordLen + 1;
        }
    }
}
#include "baseViewModel.h"
#include <iostream>
#include <sstream>
#include <ncurses.h>


void BaseViewModel::smartStringDisplay(WINDOW* window, std::string text) {
    /* Writes the text to window but breaks the line on a space, 
    not in the middle of a word, unlike `wprintw`. */
    std::stringstream stream(text);
    std::string word;
    int maxY, maxX, row, col;
    getmaxyx(window, maxY, maxX);

    // wprintw(window, "%d %d beans", maxY, maxX);

    while (stream >> word) {
        if (word != " ") {
            int wordLen = word.length();
            if (col >= maxX || col + wordLen >= maxX) {
                row++;
                col = 0;
            }

            for (const char& ch : word) {
                mvwaddch(window, row, col, ch);
                // mvwaddstr(window, row, col, "hi");
                col += 1;
            }
            col += 1;
            // mvwaddstr(window, row, col, word.c_str());  // this may not work
            // col += wordLen;  // already includes space afterward
        }
    }
}



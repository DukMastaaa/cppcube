#include "views/baseViewModel.h"

#include <iostream>
#include <sstream>

#include <ncurses.h>


// BaseViewModel::BaseViewModel(BaseModel& modelRef) : model(modelRef) {}
BaseViewModel::BaseViewModel() {}


PopupState BaseViewModel::receiveKeyboardInput(int input) {
    /* Default behaviour is to do nothing unless enter key pressed,
    which closes window. 
    
    This method should not be called unless this view model is in a 
    window used as a popup.
    */

    if (input == '\n' || input == 27) {  // 27 is escape key
        return PopupState::CLOSE;
    } else {
        return PopupState::NOREFRESH;
    }
}


std::string BaseViewModel::getPopupReturnData() const {
    /* This method returns the data stored in the popup window, ready to be
    sent to the popup window below (or App class). This method should be called
    immediately before the window is closed. */

    return "";
}


PopupState BaseViewModel::receiveData(std::string data) {
    (void) data;  // unused
    return PopupState::REFRESH;
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
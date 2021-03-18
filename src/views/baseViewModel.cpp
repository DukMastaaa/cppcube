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


void BaseViewModel::smartStringDisplay(WINDOW* window, const std::string& text, int startRow, int startCol, int maxLines) {
    /* Writes the text to window but breaks the line on a space, 
    not in the middle of a word, unlike `wprintw`. 
    
    Can change behaviour by specifying the starting row and column, as well as
    the maximum number of lines it will write.
    */

    std::stringstream stream(text);
    std::string word;
    int maxY, maxX;
    int row = startRow;
    int col = startCol;
    getmaxyx(window, maxY, maxX);
    (void) maxY;  // unused

    while (stream >> word) {
        if (word != " ") {
            int wordLen = word.length();
            if (col >= maxX || col + wordLen >= maxX) {
                row++;
                col = 0;
            }
            
            if (maxLines != -1 && row - startRow >= maxLines) {
                break;
            }

            mvwaddstr(window, row, col, word.c_str());  // todo: possible bug where it writes past the edge for first word?
            col += wordLen + 1;
        }
    }
}
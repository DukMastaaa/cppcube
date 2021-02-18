#include "views/popups/inputPopupViewModel.h"

#include <ncurses.h>

#include <algorithm>

#include "views/baseViewModel.h"


InputPopupViewModel::InputPopupViewModel() : BaseViewModel(), inputText{}, description{} {}


Pos2D InputPopupViewModel::calcHeightWidth() const {
    return {5, std::max<unsigned int>(20, description.length())};
}


void InputPopupViewModel::draw(WINDOW* window) const {
    werase(window);
    mvwprintw(window, 0, 0, description.c_str());
    mvwprintw(window, 1, 0, inputText.c_str());
}


PopupState InputPopupViewModel::receiveKeyboardInput(int input) {
    switch (input) {
        case KEY_BACKSPACE:
        // case KEY_DC:  // what's the difference
            if (inputText.length() != 0) {
                inputText.pop_back();
            }
            break;
        case KEY_ENTER:
            return PopupState::CLOSE;
        default:
            inputText.push_back(static_cast<char>(input));
            break;
    }
    return PopupState::REFRESH;
}


std::string InputPopupViewModel::getPopupReturnData() {
    return inputText;
}


void InputPopupViewModel::receiveData(std::string data) {
    description = data;
    // force resize?
}
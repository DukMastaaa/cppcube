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


bool InputPopupViewModel::isCharAllowed(int charInput) const {
    /* All characters on US keyboard. */
    return (' ' <= charInput) && (charInput <= '~');
}


PopupState InputPopupViewModel::receiveKeyboardInput(int input) {
    switch (input) {
        case KEY_BACKSPACE:
        // case KEY_DC:  // what's the difference
            if (inputText.length() != 0) {
                inputText.pop_back();
            }
            break;
        case '\n':
            return PopupState::CLOSE;
        default:
            if (isCharAllowed(input)) {
                inputText.push_back(static_cast<char>(input));
            }
            break;
    }
    return PopupState::REFRESH;
}


std::string InputPopupViewModel::getPopupReturnData() const {
    return inputText;
}


PopupState InputPopupViewModel::receiveData(std::string data) {
    description = data;
    return PopupState::RESIZE;
}


NumericInputPopupViewModel::NumericInputPopupViewModel() : InputPopupViewModel() {}


bool NumericInputPopupViewModel::isCharAllowed(int charInput) const {
    return ('0' <= charInput) && (charInput <= '9');
}


YesNoPopupViewModel::YesNoPopupViewModel() : InputPopupViewModel() {}


PopupState YesNoPopupViewModel::receiveKeyboardInput(int input) {
    inputText = isCharAllowed(input) ? "yes" : "no";
    return PopupState::CLOSE;
}


bool YesNoPopupViewModel::isCharAllowed(int input) const {
    return (input == 'y');
}
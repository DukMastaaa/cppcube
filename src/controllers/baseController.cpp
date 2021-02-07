#include "controllers/baseController.h"

#include <ncurses.h>


BaseController::BaseController() {}


WINDOW* BaseController::getWindow() const {
    return window->fullWindow;
}


void BaseController::refresh() const {
    window->draw();
    window->wnoutrefresh();
    touchwin(window->fullWindow);
}


void BaseController::handleResize() {
    window->handleResize();
}


void BaseController::receiveKeyboardInput(int input) {
    PopupState popupState = window->receiveKeyboardInput(input);
    switch (popupState) {
        case PopupState::CLOSE:
            break;
        
        case PopupState::NOREFRESH:
            break;
        
        case PopupState::REFRESH:
            break;
    }
}
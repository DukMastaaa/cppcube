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
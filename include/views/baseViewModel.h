#pragma once

#include <iostream>
#include <utility>

#include <ncurses.h>

#include "myStructs.h"


enum PopupState {  // todo: move to better place?
    REFRESH, NOREFRESH, CLOSE
};


class BaseViewModel {
    protected:
        static const int BORDER_THICKNESS = 1;

    public:
        static void smartStringDisplay(WINDOW* window, const std::string& text);
        virtual Pos2D calcHeightWidth() const = 0;  // don't take borders into account
        virtual void draw(WINDOW* window) const = 0;
        virtual PopupState receiveKeyboardInput(int input);
};
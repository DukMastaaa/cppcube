#pragma once

#include <iostream>
#include <utility>

#include <ncurses.h>

#include "myStructs.h"


class BaseViewModel {
    protected:
        static const int BORDER_THICKNESS = 1;

    public:
        static void smartStringDisplay(WINDOW* window, const std::string& text);
        virtual Pos2D calcHeightWidth() const = 0;  // don't take borders into account
        virtual void draw(WINDOW* window) const = 0;

        // popup-specific stuff

        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();
};
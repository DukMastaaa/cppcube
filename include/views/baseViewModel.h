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
        virtual Pos2D calcHeightWidth() = 0;  // don't take borders into account
        virtual void draw(WINDOW* window) = 0;
};
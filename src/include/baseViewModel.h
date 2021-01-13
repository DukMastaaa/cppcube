#pragma once
#include <ncurses.h>
#include <utility>
#include "position.h"


class BaseViewModel {
    protected:
        static const int BORDER_THICKNESS = 1;

    public:
        virtual Pos2D calcHeightWidth() = 0;  // don't take borders into account
        virtual void draw(WINDOW* window) = 0;
};
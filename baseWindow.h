#pragma once
#include <ncurses.h>


class BaseWindow {
    public:
        WINDOW* viewWindow;
        virtual void draw() = 0;
        void wnoutrefresh();
};
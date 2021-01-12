#pragma once
#include <ncurses.h>
#include <utility>


class BaseViewModel {
    protected:
        static const int BORDER_THICKNESS = 1;

    public:
        virtual std::pair<int, int> calcHeightWidth() = 0;
        virtual void draw(WINDOW* window) = 0;
};
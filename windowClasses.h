#pragma once
#include <ncurses.h>
#include <utility>
#include "baseViewModel.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;

    public:
        WINDOW* window;
        BaseWindow(BaseViewModel& vm);
        void wnoutrefresh();
        void makeBox();
        void draw();
};


class BottomRightWindow : public BaseWindow {
    public:
        static std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth);
        BottomRightWindow(BaseViewModel& vm);
};
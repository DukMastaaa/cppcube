#pragma once
#include <ncurses.h>
#include <utility>
#include "baseViewModel.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;

    public:
        WINDOW* window;
        virtual std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth) = 0;
        BaseWindow(BaseViewModel& vm);
        void wnoutrefresh();
        void makeBox();
        void draw();
};


class BottomRightWindow : public BaseWindow {
    public:
        std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth);
        BottomRightWindow(BaseViewModel& vm);
};


class CentredPopupWindow : public BaseWindow {
    public:
        std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth);
        CentredPopupWindow(BaseViewModel& vm);
};


class DefaultWindow : public BaseWindow {
    public:
        std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth);
        DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX);
};
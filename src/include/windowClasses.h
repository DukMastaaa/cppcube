#pragma once
#include <ncurses.h>
#include <utility>
#include "baseViewModel.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;
        static const int BORDER_WIDTH = 1;
        static std::pair<int, int> addIntToPair(std::pair<int, int> pair, int num);

    public:
        WINDOW* window;
        WINDOW* subwin;
        virtual std::pair<int, int> calcTopLeftPos(std::pair<int, int> heightAndWidth) = 0;
        BaseWindow(BaseViewModel& vm);
        void createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX);
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
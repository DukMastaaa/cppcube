#pragma once
#include <ncurses.h>
#include <utility>
#include "baseViewModel.h"
#include "position.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;
        static const int BORDER_WIDTH = 1;
        static Pos2D addIntToPos(Pos2D pos, int num);

    public:
        WINDOW* window;
        WINDOW* subwin;
        virtual Pos2D calcTopLeftPos(Pos2D heightAndWidth) = 0;
        BaseWindow(BaseViewModel& vm);
        void createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX);
        void wnoutrefresh();
        void makeBox();
        void draw();
        ~BaseWindow();
};


class BottomRightWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        BottomRightWindow(BaseViewModel& vm);
};


class CentredPopupWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        CentredPopupWindow(BaseViewModel& vm);
};


class DefaultWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX);
};
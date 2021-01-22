#pragma once

#include <utility>

#include <ncurses.h>

#include "baseViewModel.h"
#include "myStructs.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;
        static const int BORDER_WIDTH = 1;
        static Pos2D addIntToPos(Pos2D pos, int num);
        void standardInit(BaseViewModel& vm);

    public:
        WINDOW* window;
        WINDOW* subwin;
        virtual Pos2D calcTopLeftPos(Pos2D heightAndWidth) = 0;
        BaseWindow(BaseViewModel& vm);
        void createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX);
        void wnoutrefresh();
        void makeBox();
        void draw();
        void wclear();
        void werase();
        void fullRefresh(bool drawBox = true, bool clear = true, bool erase = false);
        ~BaseWindow();
};


class BottomRightWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        BottomRightWindow(BaseViewModel& vm);
};


class BottomLeftWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        BottomLeftWindow(BaseViewModel& vm);
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
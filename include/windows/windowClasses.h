#pragma once

#include <utility>

#include <ncurses.h>

#include "views/baseViewModel.h"
#include "myStructs.h"


class BaseWindow {
    protected:
        BaseViewModel& viewModel;
        static const int BORDER_WIDTH = 1;
        static Pos2D addIntToPos(Pos2D pos, int num);
        void standardInit(BaseViewModel& vm);
        void createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX);

    public:
        WINDOW* fullWindow;
        WINDOW* subwin;
        virtual Pos2D calcTopLeftPos(Pos2D heightAndWidth) = 0;
        BaseWindow(BaseViewModel& vm);
        void wnoutrefresh();
        void makeBox();
        void draw();
        void wclear();  // forces refresh
        void werase();  // doesn't force refresh
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


class CentredWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        CentredWindow(BaseViewModel& vm);
};


class DefaultWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth);
        DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX);
};
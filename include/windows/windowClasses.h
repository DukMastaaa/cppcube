#pragma once

#include <utility>
#include <iostream>

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
        void createSubwin(int fullHeight, int fullWidth);

    public:
        WINDOW* fullWindow;
        WINDOW* subwin;
        virtual Pos2D calcTopLeftPos(Pos2D heightAndWidth) const;
        virtual Pos2D calcHeightAndWidth(BaseViewModel& vm) const;
        BaseWindow(BaseViewModel& vm);
        void wnoutrefresh() const;
        void makeBox() const;
        void draw() const;
        void title(std::string titleText) const;
        void wclear() const;  // forces refresh
        void werase() const;  // doesn't force refresh
        virtual void handleResize();

        // popup-specific

        PopupState receiveKeyboardInput(int input);
        std::string getPopupReturnData();
        PopupState receiveData(std::string data);

        ~BaseWindow();
};


class BottomRightWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth) const override;
        BottomRightWindow(BaseViewModel& vm);
};


class BottomLeftWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth) const override;
        BottomLeftWindow(BaseViewModel& vm);
};


class CentredWindow : public BaseWindow {
    public:
        Pos2D calcTopLeftPos(Pos2D heightAndWidth) const override;
        CentredWindow(BaseViewModel& vm);
};


class DefaultWindow : public BaseWindow {
    public:
        DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX);
};


class TopBannerWindow : public BaseWindow {
    public:
        virtual Pos2D calcHeightAndWidth(BaseViewModel& vm) const override;
        TopBannerWindow(BaseViewModel& vm);
};
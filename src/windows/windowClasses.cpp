#include <ncurses.h>
#include <utility>
#include "windowClasses.h"
#include "baseViewModel.h"
#include "position.h"


BaseWindow::BaseWindow(BaseViewModel& vm) : viewModel(vm) {}


void BaseWindow::wnoutrefresh() {
    ::touchwin(window);
    ::wnoutrefresh(window);
    ::wnoutrefresh(subwin);
}


void BaseWindow::makeBox() {
    ::box(window, '|', '-');
}


void BaseWindow::draw() {
    viewModel.draw(subwin);
}


void BaseWindow::wclear() {
    ::wclear(window);
}


void BaseWindow::werase() {
    ::werase(window);
}


void BaseWindow::fullRefresh(bool drawBox, bool clear, bool erase) {
    if (clear) {
        wclear();
    } else if (erase) {
        werase();
    }
    draw();
    if (drawBox) {
        makeBox();
    }
    wnoutrefresh();
}



Pos2D BaseWindow::addIntToPos(Pos2D pos, int num) {
    return {pos.y + num, pos.x + num};
}


void BaseWindow::createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX) {
    window = newwin(fullHeight, fullWidth, topLeftY, topLeftX);
    subwin = derwin(
        window,  // derive from main window
        fullHeight - 2 * BORDER_WIDTH, fullWidth - 2 * BORDER_WIDTH,  // cut off both borders
        BORDER_WIDTH, BORDER_WIDTH  // start at first part after border
    );
}


BaseWindow::~BaseWindow() {
    delwin(subwin);
    delwin(window);
}


Pos2D BottomRightWindow::calcTopLeftPos(Pos2D heightAndWidth) {
    /* Calculates the position (y, x) of the top-left corner of the window
    given the window's height and width. */

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int topLeftX = maxX - heightAndWidth.x;
    int topLeftY = maxY - heightAndWidth.y;
    return {topLeftY, topLeftX};
}


BottomRightWindow::BottomRightWindow(BaseViewModel& vm) : BaseWindow(vm) {
    Pos2D heightAndWidth = addIntToPos(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    Pos2D topLeftPos = calcTopLeftPos(heightAndWidth);
    createWindows(heightAndWidth.y, heightAndWidth.x, topLeftPos.y, topLeftPos.x);
}


Pos2D CentredPopupWindow::calcTopLeftPos(Pos2D heightAndWidth) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int topLeftX = (maxX - heightAndWidth.x) / 2;
    int topLeftY = (maxY - heightAndWidth.y) / 2;
    return {topLeftY, topLeftX};
}


CentredPopupWindow::CentredPopupWindow(BaseViewModel& vm) : BaseWindow(vm) {
    // todo: blatant code duplication - will i ever need to do something different here? if not then make base method
    Pos2D heightAndWidth = addIntToPos(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    Pos2D topLeftPos = calcTopLeftPos(heightAndWidth);
    createWindows(heightAndWidth.y, heightAndWidth.x, topLeftPos.y, topLeftPos.x);
}


Pos2D DefaultWindow::calcTopLeftPos(Pos2D heightAndWidth) {
    // this doesn't need to be called.
    (void) heightAndWidth;  // unused.
    return {-1, -1};
}


DefaultWindow::DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX) : BaseWindow(vm) {
    Pos2D heightAndWidth = addIntToPos(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    createWindows(heightAndWidth.y, heightAndWidth.x, topLeftY, topLeftX);
}
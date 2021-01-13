#include <ncurses.h>
#include <utility>
#include "windowClasses.h"
#include "baseViewModel.h"


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


std::pair<int, int> BaseWindow::addIntToPair(std::pair<int, int> pair, int num) {
    int first = pair.first;
    int second = pair.second;
    return std::make_pair(first + num, second + num);
}


void BaseWindow::createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX) {
    window = newwin(fullHeight, fullWidth, topLeftY, topLeftX);
    subwin = derwin(
        window,  // derive from main window
        fullHeight - 2 * BORDER_WIDTH, fullWidth - 2 * BORDER_WIDTH,  // cut off both borders
        BORDER_WIDTH, BORDER_WIDTH  // start at first part after border
    );
}


std::pair<int, int> BottomRightWindow::calcTopLeftPos(std::pair<int, int> heightAndWidth) {
    /* Calculates the position (y, x) of the top-left corner of the window
    given the window's height and width. */

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int topLeftX = maxX - heightAndWidth.second;
    int topLeftY = maxY - heightAndWidth.first;
    return std::make_pair(topLeftY, topLeftX);
}


BottomRightWindow::BottomRightWindow(BaseViewModel& vm) : BaseWindow(vm) {
    std::pair<int, int> heightAndWidth = addIntToPair(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    std::pair<int, int> topLeftPos = calcTopLeftPos(heightAndWidth);
    createWindows(heightAndWidth.first, heightAndWidth.second, topLeftPos.first, topLeftPos.second);
}


std::pair<int, int> CentredPopupWindow::calcTopLeftPos(std::pair<int, int> heightAndWidth) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int topLeftX = (maxX - heightAndWidth.second) / 2;
    int topLeftY = (maxY - heightAndWidth.first) / 2;
    return std::make_pair(topLeftY, topLeftX);
}


CentredPopupWindow::CentredPopupWindow(BaseViewModel& vm) : BaseWindow(vm) {
    // todo: blatant code duplication - will i ever need to do something different here? if not then make base method
    std::pair<int, int> heightAndWidth = addIntToPair(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    std::pair<int, int> topLeftPos = calcTopLeftPos(heightAndWidth);
    createWindows(heightAndWidth.first, heightAndWidth.second, topLeftPos.first, topLeftPos.second);
}


std::pair<int, int> DefaultWindow::calcTopLeftPos(std::pair<int, int> heightAndWidth) {
    // this doesn't need to be called.
    (void) heightAndWidth;  // unused.
    return std::make_pair(-1, -1);
}


DefaultWindow::DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX) : BaseWindow(vm) {
    std::pair<int, int> heightAndWidth = addIntToPair(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
    createWindows(heightAndWidth.first, heightAndWidth.second, topLeftY, topLeftX);
}
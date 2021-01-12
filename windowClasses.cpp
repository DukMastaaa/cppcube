#include <ncurses.h>
#include <utility>
#include "windowClasses.h"
#include "baseViewModel.h"


BaseWindow::BaseWindow(BaseViewModel& vm) : viewModel(vm) {}


void BaseWindow::wnoutrefresh() {
    ::wnoutrefresh(window);
}


void BaseWindow::makeBox() {
    box(window, '|', '-');
}


void BaseWindow::draw() {
    viewModel.draw(window);
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
    std::pair<int, int> heightAndWidth = vm.calcHeightWidth();
    std::pair<int, int> topLeftPos = calcTopLeftPos(heightAndWidth);
    window = newwin(heightAndWidth.first, heightAndWidth.second, topLeftPos.first, topLeftPos.second);
}
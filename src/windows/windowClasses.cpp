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


std::pair<int, int> CentredPopupWindow::calcTopLeftPos(std::pair<int, int> heightAndWidth) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int topLeftX = (maxX - heightAndWidth.second) / 2;
    int topLeftY = (maxY - heightAndWidth.first) / 2;
    return std::make_pair(topLeftY, topLeftX);
}


CentredPopupWindow::CentredPopupWindow(BaseViewModel& vm) : BaseWindow(vm) {
    // todo: blatant code duplication - will i ever need to do something different here? if not then make base method
    std::pair<int, int> heightAndWidth = vm.calcHeightWidth();
    std::pair<int, int> topLeftPos = calcTopLeftPos(heightAndWidth);
    window = newwin(heightAndWidth.first, heightAndWidth.second, topLeftPos.first, topLeftPos.second);
}


std::pair<int, int> DefaultWindow::calcTopLeftPos(std::pair<int, int> heightAndWidth) {
    // this doesn't need to be called.
    return std::make_pair(-1, -1);
}


DefaultWindow::DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX) : BaseWindow(vm) {
    std::pair<int, int> heightAndWidth = vm.calcHeightWidth();
    window = newwin(heightAndWidth.first, heightAndWidth.second, topLeftY, topLeftX);
}
#include "windows/windowClasses.h"

#include <utility>
#include <algorithm>

#include <ncurses.h>

#include "views/baseViewModel.h"
#include "myStructs.h"


BaseWindow::BaseWindow(BaseViewModel& vm) : viewModel(vm) {}


Pos2D BaseWindow::calcTopLeftPos(Pos2D heightAndWidth) const {
    (void) heightAndWidth;  // unused
    return {0, 0};
}


Pos2D BaseWindow::calcHeightAndWidth(BaseViewModel& vm) const {
    return addIntToPos(vm.calcHeightWidth(), 2 * BORDER_WIDTH);
}


void BaseWindow::standardInit(BaseViewModel& vm) {
    /* Standard window initialisation. Don't call in ctor if window is special. */

    Pos2D heightAndWidth = calcHeightAndWidth(vm);
    Pos2D topLeftPos = calcTopLeftPos(heightAndWidth);
    createWindows(heightAndWidth.y, heightAndWidth.x, topLeftPos.y, topLeftPos.x);
}


void BaseWindow::createSubwin(int fullHeight, int fullWidth) {
    /* Helper function to create a subwindow. */
    
    subwin = derwin(
        fullWindow,  // derive from main window
        fullHeight - 2 * BORDER_WIDTH, fullWidth - 2 * BORDER_WIDTH,  // cut off both borders
        BORDER_WIDTH, BORDER_WIDTH  // start at first part after border
    );
}


void BaseWindow::createWindows(int fullHeight, int fullWidth, int topLeftY, int topLeftX) {
    fullWindow = newwin(fullHeight, fullWidth, topLeftY, topLeftX);
    createSubwin(fullHeight, fullWidth);
    keypad(fullWindow, true);  // allows special keys to work
}


void BaseWindow::wnoutrefresh() const {
    ::touchwin(fullWindow);
    ::wnoutrefresh(fullWindow);
    ::wnoutrefresh(subwin);
}


void BaseWindow::makeBox() const {
    ::box(fullWindow, '|', '-');
}


void BaseWindow::draw() const {
    viewModel.draw(subwin);
}


void BaseWindow::title(std::string titleText) const {
    unsigned int winHeight, winWidth;
    getmaxyx(fullWindow, winHeight, winWidth);
    (void) winHeight;  // unused
    unsigned int titleLen = titleText.length();
    unsigned int startCol = (titleLen < winWidth) ? (winWidth - titleLen) / 2 : 0;
    mvwprintw(fullWindow, 0, startCol, titleText.c_str());
}


void BaseWindow::wclear() const {
    ::wclear(fullWindow);
}


void BaseWindow::werase() const {
    ::werase(fullWindow);
}


void BaseWindow::handleResize() {
    delwin(subwin);
    wclear();
    Pos2D heightAndWidth = calcHeightAndWidth(viewModel);
    Pos2D topLeftPos = calcTopLeftPos(heightAndWidth);
    mvwin(fullWindow, topLeftPos.y, topLeftPos.x);
    wresize(fullWindow, heightAndWidth.y, heightAndWidth.x);
    createSubwin(heightAndWidth.y, heightAndWidth.x);
}


Pos2D BaseWindow::addIntToPos(Pos2D pos, int num) {
    return {pos.y + num, pos.x + num};
}


PopupState BaseWindow::receiveKeyboardInput(int input) {
    return viewModel.receiveKeyboardInput(input);
}


std::string BaseWindow::getPopupReturnData() {
    return viewModel.getPopupReturnData();
}


PopupState BaseWindow::receiveData(std::string data) {
    return viewModel.receiveData(data);
}


BaseWindow::~BaseWindow() {
    delwin(subwin);
    delwin(fullWindow);
}


Pos2D BottomRightWindow::calcTopLeftPos(Pos2D heightAndWidth) const {
    /* Calculates the position (y, x) of the top-left corner of the window
    given the window's height and width. */

    unsigned int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    unsigned int topLeftX = maxX - heightAndWidth.x;
    unsigned int topLeftY = maxY - heightAndWidth.y;
    return {topLeftY, topLeftX};
}


BottomRightWindow::BottomRightWindow(BaseViewModel& vm) : BaseWindow(vm) {
    standardInit(vm);
}


Pos2D BottomLeftWindow::calcTopLeftPos(Pos2D heightAndWidth) const {
    unsigned int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxX;  // unused
    return {maxY - heightAndWidth.y, 0};
}


BottomLeftWindow::BottomLeftWindow(BaseViewModel& vm) : BaseWindow(vm) { standardInit(vm); }


Pos2D CentredWindow::calcTopLeftPos(Pos2D heightAndWidth) const {
    unsigned int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    unsigned int topLeftY = (maxY - heightAndWidth.y) / 2;
    unsigned int topLeftX = (maxX - heightAndWidth.x) / 2;
    return {topLeftY, topLeftX};
}


CentredWindow::CentredWindow(BaseViewModel& vm) : BaseWindow(vm) { standardInit(vm); }


DefaultWindow::DefaultWindow(BaseViewModel& vm, int topLeftY, int topLeftX) : BaseWindow(vm) {
    Pos2D heightAndWidth = calcHeightAndWidth(vm);
    createWindows(heightAndWidth.y, heightAndWidth.x, topLeftY, topLeftX);
}


Pos2D TopBannerWindow::calcHeightAndWidth(BaseViewModel& vm) const {
    Pos2D heightAndWidth = BaseWindow::calcHeightAndWidth(vm);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    (void) maxY;  // unused
    heightAndWidth.x = maxX;

    return heightAndWidth;
}


TopBannerWindow::TopBannerWindow(BaseViewModel& vm) : BaseWindow(vm) { standardInit(vm); }
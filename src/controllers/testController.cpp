#include "controllers/testController.h"

#include <ncurses.h>

#include "myStructs.h"


TestViewModel::TestViewModel(TestModel& modelRef) : model(modelRef) {}


Pos2D TestViewModel::calcHeightWidth() {
    return {3, 10};
}


void TestViewModel::draw(WINDOW* window) {
    mvwprintw(window, 0, 0, "beans");
}


TestController::TestController() :
        model(),
        viewModel(model),
        window(viewModel) {}


void TestController::refresh() {
    window.makeBox();
    window.draw();
    window.wnoutrefresh();
}


WINDOW* TestController::getWindow() {
    return window.fullWindow;
}
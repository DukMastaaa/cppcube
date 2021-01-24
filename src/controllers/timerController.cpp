#include "controllers/timerController.h"

#include <chrono>

#include "controllers/baseController.h"
#include "myStructs.h"


TimerController::TimerController() :
        BaseController(),
        model(),
        viewModel(model),
        window(viewModel) {}


bool TimerController::isTiming() {
    return model.isTiming;
}


void TimerController::toggleTiming() {
    model.toggleTiming();
}


void TimerController::togglePenalty(Penalty penalty) {
    model.togglePenalty(penalty);
}


std::chrono::milliseconds TimerController::getTimeElapsed() {
    return model.getTimeElapsed();
}


void TimerController::refresh() {
    window.werase();
    window.draw();
    window.wnoutrefresh();
}
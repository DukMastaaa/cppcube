#include "controllers/timerController.h"

#include <chrono>
#include <memory>

#include "controllers/baseController.h"
#include "myStructs.h"


TimerController::TimerController() :
        BaseController(),
        model(),
        viewModel(model) {
    window = std::make_unique<CentredWindow>(viewModel);
}

bool TimerController::isTiming() const {
    return model.isTiming;
}


void TimerController::toggleTiming() {
    model.toggleTiming();
}


void TimerController::togglePenalty(Penalty penalty) {
    model.togglePenalty(penalty);
}


std::chrono::milliseconds TimerController::getTimeElapsed() const {
    return model.getTimeElapsed();
}
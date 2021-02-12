#pragma once

#include "controllers/baseController.h"

#include <chrono>

#include "models/cubeTimer.h"
#include "views/normal/timerViewModel.h"
#include "windows/windowClasses.h"
#include "myStructs.h"


class TimerController : public BaseController {
    public:
        CubeTimer model;
        TimerController();
        bool isTiming() const;
        void toggleTiming();
        void togglePenalty(Penalty penalty);
        std::chrono::milliseconds getTimeElapsed() const;

    private:
        TimerViewModel viewModel;
};
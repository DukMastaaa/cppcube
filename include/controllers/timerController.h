#pragma once

#include "controllers/baseController.h"

#include <chrono>

#include "models/cubeTimer.h"
#include "views/timerViewModel.h"
#include "windows/windowClasses.h"
#include "myStructs.h"


class TimerController : public BaseController {
    private:
        CubeTimer model;
        TimerViewModel viewModel;
        CentredWindow window;

    public:
        TimerController();
        bool isTiming();
        void toggleTiming();
        void togglePenalty(Penalty penalty);
        std::chrono::milliseconds getTimeElapsed();
        void refresh();
};
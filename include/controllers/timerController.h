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

    public:
        TimerController();
        bool isTiming() const;
        void toggleTiming();
        void togglePenalty(Penalty penalty);
        std::chrono::milliseconds getTimeElapsed() const;
        void refresh() const override;
};
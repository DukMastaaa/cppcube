#pragma once
#include <utility>
#include <iostream>
#include "baseViewModel.h"
#include "cubeTimer.h"
#include "position.h"


class TimerViewModel : public BaseViewModel {
    private:
        CubeTimer& timer;
        static const std::string NUM_BLOCK[10][5];
        static const std::string FULL_STOP[5];
        static const std::string COLON[5];
        static const std::string PLUS[5];

    public:
        TimerViewModel(CubeTimer& timerRef);
        Pos2D calcHeightWidth();
        void draw(WINDOW* window);
};
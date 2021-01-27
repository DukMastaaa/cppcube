#pragma once

#include <iostream>
#include <array>

#include "views/baseViewModel.h"
#include "models/cubeTimer.h"
#include "myStructs.h"


class TimerViewModel : public BaseViewModel {
    private:
        CubeTimer& timer;
        static const std::string NUM_BLOCK[10][5];
        static const std::string FULL_STOP[5];
        static const std::string COLON[5];
        static const std::string PLUS[5];
        static const std::string DNF[5];
        void drawCharMatrix(WINDOW* window, std::array<int, 3> times, bool plus2) const;
        void drawEllipsis(WINDOW* window) const;
        void drawDNF(WINDOW* window) const;

    public:
        TimerViewModel(CubeTimer& timerRef);
        Pos2D calcHeightWidth() const override;
        void draw(WINDOW* window) const override;
};
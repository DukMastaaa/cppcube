#pragma once

#include <iostream>
#include <map>
#include <array>

#include "views/baseViewModel.h"
#include "models/cubeTimer.h"
#include "myStructs.h"


class TimerViewModel : public BaseViewModel {
    private:
        CubeTimer& timer;
        static const std::map<char, std::array<std::string, 5>> SYMBOL_BLOCKS;
        // static int charDigitToInt(char digit);  // todo: deprecate lol
        void drawCharMatrix(WINDOW* window, std::string formattedTime) const;
        void drawEllipsis(WINDOW* window) const;

    public:
        TimerViewModel(CubeTimer& timerRef);
        Pos2D calcHeightWidth() const override;
        void draw(WINDOW* window) const override;
};
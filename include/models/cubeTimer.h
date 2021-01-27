#pragma once

#include <chrono>
#include <array>

#include "myStructs.h"


class CubeTimer {
    private:
        static std::chrono::steady_clock clock;
        std::chrono::steady_clock::time_point startingTime;
        std::chrono::steady_clock::time_point endingTime;
        std::chrono::milliseconds timeElapsed;

    public:
        bool isTiming;
        Penalty currentPenalty;
        CubeTimer();
        void resetTime();
        void startTimingAndReset();
        void stopTiming();
        void toggleTiming();
        void togglePenalty(Penalty penalty);
        std::chrono::milliseconds getTimeElapsed() const;
        static std::array<int, 3> getTimeDivisions(std::chrono::milliseconds elapsedTime);
};
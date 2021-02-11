#pragma once

#include <chrono>
#include <array>

#include "models/baseModel.h"
#include "myStructs.h"


class CubeTimer : public BaseModel {
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
        static std::string formatTime(std::chrono::milliseconds time, Penalty penalty);
};
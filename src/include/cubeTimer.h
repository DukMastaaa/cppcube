#pragma once
#include <chrono>


class CubeTimer {
    // very much WIP!
    private:
        static std::chrono::steady_clock clock;
        std::chrono::steady_clock::time_point startingTime;
        std::chrono::steady_clock::time_point endingTime;
        std::chrono::milliseconds timeElapsed;
        bool isTiming;

    public:
        CubeTimer();
        void resetTime();
        void startTimingAndReset();
        void stopTiming();
        std::chrono::milliseconds getTimeElapsed();
};
#include "models/cubeTimer.h"

#include <chrono>
#include <array>

#include "myStructs.h"


CubeTimer::CubeTimer() {
    isTiming = false;
    resetTime();
}


void CubeTimer::resetTime() {
    timeElapsed = std::chrono::milliseconds(0);
    currentPenalty = NO_PENALTY;
}


void CubeTimer::startTimingAndReset() {
    isTiming = true;
    resetTime();
    startingTime = clock.now();
}


void CubeTimer::stopTiming() {
    namespace chrono = std::chrono;
    if (isTiming) {
        isTiming = false;
        endingTime = clock.now();
        timeElapsed = chrono::duration_cast<chrono::milliseconds>(endingTime - startingTime);
    }
}


void CubeTimer::toggleTiming() {
    if (isTiming) {
        stopTiming();
    } else {
        startTimingAndReset();
    }
}


std::chrono::milliseconds CubeTimer::getTimeElapsed() {
    return timeElapsed;
}


void CubeTimer::togglePenalty(Penalty penalty) {
    if (currentPenalty != penalty) {
        currentPenalty = penalty;
    } else {
        currentPenalty = NO_PENALTY;
    }
}


std::array<int, 3> CubeTimer::getTimeDivisions(std::chrono::milliseconds elapsedTime) {
    /* Changes milliseconds to string representation of equivalent minutes:seconds.centiseconds. */
    namespace chrono = std::chrono;
    static const int millisecToSec = 1000;

    int min = chrono::duration_cast<chrono::minutes>(elapsedTime).count();
    int sec, centisec;
    if (min >= 100) {  // wrap at 100 min
        min = 99;
        sec = 59;
        centisec = 99;
    } else {
        sec = chrono::duration_cast<chrono::seconds>(elapsedTime).count() % 60;
        centisec = (elapsedTime.count() % millisecToSec) / 10;  // round instead of floor div?
    }
    return {min, sec, centisec};
}

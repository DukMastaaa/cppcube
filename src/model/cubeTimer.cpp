#include <chrono>
#include "cubeTimer.h"


CubeTimer::CubeTimer() {
    isTiming = false;
    resetTime();
}


void CubeTimer::resetTime() {
    timeElapsed = std::chrono::milliseconds(0);
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
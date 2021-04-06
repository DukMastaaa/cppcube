#include "myStructs.h"

#include <iostream>


bool Record::isDNF(const Record& record) {
    return (record.penalty == Penalty::DNF_PENALTY);
}


std::chrono::milliseconds Record::getFinalTime() const {
    switch (penalty) {
        case Penalty::DNF_PENALTY:
            return std::chrono::milliseconds(-1);
            break;
        
        case Penalty::PLUS_2_PENALTY:
            return time + std::chrono::seconds(2);
            break;
        
        case Penalty::NO_PENALTY:
            return time;
            break;

        default:
            return time;
            break;
    }
}


bool Record::operator<(const Record& otherRecord) const {
    return getFinalTime() < otherRecord.getFinalTime();
}


bool Record::operator>(const Record& otherRecord) const {
    return getFinalTime() > otherRecord.getFinalTime();
}


std::array<int, 3> Record::millisecondsToTimeDivisions(std::chrono::milliseconds elapsedTime) {
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


std::string Record::getFormattedTime(std::chrono::milliseconds time, Penalty penalty) {
    if (penalty == Penalty::DNF_PENALTY) {
        return "DNF";
    } else {
        bool plus2 = (penalty == Penalty::PLUS_2_PENALTY);
        auto offset = plus2 ? std::chrono::seconds(2) : std::chrono::seconds(0); 
        std::array<int, 3> times = millisecondsToTimeDivisions(time + offset);

        std::string formattedTime;
        for (int timeSelector = 0; timeSelector < 3; timeSelector++) {
            int thisTime = times[timeSelector];
            int tens = thisTime / 10;
            int ones = thisTime % 10;
            formattedTime += std::to_string(tens) + std::to_string(ones);
            
            // punctuation
            switch (timeSelector) {
                case 0:
                    formattedTime += ':';
                    break;
                case 1:
                    formattedTime += '.';
                    break;
                case 2:
                    if (plus2) {
                        formattedTime += '+';
                    }
                    break;
            }
        }
        return formattedTime;
    }
}


std::string Record::penaltyAsString(Penalty penalty) {
    switch (penalty) {
        case Penalty::NO_PENALTY:
            return "NONE";
            break;
        case Penalty::PLUS_2_PENALTY:
            return "+2";
            break;
        case Penalty::DNF_PENALTY:
            return "DNF";
            break;
        default:
            return "what";
            break;
    }
}


std::chrono::milliseconds Record::timeDivisionsToMilliseconds(int minutes, int seconds, int centiseconds) {
    return std::chrono::minutes(minutes) + std::chrono::seconds(seconds) + std::chrono::milliseconds(centiseconds * 10);
}


void dummyPopupCallback(std::string returnVal) {
    (void) returnVal;  // unused
}

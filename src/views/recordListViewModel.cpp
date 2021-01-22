#include "recordListViewModel.h"

#include <iostream>
#include <cstddef>
#include <chrono>
#include <array>

#include <ncurses.h>

#include "recordList.h"
#include "cubeTimer.h"
#include "myStructs.h"
#include "colours.h"


std::string RecordListViewModel::formatTime(std::chrono::milliseconds time, Penalty penalty) {
    if (penalty == DNF_PENALTY) {
        return "DNF";
    } else {
        bool plus2 = (penalty == PLUS_2_PENALTY);
        auto offset = plus2 ? std::chrono::seconds(2) : std::chrono::seconds(0); 
        std::array<int, 3> times = CubeTimer::getTimeDivisions(time + offset);

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


RecordListViewModel::RecordListViewModel(RecordList& recordsRef) : records(recordsRef) {
    recordsShown = 13UL;  // todo: this can be changed
    selectedIndex = 0UL;
    topIndex = 0UL;
}


Pos2D RecordListViewModel::calcHeightWidth() {
    return {static_cast<unsigned int>(recordsShown) + 1, 14};
}


inline std::size_t RecordListViewModel::indexAtBottom() const {
    return topIndex - (recordsShown - 1);
}


inline std::size_t RecordListViewModel::indexMax() const {
    return records.getRecordCount() - 1;
}


void RecordListViewModel::recordAdded() {
    if (records.getRecordCount() == 1) {
        topIndex = 0;
        selectedIndex = 0;
    } else {
        std::size_t maxIndex = indexMax();
        if (topIndex == maxIndex - 1) {
            topIndex = maxIndex;
        }
        if (selectedIndex == maxIndex - 1) {
            selectedIndex = maxIndex;
        }
    }
}


void RecordListViewModel::recordRemoved() {
    std::size_t maxIndex = indexMax();
    if (topIndex > maxIndex) {
        topIndex = maxIndex;
    }
    if (selectedIndex > maxIndex) {
        selectedIndex = maxIndex;
    }
}


void RecordListViewModel::moveUp() {
    if (records.getRecordCount() > 0) {
        if (topIndex < indexMax() && selectedIndex >= topIndex) {
            topIndex++;
        }
        if (selectedIndex < indexMax()) {
            selectedIndex++;
        }
    }
}


void RecordListViewModel::moveDown() {
    if (selectedIndex == indexAtBottom()) {
        topIndex--;
    }
    if (selectedIndex > 0) {
        selectedIndex--;
    }
}


void RecordListViewModel::drawRecords(WINDOW* window) {
    std::size_t recordCount = records.getRecordCount();
    if (recordCount == 0) {
        mvwprintw(window, 1, 0, "none yet");
    } else {
        for (std::size_t rowCounter = 0; rowCounter < recordsShown; rowCounter++) {
            std::size_t currentIndex = topIndex - rowCounter;
            Record& thisRecord = records.getRecord(currentIndex);

            std::string formattedTime = formatTime(thisRecord.time, thisRecord.penalty);
            
            // todo: what on earth is this mate
            if (currentIndex == selectedIndex) {
                wattron(window, COLOR_PAIR(GREEN_ON_BLACK));
            }

            mvwprintw(window, rowCounter + 1, 0, "%3ld: %s", currentIndex + 1, formattedTime.c_str());
            
            if (currentIndex == selectedIndex) {
                wattroff(window, COLOR_PAIR(GREEN_ON_BLACK));
            }
            
            if (topIndex - rowCounter == 0) {
                break;
            }
        }
    }
}


void RecordListViewModel::draw(WINDOW* window) {
    mvwprintw(window, 0, 0, "History (%ld)", records.getRecordCount());
    drawRecords(window);
}
#include "views/normal/recordListViewModel.h"

#include <algorithm>
#include <iostream>
#include <cstddef>
#include <chrono>
#include <array>

#include <ncurses.h>

#include "models/recordList.h"
#include "models/cubeTimer.h"
#include "myStructs.h"
#include "views/colours.h"


RecordListViewModel::RecordListViewModel(RecordList& recordsRef) : records(recordsRef) {
    recordsShown = 13UL;  // todo: this can be changed
    selectedIndex = 0UL;
    topIndex = 0UL;
}


Pos2D RecordListViewModel::calcHeightWidth() const {
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
    if (selectedIndex > 0) {
        selectedIndex--;
    }
    if (selectedIndex == indexAtBottom() && selectedIndex > 0) {
        topIndex--;
    }
}


void RecordListViewModel::jumpToIndex(std::size_t index) {
    if (index < records.getRecordCount()) {
        selectedIndex = index;
        if (index < recordsShown - 1) {
            topIndex = std::min(recordsShown - 1, records.getRecordCount() - 1);
        } else {
            topIndex = index;
        }
    }
}


void RecordListViewModel::drawRecords(WINDOW* window) const {
    std::size_t recordCount = records.getRecordCount();
    if (recordCount == 0) {
        mvwprintw(window, 1, 0, "none yet");
    } else {
        for (std::size_t rowCounter = 0; rowCounter < recordsShown; rowCounter++) {
            std::size_t currentIndex = topIndex - rowCounter;
            const Record& thisRecord = records.getRecord(currentIndex);

            std::string formattedTime = Record::getFormattedTime(thisRecord.time, thisRecord.penalty);
            
            TextColours colourPair = (currentIndex == selectedIndex) ? GREEN_ON_BLACK : WHITE_ON_BLACK;
            wattron(window, COLOR_PAIR(colourPair));
            mvwprintw(window, rowCounter + 1, 0, "%3ld: %s", currentIndex + 1, formattedTime.c_str());
            wattroff(window, COLOR_PAIR(colourPair));
            
            if (topIndex - rowCounter == 0) {
                break;
            }
        }
    }
}


void RecordListViewModel::draw(WINDOW* window) const {
    /* Erases and draws record list window. */
    werase(window);
    mvwprintw(window, 0, 0, "History (%ld)", records.getRecordCount());
    // mvwprintw(window, 0, 0, "%ld %ld %ld", records.getRecordCount(), topIndex, selectedIndex);
    drawRecords(window);
}


std::size_t RecordListViewModel::getSelectedIndex() const {
    return selectedIndex;
}


const Record& RecordListViewModel::getRecord(std::size_t index) const {
    return records.getRecord(index);
}
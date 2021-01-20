#include "recordListViewModel.h"

#include <chrono>

#include <ncurses.h>

#include "recordList.h"
#include "myStructs.h"


RecordListViewModel::RecordListViewModel(RecordList& recordsRef) : records(recordsRef) {
    recordsShown = 10UL;  // this can be changed
    selectedIndex = 0UL;
    topIndex = 0UL;
}


Pos2D RecordListViewModel::calcHeightWidth() {
    return {recordsShown + 1, 14};
}


void RecordListViewModel::recordAdded() {
    if (records.getRecordCount() == 1) {
        topIndex = 0;
        selectedIndex = 0;
    } else {
        std::size_t bottomIndex = topIndex - (recordsShown - 1);  // todo: inline functions
        std::size_t maxIndex = records.getRecordCount() - 1;
        // if (selectedIndex > bottomIndex && bottomIndex > 0) {
        //     topIndex++;
        // }
        if (topIndex == maxIndex - 1) {
            topIndex = maxIndex;
        }
        if (selectedIndex == maxIndex - 1) {
            selectedIndex = maxIndex;
        }
    }
}


void RecordListViewModel::recordRemoved() {
    std::size_t maxIndex = records.getRecordCount() - 1;
    if (topIndex > maxIndex) {
        topIndex = maxIndex;
    }
}


void RecordListViewModel::moveUp() {
    std::size_t recordCount = records.getRecordCount();
    if (recordCount > 0) {
        std::size_t maxIndex = records.getRecordCount() - 1;
        if (selectedIndex < maxIndex) {
            selectedIndex++;
        }
        if (topIndex < maxIndex && selectedIndex >= topIndex) {
            topIndex++;
        }
    }
}


void RecordListViewModel::moveDown() {
    if (selectedIndex > 0) {
        selectedIndex--;
    }
    if (topIndex - (recordsShown - 1) > 0 && selectedIndex < topIndex) {
        topIndex--;
    }
}




void RecordListViewModel::drawRecords(WINDOW* window) {
    for (std::size_t )  // how to fix this - it doesnt display the first record, probably off by 1 error


    for (std::size_t rowCounter = 0; rowCounter < recordsShown && topIndex - rowCounter >= 0 && records.getRecordCount() > 0; rowCounter++) {
        std::size_t currentIndex = topIndex - rowCounter;
        Record& thisRecord = records.getRecord(currentIndex);
        int time = thisRecord.time.count();
        mvwprintw(window, rowCounter + 1, 0, "%ld: %d", currentIndex + 1, time);
    }
}


void RecordListViewModel::draw(WINDOW* window) {
    mvwaddstr(window, 0, 0, "History");
    drawRecords(window);
    mvwprintw(window, 9, 0, "%lu %lu %lu", topIndex, selectedIndex, records.getRecordCount());
}
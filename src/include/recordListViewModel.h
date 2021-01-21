#pragma once

#include <iostream>

#include <stddef.h>

#include "baseViewModel.h"
#include "recordList.h"
#include "myStructs.h"


class RecordListViewModel : public BaseViewModel {
    private:
        RecordList& records;
        std::size_t recordsShown;
        std::size_t selectedIndex;
        std::size_t topIndex;
        void drawRecords(WINDOW* window);
        std::string formatTime(std::chrono::milliseconds time, Penalty penalty);
    
    public:
        RecordListViewModel(RecordList& recordsRef);
        Pos2D calcHeightWidth();
        void recordAdded();
        void recordRemoved();
        void moveUp();
        void moveDown();
        void draw(WINDOW* window);
};
#pragma once

#include <iostream>

#include <stddef.h>

#include "views/baseViewModel.h"
#include "models/recordList.h"
#include "myStructs.h"


class RecordListViewModel : public BaseViewModel {
    private:
        RecordList& records;
        std::size_t recordsShown;
        std::size_t selectedIndex;
        std::size_t topIndex;
        void drawRecords(WINDOW* window) const;
        static std::string formatTime(std::chrono::milliseconds time, Penalty penalty);
        inline std::size_t indexAtBottom() const;
        inline std::size_t indexMax() const;
    
    public:
        RecordListViewModel(RecordList& recordsRef);
        Pos2D calcHeightWidth() const override;
        void recordAdded();
        void recordRemoved();
        void moveUp();
        void moveDown();
        void draw(WINDOW* window) const override;
};
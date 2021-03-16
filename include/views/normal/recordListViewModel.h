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
        inline std::size_t indexAtBottom() const;
        inline std::size_t indexMax() const;
    
    public:
        RecordListViewModel(RecordList& recordsRef);
        Pos2D calcHeightWidth() const override;
        void recordAdded();
        void recordRemoved();
        void moveUp();
        void moveDown();
        void jumpToIndex(std::size_t index);
        void draw(WINDOW* window) const override;
        std::size_t getSelectedIndex() const;
        const Record& getRecord(std::size_t index) const;
};
#pragma once

#include <stddef.h>
#include <memory>

#include "baseController.h"
#include "models/recordList.h"
#include "views/recordListViewModel.h"
#include "windows/windowClasses.h"
#include "myStructs.h"


class RecordListController : public BaseController {
    private:
        RecordList model;
    
    public:
        RecordListController();
        std::size_t getRecordCount() const;
        void moveUp();
        void moveDown();
        void addRecord(Record record);

        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void togglePenaltyLatestRecord(Penalty penalty);
        void togglePenaltySelectedRecord(Penalty penalty);
        
        void deleteRecord(std::size_t recordNum);
        void deleteLatestRecord();
        void deleteSelectedRecord();
        
        const Record& getRecord(std::size_t recordNum) const;
        void refresh() const override;
};
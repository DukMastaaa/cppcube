#pragma once

#include <stddef.h>

#include "controllers/baseController.h"
#include "models/recordList.h"
#include "views/normal/recordListViewModel.h"
#include "windows/windowClasses.h"
#include "myStructs.h"


class RecordListController : public BaseController {
    public:
        RecordListController();
        
        void moveUp();
        void moveDown();
        void moveToTop();
        void moveToBottom();
        void jumpToIndex(std::size_t index);

        void addRecord(Record record);

        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void togglePenaltyLatestRecord(Penalty penalty);
        void togglePenaltySelectedRecord(Penalty penalty);
        
        void deleteRecord(std::size_t recordNum);
        void deleteLatestRecord();
        void deleteSelectedRecord();
        void deleteAllRecords();  // :eyes:
        
        std::size_t getRecordCount() const;
        const Record& getRecord(std::size_t recordNum) const;
        std::size_t getSelectedIndex() const;
        void refresh() const override;

        const RecordListViewModel& getViewModelRef() const;
        RecordListViewModel& getViewModelRef();
        const RecordList& getModelRef() const;
        RecordList& getModelRef();
    
    private:
        RecordList model;
        RecordListViewModel viewModel;
};
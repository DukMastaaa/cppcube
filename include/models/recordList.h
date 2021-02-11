#pragma once

#include <stddef.h>

#include <vector>

#include "myStructs.h"
#include "models/baseModel.h"


class RecordList : public BaseModel {
    private:
        std::vector<Record> records;

    public:
        RecordList();
        std::size_t getRecordCount() const;
        void addRecord(Record record);
        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void togglePenaltyLatestRecord(Penalty penalty);
        void deleteRecord(std::size_t recordNum);
        void deleteLatestRecord();
        const Record& getRecord(std::size_t recordNum) const;
};
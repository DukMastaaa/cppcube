#pragma once

#include <stddef.h>

#include <vector>

#include "myStructs.h"


class RecordList {
    private:
        std::vector<Record> records;

    public:
        RecordList();
        std::size_t getRecordCount();
        void addRecord(Record record);
        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void togglePenaltyLatestRecord(Penalty penalty);
        void deleteRecord(std::size_t recordNum);
        void deleteLatestRecord();
        Record& getRecord(std::size_t recordNum);
};
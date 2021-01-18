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
        void togglePenalty(Penalty penalty, int recordNum);
        void togglePenaltyLatestRecord(Penalty penalty);
        void deleteRecord(int recordNum);
        void deleteLatestRecord();
};
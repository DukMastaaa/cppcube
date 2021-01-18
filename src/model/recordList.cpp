#include "recordList.h"

#include <stddef.h>

#include "myStructs.h"


RecordList::RecordList() {

}


std::size_t RecordList::getRecordCount() {
    return records.size();
}


void RecordList::addRecord(Record record) {
    records.push_back(record);
}


void RecordList::togglePenalty(Penalty penalty, int recordNum) {
    if (0 <= recordNum <= records.size() - 1) {
        Record& selectedRecord = records.at(recordNum);
        if (selectedRecord.penalty == penalty) {
            selectedRecord.penalty = NO_PENALTY;
        } else {
            selectedRecord.penalty = penalty;
        }
    }
}


void RecordList::togglePenaltyLatestRecord(Penalty penalty) {
    togglePenalty(penalty, records.size() - 1);
}


void RecordList::deleteRecord(int recordNum) {
    if (0 <= recordNum <= records.size() - 1) {
        records.erase(records.begin() + recordNum);
    }
}


void RecordList::deleteLatestRecord() {
    deleteRecord(records.size() - 1);
}
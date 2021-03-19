#include "models/summaryStatsModel.h"

#include <chrono>

#include "myStructs.h"


SummaryStatsModel::SummaryStatsModel(const RecordList& recordListRef) : recordList(recordListRef) {}


Record SummaryStatsModel::meanInRange(unsigned int start, unsigned int end) const {
    std::chrono::milliseconds cumulativeTime{0};

    for (unsigned int i = start; i < end; i++) {
        Record currentRecord = recordList.getRecord(i);
        switch (currentRecord.penalty) {
            case Penalty::NO_PENALTY:
                cumulativeTime += currentRecord.time;
                break;
            
            case Penalty::PLUS_2_PENALTY:
                cumulativeTime += currentRecord.time + std::chrono::seconds(2);
                break;
            
            case Penalty::DNF_PENALTY:
                break;
        }
    }

    cumulativeTime /= total();  // todo: something's not right here
    

    return {cumulativeTime, "", Penalty::NO_PENALTY};
}


Record SummaryStatsModel::averageOf(unsigned int count) const {
    if (count >= total() || count == 0) {
        return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
    } else if (total() <= 2) {
        return meanInRange(0, count);
    } else {
        // todo: this needs work, split into steps, sort 
    }
}


Record SummaryStatsModel::meanOf(unsigned int count) const {
    if (count >= total() || count == 0) {
        return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
    } else {
        return meanInRange(total() - 1 - count, total());
    }
}


Record SummaryStatsModel::averageOfAll() const {
    return averageOf(total() - 1);
}


Record SummaryStatsModel::meanOfAll() const {
    return meanInRange(0, total() - 1);
}


Record SummaryStatsModel::best() const {
    // not implemented
    return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
}


Record SummaryStatsModel::worst() const {
    // not implemeneted
    return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
}


unsigned int SummaryStatsModel::total() const {
    return recordList.getRecordCount();
}
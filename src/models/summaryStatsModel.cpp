#include "models/summaryStatsModel.h"

#include <chrono>
#include <vector>
#include <algorithm>

#include "myStructs.h"


SummaryStatsModel::SummaryStatsModel(const RecordList& recordListRef) : recordList(recordListRef) {}


std::chrono::milliseconds SummaryStatsModel::sumOfVector(std::vector<Record>::const_iterator begin, std::vector<Record>::const_iterator end) {
    std::chrono::milliseconds cumulativeTime{0};
    for (std::vector<Record>::const_iterator iter = begin; iter != end; ++iter) {
        if (Record::isDNF(*iter)) {
            break;
        }
        cumulativeTime += iter->getFinalTime();
    }
    return cumulativeTime;
}


Record SummaryStatsModel::averageOf(unsigned int count) const {
    if (count > total() || count == 0) {
        return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
    }
    
    const std::vector<Record>& records = recordList.getRecordVector();

    // selects last `count` elements of records
    std::vector<Record>::const_iterator begin = records.begin() + (total() - count);
    std::vector<Record>::const_iterator end = records.end();

    unsigned int dnfCount = std::count_if(begin, end, Record::isDNF);
    if (dnfCount >= 3 || (total() <= 2 && dnfCount >= count)) {  // off-by-one error here?
        return {std::chrono::milliseconds(0), "", Penalty::DNF_PENALTY};
    } else if (total() == 2) {
        return meanOfAll();  // mmmmmmmmm
    }

    Record lowest = *begin;
    Record highest = *begin;
    for (std::vector<Record>::const_iterator iter = begin; iter != end; ++iter) {
        const auto& record = *iter;
        if (Record::isDNF(record)) {
            continue;
        } else if (record < lowest) {
            lowest = record;
        } else if (record > highest) {
            highest = record;
        }
    }

    std::chrono::milliseconds sum = sumOfVector(begin, end);
    sum -= lowest.getFinalTime();
    sum -= highest.getFinalTime();

    return {sum / (count - 2), "", Penalty::NO_PENALTY};
}


Record SummaryStatsModel::meanOf(unsigned int count) const {
    if (count > total() || count == 0) {
        return {std::chrono::milliseconds(0), "", Penalty::NO_PENALTY};
    } else {
        std::vector<Record> recordVector = recordList.getRecordVector();
        auto sum = sumOfVector(recordVector.begin() + (total() - count), recordVector.end());
        return {sum / count, "", Penalty::NO_PENALTY};
    }
}


Record SummaryStatsModel::averageOfAll() const {
    return averageOf(total());
}


Record SummaryStatsModel::meanOfAll() const {
    return meanOf(total());
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
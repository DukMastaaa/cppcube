#pragma once

#include "models/recordList.h"
#include "myStructs.h"


class SummaryStatsModel {
    private:
        const RecordList& recordList;

        // Sums the final times of each record between two vector iterators, ignoring DNFs.
        static std::chrono::milliseconds sumOfVector(std::vector<Record>::const_iterator begin, std::vector<Record>::const_iterator end);

    public:
        SummaryStatsModel(const RecordList& recordListRef);
        Record averageOf(unsigned int count) const;
        Record meanOf(unsigned int count) const;

        // Average of all times; discards 
        Record averageOfAll() const;

        // Mean of all times, ignoring DNF.
        Record meanOfAll() const;

        // Best time, ignoring DNF.
        Record best() const;

        // Worst time, ignoring DNF.
        Record worst() const;

        // Total amount of records.
        unsigned int total() const;
};
#pragma once

#include "models/recordList.h"
#include "myStructs.h"


class SummaryStatsModel {
    private:
        const RecordList& recordList;

        // Calculates mean of records within [start, end), without checking bounds.
        Record meanInRange(unsigned int start, unsigned int end) const;

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
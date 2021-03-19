#pragma once

#include "models/recordList.h"


class SummaryStatsModel {
    private:
        const RecordList& recordList;

    public:
        SummaryStatsModel(const RecordList& recordListRef);
};
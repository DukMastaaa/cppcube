#pragma once

#include <iostream>

#include "models/recordList.h"
#include "myStructs.h"


class FileManager {
    private:
        const RecordList& recordList;
    
    public:
        FileManager(const RecordList& recordListRef);
        static std::string recordToString(const Record& record);
        void exportFile(const std::string& filename);
        void readFile(const std::string& filename);
};
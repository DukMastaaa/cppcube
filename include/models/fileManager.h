#pragma once

#include <iostream>
#include <regex>

#include "models/recordList.h"
#include "myStructs.h"


class FileManager {
    private:
        RecordList& recordList;
        static const std::regex RECORD_PATTERN;
    
    public:
        FileManager(RecordList& recordListRef);

        static std::string recordToString(const Record& record);
        
        // returns {-1, Penalty::NO_PENALTY, ""} if format wrong
        static Record stringToRecord(std::string string);

        void exportFile(const std::string& filename);
        void readFile(const std::string& filename);
};
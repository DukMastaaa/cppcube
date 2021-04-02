#include "models/fileManager.h"

#include <fstream>


FileManager::FileManager(const RecordList& recordListRef) : recordList(recordListRef) {}


std::string FileManager::recordToString(const Record& record) {
    std::string conversion = Record::getFormattedTime(record.time, Penalty::NO_PENALTY);

    if (record.penalty != Penalty::NO_PENALTY) {
        conversion += "(" + Record::penaltyAsString(record.penalty) + ")";
    }

    conversion += ": " + record.scramble;
    return conversion;
}


void FileManager::exportFile(const std::string& filename) {
    std::ofstream file(filename);

    int index = 1;
    for (const auto& record : recordList.getRecordVector()) {
        file << index << ". " << recordToString(record) << "\n";
        index++;
    }

    file.close();
}


void FileManager::readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        
    }
}
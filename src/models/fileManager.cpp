#include "models/fileManager.h"

#include <chrono>
#include <fstream>
#include <regex>


FileManager::FileManager(RecordList& recordListRef) : recordList(recordListRef) {}


const std::regex FileManager::RECORD_PATTERN(R"~(^\d+\. (\d\d):([0-5]{2}).(\d\d)\(?([DNF2\+]+)?\)?: ([UFRBLDw'2 ]+)$)~");


std::string FileManager::recordToString(const Record& record) {
    std::string conversion = Record::getFormattedTime(record.time, Penalty::NO_PENALTY);

    if (record.penalty != Penalty::NO_PENALTY) {
        conversion += "(" + Record::penaltyAsString(record.penalty) + ")";
    }

    conversion += ": " + record.scramble;
    return conversion;
}


Record FileManager::stringToRecord(std::string string) {
    std::smatch match;
    if (std::regex_match(string, match, RECORD_PATTERN)) {
        std::chrono::milliseconds time = Record::timeDivisionsToMilliseconds(
            std::stoi(match.str(1)), std::stoi(match.str(2)), std::stoi(match.str(3))
        );
        std::string scramble = match.str(5);
        
        Penalty penalty;
        if (match.str(4) == "DNF") {
            penalty = Penalty::DNF_PENALTY;
        } else if (match.str(4) == "+2") {
            penalty = Penalty::PLUS_2_PENALTY;
        } else {
            penalty = Penalty::NO_PENALTY;
        }

        return {time, scramble, penalty};
    } else {
        return {std::chrono::milliseconds(-1), "", Penalty::NO_PENALTY};
    }
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
    std::smatch match;
    while (std::getline(file, line)) {
        Record convertedRecord = stringToRecord(line);
        if (convertedRecord.time != std::chrono::milliseconds(-1)) {
            recordList.addRecord(convertedRecord);
        }
    }
}
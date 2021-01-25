#include "controllers/recordListController.h"

#include <stddef.h>

#include "controllers/baseController.h"
#include "myStructs.h"


RecordListController::RecordListController() :
        BaseController(),
        model(),
        viewModel(model),
        window(viewModel) {}


std::size_t RecordListController::getRecordCount() {
    return model.getRecordCount();
}


void RecordListController::moveUp() {
    viewModel.moveUp();
}


void RecordListController::moveDown() {
    viewModel.moveDown();
}


void RecordListController::addRecord(Record record) {
    model.addRecord(record);
    viewModel.recordAdded();
}


void RecordListController::togglePenalty(Penalty penalty, std::size_t recordNum) {
    model.togglePenalty(penalty, recordNum);
}


void RecordListController::togglePenaltyLatestRecord(Penalty penalty) {
    model.togglePenaltyLatestRecord(penalty);
}


void RecordListController::deleteRecord(std::size_t recordNum) {
    model.deleteRecord(recordNum);
}


void RecordListController::deleteLatestRecord() {
    model.deleteLatestRecord();
}


Record& RecordListController::getRecord(std::size_t recordNum) {
    return model.getRecord(recordNum);
}


void RecordListController::refresh() {
    window.werase();  // todo: flickering?
    window.makeBox();
    window.draw();
    window.wnoutrefresh();
}
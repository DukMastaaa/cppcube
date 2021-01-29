#include "controllers/recordListController.h"

#include <stddef.h>

#include "controllers/baseController.h"
#include "myStructs.h"


RecordListController::RecordListController() :
        BaseController(),
        model(),
        viewModel(model) {
    window = std::make_unique<BottomLeftWindow>(viewModel);
}


std::size_t RecordListController::getRecordCount() const {
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


void RecordListController::togglePenaltySelectedRecord(Penalty penalty) {
    model.togglePenalty(penalty, viewModel.getSelectedIndex());
}


void RecordListController::deleteRecord(std::size_t recordNum) {
    model.deleteRecord(recordNum);
}


void RecordListController::deleteLatestRecord() {
    model.deleteLatestRecord();
}


void RecordListController::deleteSelectedRecord() {
    model.deleteRecord(viewModel.getSelectedIndex());
}


const Record& RecordListController::getRecord(std::size_t recordNum) const {
    return model.getRecord(recordNum);
}


void RecordListController::refresh() const {
    window->makeBox();
    BaseController::refresh();
}
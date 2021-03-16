#include "views/popups/recordInfoPopupViewModel.h"

#include <iostream>

#include <ncurses.h>

#include "models/cubeTimer.h"
#include "myStructs.h"


RecordInfoPopupViewModel::RecordInfoPopupViewModel(RecordListViewModel& viewModelRef) : viewModel(viewModelRef) {};


Pos2D RecordInfoPopupViewModel::calcHeightWidth() const {
    unsigned maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    return {10, std::min<unsigned int>(55, 2 * maxX / 3)};

    // return {10, 40};  // maybe?!
}


void RecordInfoPopupViewModel::draw(WINDOW* window) const {
    ::werase(window);
    mvwprintw(window, 0, 0, "Record number %ld", viewModel.getSelectedIndex() + 1);

    Record selectedRecord = viewModel.getRecord(viewModel.getSelectedIndex());
    
    std::string finalTime = "Final time: " + CubeTimer::formatTime(selectedRecord.time, selectedRecord.penalty);
    if (selectedRecord.penalty != Penalty::NO_PENALTY) {
        finalTime += " (orig. " + CubeTimer::formatTime(selectedRecord.time, Penalty::NO_PENALTY) + ")";
    }
    mvwaddstr(window, 1, 0, finalTime.c_str());

    std::string scramble = "Scramble: " + selectedRecord.scramble;
    mvwaddstr(window, 2, 0, scramble.c_str());
}


PopupState RecordInfoPopupViewModel::receiveKeyboardInput(int input) {
    if (input == '\n') {
        return PopupState::CLOSE;
    } else {
        return PopupState::REFRESH;
    }
}


std::string RecordInfoPopupViewModel::getPopupReturnData() const {
    return "idk what to put here";
}


PopupState RecordInfoPopupViewModel::receiveData(std::string data) {
    return PopupState::REFRESH;
}


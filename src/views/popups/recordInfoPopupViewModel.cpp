#include "views/popups/recordInfoPopupViewModel.h"

#include <functional>
#include <iostream>

#include <ncurses.h>

#include "views/popups/inputPopupViewModel.h"
#include "controllers/popupControllers.h"
#include "models/cubeTimer.h"
#include "myStructs.h"
#include "app.h"


RecordInfoPopupViewModel::RecordInfoPopupViewModel(RecordListController& controllerRef) : controller(controllerRef) {};


Pos2D RecordInfoPopupViewModel::calcHeightWidth() const {
    unsigned maxY, maxX;
    (void) maxY;  // unused
    getmaxyx(stdscr, maxY, maxX);

    return {10, std::min<unsigned int>(55, 2 * maxX / 3)};
}


void RecordInfoPopupViewModel::draw(WINDOW* window) const {
    std::size_t selectedIndex = controller.getSelectedIndex();

    ::werase(window);
    mvwprintw(window, 0, 0, "Record number %ld", selectedIndex + 1);

    Record selectedRecord = controller.getRecord(selectedIndex);
    
    std::string finalTime = "Final time: " + CubeTimer::formatTime(selectedRecord.time, selectedRecord.penalty);
    if (selectedRecord.penalty != Penalty::NO_PENALTY) {
        finalTime += " (orig. " + CubeTimer::formatTime(selectedRecord.time, Penalty::NO_PENALTY) + ")";
    }
    mvwaddstr(window, 1, 0, finalTime.c_str());

    std::string scramble = "Scramble: " + selectedRecord.scramble;
    smartStringDisplay(window, scramble, 2, 0, 5);
}


PopupState RecordInfoPopupViewModel::receiveKeyboardInput(int input) {
    using namespace std::placeholders;  // for _1

    switch (input) {
        case '\n':
            return PopupState::CLOSE;
        
        case '2':
            controller.togglePenaltySelectedRecord(Penalty::PLUS_2_PENALTY);
            return PopupState::REFRESH;

        case 'd':
            controller.togglePenaltySelectedRecord(Penalty::DNF_PENALTY);
            return PopupState::REFRESH;

        case 'x':
            app->createPopup<YesNoPopupViewModel>(std::bind(&RecordInfoPopupViewModel::confirmDeletion, this, _1));
            // app->createPopup<YesNoPopupViewModel>(dummyPopupCallback);
            app->sendDataToLatestPopup("Confirm delete (y/n)?");
            return PopupState::NOREFRESH;

        default:
            return PopupState::REFRESH;
    }

    if (input == '\n') {
        return PopupState::CLOSE;
    } else {
        return PopupState::REFRESH;
    }
}


PopupState RecordInfoPopupViewModel::receiveData(std::string data) {
    return PopupState::REFRESH;
}


void RecordInfoPopupViewModel::receiveAppRef(App& appRef) {
    app = &appRef;
}


void RecordInfoPopupViewModel::confirmDeletion(std::string popupReturnData) {
    if (popupReturnData == "yes") {
        controller.deleteSelectedRecord();
        app->closeLatestPopup();
    }
}
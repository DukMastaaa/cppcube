#include "app.h"

#include <utility>
#include <string>
#include <iostream>
#include <functional>

#include <ncurses.h>

#include "controllers/popupControllers.h"
#include "controllers/normal/cubeController.h"
#include "controllers/normal/recordListController.h"
#include "controllers/normal/scramblerController.h"
#include "controllers/normal/timerController.h"

#include "views/popups/inputPopupViewModel.h"
#include "views/popups/recordInfoPopupViewModel.h"

#include "views/colours.h"
#include "myStructs.h"


App::App(int cubeDim) :
        cubeController(cubeDim),
        recordListController(),
        scramblerController(),
        timerController(),
        mainControllers{&cubeController, &recordListController, &scramblerController, &timerController},
        popupControllers(),
        dim(cubeDim),
        doAnUpdate(false),
        appRunning(true) {}


void App::refreshAllControllers() const {
    for (const auto& controller : mainControllers) {
        controller->refresh();
    }
    for (const auto& pair : popupControllers) {
        const auto& controllerPtr = pair.second;
        controllerPtr->refresh();
    }
}

void App::initialRefreshUpdate() {
    scramblerController.generateScramble(dim);
    cubeController.parseMovesReset(scramblerController.getLatestScramble());
    refreshAllControllers();
    doupdate();
}


void App::handleTerminalResize() {
    /* To handle terminal resize events, clear() must be called, followed by
    refresh(). This order is to ensure that the old screen image of windows is
    cleared before the new locations are drawn to the screen. */

    for (const auto& controller : mainControllers) {
        controller->handleResize();
    }
    for (const auto& pair : popupControllers) {
        const auto& controllerPtr = pair.second;
        controllerPtr->handleResize();
    }

    clear();  // stdscr clear
    refresh();  // stdscr refresh
    refreshAllControllers();  // wnoutrefresh for each window
    doupdate();
}


void App::toggleTimer() {
    timerController.toggleTiming();
    timerController.refresh();
    if (!timerController.isTiming()) {
        generateNewScramble();
        recordListController.addRecord({
            timerController.getTimeElapsed(), 
            scramblerController.getLatestScramble(), 
            Penalty::NO_PENALTY
        });
        recordListController.refresh();
    }
}


void App::togglePenalty(Penalty penalty, std::size_t recordNum) {
    if (recordListController.getRecordCount() != 0) {
        recordListController.togglePenalty(penalty, recordNum);

        if (recordNum == recordListController.getRecordCount() - 1) {
            timerController.togglePenalty(penalty);
            timerController.refresh();
        }
        recordListController.refresh();
    }
}


void App::moveSelectedRecordUp() {
    recordListController.moveUp();
    recordListController.refresh();
}


void App::moveSelectedRecordDown() {
    recordListController.moveDown();
    recordListController.refresh();
}


void App::moveSelectedRecordTop() {
    recordListController.moveToTop();
    recordListController.refresh();
}


void App::moveSelectedRecordBottom() {
    recordListController.moveToBottom();
    recordListController.refresh();
}


void App::jumpSelectedIndex(std::size_t index) {
    recordListController.jumpToIndex(index);
    recordListController.refresh();
}


void App::generateNewScramble() {
    scramblerController.generateScramble(dim);
    cubeController.parseMovesReset(scramblerController.getLatestScramble());
    cubeController.refresh();
    scramblerController.refresh();
}


void App::deleteLatestRecord() {
    using namespace std::placeholders;
    if (recordListController.getRecordCount() > 0) {
        createPopup<YesNoPopupViewModel>(std::bind(&App::confirmRecordDeletion, this, _1, recordListController.getRecordCount() - 1));
        sendDataToLatestPopup("Delete latest record? (y/n)");
    }
}


void App::deleteSelectedRecord() {
    using namespace std::placeholders;
    if (recordListController.getRecordCount() > 0) {
        std::size_t selectedIndex = recordListController.getSelectedIndex();
        createPopup<YesNoPopupViewModel>(std::bind(&App::confirmRecordDeletion, this, _1, selectedIndex));
        std::string description = "Delete record no. " + std::to_string(selectedIndex + 1) + "? (y/n)";
        sendDataToLatestPopup(description.c_str());
    }
}


void App::changeCubeDim(std::string popupReturnData) {
    if (popupReturnData.empty()) {
        return;
    }
    dim = std::stoi(popupReturnData);
    cubeController.resetState(dim);
    scramblerController.generateScramble(dim);
    cubeController.parseMovesReset(scramblerController.getLatestScramble());
    scramblerController.refresh();
    cubeController.handleResize();
    forceUpdate();
}


void App::confirmRecordDeletion(std::string popupReturnData, unsigned int recordIndex) {
    if (popupReturnData == "yes") {
        recordListController.deleteRecord(recordIndex);
        recordListController.refresh();
        forceUpdate();
    }
}



void App::mainWindowKeyboardInput(int input) {
    using namespace std::placeholders;  // for _1

    if (timerController.isTiming()) {
        switch (input) {
            // nothing here yet
        }
    } else {
        switch (input) {
            case '2': togglePenalty(Penalty::PLUS_2_PENALTY, recordListController.getRecordCount() - 1); break;
            case 'd': togglePenalty(Penalty::DNF_PENALTY, recordListController.getRecordCount() - 1); break;
            case 'x': deleteLatestRecord(); break;

            case '@': togglePenalty(Penalty::PLUS_2_PENALTY, recordListController.getSelectedIndex()); break;
            case 'D': togglePenalty(Penalty::DNF_PENALTY, recordListController.getSelectedIndex()); break;
            case 'X': deleteSelectedRecord(); break;

            case KEY_UP: moveSelectedRecordUp(); break;
            case KEY_DOWN: moveSelectedRecordDown(); break;

            case 'n': generateNewScramble(); break;

            case 't': moveSelectedRecordTop(); break;
            case 'b': moveSelectedRecordBottom(); break;

            case 'v': createPopup<CubeViewModel, CubeModel>(dummyPopupCallback, cubeController.getModelRef()); break;

            case 'p': createPopup<NumericInputPopupViewModel>(std::bind(&App::changeCubeDim, this, _1)); sendDataToLatestPopup("Input side length:"); break;

            case 'i': createPopup<RecordInfoPopupViewModel, RecordListViewModel>(dummyPopupCallback, recordListController.getViewModelRef()); break;

            case 'q': appRunning = false; break;
        }
    }

    switch (input) {
        case ERR: return;
        case ' ': toggleTimer(); break;
    }

    forceUpdate();
}


void App::keyboardInput(int input) {

    // this should be caught before any delegation to popups
    if (input == KEY_RESIZE) {
        handleTerminalResize();
        forceUpdate();
        return;
    }

    if (popupControllers.size() == 0) {
        mainWindowKeyboardInput(input);
    } else {
        auto& lastItem = popupControllers.back();

        PopupCallback callback = lastItem.first;
        auto& controllerPtr = lastItem.second;
        PopupState popupState = controllerPtr->receiveKeyboardInput(input);

        if (popupState == PopupState::CLOSE) {
            std::string returnData = controllerPtr->getPopupReturnData();
            controllerPtr.reset();
            popupControllers.pop_back();
            callback(returnData);

            clear();
            refresh();
            refreshAllControllers();
        }
    }
}


bool App::needUpdate() const {
    return doAnUpdate;
}


void App::turnOffUpdate() {
    doAnUpdate = false;
}


void App::forceUpdate() {
    doAnUpdate = true;
}


bool App::appIsRunning() const {
    return appRunning;
}


WINDOW* App::getWindow() const {
    if (popupControllers.size() == 0) {
        return cubeController.getWindow();
    } else {
        return popupControllers.back().second->getWindow();
    }
}


void App::sendDataToLatestPopup(std::string data) {
    if (popupControllers.size() != 0) {
        auto& controllerPtr = popupControllers.back().second;
        PopupState receiveState = controllerPtr->receiveData(data);
        if (receiveState == PopupState::RESIZE) {
            handleTerminalResize();
        } else {
            controllerPtr->refresh();
            forceUpdate();
        }
    }
}
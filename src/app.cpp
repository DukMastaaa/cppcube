#include "app.h"

#include <utility>
#include <string>
#include <iostream>
#include <functional>
#include <filesystem>

#include <ncurses.h>

#include "controllers/popupControllers.h"
#include "controllers/normal/cubeController.h"
#include "controllers/normal/recordListController.h"
#include "controllers/normal/scramblerController.h"
#include "controllers/normal/timerController.h"

#include "views/popups/infoPopupViewModel.h"
#include "views/popups/inputPopupViewModel.h"
#include "views/popups/recordInfoPopupViewModel.h"
#include "views/popups/summaryStatsPopupViewModel.h"
#include "views/popups/helpPopupViewModel.h"

#include "views/colours.h"
#include "models/fileManager.h"
#include "myStructs.h"


App::App(int cubeDim) :
        cubeController(cubeDim),
        recordListController(),
        scramblerController(),
        timerController(),
        summaryStatsModel(recordListController.getModelRef()),
        fileManager(recordListController.getModelRef()),
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
        pair.controller->refresh();
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
    refresh(). This order is to ensure that the old screen image of windows are
    cleared before the new locations are drawn to the screen. */

    for (const auto& controller : mainControllers) {
        controller->handleResize();
    }
    for (const auto& pair : popupControllers) {
        pair.controller->handleResize();
    }

    clear();  // stdscr clear
    refresh();  // stdscr refresh
    refreshAllControllers();  // wnoutrefresh for each window
    doupdate();
}


void App::createInfoPopup(std::string description) {
    createPopup<InfoPopupViewModel>(dummyPopupCallback);
    makeTitleForLatestPopup("Info");
    sendDataToLatestPopup(description);
}


void App::toggleTimer() {

    if (!timerController.isTiming() && recordListController.getRecordCount() >= 2000) {
        createInfoPopup("2000 record limit. Please export session and clear all.");
        return;
    }

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
        makeTitleForLatestPopup("Delete?");
    }
}


void App::deleteSelectedRecord() {
    using namespace std::placeholders;
    if (recordListController.getRecordCount() > 0) {
        std::size_t selectedIndex = recordListController.getSelectedIndex();
        createPopup<YesNoPopupViewModel>(std::bind(&App::confirmRecordDeletion, this, _1, selectedIndex));
        std::string description = "Delete record no. " + std::to_string(selectedIndex + 1) + "? (y/n)";
        sendDataToLatestPopup(description.c_str());
        makeTitleForLatestPopup("Delete?");
    }
}


void App::displayRecordInfoPopup() {
    if (recordListController.getRecordCount() > 0) {
        createPopup<RecordInfoPopupViewModel, RecordListController>(dummyPopupCallback, recordListController);
        makeTitleForLatestPopup("Record Info");
    }
}


// todo: duplication?
void App::exportTimes() {
    using namespace std::placeholders;  // for _1

    createPopup<InputPopupViewModel>(std::bind(&App::exportToFilename, this, _1));
    makeTitleForLatestPopup("Export Data");
    sendDataToLatestPopup("Filename? Current is default.");
    sendDataToLatestPopup("times.txt");
}


void App::importTimes() {
    using namespace std::placeholders;  // for _1

    createPopup<InputPopupViewModel>(std::bind(&App::importFromFilename, this, _1));
    makeTitleForLatestPopup("Import Data");
    sendDataToLatestPopup("Filename? Current is default.");
    sendDataToLatestPopup("times.txt");
}


void App::changeCubeDim(std::string popupReturnData) {
    if (popupReturnData == "") {
        return;
    }

    if (popupReturnData.length() >= 3 || std::stoi(popupReturnData) > 20) {
        createInfoPopup("Maximum length is 20.");
        return;
    }

    dim = std::stoi(popupReturnData);
    cubeController.resetState(dim);
    scramblerController.generateScramble(dim);
    cubeController.parseMovesReset(scramblerController.getLatestScramble());
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


void App::jumpToSelectedIndex(std::string popupReturnData) {
    if (popupReturnData == "" || popupReturnData.length() >= 4) {
        return;
    }

    unsigned int index = std::stoi(popupReturnData) - 1;
    if (index < recordListController.getRecordCount()) {
        recordListController.jumpToIndex(index);
        recordListController.refresh();
    }
}


void App::exportToFilename(std::string popupReturnData) {
    if (popupReturnData != "") {
        if (popupReturnData.find("/") == std::string::npos && popupReturnData.find("\\") == std::string::npos) {
            fileManager.exportFile(popupReturnData);
        } else {
            createInfoPopup("Invalid file path.");
        }
    }
}


void App::importFromFilename(std::string popupReturnData) {
    if (popupReturnData != "") {
        if (popupReturnData.find("/") != std::string::npos || popupReturnData.find("\\") != std::string::npos) {
            createInfoPopup("Invalid file path.");
        } else if (!std::filesystem::exists(popupReturnData)) {
            createInfoPopup("File does not exist.");
        } else {
            recordListController.deleteAllRecords();
            fileManager.readFile(popupReturnData);
            recordListController.moveToTop();
            refreshAllControllers();
            forceUpdate();
        }
    }
}


void App::closeProgram(std::string popupReturnData) {
    if (popupReturnData == "yes") {
        appRunning = false;
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

            // POPUPS

            case 'v': 
                createPopup<CubeViewModel, CubeModel>(dummyPopupCallback, cubeController.getModelRef());
                makeTitleForLatestPopup("Cube View");
                break;
            
            case 's':
                createPopup<ScramblerViewModel, CubeScrambler>(dummyPopupCallback, scramblerController.getModelRef());
                makeTitleForLatestPopup("Scramble View");
                break;

            case 'p': 
                createPopup<NumericInputPopupViewModel>(std::bind(&App::changeCubeDim, this, _1));
                makeTitleForLatestPopup("Change Puzzle");
                sendDataToLatestPopup("Input side length:"); 
                break;

            case 'i': 
                displayRecordInfoPopup(); 
                break;
            
            case 'h':
                createPopup<HelpPopupViewModel>(dummyPopupCallback);
                makeTitleForLatestPopup("Help");
                break;

            case 'g': 
                createPopup<SummaryStatsPopupViewModel, SummaryStatsModel>(dummyPopupCallback, summaryStatsModel);
                makeTitleForLatestPopup("Summary Stats");
                break;

            case 'j': 
                createPopup<NumericInputPopupViewModel>(std::bind(&App::jumpToSelectedIndex, this, _1));
                makeTitleForLatestPopup("Jump");
                sendDataToLatestPopup("Jump to index:"); 
                break;

            case 'q': 
                createPopup<YesNoPopupViewModel>(std::bind(&App::closeProgram, this, _1)); 
                makeTitleForLatestPopup("Quit?");
                sendDataToLatestPopup("Exit cppcube? (y/n)"); 
                break;
        
            case 'E': exportTimes(); break;

            case 'I': importTimes(); break;
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
        PopupState popupState = lastItem.controller->receiveKeyboardInput(input);

        if (popupState == PopupState::CLOSE) {
            closeLatestPopup();
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
        return popupControllers.back().controller->getWindow();
    }
}


void App::sendDataToLatestPopup(std::string data) {
    if (popupControllers.size() != 0) {
        auto& controller = popupControllers.back().controller;
        PopupState receiveState = controller->receiveData(data);
        if (receiveState == PopupState::RESIZE) {
            handleTerminalResize();
        } else {
            controller->refresh();
            forceUpdate();
        }
    }
}


void App::makeTitleForLatestPopup(std::string title) {
    if (popupControllers.size() != 0) {
        auto& controller = popupControllers.back().controller;
        controller->makeTitle(title);
        controller->refresh();
        forceUpdate();
    }
}


void App::closeLatestPopup() {

    auto& lastItem = popupControllers.back();
    PopupCallback callback = lastItem.callback;
    auto& controller = lastItem.controller;

    std::string returnData = controller->getPopupReturnData();
    controller.reset();
    popupControllers.pop_back();
    callback(returnData);

    // clear();
    // refresh();
    // refreshAllControllers();
    handleTerminalResize();  // overkill, but other options don't move resized windows.
    forceUpdate();
}
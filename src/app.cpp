#include "app.h"

#include <utility>
#include <iostream>

#include <ncurses.h>

#include "controllers/basePopupController.h"
#include "controllers/cubeController.h"
#include "controllers/recordListController.h"
#include "controllers/scramblerController.h"
#include "controllers/timerController.h"
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
    cubeController.parseMovesReset(scramblerController.generateScramble(dim));
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
    if (!timerController.isTiming() && recordListController.getRecordCount() != 0) {
        recordListController.togglePenalty(penalty, recordNum);

        if (recordNum == recordListController.getRecordCount() - 1) {
            timerController.togglePenalty(penalty);
            timerController.refresh();
        }
        recordListController.refresh();
    }
}


void App::moveSelectedRecord(Direction direction) {
    // todo: huh
    if (!timerController.isTiming()) {
        switch (direction) {
            case Direction::UP_DIR:
                recordListController.moveUp();
                break;
            case Direction::DOWN_DIR:
                recordListController.moveDown();
                break;
            default:
                break;
        }
        recordListController.refresh();
    }
}


void App::moveToEndsOfRecords(Direction direction) {
    if (!timerController.isTiming()) {
        switch (direction) {
            case Direction::UP_DIR:
                recordListController.moveToTop();
                break;
            case Direction::DOWN_DIR:
                recordListController.moveToBottom();
                break;
            default:
                break;
        }
        recordListController.refresh();
    }
}


void App::jumpSelectedIndex(std::size_t index) {
    if (!timerController.isTiming()) {
        recordListController.jumpToIndex(index);
        recordListController.refresh();
    }
}


void App::generateNewScramble() {
    if (!timerController.isTiming()) {
        cubeController.parseMovesReset(scramblerController.generateScramble(dim));
        cubeController.refresh();
        scramblerController.refresh();
    }
}


void App::makeCubeViewPopup() {
    // popupControllers.push_back(std::make_unique)  // todo: resume
}


void App::mainWindowKeyboardInput(int input) {
    switch (input) {
        case ERR: return; break;

        case KEY_RESIZE: handleTerminalResize(); break;

        case ' ': toggleTimer(); break;

        case '2': togglePenalty(Penalty::PLUS_2_PENALTY, recordListController.getRecordCount() - 1); break;
        case 'd': togglePenalty(Penalty::DNF_PENALTY, recordListController.getRecordCount() - 1); break;

        case '@': togglePenalty(Penalty::PLUS_2_PENALTY, recordListController.getSelectedIndex()); break;
        case 'D': togglePenalty(Penalty::DNF_PENALTY, recordListController.getSelectedIndex()); break;

        case KEY_UP: moveSelectedRecord(Direction::UP_DIR); break;
        case KEY_DOWN: moveSelectedRecord(Direction::DOWN_DIR); break;

        case 'n': generateNewScramble(); break;

        case 't': moveToEndsOfRecords(Direction::UP_DIR); break;
        case 'b': moveToEndsOfRecords(Direction::DOWN_DIR); break;

        case 'v': createPopup<

        case 'q': appRunning = false; break;
    }
    doAnUpdate = true;
}


void App::keyboardInput(int input) {
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
    // todo: is below comment still true after popups?
    // doesn't really matter what controller, any window other than stdscr will do
    return cubeController.getWindow();  
}


template<typename T>
void App::createPopup(PopupCallback callback) {
    popupControllers.push_back(std::make_pair(callback, std::make_unique<T>()));  // todo: constructor for T
}
#include "app.h"

#include <iostream>

#include <ncurses.h>

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
        dim(cubeDim),
        doAnUpdate(false),
        appRunning(true) {}


void App::initialRefreshUpdate() {
    cubeController.parseMovesReset(scramblerController.generateScramble(dim));
    cubeController.refresh();
    recordListController.refresh();
    scramblerController.refresh();
    timerController.refresh();
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


// todo: duplicated
void App::togglePenaltyLatestRecord(Penalty penalty) {
    if (!timerController.isTiming() && recordListController.getRecordCount() != 0) {
        recordListController.togglePenaltyLatestRecord(penalty);
        timerController.togglePenalty(penalty);
        timerController.refresh();
        recordListController.refresh();
    }
}


void App::togglePenaltySelectedRecord(Penalty penalty) {
    if (!timerController.isTiming() && recordListController.getRecordCount() != 0) {
        recordListController.togglePenaltySelectedRecord(penalty);
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


void App::moveSelectedRecordUp() {
    if (!timerController.isTiming()) {
        recordListController.moveUp();
        recordListController.refresh();
    }
}


void App::moveSelectedRecordDown() {
    // todo: duplicated
    if (!timerController.isTiming()) {
        recordListController.moveDown();
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


void App::keyboardInput(int input) {
    switch (input) {
        case ERR:
            return;
            break;

        case ' ':
            toggleTimer();
            break;
        
        case '2':
            togglePenaltyLatestRecord(Penalty::PLUS_2_PENALTY);
            break;
        
        case 'd':
            togglePenaltyLatestRecord(Penalty::DNF_PENALTY);
            break;

        case '@':
            togglePenaltySelectedRecord(Penalty::PLUS_2_PENALTY);
            break;

        case 'D':
            togglePenaltySelectedRecord(Penalty::DNF_PENALTY);
            break;
        
        case KEY_UP:
            moveSelectedRecordUp();
            break;
        
        case KEY_DOWN:
            moveSelectedRecordDown();
            break;
        
        case 'n':
            generateNewScramble();
            break;
        
        case 'q':
            appRunning = false;
            break;
    }
    doAnUpdate = true;
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
    return cubeController.getWindow();
}
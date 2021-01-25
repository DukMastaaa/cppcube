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
        doAnUpdate(false),
        dim(cubeDim),
        cubeController(dim),
        recordListController(),
        scramblerController(),
        timerController() {}


void App::initialRefreshUpdate() {
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
        cubeController.parseMovesReset(scramblerController.generateScramble(dim));
        recordListController.addRecord({
            timerController.getTimeElapsed(), 
            scramblerController.getLatestScramble(), 
            Penalty::NO_PENALTY
        });
        cubeController.refresh();
        scramblerController.refresh();
        recordListController.refresh();
    }
    doAnUpdate = true;
}


void App::togglePenalty(Penalty penalty) {
    if (!timerController.isTiming() && recordListController.getRecordCount() != 0) {
        recordListController.togglePenaltyLatestRecord(penalty);
        timerController.togglePenalty(penalty);
        timerController.refresh();
        recordListController.refresh();
        doAnUpdate = true;
    }
}


void App::moveSelectedRecordUp() {
    if (!timerController.isTiming()) {
        recordListController.moveUp();
        recordListController.refresh();
        doAnUpdate = true;
    }
}


void App::moveSelectedRecordDown() {
    // todo: duplicated
    if (!timerController.isTiming()) {
        recordListController.moveDown();
        recordListController.refresh();
        doAnUpdate = true;
    }
}


void App::keyboardInput(int input) {
    switch (input) {
        case ' ':
            toggleTimer();
            break;
        
        case '2':
            togglePenalty(Penalty::PLUS_2_PENALTY);
            break;
        
        case 'd':
            togglePenalty(Penalty::DNF_PENALTY);
            break;
        
        case 'w':
            moveSelectedRecordUp();
            break;
        
        case 's':
            moveSelectedRecordDown();
            break;
        
        case 'q':
            appRunning = false;
            break;
    }
}


bool App::needUpdate() {
    return doAnUpdate;
}


void App::turnOffUpdate() {
    doAnUpdate = false;
}


void App::forceUpdate() {
    doAnUpdate = true;
}


bool App::appIsRunning() {
    return appRunning;
}
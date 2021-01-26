#include "testapp.h"

#include <ncurses.h>


TestApp::TestApp() :
        cubeController(3),
        doAnUpdate(false),
        appRunning(true) {}


void TestApp::initialRefreshUpdate() {
    cubeController.parseMovesReset("R U R' F' R2 R");
    cubeController.refresh();
    doupdate();
}


void TestApp::keyboardInput(int input) {
    switch (input) {
        case ' ':
            cubeController.parseMovesReset("R U R' U'");
            cubeController.refresh();
            doAnUpdate = true;
            break;
        
        case 'q':
            appRunning = false;
            break;
    }
}


void TestApp::turnOffUpdate() {
    doAnUpdate = false;
}


bool TestApp::needUpdate() {
    return doAnUpdate;
}


bool TestApp::appIsRunning() {
    return appRunning;
}


WINDOW* TestApp::getWindow() {
    return cubeController.getWindow();
}
/*
#pragma once

#include <ncurses.h>

#include "controllers/cubeController.h"


class TestApp {
    private:
        CubeController cubeController;
        bool doAnUpdate;
        bool appRunning;

    public:
        TestApp();
        void initialRefreshUpdate();
        void keyboardInput(int input);
        bool needUpdate();
        void turnOffUpdate();
        bool appIsRunning();
        WINDOW* getWindow();
};
*/
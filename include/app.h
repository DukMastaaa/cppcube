#pragma once

#include <ncurses.h>

#include "controllers/cubeController.h"
#include "controllers/recordListController.h"
#include "controllers/scramblerController.h"
#include "controllers/timerController.h"


class App {
    private:
        CubeController cubeController;
        RecordListController recordListController;
        ScramblerController scramblerController;
        TimerController timerController;

        int dim;  // todo: only temporary
        bool doAnUpdate;
        bool appRunning;

        // app functionality
        void toggleTimer();
        void togglePenalty(Penalty penalty);
        void moveSelectedRecordUp();
        void moveSelectedRecordDown();

    public:
        App(int cubeDim);
        void initialRefreshUpdate();
        void keyboardInput(int input);
        bool needUpdate();
        void turnOffUpdate();
        void forceUpdate();
        bool appIsRunning();
};
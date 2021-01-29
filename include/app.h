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
        void togglePenaltyLatestRecord(Penalty penalty);
        void togglePenaltySelectedRecord(Penalty penalty);
        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void moveSelectedRecordUp();
        void moveSelectedRecordDown();
        void generateNewScramble();

    public:
        App(int cubeDim);
        void initialRefreshUpdate();
        void keyboardInput(int input);
        bool needUpdate() const;
        void turnOffUpdate();
        void forceUpdate();
        bool appIsRunning() const;
        WINDOW* getWindow() const;
};
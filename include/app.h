#pragma once

#include <ncurses.h>

#include "controllers/cubeController.h"
#include "controllers/recordListController.h"
#include "controllers/scramblerController.h"
#include "controllers/timerController.h"
#include "myStructs.h"


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
        void togglePenalty(Penalty penalty, std::size_t recordNum);
        void moveSelectedRecord(Direction direction);
        void moveToEndsOfRecords(Direction direction);
        void jumpSelectedIndex(std::size_t index);
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
#pragma once

#include <ncurses.h>

#include "controllers/cubeController.h"
#include "controllers/recordListController.h"
#include "controllers/scramblerController.h"
#include "controllers/timerController.h"


class Controller {
    private:
        
        /*
        CubeModel cubeModel;
        CubeViewModel cubeViewModel;
        BottomRightWindow cubeWindow;

        CubeScrambler cubeScrambler;
        ScramblerViewModel scramblerViewModel;
        DefaultWindow scramblerWindow;

        CubeTimer cubeTimer;
        TimerViewModel timerViewModel;
        CentredWindow timerWindow;

        RecordList recordList;
        RecordListViewModel recordListViewModel;
        DefaultWindow recordListWindow;
        */  // todo: resume

        int dim;  // todo: only temporary
        bool doAnUpdate;

    public:
        Controller(int cubeDim);
        void initialRefresh();
        void keyboardInput(int input);
        bool needUpdate();

};
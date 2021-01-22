#include "controller.h"

#include <iostream>

#include <ncurses.h>

#include "colours.h"
#include "cubes.h"
#include "scrambler.h"
#include "cubeTimer.h"
#include "windowClasses.h"
#include "cubeViewModel.h"
#include "scramblerViewModel.h"
#include "timerViewModel.h"
#include "myStructs.h"
#include "recordList.h"
#include "recordListViewModel.h"


Controller::Controller() {  // todo: resume, no default ctor for cubemodel
    dim = 5;
    doAnUpdate = false;

    CubeScrambler cubeScrambler;
    CubeModel cubeModel(dim);
    cubeModel.parseMoves(cubeScrambler.getScramble(dim));
    
    CubeViewModel cubeViewModel(cubeModel);
    BottomRightWindow cubeWindow(CubeViewModel);

    ScramblerViewModel scramblerViewModel(cubeScrambler);
    DefaultWindow scramblerWindow(scramblerViewModel, 0, 0);

    RecordList recordList;
    RecordListViewModel recordListViewModel(recordList);
    DefaultWindow recordListWindow(recordListViewModel, 6, 0);

    CubeTimer cubeTimer;
    TimerViewModel timerViewModel(cubeTimer);
    CentredPopupWindow timerWindow(timerViewModel);
}
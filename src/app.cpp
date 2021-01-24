/*
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


Controller::Controller(int cubeDim) : 
        dim(cubeDim), 
        cubeScrambler(), cubeModel(dim), cubeViewModel(cubeModel), cubeWindow(cubeViewModel), 
        scramblerViewModel(cubeScrambler), scramblerWindow(scramblerViewModel, 0, 0), 
        recordList(), recordListViewModel(recordList), recordListWindow(recordListViewModel, 6, 0), 
        cubeTimer(), timerViewModel(cubeTimer), timerWindow(timerViewModel) {

    doAnUpdate = false;

    
    CubeScrambler cubeScrambler;
    CubeModel cubeModel(dim);
    cubeModel.parseMoves(cubeScrambler.generateScramble(dim));
    
    CubeViewModel cubeViewModel(cubeModel);
    BottomRightWindow cubeWindow(CubeViewModel);

    ScramblerViewModel scramblerViewModel(cubeScrambler);
    DefaultWindow scramblerWindow(scramblerViewModel, 0, 0);

    RecordList recordList;
    RecordListViewModel recordListViewModel(recordList);
    DefaultWindow recordListWindow(recordListViewModel, 6, 0);

    CubeTimer cubeTimer;
    TimerViewModel timerViewModel(cubeTimer);
    CentredWindow timerWindow(timerViewModel);
    
}
*/
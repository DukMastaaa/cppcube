/*
#include <ncurses.h>

#include "cubes.h"
#include "scrambler.h"
#include "cubeTimer.h"
#include "windowClasses.h"
#include "cubeViewModel.h"
#include "scramblerViewModel.h"
#include "timerViewModel.h"
#include "recordList.h"
#include "recordListViewModel.h"


class Controller {
    private:
        CubeModel cubeModel;
        CubeViewModel cubeViewModel;
        BottomRightWindow cubeWindow;

        CubeScrambler cubeScrambler;
        ScramblerViewModel scramblerViewModel;
        DefaultWindow scramblerWindow;

        CubeTimer cubeTimer;
        TimerViewModel timerViewModel;
        CentredPopupWindow timerWindow;

        RecordList recordList;
        RecordListViewModel recordListViewModel;
        DefaultWindow recordListWindow;  // todo: change to BottomLeftWindow or something idk

        int dim;  // todo: only temporary
        bool doAnUpdate;

    public:
        Controller(int cubeDim);
        void initialRefresh();
        void keyboardInput(int input);
        bool needUpdate();

};
*/
#include <iostream>
#include <random>

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

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    timeout(0);  // non-blocking getch().
    startColours();

    int dim = 5;

    CubeScrambler cs;
    CubeModel cube(dim);
    cube.parseMoves(cs.getScramble(dim));

    RecordList recordList;
    RecordListViewModel rlvm(recordList);
    DefaultWindow rlwin(rlvm, 6, 0);

    CubeViewModel cubevm(cube);
    BottomRightWindow cwin(cubevm);

    ScramblerViewModel scramblervm(cs);
    DefaultWindow swin(scramblervm, 0, 0);

    CubeTimer ct;
    TimerViewModel tvm(ct);
    CentredPopupWindow twin(tvm);


    // surely i have to design a better interface instead of `true, false, false`...
    cwin.fullRefresh(true, false, false);
    swin.fullRefresh(true, false, false);
    twin.fullRefresh(false, false, false);
    rlwin.fullRefresh(true, false, false);
    doupdate();

    int input;
    while (input != 'q') {
        input = wgetch(cwin.window);

        switch (input) {
            case ' ':
                ct.toggleTiming();
                twin.fullRefresh(false, false, true);
                if (!ct.isTiming) {
                    cube.resetState();
                    cube.parseMoves(cs.getScramble(dim));
                    recordList.addRecord({ct.getTimeElapsed(), cs.getMostRecentScramble(), NO_PENALTY});
                    rlvm.recordAdded();
                    cwin.fullRefresh();
                    swin.fullRefresh();
                    rlwin.fullRefresh();
                }
                doupdate();
                break;
            
            case '2':
            case 'd':
                if (!ct.isTiming && recordList.getRecordCount() != 0) {
                    Penalty appliedPenalty = (input == '2') ? PLUS_2_PENALTY : DNF_PENALTY;
                    recordList.togglePenaltyLatestRecord(appliedPenalty);
                    ct.togglePenalty(appliedPenalty);
                    twin.fullRefresh(false, true, false);
                    rlwin.fullRefresh();
                    doupdate();
                }
                break;
            
            case 'w':
            case 's':
                if (!ct.isTiming) {
                    if (input == 'w') {
                        rlvm.moveUp();
                    } else if (input == 's') {
                        rlvm.moveDown();
                    }
                    rlwin.fullRefresh();
                    doupdate();
                }
                break;
        }
    }
    
    endwin();
    return 0;
}
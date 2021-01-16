#include <ncurses.h>
#include <iostream>
#include <random>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"
#include "scrambler.h"
#include "windowClasses.h"
#include "scramblerView.h"
#include "cubeTimer.h"
#include "timerView.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    timeout(0);  // non-blocking getch().
    startColours();

    int dim = 3;

    CubeScrambler cs;
    CubeModel cube(dim);
    cube.parseMoves(cs.getScramble(dim));

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
    doupdate();

    char input;
    while (input != 'q') {
        input = wgetch(cwin.window);
        if (input == ' ') {
            ct.toggleTiming();
            twin.fullRefresh(false, false, true);

            if (!ct.isTiming) {
                cube.resetState();
                cube.parseMoves(cs.getScramble(dim));
                cwin.fullRefresh();
                swin.fullRefresh();
            }
            doupdate();
        }
    }
    
    endwin();
    return 0;
}
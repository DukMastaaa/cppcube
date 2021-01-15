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
    startColours();

    int dim = 4;

    CubeScrambler cs;
    CubeModel cube(dim);
    std::string scramble = cs.getScramble(dim);
    cube.parseMoves(scramble);


    CubeViewModel cubevm(cube);
    BottomRightWindow brwin(cubevm);
    brwin.draw();
    brwin.makeBox();
    brwin.wnoutrefresh();

    ScramblerViewModel scramblervm(cs);
    DefaultWindow swin(scramblervm, 0, 0);
    swin.draw();
    swin.makeBox();
    swin.wnoutrefresh();

    CubeTimer ct;
    TimerViewModel tvm(ct);
    CentredPopupWindow twin(tvm);
    twin.draw();
    twin.makeBox();
    twin.wnoutrefresh();

    doupdate();

    char beans;
    bool isTiming;
    while (beans != 'q') {
        beans = wgetch(brwin.window);
            if (beans == 't') {
                ct.startTimingAndReset();
            } else if (beans == 's') {
                ct.stopTiming();
                twin.draw();
                twin.makeBox();
                twin.wnoutrefresh();
            }
    }
    
    endwin();

    return 0;
}
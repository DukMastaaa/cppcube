#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"


void ncursesSetup() {
    initscr();
    noecho();
    cbreak();
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    curs_set(0);
    // timeout(0);
    keypad(stdscr, TRUE);
    startColours();
}


int main() {
    ncursesSetup();

    int dim = 3;
    int counter = 0;

    App app(dim);
    app.initialRefreshUpdate();

    int input;
    while (app.appIsRunning()) {
        if (app.needUpdate()) {
            // clearok(curscr, TRUE);  // todo: temporary solution to ncurses bug?
            doupdate();
            app.turnOffUpdate();
        }
        input = wgetch(app.getWindow());
        if (input != ERR) {
            app.keyboardInput(input);
        }
    }
    
    endwin();
    return 0;
}
#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"


void ncursesSetup() {
    initscr();
    startColours();
    noecho();
    cbreak();
    // leaveok(stdscr, true);
    // scrollok(stdscr, false);
    curs_set(0);
    // timeout(0);  // don't really need non-blocking wgetch()
    keypad(stdscr, true);
}


int main() {
    ncursesSetup();

    App app(3);
    app.initialRefreshUpdate();

    int input;
    while (app.appIsRunning()) {
        if (app.needUpdate()) {
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
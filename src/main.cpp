#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"
#include "models/cubes.h"


void ncursesSetup() {
    initscr();
    setlocale(LC_ALL, "");
    startColours();
    noecho();
    cbreak();
    // leaveok(stdscr, true);
    // scrollok(stdscr, false);
    curs_set(0);
    // timeout(0);  // don't really need non-blocking wgetch()
    keypad(stdscr, true);
}


void cycleBlockChar() {
    if (BLOCK_CHAR == ACS_BLOCK) {
        BLOCK_CHAR = ACS_CKBOARD;
    } else if (BLOCK_CHAR == ACS_CKBOARD) {
        BLOCK_CHAR = ACS_DIAMOND;
    } else if (BLOCK_CHAR == ACS_DIAMOND) {
        BLOCK_CHAR = ACS_BLOCK;
    }
}


int main() {
    setenv("ESCDELAY", "25", 1);
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
        if (input == ',') {
            cycleBlockChar();
            app.forceUpdate();
        } else if (input != ERR) {
            app.keyboardInput(input);
        }
    }
    
    endwin();
    return 0;
}
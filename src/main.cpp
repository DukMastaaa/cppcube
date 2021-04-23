/**
 * @file main.cpp
 * @brief Contains main loop and initialises ncurses.
 */


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
        if (input != ERR) {
            app.keyboardInput(input);
        }
    }
    
    endwin();
    return 0;
}
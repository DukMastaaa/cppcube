#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    timeout(0);  // non-blocking getch().
    startColours();

    int dim = 5;

    App app(dim);
    app.initialRefreshUpdate();

    int input;
    while (app.appIsRunning()) {
        input = wgetch(stdscr);
        app.keyboardInput(input);
        if (app.needUpdate()) {
            doupdate();
        }
    }
    
    endwin();
    return 0;
}
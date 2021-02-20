#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"


int main() {
    // ncursesSetup();

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
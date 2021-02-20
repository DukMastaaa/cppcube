#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"


int main() {
    // ncursesSetup();

    App::initialRefreshUpdate();

    int input;
    while (App::appIsRunning()) {
        if (App::needUpdate()) {
            doupdate();
            App::turnOffUpdate();
        }
        input = wgetch(App::getWindow());
        if (input != ERR) {
            App::keyboardInput(input);
        }
    }
    
    endwin();
    return 0;
}
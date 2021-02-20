#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"


int main() {
    // ncursesSetup();

<<<<<<< HEAD
    App::initialRefreshUpdate();
=======
    int dim = 3;

    App app(dim);
    app.initialRefreshUpdate();
>>>>>>> parent of 2245c45... input popups done

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
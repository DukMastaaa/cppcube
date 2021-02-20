#include <iostream>
#include <random>

#include <ncurses.h>

#include "app.h"
#include "myStructs.h"
#include "views/colours.h"
#include "models/cubes.h"


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


void printarray(const Vector2DSquare<int>& arr, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            std::cout << arr.at(i, j);
        }
        std::cout << '\n';
    }
}


int main2() {
    // Vector2DSquare<int> array(2, 0);
    // printarray(array, 2);
    // array.reset(2);
    // printarray(array, 2);
    // array.resetAndResize(3, 5);
    // printarray(array, 3);
    // array.resetAndResize(2, 9);
    // printarray(array, 2);

    // array.at(0, 0) = 1;
    // array.at(0, 1) = 2;
    // array.at(1, 0) = 3;
    // array.at(1, 1) = 4;
    // printarray(array, 2);
    // array.rot90();
    // printarray(array, 2);

    CubeModel model(2);
    // model.coutDisplayNet();
    model.parseMovesReset("R U R' U'");
    // model.coutDisplayNet(); 
}
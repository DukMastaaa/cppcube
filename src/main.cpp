#include <iostream>
#include <random>

#include <ncurses.h>

#include "testapp.h"
#include "myStructs.h"
#include "views/colours.h"


void ncursesSetup() {
    initscr();
    noecho();
    cbreak();
    leaveok(stdscr, true);
    scrollok(stdscr, false);
    curs_set(0);
    // timeout(0);
    startColours();
}


// int main() {
//     std::cout << "test";
//     int test;
//     std::cin >> test;
//     ncursesSetup();
//     int dim = 5;
//     App app(dim);
//     getch();
//     return 0;
// }

int main() {
    ncursesSetup();

    int dim = 2;

    WINDOW* test = newwin(0, 0, 3, 10);
    mvwprintw(test, 0, 0, "test");
    wnoutrefresh(test);

    TestApp app;
    app.initialRefreshUpdate();
    doupdate();

    int input;
    while (app.appIsRunning()) {
        if (app.needUpdate()) {
            mvwprintw(test, 0, 0, "test");
            wnoutrefresh(test);
            doupdate();
            app.turnOffUpdate();
        }
        input = wgetch(app.getWindow());
        app.keyboardInput(input);
    }
    
    endwin();
    return 0;
}
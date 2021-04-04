#include <iostream>
#include <ncurses.h>


void ncursesSetup() {
    initscr();
    setlocale(LC_ALL, "");
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
    while (true) {
        int input = getch();
        if (input == 'q') {
            break;
        } else {
            std::cout << input << '\n';
        }
    }

    endwin();
}
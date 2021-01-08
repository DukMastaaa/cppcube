#include <ncurses.h>
#include <iostream>

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    int beforeX, beforeY;
    getmaxyx(stdscr, beforeY, beforeX);
    WINDOW* meow = newwin(5, 5, 0, 0);
    int afterX, afterY;
    getmaxyx(stdscr, afterY, afterX);
    int lolx, loly;
    getmaxyx(meow, lolx, loly);
    endwin();
    std::cout << beforeX << ' ' << beforeY << '\n';
    std::cout << afterX << ' ' << afterY << '\n';
    std::cout << lolx << ' ' << loly << '\n';
    return 0;
}
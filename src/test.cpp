#include <ncurses.h>

/*
basically, to handle window moving:
1. mvwin(base, ...);
2. refresh();
3. do other stuff as normal.
you DON'T need to delete sub and 
call derwin again.
*/

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    WINDOW* base = newwin(5, 20, 1, 1);
    WINDOW* sub = derwin(base, 3, 10, 1, 1);
    box(base, 'h', 'v');
    mvwprintw(sub, 0, 0, "beans lol");
    wnoutrefresh(base);
    doupdate();
    wgetch(base);

    mvwin(base, 5, 5);
    wresize(base, 6, 25);
    refresh();
    werase(base);
    box(base, 'h', 'v');
    mvwprintw(sub, 1, 1, "abcdefghijklmnop");
    wnoutrefresh(base);
    doupdate();
    wgetch(base);
    endwin();
}
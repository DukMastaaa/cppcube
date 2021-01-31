// #include <ncurses.h>

/*
basically, to handle window moving:
1. mvwin(base, ...);
2. clear();
2. refresh();
3. do other stuff as normal.
you DON'T need to delete sub and 
call derwin again.
*/

/*
int main() {
    int counter = 0;
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW* bl = newwin(5, 10, maxY - 1 - 5, 0);
    box(bl, 'h', 'v');
    mvwprintw(bl, 0, 0, "beans lol");
    wnoutrefresh(bl);

    WINDOW* br = newwin(5, 8, maxY - 1 - 5, maxX - 1 - 10);
    box(br, 'h', 'v');
    mvwprintw(br, 0, 0, "meow h");
    wnoutrefresh(br);

    doupdate();
    int input;
    while (input != 'q') {
        input = wgetch(bl);
        if (input == KEY_RESIZE) {
            int maxY, maxX;
            getmaxyx(stdscr, maxY, maxX);
            mvwin(bl, maxY - 1 - 5, 0);
            mvwin(br, maxY - 1 - 5, maxX - 1 - 10);
            clear();
            refresh();
            // wclear(bl);
            // wclear(br);
            box(bl, 'h', 'v');
            box(br, 'h', 'v');
            mvwprintw(bl, 1, 1, "bl %d", counter);
            mvwprintw(br, 2, 2, "br %d", counter);
            wnoutrefresh(bl);
            wnoutrefresh(br);
            doupdate();
            counter++;
        }
    }
    endwin();
}
*/
#include "views/colours.h"

#include <ncurses.h>


void startColours() {
    // try to override magenta colour to orange. no effect if fail.
    init_color(COLOR_MAGENTA, 255, 165, 0);

    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(ORANGE_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);  // if override fails, orange displayed as magenta
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
}
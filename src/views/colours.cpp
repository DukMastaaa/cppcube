#include "views/colours.h"

#include <ncurses.h>


void startColours() {
    // try to override magenta colour to orange. no effect if fail.
    // init_color(COLOR_MAGENTA, 255, 165, 0);
    use_default_colors();
    

    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, -1);
    init_pair(GREEN_ON_BLACK, COLOR_GREEN, -1);
    init_pair(RED_ON_BLACK, COLOR_RED, -1);
    init_pair(BLUE_ON_BLACK, COLOR_BLUE, -1);
    init_pair(ORANGE_ON_BLACK, COLOR_MAGENTA, -1);  // if override fails, orange displayed as magenta
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, -1);
    init_pair(BLACK_ON_WHITE, -1, COLOR_WHITE);
}
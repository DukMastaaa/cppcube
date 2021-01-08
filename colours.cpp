#include <ncurses.h>
#include "colours.h"


void startColours() {
    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(ORANGE_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);  // no orange..
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
}
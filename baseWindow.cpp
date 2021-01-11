#include <ncurses.h>
#include "baseWindow.h"


void BaseWindow::wnoutrefresh() {
    ::wnoutrefresh(viewWindow);
}
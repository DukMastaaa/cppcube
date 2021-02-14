#include "views/normal/simpleViewModel.h"


SimpleViewModel::SimpleViewModel() {}


Pos2D SimpleViewModel::calcHeightWidth() const {
    return {10, 40};
}


void SimpleViewModel::draw(WINDOW* window) const {
    werase(window);
    ::box(window, '|', '-');
    mvwprintw(window, 1, 1, "this is a popup");
    mvwprintw(window, 3, 1, "beanos");
}
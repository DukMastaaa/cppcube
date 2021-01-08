#include <ncurses.h>
#include <tuple>
#include <cubes.h>
#include "cubeView.h"
#include "colours.h"


static std::tuple<int, int> calcHeightWidth(int dim, int spacing) {
    /* Calculates height and width of the window 
    given cube of size `dim`. */
    int height = 3 * dim + 2 * spacing;
    int width = 4 * dim + 3 * spacing;
    return std::make_tuple(height, width);
}


static std::tuple<int, int> calcTopLeftPos(int dim, int spacing) {
    /* Calculates the position (y, x) of the top-left corner of the window
    given cube of size `dim`. */
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int width, height;
    std::tie(width, height) = calcHeightWidth(dim, spacing);

    int topLeftX = maxX - width;
    int topLeftY = maxY - height;

    return std::make_tuple(topLeftY, topLeftX);
}


CubeView::CubeView(CubeModel& cubeRef) :
        cube(cubeRef) {
    int height, width;
    std::tie(height, width) = calcHeightWidth(cube.dim, 1);

    int topLeftY, topLeftX;
    std::tie(topLeftY, topLeftX) = calcTopLeftPos(cube.dim, 1);
    viewWindow = newwin(height, width, topLeftY, topLeftX);
}


void CubeView::draw() {
    int yOffset = 0;  // keeps track of y pos in window after each layer

    // FACE_UP
    int upOffset = cube.dim + 1;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            int thisColour = cube.getColourAtSticker(FACE_UP, row, col);

            wattron(viewWindow, COLOR_PAIR(thisColour));
            mvwaddch(viewWindow, yOffset + row, upOffset + col, BLOCK);
            wattroff(viewWindow, COLOR_PAIR(thisColour));
        }
    }

    yOffset = cube.dim + 1;

    // 




}


void CubeView::wnoutrefresh() {
    ::wnoutrefresh(viewWindow);
}
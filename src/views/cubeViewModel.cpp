#include "views/cubeViewModel.h"

#include <utility>

#include <ncurses.h>

#include "models/cubes.h"
#include "views/colours.h"


Pos2D CubeViewModel::calcHeightWidth() const {
    /* Calculates height and width of the window given the side length
    of `cube`. */
    unsigned int height = 3 * cube.dim + 2 * NET_SPACING;
    unsigned int width = 4 * cube.dim + 3 * NET_SPACING;
    return {height, width};
}


CubeViewModel::CubeViewModel(CubeModel& cubeRef) : cube(cubeRef) { }


void CubeViewModel::draw(WINDOW* window) const {
    /* Clears and draws cube window. */
    wclear(window);

    int yOffset = 0;  // keeps track of y pos in window after each layer

    // UP
    int leftOffset = cube.dim + NET_SPACING;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            int thisColour = cube.getColourAtSticker(UP, row, col);

            wattron(window, COLOR_PAIR(thisColour));
            mvwaddch(window, yOffset + row, leftOffset + col, BLOCK);
            wattroff(window, COLOR_PAIR(thisColour));
        }
    }

    yOffset = cube.dim + NET_SPACING;

    // LEFT, FRONT, RIGHT, BACK
    static const int middleFaces[] = {LEFT, FRONT, RIGHT, BACK};
    for (int row = 0; row < cube.dim; row++ ) {
        for (int faceIndex = 0; faceIndex < 4; faceIndex++) {
            leftOffset = faceIndex * (cube.dim + 1);
            for (int col = 0; col < cube.dim; col++) {
                int thisColour = cube.getColourAtSticker(middleFaces[faceIndex], row, col);

                wattron(window, COLOR_PAIR(thisColour));
                mvwaddch(window, yOffset + row, leftOffset + col, BLOCK);
                wattroff(window, COLOR_PAIR(thisColour));
            }
        }
    }

    yOffset = 2 * (cube.dim + NET_SPACING);

    // DOWN  // duplicated code... aeugh
    leftOffset = cube.dim + NET_SPACING;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            int thisColour = cube.getColourAtSticker(DOWN, row, col);

            wattron(window, COLOR_PAIR(thisColour));
            mvwaddch(window, yOffset + row, leftOffset + col, BLOCK);
            wattroff(window, COLOR_PAIR(thisColour));
        }
    }
}



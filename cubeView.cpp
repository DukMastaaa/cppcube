#include <ncurses.h>
#include <utility>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"


std::pair<int, int> CubeView::calcHeightWidth() {
    /* Calculates height and width of the window given the side length
    of `cube`. */
    int height = 3 * cube.dim + 2 * SPACING;
    int width = 4 * cube.dim + 3 * SPACING;

    height += 2 * BORDER_THICKNESS;
    width += 2 * BORDER_THICKNESS;
    return std::make_pair(height, width);
}


CubeView::CubeView(CubeModel& cubeRef) : cube(cubeRef) { }


void CubeView::draw(WINDOW* window) {
    int yOffset = 0;  // keeps track of y pos in window after each layer

    // FACE_UP
    int leftOffset = cube.dim + 1;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            int thisColour = cube.getColourAtSticker(FACE_UP, row, col);

            wattron(window, COLOR_PAIR(thisColour));
            mvwaddch(window, yOffset + row + BORDER_THICKNESS, leftOffset + col + BORDER_THICKNESS, BLOCK);
            wattroff(window, COLOR_PAIR(thisColour));
        }
    }

    yOffset = cube.dim + 1;

    // FACE_LEFT, FACE_FRONT, FACE_RIGHT, FACE_BACK
    static const int middleFaces[] = {FACE_LEFT, FACE_FRONT, FACE_RIGHT, FACE_BACK};
    for (int row = 0; row < cube.dim; row++ ) {
        for (int faceIndex = 0; faceIndex < 4; faceIndex++) {
            leftOffset = faceIndex * (cube.dim + 1);
            for (int col = 0; col < cube.dim; col++) {
                int thisColour = cube.getColourAtSticker(middleFaces[faceIndex], row, col);

                wattron(window, COLOR_PAIR(thisColour));
                mvwaddch(window, yOffset + row + BORDER_THICKNESS, leftOffset + col + BORDER_THICKNESS, BLOCK);
                wattroff(window, COLOR_PAIR(thisColour));
            }
        }
    }

    yOffset = 2 * (cube.dim + 1);

    // FACE_DOWN  // duplicated code... aeugh
    leftOffset = cube.dim + 1;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            int thisColour = cube.getColourAtSticker(FACE_DOWN, row, col);

            wattron(window, COLOR_PAIR(thisColour));
            mvwaddch(window, yOffset + row + BORDER_THICKNESS, leftOffset + col + BORDER_THICKNESS, BLOCK);
            wattroff(window, COLOR_PAIR(thisColour));
        }
    }
}



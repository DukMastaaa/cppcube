#include <ncurses.h>
#include <tuple>
#include "cubes.h"
#include "cubeView.h"
#include "colours.h"


std::tuple<int, int> CubeView::calcHeightWidth(int dim, int spacing) {
    /* Calculates height and width of the window 
    given cube of size `dim`. */
    int height = 3 * dim + 2 * spacing;
    int width = 4 * dim + 3 * spacing;
    return std::make_tuple(height, width);
}


std::tuple<int, int> CubeView::calcTopLeftPos(int dim, int spacing) {
    /* Calculates the position (y, x) of the top-left corner of the window
    given cube of size `dim`. */
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int height, width;
    std::tie(height, width) = calcHeightWidth(dim, spacing);

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


char intToDigit(int number) {
    switch (number) {
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        default:
            return 'h';
    }
}




void CubeView::draw() {
    int yOffset = 0;  // keeps track of y pos in window after each layer

    // FACE_UP
    int leftOffset = cube.dim + 1;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            
            int thisColour = cube.getColourAtSticker(FACE_UP, row, col);
            wattron(viewWindow, COLOR_PAIR(thisColour));
            mvwaddch(viewWindow, yOffset + row, leftOffset + col, BLOCK);
            wattroff(viewWindow, COLOR_PAIR(thisColour));
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
                wattron(viewWindow, COLOR_PAIR(thisColour));
                mvwaddch(viewWindow, yOffset + row, leftOffset + col, BLOCK);
                wattroff(viewWindow, COLOR_PAIR(thisColour));
                
            }
        }
    }

    yOffset = 2 * (cube.dim + 1);

    // FACE_DOWN  // duplicated code... aeugh
    leftOffset = cube.dim + 1;
    for (int row = 0; row < cube.dim; row++) {
        for (int col = 0; col < cube.dim; col++) {
            
            int thisColour = cube.getColourAtSticker(FACE_DOWN, row, col);
            wattron(viewWindow, COLOR_PAIR(thisColour));
            mvwaddch(viewWindow, yOffset + row, leftOffset + col, BLOCK);
            wattroff(viewWindow, COLOR_PAIR(thisColour));
        }
    }
}


void CubeView::wnoutrefresh() {
    ::wnoutrefresh(viewWindow);
}
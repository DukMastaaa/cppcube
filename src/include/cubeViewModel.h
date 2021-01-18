#pragma once

#include <utility>

#include <ncurses.h>

#include "baseViewModel.h"
#include "cubes.h"
#include "myStructs.h"


class CubeViewModel : public BaseViewModel {
    private:
        CubeModel& cube;
        static const char BLOCK = '#';
        static const int SPACING = 1;
    
    public:
        CubeViewModel(CubeModel& cubeRef);
        Pos2D calcHeightWidth();
        void draw(WINDOW* window);
};
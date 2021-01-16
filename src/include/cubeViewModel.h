#pragma once
#include <ncurses.h>
#include <utility>
#include "baseViewModel.h"
#include "cubes.h"
#include "position.h"


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
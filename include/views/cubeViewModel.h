#pragma once

#include <utility>

#include <ncurses.h>

#include "views/baseViewModel.h"
#include "models/cubes.h"
#include "myStructs.h"


class CubeViewModel : public BaseViewModel {
    private:
        CubeModel& model;
        static const char BLOCK = '#';
        static const int NET_SPACING = 1;
    
    public:
        CubeViewModel(CubeModel& cubeRef);
        Pos2D calcHeightWidth() const override;
        void draw(WINDOW* window) const override;
};
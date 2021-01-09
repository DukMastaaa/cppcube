#pragma once
#include <ncurses.h>
#include <tuple>
#include "cubes.h"


class CubeView {
    private:
        CubeModel& cube;
    
    public:
        WINDOW* viewWindow;
        static const char BLOCK = '#';
        static std::tuple<int, int> calcHeightWidth(int dim, int spacing = 1);
        static std::tuple<int, int> calcTopLeftPos(int dim, int spacing = 1);
        CubeView(CubeModel& cubeRef);
        void draw();
        void wnoutrefresh();
};
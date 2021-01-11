#pragma once
#include <ncurses.h>
#include <tuple>
#include "baseWindow.h"
#include "cubes.h"


class CubeView : public BaseWindow {
    private:
        CubeModel& cube;
        static const char BLOCK = '#';
    
    public:
        static std::tuple<int, int> calcHeightWidth(int dim, int spacing = 1);
        static std::tuple<int, int> calcTopLeftPos(int dim, int spacing = 1);
        CubeView(CubeModel& cubeRef);
        void draw();
};
#pragma once

#include <iostream>

#include "controllers/baseController.h"
#include "models/cubes.h"
#include "views/cubeViewModel.h"
#include "windows/windowClasses.h"


class CubeController : public BaseController {
    private:
        CubeModel cubeModel;
        CubeViewModel cubeViewModel;
        BottomRightWindow cubeWindow;
        int dim;

    public:
        CubeController(int cubeDim);
        void parseMoves(std::string scramble);
        void refresh();
};
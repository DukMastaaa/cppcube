#pragma once

#include <iostream>
#include <memory>

#include "controllers/baseController.h"
#include "models/cubes.h"
#include "views/cubeViewModel.h"
#include "windows/windowClasses.h"


class CubeController : public BaseController {
    protected:
        CubeModel model;
        int dim;

    public:
        CubeController(int cubeDim);
        void parseMovesReset(std::string scramble);
        void parseMovesNoReset(std::string scramble);
        void resetState();
        void resetState(int dim);
        void refresh() const override;
};
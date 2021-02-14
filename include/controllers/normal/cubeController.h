#pragma once

#include <iostream>

#include "controllers/baseController.h"
#include "models/cubes.h"
#include "views/normal/cubeViewModel.h"
#include "windows/windowClasses.h"


class CubeController : public BaseController {
    public:
        CubeController(int cubeDim);
        void parseMovesReset(std::string scramble);
        void parseMovesNoReset(std::string scramble);
        void resetState();
        void resetState(int dim);
        void refresh() const override;
        CubeModel& getModelRef();

    protected:
        CubeModel model;
        CubeViewModel viewModel;
        int dim;
};
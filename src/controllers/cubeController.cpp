#include "controllers/cubeController.h"

#include <iostream>

#include "controllers/baseController.h"

CubeController::CubeController(int cubeDim) : 
        BaseController(), 
        dim(cubeDim), 
        model(dim), 
        viewModel(model), 
        window(viewModel) {}


void CubeController::parseMovesReset(std::string scramble) {
    model.parseMovesReset(scramble);
}


void CubeController::parseMovesNoReset(std::string scramble) {
    model.parseMovesNoReset(scramble);
}


void CubeController::resetState() {
    model.resetState();
}


void CubeController::resetState(int dim) {
    model.resetState(dim);
}


void CubeController::refresh() {
    window.makeBox();
    window.draw();
    window.wnoutrefresh();
}


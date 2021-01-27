#include "controllers/cubeController.h"

#include <iostream>

#include "controllers/baseController.h"


CubeController::CubeController(int cubeDim) : BaseController(), model(cubeDim) {
    viewModel = std::make_unique<CubeViewModel>(model);
    window = std::make_unique<BottomRightWindow>(viewModel);
}


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


void CubeController::refresh() const {
    window->makeBox();
    window->draw();
    window->wnoutrefresh();
    touchwin(window->fullWindow);
}
#include "controllers/scramblerController.h"

#include <iostream>

#include "controllers/baseController.h"


ScramblerController::ScramblerController() : 
        BaseController(), 
        model(), 
        viewModel(model), 
        window(viewModel, 0, 0) {}


std::string ScramblerController::generateScramble(int dim) {
    return model.generateScramble(dim);
}


std::string ScramblerController::getLatestScramble() {
    return model.getLatestScramble();
}


void ScramblerController::refresh() {
    // todo: duplicated? maybe
    window.makeBox();
    window.werase();
    window.draw();
    window.wnoutrefresh();
}
#include "controllers/scramblerController.h"

#include <iostream>
#include <memory>

#include "controllers/baseController.h"


ScramblerController::ScramblerController() : 
        BaseController(), 
        model(), 
        viewModel(model) {
    window = std::make_unique<DefaultWindow>(viewModel, 0, 0);
}


std::string ScramblerController::generateScramble(int dim) {
    return model.generateScramble(dim);
}


std::string ScramblerController::getLatestScramble() const {
    return model.getLatestScramble();
}


void ScramblerController::refresh() const {
    window->makeBox();
    BaseController::refresh();
}
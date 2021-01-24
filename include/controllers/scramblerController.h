#pragma once

#include <iostream>

#include "controllers/baseController.h"
#include "models/scrambler.h"
#include "views/scramblerViewModel.h"
#include "windows/windowClasses.h"


class ScramblerController : public BaseController {
    private:
        CubeScrambler model;
        ScramblerViewModel viewModel;
        DefaultWindow window;
    
    public:
        ScramblerController();
        std::string generateScramble(int dim);
        std::string getLatestScramble();
        void refresh();
};
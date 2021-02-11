#pragma once

#include <iostream>

#include "controllers/baseController.h"
#include "models/scrambler.h"
#include "views/scramblerViewModel.h"
#include "windows/windowClasses.h"


class ScramblerController : public BaseController {
    public:
        CubeScrambler model;
        ScramblerController();
        std::string generateScramble(int dim);
        std::string getLatestScramble() const;
        void refresh() const override;
    
    private:
        ScramblerViewModel viewModel;
};
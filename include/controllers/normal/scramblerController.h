#pragma once

#include <iostream>

#include "controllers/baseController.h"
#include "models/scrambler.h"
#include "views/normal/scramblerViewModel.h"
#include "windows/windowClasses.h"


class ScramblerController : public BaseController {
    public:
        ScramblerController();
        std::string generateScramble(int dim);
        std::string getLatestScramble() const;
        void refresh() const override;

        const CubeScrambler& getModelRef() const;
    
    private:
        CubeScrambler model;
        ScramblerViewModel viewModel;
};
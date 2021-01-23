#pragma once

#include "controllers/baseController.h"
#include "models/scrambler.h"
#include "views/scramblerViewModel.h"
#include "windows/windowClasses.h"


class ScramblerController : public BaseController {
    private:
        CubeScrambler scrambler;
        ScramblerViewModel scramblerViewModel;
        DefaultWindow scramblerWindow;
    
    public:
        ScramblerController();
        // todo: resume, rename getScramble -> generateScramble, getMos.. -> getLatestScramble
}
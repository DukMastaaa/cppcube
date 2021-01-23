#pragma once

#include "views/baseViewModel.h"
#include "models/scrambler.h"
#include "myStructs.h"


class ScramblerViewModel : public BaseViewModel {
    private:
        CubeScrambler& scrambler;

    public:
        ScramblerViewModel(CubeScrambler& scramblerRef);
        Pos2D calcHeightWidth();  // if not in a popup
        void draw(WINDOW* window);
};
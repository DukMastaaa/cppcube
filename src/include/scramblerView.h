#pragma once
#include "baseViewModel.h"
#include "scrambler.h"
#include "position.h"


class ScramblerViewModel : public BaseViewModel {
    private:
        CubeScrambler& scrambler;

    public:
        ScramblerViewModel(CubeScrambler& scramblerRef);
        Pos2D calcHeightWidth();  // if not in a popup
        void draw(WINDOW* window);
};
#pragma once
#include "baseViewModel.h"
#include "scrambler.h"


class ScramblerViewModel : public BaseViewModel {
    private:
        CubeScrambler& scrambler;

    public:
        ScramblerViewModel(CubeScrambler& scramblerRef);
        std::pair<int, int> calcHeightWidth();  // if not in a popup
        void draw(WINDOW* window);
};
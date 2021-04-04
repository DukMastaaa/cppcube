#pragma once

#include "views/baseViewModel.h"
#include "models/scrambler.h"
#include "myStructs.h"


class ScramblerViewModel : public BaseViewModel {
    private:
        const CubeScrambler& scrambler;

    public:
        ScramblerViewModel(const CubeScrambler& scramblerRef);
        Pos2D calcHeightWidth() const override;  // if not in a popup
        void draw(WINDOW* window) const override;
};
#pragma once

#include "views/baseViewModel.h"


class SimpleViewModel : public BaseViewModel {
    public:
        SimpleViewModel();
        Pos2D calcHeightWidth() const override;
        void draw(WINDOW* window) const override;
};
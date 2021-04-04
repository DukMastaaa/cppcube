#pragma once

#include <array>

#include "views/baseViewModel.h"


class HelpPopupViewModel : public BaseViewModel {
    public:
        HelpPopupViewModel();

        virtual Pos2D calcHeightWidth() const override;
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
    
    private:
        unsigned int currentPage;
        static const std::array<std::string, 4> helpPages;
        static const std::array<std::string, 4> pageTitles;
};
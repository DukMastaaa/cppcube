#pragma once

#include <views/baseViewModel.h>


class InfoPopupViewModel : public BaseViewModel {
    public:
        InfoPopupViewModel();

        virtual Pos2D calcHeightWidth() const override;  // don't take borders into account
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
        virtual std::string getPopupReturnData() const override;
        virtual PopupState receiveData(std::string data) override;

    
    private:
        std::string description;
};
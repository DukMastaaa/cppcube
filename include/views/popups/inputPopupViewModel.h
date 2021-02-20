#pragma once

#include "views/baseViewModel.h"
#include "myStructs.h"


class InputPopupViewModel : public BaseViewModel {
    public:
        InputPopupViewModel();

        virtual Pos2D calcHeightWidth() const override;  // don't take borders into account
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();
        virtual void receiveData(std::string data);
    
    protected:
        std::string inputText;
        std::string description;
};


class NumericInputPopupViewModel : public InputPopupViewModel {
    // this class specifically only takes in positive integers as input
    // only number key presses, backspace, enter will register
};
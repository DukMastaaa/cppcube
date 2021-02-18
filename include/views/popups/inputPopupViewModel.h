#pragma once

#include "views/baseViewModel.h"
#include "myStructs.h"


class InputPopupViewModel : public BaseViewModel {
    public:
        InputPopupViewModel();

        virtual Pos2D calcHeightWidth() const override;  // don't take borders into account
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
        virtual std::string getPopupReturnData() const override;
        virtual PopupState receiveData(std::string data) override;

        virtual bool isCharAllowed(int inputChar) const;
    
    protected:
        std::string inputText;
        std::string description;
};


class NumericInputPopupViewModel : public InputPopupViewModel {
    public:
        NumericInputPopupViewModel();
        virtual bool isCharAllowed(int inputChar) const override;
};
#pragma once

#include <iostream>
#include <utility>

#include <ncurses.h>

#include "myStructs.h"
#include "models/baseModel.h"


class PopupControllerInterface;


class BaseViewModel {
    protected:
        static const int BORDER_THICKNESS = 1;

    public:
        BaseViewModel();

        // maxLines is maximum number of lines written down
        static void smartStringDisplay(WINDOW* window, const std::string& text, int startRow = 0, int startCol = 0, int maxLines = -1);
        virtual Pos2D calcHeightWidth() const = 0;  // don't take borders into account
        virtual void draw(WINDOW* window) const = 0;

        // popup-specific stuff

        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData() const;
        virtual PopupState receiveData(std::string data);
        
        // Placeholder for popup controllers to pass a PopupControllerInterface& to the popup view model.
        // This is specifically for popup vms to create new popup vms through App.
        virtual void receivePopupControllerInterface(PopupControllerInterface& interfaceRef);
};
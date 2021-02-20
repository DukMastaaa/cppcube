#include "controllers/popupControllers.h"

#include "myStructs.h"

#include "app.h"


PopupControllerInterface::PopupControllerInterface() {}


PopupState PopupControllerInterface::receiveKeyboardInput(int input) {
    PopupState popupState = window->receiveKeyboardInput(input);
    switch (popupState) {
        case PopupState::REFRESH:
            refresh();
            App::forceUpdate();
            break;
        
        case PopupState::NOREFRESH:
        case PopupState::CLOSE:
            break;
    }
    return popupState;
}


std::string PopupControllerInterface::getPopupReturnData() {
    return window->getPopupReturnData();
}


void PopupControllerInterface::receiveData(std::string data) {
    window->receiveData(data);
}


void PopupControllerInterface::refresh() const {
    window->makeBox();
    BaseController::refresh();
}
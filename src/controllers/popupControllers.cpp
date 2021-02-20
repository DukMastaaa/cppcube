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
        case PopupState::RESIZE:
            break;
    }
    return popupState;
}


std::string PopupControllerInterface::getPopupReturnData() {
    return window->getPopupReturnData();
}


PopupState PopupControllerInterface::receiveData(std::string data) {
    return window->receiveData(data);
}


void PopupControllerInterface::refresh() const {
    window->makeBox();
    BaseController::refresh();
}
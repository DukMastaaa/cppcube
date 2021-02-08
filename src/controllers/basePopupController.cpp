#include "controllers/basePopupController.h"

#include "myStructs.h"


BasePopupController::BasePopupController() {

}


PopupState BasePopupController::receiveKeyboardInput(int input) {
    PopupState popupState = window->receiveKeyboardInput(input);
    switch (popupState) {
        case PopupState::REFRESH:
            refresh();
            break;
        
        case PopupState::NOREFRESH:
        case PopupState::CLOSE:
            break;
    }
    return popupState;
}


std::string BasePopupController::getPopupReturnData() {
    return window->getPopupReturnData();
}
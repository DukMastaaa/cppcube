#include "controllers/basePopupController.h"

#include "myStructs.h"

#include "app.h"


BasePopupController::BasePopupController(App& appRef) : app(appRef) {}


PopupState BasePopupController::receiveKeyboardInput(int input) {
    PopupState popupState = window->receiveKeyboardInput(input);
    switch (popupState) {
        case PopupState::REFRESH:
            refresh();
            app.forceUpdate();
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
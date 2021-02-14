#include "controllers/popupControllers.h"

#include "myStructs.h"

#include "app.h"


PopupControllerInterface::PopupControllerInterface(App& appRef) : app(appRef) {}


PopupState PopupControllerInterface::receiveKeyboardInput(int input) {
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


std::string PopupControllerInterface::getPopupReturnData() {
    return window->getPopupReturnData();
}
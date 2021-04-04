#include "controllers/popupControllers.h"

#include "myStructs.h"

#include "app.h"


PopupControllerInterface::PopupControllerInterface(App& appRef) : app(appRef), title{} {}


PopupState PopupControllerInterface::receiveKeyboardInput(int input) {
    PopupState popupState = window->receiveKeyboardInput(input);
    switch (popupState) {
        case PopupState::REFRESH:
            refresh();
            app.forceUpdate();
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


PopupState PopupControllerInterface::makeTitle(std::string titleText) {
    title = titleText;
    return PopupState::REFRESH;
}


void PopupControllerInterface::refresh() const {
    window->makeBox();
    window->title(title);
    BaseController::refresh();
}
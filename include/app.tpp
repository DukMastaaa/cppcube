#pragma once

#include "app.h"


template<typename ViewModel, typename ModelClass, typename Window>
void App::createPopup(PopupCallback callback, ModelClass& modelRef) {
    popupControllers.push_back(
        {
            callback,
            std::make_unique<PopupController<ViewModel, ModelClass, Window>>(*this, modelRef)
        }
    );
    popupControllers.back().controller->refresh();
}


template<typename ViewModel, typename ModelClass, typename Window>
void App::createPopup(PopupCallback callback, const ModelClass& constModelRef) {
    popupControllers.push_back(
        {
            callback,
            std::make_unique<PopupController<ViewModel, ModelClass, Window>>(*this, constModelRef)
        }
    );
    popupControllers.back().controller->refresh();
}


template<typename ViewModel>
void App::createPopup(PopupCallback callback) {
    popupControllers.push_back(
        {
            callback,
            std::make_unique<PopupController<ViewModel>>(*this)
        }
    );
    popupControllers.back().controller->refresh();
}

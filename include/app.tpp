#pragma once

#include "app.h"

// todo: this can't be it

template<typename ViewModel, typename ModelClass, typename Window>
void App::createPopup(PopupCallback callback, ModelClass& modelRef) {
    popupControllers.push_back(
        std::make_pair(
            callback, std::make_unique<PopupController<ViewModel, ModelClass, Window>>(modelRef)
        )
    );
    popupControllers.back().second->refresh();
}

template<typename ViewModel>
void App::createPopup(PopupCallback callback) {
    popupControllers.push_back(
        std::make_pair(
            callback, std::make_unique<PopupController<ViewModel>>()
        )
    );
    popupControllers.back().second->refresh();
}
#pragma once

#include "app.h"

// todo: this can't be it

// template<typename ViewModel, typename ModelClass, typename Window>
// void App::createPopup<ViewModel, ModelClass, Window>(PopupCallback callback, ModelClass& modelRef) {
//     popupControllers.push_back(
//         std::make_pair(
//             callback, std::make_unique<PopupController<ViewModel, ModelClass, Window>>(*this, modelRef)
//         )
//     );
// }


// template<typename ViewModel, typename ModelClass>
// void App::createPopup<ViewModel, ModelClass>(PopupCallback callback, ModelClass& modelRef) {
//     popupControllers.push_back(
//         std::make_pair(
//             callback, std::make_unique<PopupController<ViewModel, ModelClass, CentredWindow>>(*this, modelRef)
//         )
//     );
// }

template<typename ViewModel>
void App::createPopup(PopupCallback callback) {
    popupControllers.push_back(
        std::make_pair(
            callback, std::make_unique<PopupController<ViewModel>>(*this)
        )
    );
    popupControllers.back().second->refresh();
}

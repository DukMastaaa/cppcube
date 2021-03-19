#pragma once

#include "controllers/popupControllers.h"

#include <memory>


template<typename ViewModel, typename ModelClass, typename Window>
PopupController<ViewModel, ModelClass, Window>::PopupController(App& appRef, ModelClass& modelRef) : 
        PopupControllerInterface(appRef), viewModel(modelRef) {
    window = std::make_unique<Window>(viewModel);
    viewModel.receiveAppRef(app);
}


template<typename ViewModel>
PopupController<ViewModel>::PopupController(App& appRef) : 
        PopupControllerInterface(appRef), viewModel() {
    window = std::make_unique<CentredWindow>(viewModel);
    viewModel.receiveAppRef(app);
}
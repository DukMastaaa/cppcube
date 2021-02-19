#pragma once

#include "controllers/popupControllers.h"

#include <memory>


template<typename ViewModel, typename ModelClass, typename Window>
PopupController<ViewModel, ModelClass, Window>::PopupController(ModelClass& modelRef) : 
        PopupControllerInterface(), viewModel(modelRef) {
    window = std::make_unique<Window>(viewModel);
}


template<typename ViewModel>
PopupController<ViewModel>::PopupController() : 
        PopupControllerInterface(), viewModel() {
    window = std::make_unique<CentredWindow>(viewModel);
}
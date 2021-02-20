#pragma once

#include <iostream>

#include "myStructs.h"
#include "controllers/baseController.h"
#include "views/baseViewModel.h"
#include "windows/windowClasses.h"


class App;  // aeugh


class PopupControllerInterface : public BaseController {
    public:
        PopupControllerInterface();
        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();  // todo: does this need to be virtual?
        virtual void refresh() const override;
        void receiveData(std::string data);
};


template<typename ViewModel, typename ModelClass = BaseModel, typename Window = CentredWindow>
class PopupController : public PopupControllerInterface {
    public:
        PopupController(ModelClass& modelRef);

    private:
        ViewModel viewModel;
};


template <typename ViewModel>
class PopupController<ViewModel> : public PopupControllerInterface {
    public:
        PopupController();
    
    private:
        ViewModel viewModel;
};


#include "controllers/popupControllers.tpp"
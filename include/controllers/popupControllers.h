#pragma once

#include <iostream>

#include "app.h"
#include "myStructs.h"
#include "controllers/baseController.h"
#include "views/baseViewModel.h"
#include "windows/windowClasses.h"


// class App;  // aeugh


class PopupControllerInterface : public BaseController {
    protected:
        App& app;

    public:
        PopupControllerInterface(App& appRef);
        virtual PopupState receiveKeyboardInput(int input);
        std::string getPopupReturnData();
        virtual void refresh() const override;
        PopupState receiveData(std::string data);

        template<typename ViewModel, typename ModelClass, typename Window = CentredWindow>
        void createPopup(PopupCallback callback, ModelClass& modelRef);

        template<typename ViewModel>
        void createPopup(PopupCallback callback);
};


template<typename ViewModel, typename ModelClass = BaseModel, typename Window = CentredWindow>
class PopupController : public PopupControllerInterface {
    public:
        PopupController(App& appRef, ModelClass& modelRef);

    private:
        ViewModel viewModel;
};


template <typename ViewModel>
class PopupController<ViewModel> : public PopupControllerInterface {
    public:
        PopupController(App& appRef);
    
    private:
        ViewModel viewModel;
};


#include "controllers/popupControllers.tpp"
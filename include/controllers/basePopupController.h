#pragma once

#include <type_traits>

#include "myStructs.h"
#include "controllers/baseController.h"
#include "views/baseViewModel.h"
#include "windows/windowClasses.h"


class App;  // aeugh



class BasePopupController : public BaseController {
    protected:
        App& app;

    public:
        BasePopupController(App& appRef);
        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();  // todo: does this need to be virtual?
};
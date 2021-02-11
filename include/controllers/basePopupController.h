#pragma once

#include "controllers/baseController.h"

#include "myStructs.h"


class App;  // aeugh


class BasePopupController : public BaseController {
    protected:
        App& app;

    public:
        BasePopupController(App& appRef);
        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();  // todo: does this need to be virtual?
};
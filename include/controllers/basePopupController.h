#pragma once

#include "controllers/baseController.h"

#include "myStructs.h"


class BasePopupController : public BaseController {
    public:
        BasePopupController();
        virtual PopupState receiveKeyboardInput(int input);
        virtual std::string getPopupReturnData();  // todo: does this need to be virtual?
};
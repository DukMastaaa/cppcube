#pragma once


#include "windows/windowClasses.h"


class BaseController {
    // todo: don't have much here
    public:
        BaseController();
        virtual void refresh() = 0;
};
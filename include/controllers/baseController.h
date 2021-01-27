#pragma once

#include <memory>

#include <ncurses.h>

#include "views/baseViewModel.h"
#include "windows/windowClasses.h"


class BaseController {
    protected:
        // in derived classes of `BaseController`, we can't use initialiser lists for the 
        // unique_ptrs because they lack copy constructors. have to reassign in constructor body.
        std::unique_ptr<BaseViewModel> viewModel;
        std::unique_ptr<BaseWindow> window;

    public:
        BaseController();
        virtual void refresh() const;  // if you want to draw box, override, draw box and call base function
        WINDOW* getWindow() const;
};
#pragma once

#include <ncurses.h>

#include "controllers/baseController.h"
#include "views/baseViewModel.h"
#include "windows/windowClasses.h"
#include "myStructs.h"


class TestModel {};


class TestViewModel : public BaseViewModel {
    private:
        TestModel& model;

    public:
        TestViewModel(TestModel& modelRef);
        Pos2D calcHeightWidth();
        void draw(WINDOW* window);
};


class TestController : public BaseController {
    private:
        TestModel model;
        TestViewModel viewModel;
        CentredWindow window;
    
    public:
        TestController();
        void refresh();
        WINDOW* getWindow();
};
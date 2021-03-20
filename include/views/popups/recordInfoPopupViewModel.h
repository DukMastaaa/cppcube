#pragma once

#include "views/baseViewModel.h"
#include "controllers/normal/recordListController.h"
#include "views/normal/recordListViewModel.h"


class App;


class RecordInfoPopupViewModel : public BaseViewModel {
    public:
        RecordInfoPopupViewModel(RecordListController& controllerRef);

        virtual Pos2D calcHeightWidth() const override;
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;

        virtual void receiveAppRef(App& appRef) override;

        void confirmDeletion(std::string popupReturnData);

    private:
        RecordListController& controller;
        App* app;  // :iveseenthings:
};
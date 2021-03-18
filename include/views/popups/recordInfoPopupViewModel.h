#pragma once

#include "views/baseViewModel.h"
#include "controllers/normal/recordListController.h"
#include "views/normal/recordListViewModel.h"


class PopupControllerInterface;  // does this need to be forward-declared?


class RecordInfoPopupViewModel : public BaseViewModel {
    public:
        RecordInfoPopupViewModel(RecordListController& controllerRef);

        virtual Pos2D calcHeightWidth() const override;
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
        virtual std::string getPopupReturnData() const override;
        virtual PopupState receiveData(std::string data) override;

        virtual void receivePopupControllerInterface(PopupControllerInterface& interfaceRef);

    private:
        RecordListController& controller;
        PopupControllerInterface* popupController;

};
#pragma once

#include "views/baseViewModel.h"
#include "views/normal/recordListViewModel.h"


class RecordInfoPopupViewModel : public BaseViewModel {
    public:
        RecordInfoPopupViewModel(RecordListViewModel& modelRef);

        virtual Pos2D calcHeightWidth() const override;
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
        virtual std::string getPopupReturnData() const override;
        virtual PopupState receiveData(std::string data) override;

    private:
        RecordListViewModel& model;
};
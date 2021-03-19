#pragma once

#include "views/baseViewModel.h"
#include "models/summaryStatsModel.h"


class SummaryStatsPopupViewModel : public BaseViewModel {
    public:
        SummaryStatsPopupViewModel(SummaryStatsModel& modelRef);

        virtual Pos2D calcHeightWidth() const override;
        virtual void draw(WINDOW* window) const override;

        virtual PopupState receiveKeyboardInput(int input) override;
        virtual PopupState receiveData(std::string data) override;
    
    private:
        SummaryStatsModel& model;
};
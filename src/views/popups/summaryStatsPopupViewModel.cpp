#include "views/popups/summaryStatsPopupViewModel.h"

#include "models/cubeTimer.h"


SummaryStatsPopupViewModel::SummaryStatsPopupViewModel(SummaryStatsModel& modelRef) : model(modelRef) {}


Pos2D SummaryStatsPopupViewModel::calcHeightWidth() const {
    return {10, 30};
}


void SummaryStatsPopupViewModel::draw(WINDOW* window) const {
    ::werase(window);
    Record totalMean = model.meanOfAll();
    std::string totalMeanTime = CubeTimer::formatTime(totalMean.time, totalMean.penalty);
    mvwprintw(window, 0, 0, "total mean: %s", totalMeanTime.c_str());
}


PopupState SummaryStatsPopupViewModel::receiveKeyboardInput(int input) {
    switch (input) {
        case '\n':
            return PopupState::CLOSE;
        
        default:
            return PopupState::NOREFRESH;
    }
}


PopupState SummaryStatsPopupViewModel::receiveData(std::string data) {
    return PopupState::REFRESH;
}

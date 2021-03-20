#include "views/popups/summaryStatsPopupViewModel.h"

#include "models/cubeTimer.h"
#include <array>


SummaryStatsPopupViewModel::SummaryStatsPopupViewModel(SummaryStatsModel& modelRef) : model(modelRef) {}


Pos2D SummaryStatsPopupViewModel::calcHeightWidth() const {
    return {10, 30};
}


void SummaryStatsPopupViewModel::draw(WINDOW* window) const {
    ::werase(window);

    mvwprintw(window, 0, 0, "Total mean: %s", model.meanOfAll().getFormattedTime().c_str());
    
    mvwprintw(window, 1, 0, "Total average: %s", model.averageOfAll().getFormattedTime().c_str());
    
    static std::array<unsigned int, 4> sampleSizes = {5, 12, 50, 100};

    int windowRow = 2;  // ew hardcode
    for (const auto& size : sampleSizes) {
        mvwprintw(window, windowRow, 0, "ao%ld: %s", size, model.averageOf(size).getFormattedTime().c_str());
        windowRow++;
    }
}


PopupState SummaryStatsPopupViewModel::receiveKeyboardInput(int input) {
    switch (input) {
        case '\n':
            return PopupState::CLOSE;
        
        default:
            return PopupState::NOREFRESH;
    }
}
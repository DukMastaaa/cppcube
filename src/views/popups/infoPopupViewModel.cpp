#include <views/popups/infoPopupViewModel.h>


InfoPopupViewModel::InfoPopupViewModel() : BaseViewModel(), description{} {}


Pos2D InfoPopupViewModel::calcHeightWidth() const {
    return {5, std::min<unsigned int>(35, description.length() + 1)};
}


void InfoPopupViewModel::draw(WINDOW* window) const {
    werase(window);
    smartStringDisplay(window, description, 0, 0);
}


PopupState InfoPopupViewModel::receiveKeyboardInput(int input) {
    if (input == KEY_ESCAPE || input == '\n') {
        return PopupState::CLOSE;
    } else {
        return PopupState::REFRESH;
    }
}


PopupState InfoPopupViewModel::receiveData(std::string data) {
    description = data;
    return PopupState::RESIZE;
}
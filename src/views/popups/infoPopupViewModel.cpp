#include <views/popups/infoPopupViewModel.h>


InfoPopupViewModel::InfoPopupViewModel() : BaseViewModel(), description{} {}


Pos2D InfoPopupViewModel::calcHeightWidth() const {
    return {5, std::max<unsigned int>(20, description.length())};
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


std::string InfoPopupViewModel::getPopupReturnData() const {
    return "";  // lol
}


PopupState InfoPopupViewModel::receiveData(std::string data) {
    description = data;
    return PopupState::RESIZE;
}
#include "views/popups/helpPopupViewModel.h"

#include "myStructs.h"


const std::array<std::string, 4> HelpPopupViewModel::pageTitles = {
    "General",
    "Movement and Files",
    "Popups",
    "hah gotem"
};


// can't indent...
const std::array<std::string, 4> HelpPopupViewModel::helpPages = {
R"~(<Space>: Toggle timer
q: Quit
<Up>, <Down>: Select record
2/d: Toggle +2/DNF for latest record
x: Delete latest record
n: New scramble
p: Change puzzle
i: Show info for selected time
g: Generate summary statistics
)~",

R"~(<S-2>, <S-d>, <S-x>: Apply to selected record
j: Jump to index
t: Jump to top
b: Jump to bottom
E: Export data
I: Import data
)~",

R"~(v: Display cube view in pop-up
s: Display scramble view in pop-up
h: Display this help message
)~",

R"~(never gonna give you up
never gonna let you down
never gonna run around and
desert you
)~"
};


HelpPopupViewModel::HelpPopupViewModel() : BaseViewModel(), currentPage{0} {}


Pos2D HelpPopupViewModel::calcHeightWidth() const {
    return {12, 55};
}


void HelpPopupViewModel::draw(WINDOW* window) const {
    werase(window);

    std::string header = "Page " 
        + std::to_string(currentPage+1) 
        + '/' + std::to_string(helpPages.size()) 
        + ": " + pageTitles[currentPage];

    mvwprintw(window, 0, 0, header.c_str());
    mvwprintw(window, 2, 0, helpPages.at(currentPage).c_str());
}


PopupState HelpPopupViewModel::receiveKeyboardInput(int input) {
    switch (input) {
        case KEY_ESCAPE:
        case '\n':
            return PopupState::CLOSE;
        
        case KEY_RIGHT:
            if (currentPage < helpPages.size() - 1) {
                currentPage++;
            }
            break;
        
        case KEY_LEFT:
            if (currentPage > 0) {
                currentPage--;
            }
            break;
    }
    return PopupState::REFRESH;
}
#include "views/normal/timerViewModel.h"

#include <chrono>
#include <array>
#include <map>

#include <ncurses.h>

#include "models/cubeTimer.h"
#include "myStructs.h"
#include "views/colours.h"


const std::map<char, std::array<std::string, 5>> TimerViewModel::SYMBOL_BLOCKS = {
    {
        '0', 
        {
            "###",
            "# #",
            "# #",
            "# #",
            "###",
        },
    },
    {
        '1',
        {
            "## ",
            " # ",
            " # ",
            " # ",
            "###",
        },
    },
    {
        '2',
        {
            "## ",
            "  #",
            " # ",
            "#  ",
            "###",
        },
    },
    {
        '3',
        {
            "## ",
            "  #",
            "## ",
            "  #",
            "## ",
        },
    },
    {
        '4',
        {
            "# #",
            "# #",
            "###",
            "  #",
            "  #",
        },
    },
    {
        '5',
        {
            "###",
            "#  ",
            "###",
            "  #",
            "###",
        },
    },
    {
        '6',
        {
            "###",
            "#  ",
            "###",
            "# #",
            "###",
        },
    },
    {
        '7',
        {
            "###",
            "  #",
            "  #",
            "  #",
            "  #",
        },
    },
    {
        '8',
        {
            "###",
            "# #",
            "###",
            "# #",
            "###",
        },
    },
    {
        '9',
        {
            "###",
            "# #",
            "###",
            "  #",
            "  #",
        },  
    },
    {
        '.',
        {
            " ",
            " ",
            " ",
            " ",
            "#"
        },
    },
    {
        ':',
        {
            " ",
            "#",
            " ",
            "#",
            " "
        },
    },
    {
        '+',
        {
            "   ",
            " # ",
            "###",
            " # ",
            "   "
        },
    },
    {
        'D',
        {
            "## ",
            "# #",
            "# #",
            "# #",
            "## ",
        },
    },
    {
        'N',
        {
            "###",
            "# #",
            "# #",
            "# #",
            "# #",
        },
    },
    {
        'F',
        {
            "###",
            "#  ",
            "###",
            "#  ",
            "#  ",
        },
    },
};


Pos2D TimerViewModel::calcHeightWidth() const {
    return {5, 31};  // hardcode for now
}


TimerViewModel::TimerViewModel(CubeTimer& timerRef) : timer(timerRef) {}


void TimerViewModel::drawCharMatrix(WINDOW* window, std::string formattedTime) const {
    for (int row = 0; row < 5; row++) {

        // aligns time in center of window
        int xPos;
        switch (formattedTime.back()) {
            case '+':
                xPos = 0;
                break;
            
            case 'F':  // for DNF
                xPos = 10;
                break;
            
            default:
                xPos = 2;
                break;
        }

        for (const char& symbol: formattedTime) {
            const std::string& block = SYMBOL_BLOCKS.at(symbol).at(row);

            for (const char tile : block) {
                chtype newTile = (tile == '#') ? BLOCK_CHAR : ' ';
                mvwaddch(window, row, xPos, newTile);
                xPos++;
            }

            xPos++;
        }
    }
}


void TimerViewModel::drawEllipsis(WINDOW* window) const {
    for (int col = 0; col < 5; col += 2) {
        mvwaddch(window, 4, col, '#');
    }
}


void TimerViewModel::draw(WINDOW* window) const {
    /* Erases and draws timer window. */
    werase(window);
    if (!timer.isTiming) {
        Record currentRecord = {timer.getTimeElapsed(), "", timer.currentPenalty};
        std::string formattedTime = currentRecord.getFormattedTime();
        drawCharMatrix(window, formattedTime);
    } else {
        drawEllipsis(window);
    }
}
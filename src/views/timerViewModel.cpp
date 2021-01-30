#include "views/timerViewModel.h"

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
            "   ",
            "###",
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


// int TimerViewModel::charDigitToInt(char digit) {
//     /* Converts a digit character to its corresponding integer literal.
//     Returns -1 if character is not a digit. */
//     if ('0' <= digit && digit <= '9') {
//         return digit - '0';
//     } else {
//         return -1;
//     }
// }


void TimerViewModel::drawCharMatrix(WINDOW* window, std::string formattedTime) const {
    for (int row = 0; row < 5; row++) {
        int xPos = (formattedTime.back() == '+') ? 0 : 2;  // aligns time properly
        for (const char& symbol: formattedTime) {
            const std::string& block = SYMBOL_BLOCKS.at(symbol).at(row);
            std::size_t length = block.length();
            mvwprintw(window, row, xPos, block.c_str());
            xPos += length + 1;
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
        std::string formattedTime = CubeTimer::formatTime(timer.getTimeElapsed(), timer.currentPenalty);
        drawCharMatrix(window, formattedTime);
    } else {
        drawEllipsis(window);
    }
}
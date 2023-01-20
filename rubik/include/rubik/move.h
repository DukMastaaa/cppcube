#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace rubik {

enum class Action : std::int8_t {
    NOP = 0,
    Up,
    Front,
    Right,
    Back,
    Left,
    Down,
    SliceM,
    SliceE,
    SliceS,
    RotX,
    RotY,
    RotZ
};

struct Depth {
    std::int8_t min;
    std::int8_t max;
};

struct Move {
    Action action = Action::NOP;
    Depth depth = {1, 1};
    std::int8_t signedRepeat = 1;
};

static_assert(sizeof(Move) == 4);

/**
 * @brief Postfix operator used to indicate inverse.
 */
constexpr Move operator--(const Move& move, int) {
    Move copy = move;
    copy.signedRepeat = -copy.signedRepeat;
    return copy;
}

/**
 * @brief Multiplication operator used to indicate repeats.
 * Negative values will reverse the move.
 */
constexpr Move operator*(const Move& move, int signedRepeat) {
    Move copy = move;
    copy.signedRepeat = signedRepeat;
    return copy;
}

/**
 * @brief Converts the given move to a string.
 */
constexpr std::string to_string(const Move& move, bool useWSuffix = true) {
    // TODO: incomplete
    std::string output;
    bool isSlice = false;
    int unsignedRepeat = std::abs(move.signedRepeat);

    if (move.depth.min == move.depth.max) {
        if (move.depth.min == 0) {
            return "0";
        } else if (move.depth.min != 1) {
            output += std::to_string(move.depth.min);
        }
    } else {
        if (move.depth.min);
    }

    if (unsignedRepeat != 1) {
        output += std::to_string(unsignedRepeat);
    }
    if (move.signedRepeat < 0) {
        output += '\'';
    }
}


namespace move_literals {

    constexpr const Move U{Action::Up};
    constexpr const Move F{Action::Front};
    constexpr const Move R{Action::Right};
    constexpr const Move B{Action::Back};
    constexpr const Move L{Action::Left};
    constexpr const Move D{Action::Down};
    constexpr const Move M{Action::SliceM};
    constexpr const Move E{Action::SliceE};
    constexpr const Move S{Action::SliceS};
    constexpr const Move x{Action::RotX};
    constexpr const Move y{Action::RotY};
    constexpr const Move z{Action::RotZ};


}  // namespace move_literals



}  // namespace rubik

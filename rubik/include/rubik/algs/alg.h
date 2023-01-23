#pragma once

#include "rubik/core/move.h"

#include <array>
#include <iostream>

namespace rubik {

constexpr const int MAX_ALG_LENGTH = 32;

struct Algorithm {
    const char* name;
    std::array<Move, MAX_ALG_LENGTH> sequence;
};

}  // namespace rubik

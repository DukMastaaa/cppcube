#pragma once

#include "rubik/move.h"

#include <iostream>

namespace rubik {

constexpr const int MAX_ALG_LENGTH = 32;

struct Algorithm {
    const char* name;
    Move sequence[MAX_ALG_LENGTH];
};

}  // namespace rubik

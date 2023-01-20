#pragma once

#include "rubik/core/move.h"
#include "rubik/algs/alg.h"

namespace rubik {

struct PLLAlgorithm : public Algorithm {
    int auf_offset;  // adjust U face
};

using namespace move_literals;

constexpr const PLLAlgorithm PLL_T{
    "T",
    {R, U, R--, U--, R--, F, R*2, U, R--, U--, R, U, R--, F--},
    0
};



}  // namespace rubik
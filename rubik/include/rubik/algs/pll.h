#pragma once

#include "rubik/core/move.h"
#include "rubik/algs/alg.h"

namespace rubik {

struct PLLAlgorithm : public Algorithm {
    int auf_offset;  // adjust U face
};

using namespace move_literals;

constexpr const PLLAlgorithm PLL_NOP {
    {"NOP", {}},
    0
};

constexpr const PLLAlgorithm PLL_Aa {
    {"Aa", {x, R--, U, R--, D*2, R, U--, R--, D*2, R*2, x--}},
    0
};

constexpr const PLLAlgorithm PLL_Ab {
    {"Ab", {x, R, D--, R, U*2, R--, D, R, U*2, R*2, x--}},
    0
};

constexpr const PLLAlgorithm PLL_E {
    {"E", {x--, R, U--, R--, D, R, U, R--, D--, R, U, R--, D, R, U--, R--, D--, x}},
    0
};

constexpr const PLLAlgorithm PLL_F {
    {"F", {R--, U--, F--, R, U, R--, U--, R--, F, R*2, U--, R--, U--, R, U, R--, U, R}},
    0
};

constexpr const PLLAlgorithm PLL_Ga {
    {"Ga", {R*2, U, R--, U, R--, U--, R, U--, R*2, (D, U)--, R--, U, R, D--}},
    0
};

constexpr const PLLAlgorithm PLL_Gb {
    {"Gb", {R--, U--, R, U, D--, R*2, U, R--, U, R, U--, R, U--, R*2, D}},
    0
};

constexpr const PLLAlgorithm PLL_Gc {
    {"Gc", {R--*2, F*2, R, U*2, R, U*2, R--, F, R, U, R--, U--, R--, F, R*2}},
    0
};

constexpr const PLLAlgorithm PLL_Gd {
    {"Gd", {R, U, R--, U--, D, R*2, U--, R, U--, R--, U, R--, U, R*2, D--}},
    0
};

constexpr const PLLAlgorithm PLL_H {
    {"H", {M--*2, U--, M--*2, U--*2, M--*2, U--, M--*2}},
    0
};

constexpr const PLLAlgorithm PLL_Ja {
    {"Ja", {R--, U, L--, U*2, R, U--, R--, U*2, R, L}},
    0
};

constexpr const PLLAlgorithm PLL_Jb {
    {"Jb", {R, U, R--, F--, R, U, R--, U--, R--, F, R*2, U--, R--}},
    -1
};

constexpr const PLLAlgorithm PLL_Na {
    {"Na", {R, U, R--, U, R, U, R--, F--, R, U, R--, U--, R--, F, R*2, U--, R--, U*2, R, U--, R--}},
    0
};

constexpr const PLLAlgorithm PLL_Nb {
    {"Nb", {R--, U, L--, U*2, R, U--, L, R--, U, L--, U*2, R, U--, L}},
    0
};

constexpr const PLLAlgorithm PLL_Ra {
    {"Ra", {R, U--, R--, U--, R, U, R, D, R--, U--, R, D--, R--, U*2, R--}},
    0
};

constexpr const PLLAlgorithm PLL_Rb {
    {"Rb", {R--, U*2, R, U*2, R--, F, R, U, R--, U--, R--, F--, R*2}},
    0
};

constexpr const PLLAlgorithm PLL_T {
    {"T", {R, U, R--, U--, R--, F, R*2, U--, R--, U--, R, U, R--, F--}},
    0
};

constexpr const PLLAlgorithm PLL_Ua {
    {"Ua", {R, U--, R, U, R, U, R, U--, R--, U--, R*2}},
    0
};

constexpr const PLLAlgorithm PLL_Ub {
    {"Ub", {R--*2, U, R, U, R--, U--, R--, U--, R--, U, R--}},
    0
};

constexpr const PLLAlgorithm PLL_V {
    {"V", {R, U*2, R--, D, R, U--, R, U--, R, U, R*2, D, R--, U--, R, D*2}},
    0
};

constexpr const PLLAlgorithm PLL_Y {
    {"Y", {F, R, U--, R--, U--, R, U, R--, F--, R, U, R--, U--, R--, F}},
    0
};

constexpr const PLLAlgorithm PLL_Z {
    {"Z", {M--*2, U--, M--*2, U--, M--, U--*2, M--*2, U--*2, M--}},
    0
};

constexpr const std::array<PLLAlgorithm, 21+1> PLLs = {
    PLL_NOP,
    PLL_Aa, PLL_Ab,
    PLL_E,
    PLL_F,
    PLL_Ga, PLL_Gb, PLL_Gc, PLL_Gd,
    PLL_H,
    PLL_Ja, PLL_Jb,
    PLL_Na, PLL_Nb,
    PLL_Ra, PLL_Rb,
    PLL_T,
    PLL_Ua, PLL_Ub,
    PLL_V,
    PLL_Y,
    PLL_Z
};


}  // namespace rubik
#pragma once

#include <limits>
#include <numbers>

namespace Constants {
    constexpr double pi = std::numbers::pi;
    constexpr double infinity = std::numeric_limits<double>::infinity();

    // Used for comparing if floating point values are close enough to
    // be considered equal
    // if |x - y| < epsilon then x == y = true
    constexpr double epsilon = 1e-6; 
}


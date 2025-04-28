#include "marble.h"
#include "noise.h"
#include "constants.h"
#include <cmath>

Color Marble::value(double u, double v) const {
//    double R{4};
//    double r{1};
//    double theta = 4*v * Constants::pi;
//    double phi = (u - 0.5) * 2*Constants::pi;
//    double x = (R + r*std::sin(theta)) * std::cos(phi);
//    double y = (R + r*std::sin(theta)) * std::sin(phi);
//    double z = r * std::cos(theta);
//    double noise = Perlin::noise(x, y, z);
//    return Color{0.5, 0.5, 0.5} * (noise + 1);

    double theta = v * Constants::pi;
    double phi = (u - 0.5) * 2 * Constants::pi;
    double x = std::sin(theta) * std::cos(phi);
    double y = std::sin(theta) * std::sin(phi);
    double z = std::cos(theta);
    x *= 5;
    y *= 5;
    z *= 5;
    double noise = Perlin::noise(x, y, z);
    return Color{0.5, 0.5, 0.5} * (noise + 1);
}
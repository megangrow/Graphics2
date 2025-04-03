#include "ray.h"
#include "triangle.h"
#include "pixels.h"

int main() {
    Triangle t{{-1, 0, 0}, {1, 0, 0}, {0, 0, 1}, nullptr};
    Triangle s{{-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, nullptr};
    int rows = 720;
    int columns = 1280;
    double scale = 0.01;
    Pixels pixels{columns, rows};
    for (int row = 0; row < rows; ++row) {
        double z = scale * (row - rows/2);
        for (int col = 0; col < columns; ++col) {
            double x = scale * (col - columns/2);
            Ray ray{{x, -1, z}, {0, 1, 0}};
            if (t.intersect(ray)) {
                pixels(row, col) = {1, 0, 0};
            }
            else if (s.intersect(ray)) {
                pixels(row, col) = {0, 1, 0};
            }
        }
    }
    pixels.save_png("triangle.png");
    std::cout << "Wrote triangle.png";
}
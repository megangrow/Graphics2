#include "sphere.h"
#include "ray.h"
#include "constants.h"
#include "pixels.h"
#include <chrono>
#include <functional>


void timeit(std::function<std::optional<double>()> func, const std::string& label,
            int Ntimes);

int main() {

    Sphere sphere{{0, 2, 0}, 1};
    Ray ray{{0, 0, 0}, {0, 1, 0}};

    int Ntimes = 1'000'000;
    timeit([&]() { return sphere.intersect(ray); }, "intersect", Ntimes);
    timeit([&]() { return sphere.intersect2(ray); }, "intersect2", Ntimes);
    timeit([&]() { return sphere.intersect_algebraic(ray); }, "intersect_algebraic", Ntimes);
    


    // make an image
    int rows = 720;
    int columns = 1280;
    double scale = 0.01;
    Pixels pixels{columns, rows};
    for (int row = 0; row < rows; ++row) {
        double z = scale * (row - rows/2);
        for (int col = 0; col < columns; ++col) {
            double x = scale * (col - columns/2);
            Ray ray{{x, 0, z}, {0, 1, 0}};
            if (sphere.intersect2(ray)) {
                pixels(row, col) = {1, 0, 0};
            }
        }
    }
    pixels.save_png("test-intersect2.png");
}


void timeit(std::function<std::optional<double>()> func, const std::string& label,
            int Ntimes) {
    std::cout << "\n" << label << ": ";
    int sum = 0;
    std::optional<double> result;    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < Ntimes; ++i) {
        result = func();
        if (result.has_value()) {
            sum += result.value();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
    std::cout << elapsed/Ntimes << '\n';
    std::cout << sum << '\n';
    
    std::cout << "Hit? " << std::boolalpha << result.has_value() << '\n';
    if (result.has_value()) {
	double time = result.value();
	std::cout << "Distance = " << time << '\n';
    }
}

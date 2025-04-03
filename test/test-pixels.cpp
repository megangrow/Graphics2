#include "color.h"
#include "pixels.h"

// write a function to set all the pixels to the same color
void set_color(Pixels& pixels, Color color) {
    for (Color& c : pixels.values) {
        c = color;
    }
}

void gradient(Pixels& pixels) {
    auto columns = pixels.columns;
    auto rows = pixels.rows;
    for (auto i = 0; i < rows; i++) {
        for (auto j = 0; j < columns; j++) {
            double c = static_cast<double>(j) / (columns - 1);
            pixels(i, j) = {c, c, c};
        }
    }
}

// write a function to color a pretty picture!
void pretty(Pixels& pixels) {
    auto columns = pixels.columns;
    auto rows = pixels.rows;
    for (auto i = 0; i < rows; i++) {
        for (auto j = 0; j < columns; j++) {
            double r = static_cast<double>(i) / (rows - 1);
            double g = static_cast<double>(j) / (columns - 1);
            double b = 1.0 - static_cast<double>(i) / (rows - 1);
            pixels(i, j) = {r, g, b};
        }
    }
}

int main() {
    const unsigned columns = 1280;
    const unsigned rows = 720;
    Pixels pixels{columns, rows};

    Color light{0.8, 1, 0.6};
    Color material{0.4, 0.3, 0.5};
    Color red{1.0, 0, 0};
    set_color(pixels, red);
    std::string filename;
    // filename = "red.ppm";
    // pixels.save_ppm(filename);
    // std::cout << "Wrote: " << filename << '\n';
    filename = "red.png";
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';

    gradient(pixels);
    filename = "gradient.png";
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';

    pretty(pixels);
    // filename = "pretty.ppm";
    // pixels.save_ppm(filename);
    // std::cout << "Wrote: " << filename << '\n';
    filename = "pretty.png";
    pixels.save_png(filename);
    std::cout << "Wrote: " << filename << '\n';
}

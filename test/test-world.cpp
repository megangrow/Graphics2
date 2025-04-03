#include "camera.h"
#include "sphere.h"
#include "color.h"
#include "pixels.h"
#include "ray.h"
#include "hit.h"
#include "world.h"
#include "random.h"
#include <memory>


Color trace(const World& world, const Ray& ray);

int main() {
    // world
    World world;
    world.add(std::make_unique<Sphere>(Vector3D{0, 0, 0}, 0.3));
    world.add(std::make_unique<Sphere>(Vector3D{1, 0, 0}, 0.3));

  
    // specify the number of pixels
    Pixels pixels{1280, 720};

    // create the camera
    Vector3D position{10, -2, 3}, up{0, 0, 1};
    Vector3D target{0, 0, 0};
    double fov{20};
    double aspect = static_cast<double>(pixels.columns) / pixels.rows;
    Camera camera{position, target, up, fov, aspect};

    constexpr int samples = 100;
    for (auto row = 0; row < pixels.rows; ++row) {
	for (auto col = 0; col < pixels.columns; ++col) {
            for (int N = 0; N < samples; ++N) {
                double y = (row + random_double()) / (pixels.rows - 1);
                double x = (col + random_double()) / (pixels.columns - 1);
                // cast samples number of rays
                Ray ray = camera.compute_ray(x, y);
                pixels(row, col) += trace(world, ray);
            }
            pixels(row, col) /= samples;
	}
    }
    std::string filename{"sphere.png"};
    pixels.save_png(filename);
    std::cout << "Wrote " << filename << '\n';
}

Color trace(const World& world, const Ray& ray) {
    std::optional<Hit> hit = world.find_nearest(ray);
    if (hit.has_value()) {
	return hit->normal;
    }
    else {
	return Black;
    }
}

#include "pixels.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"

int main() {
    Sphere ground {{0, 0, -100}, 100};
    Sphere sphere {{0, 0, 1}, 1};

    Pixels pixels {1280, 720};

    Vector3D position {0, -10, 0}, up {0, 0, 1};
    Vector3D target {sphere.center};
    double fov {90};
    double aspect = static_cast<double>(pixels.columns) / pixels.rows;
    Camera camera {position, target, up, fov, aspect};

    for (int row = 0; row < pixels.rows; ++row) {
        double v = static_cast<double>(row) / (pixels.rows - 1);
        for (int col = 0; col < pixels.columns; ++col) {
            double u = static_cast<double>(col) / (pixels.columns - 1);
            Ray ray = camera.compute_ray(u, v);
            auto time = ground.intersect(ray);
            if (time.has_value()) {
                Hit hit = ground.construct_hit(ray, time.value());
                double shading = std::abs(dot(ray.direction, hit.normal));
                pixels(row, col) = White * shading;
            }
            time = sphere.intersect(ray);
            if (time.has_value()) {
                Hit hit = sphere.construct_hit(ray, time.value());
                pixels(row, col) = -hit.normal;
            }
        }
    }
    pixels.save_png("camera_test.png");
}

#include <cmath>
#include <iomanip>
#include <thread>
#include "ray.h"
#include "triangle.h"
#include "pixels.h"
#include "camera.h"
#include "world.h"
#include "parser.h"
#include "random.h"
#include "sphere.h"

void print_progress(long long ray_num, long long total_rays);
void render(const World& world, const Camera& camera, int depth, int samples, int num_threads, Pixels& pixels, bool progress);
Color trace_path(const World& world, const Ray& ray, int depth);


int main(int argc, char* argv[]) {
    try {
    Parser parser{argv[1]};
    World world = parser.get_world();
    Pixels pixels = parser.get_pixels();
    Camera camera = parser.get_camera();

    int depth = parser.ray_depth;
    int samples = parser.ray_samples;
    int num_threads = parser.num_threads;

    // Create n-1 images for the additional threads
    std::vector<Pixels> images;
    for (int i = 0; i < num_threads - 1; ++i) {
        images.push_back(pixels);
    }

    // Launch additional threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads - 1; ++i) {
        std::thread t{render, std::ref(world), camera, depth, static_cast<double>(samples) / num_threads,
                      num_threads, std::ref(images.at(i)), false};
        threads.push_back(std::move(t));
    }

    // render on main thread
    render(world, camera, depth, static_cast<double>(samples) / num_threads, num_threads, pixels, true);

    // wait for other threads to finish
    for (std::thread &t: threads) {
        t.join();
    }

    // collect all image data
    for (const Pixels &p: images) {
        for (std::size_t i = 0; i < p.values.size(); ++i) {
            pixels.values.at(i) += p.values.at(i);
        }
    }

    // normalize color values by the number of threads
    for (Color &c: pixels.values) {
        c /= num_threads;
    }

    pixels.save_png(parser.filename);
    std::cout << "\nWrote " << parser.filename << '\n';
} catch (std::exception &err) {
    std::cout << err.what() << '\n';
}
}


void render(const World& world, const Camera& camera, int depth, int samples, int num_threads, Pixels& pixels, bool progress) {
    const long long rays_total = pixels.rows * pixels.columns * static_cast<long long>(samples);
    long long ray_num = 0;

    if (progress) {
        print_progress(ray_num*num_threads, rays_total*num_threads);
    }

    for (auto row = 0; row < pixels.rows; ++row) {
        for (auto col = 0; col < pixels.columns; ++col) {
            Color color{0, 0, 0};
            for (int N = 0; N < samples; ++N) {
                double y = (row + random_double()) / (pixels.rows - 1);
                double x = (col + random_double()) / (pixels.columns - 1);
                // cast samples number of rays
                Ray ray = camera.compute_ray(x, y);
                color += trace_path(world, ray, depth);

                ++ray_num;
                if (progress && ray_num % (rays_total / 100) == 0) {
                    print_progress(ray_num*num_threads, rays_total*num_threads);
                }
            }
            pixels(row, col) = color/samples;
        }
    }
}
void print_progress(long long ray_num, long long total_rays) {
    auto width = std::to_string(total_rays).length() + 4;
    int percentage = std::round(static_cast<double>(ray_num) / total_rays * 100);
    std::cout << "\rProgram: " << std::setw(3) << percentage << "% ";
    std::cout << std::setw(width) << ray_num << "/" << total_rays << " rays";
    std::cout << std::flush;
}

Color trace_path(const World& world, const Ray& ray, int depth) {
    if (depth == 0) {
        return Black;
    }
    std::optional<Hit> hit = world.find_nearest(ray);
    if (!hit) {
        return Black;
    }
    const Object *object = hit->object;
    auto [u, v] = object->uv(*hit); // new
    const Material *material = object->material;
    Color color = material->texture->value(u, v); // new
    if (material->emitting) {
        return color;
    }
    Ray scattered = material->scatter(ray, hit.value());
    return color * trace_path(world, scattered, depth - 1);
}

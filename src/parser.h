#pragma once
#include <string>
#include <map>
#include <memory>
#include "world.h"
class Camera;
class Pixels;
class Material;
class Texture;

using Materials = std::map<std::string, std::unique_ptr<Material>>;
using Textures = std::map<std::string, std::unique_ptr<Texture>>;

class Parser {
public:
    Parser(const std::string& filename);

    Camera get_camera();
    Pixels get_pixels();
    World get_world();

    std::string filename;
    int ray_depth, ray_samples, num_threads=1;

private:

    void parse(std::ifstream& input);
    void verify();

    void parse_material(std::stringstream& ss);
    Material* get_material(const std::string& material);
    void parse_texture(std::stringstream& ss);
    void parse_mesh(std::stringstream& ss);
    Texture* get_texture(const std::string& texture);
    void parse_sphere(std::stringstream& ss);
    void parse_triangle(std::stringstream& ss);
    void parse_constant_medium(std::stringstream& ss);
    void parse_square(std::stringstream &ss);
    void parse_camera(std::stringstream& ss);
    void parse_rays(std::stringstream& ss);
    void parse_pixels(std::stringstream& ss);
    void parse_output(std::stringstream& ss);
    void parse_threads(std::stringstream& ss);


    
    World world;
    
    Materials materials;
    Textures textures;

    Point3D camera_position, camera_target;
    Vector3D camera_up;
    double camera_fov, aspect;
    int rows, columns;

    bool found_camera, found_pixels, found_output, found_rays;
};

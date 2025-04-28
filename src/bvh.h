#pragma once
#include <vector>
#include <memory>
#include "object.h"
#include "aabb.h"

class BVH {
public:
    BVH(const std::vector<std::unique_ptr<Object>>& objects);
    std::optional<Hit> find_nearest(const Ray& ray) const;

private:
    class Node {
    public:
        Node(AABB box = AABB(Point3D{}, Point3D{}), Node* left = nullptr, Node* right = nullptr, Object* object = nullptr)
                : left(left), right(right), object(object), box(box) {}

        Node* left;
        Node* right;
        Object* object;
        AABB box;

    };
    Node* root;

    Node* build_tree(std::vector<Object*> objects) const;
    bool compare_boxes(Object* a, Object* b, int axis) const;
    std::pair<std::vector<Object*>, std::vector<Object*>> partition_along_random_axis(std::vector<Object*> objects) const;

    std::pair<Object*, std::optional<double>> intersect(Node* n, const Ray& ray) const;
};

#include "bvh.h"
#include "constants.h"
#include "random.h"
#include "hit.h"
#include <algorithm>

int random_int(int min, int max) {
    return static_cast<int>(random_double(min, max + 1));
}

BVH::BVH(const std::vector<std::unique_ptr<Object>>& objects) {
    // Nodes of the BVH only need a pointer to the object, not to maintain ownership.
    // Build a list of raw object pointers
    std::vector<Object*> object_pointers;
    for (const auto& obj : objects) {
        object_pointers.push_back(obj.get());
    }
    root = build_tree(object_pointers);
}

std::optional<Hit> BVH::find_nearest(const Ray& ray) const {
    // test intersection with the root node
    // if you hit something, then construct a hit on the object
    // otherwise no hit
    auto intersection = intersect(root, ray);
    if (!intersection.first || !intersection.second) {
        return {};
    }
    Object* object = intersection.first;
    double time = *intersection.second;
    return object->construct_hit(ray, time);
}


BVH::Node* BVH::build_tree(std::vector<Object*> objects) const {
    // Recursively build a tree
    // at leaf nodes, set the node object and bounding box
    // for all others partition and recursively call build_tree
    // make sure to handle surrounding boxes at non-leaf nodes
    Node* n = new Node{};
    if (size(objects) == 1) {
        n->box = objects[0]->bounding_box();
        n->object = objects[0];
    }
    else {
        auto [left, right] = partition_along_random_axis(objects);
        n->left = build_tree(left);
        n->right = build_tree(right);
        n->box = surrounding_box(n->left->box, n->right->box);
    }
     return n;
}


bool BVH::compare_boxes(Object* a, Object* b, int axis) const {
    // For the given axis (x=0, y=1, z=2) returns whether a's box is less than b's
    if (axis == 0) {
        return (a->bounding_box().minimum.x < b->bounding_box().minimum.x);
    }
    else if (axis == 1) {
        return (a->bounding_box().minimum.y < b->bounding_box().minimum.y);
    }
    else if (axis == 2) {
        return (a->bounding_box().minimum.z < b->bounding_box().minimum.z);
    }
    return false;  // couldn't find box
}

std::pair<std::vector<Object*>, std::vector<Object*>> BVH::partition_along_random_axis(std::vector<Object*> objects) const {
    // sort objects along a random axis
    // divide objects vector into two vectors
    int axis = random_int(0, 2);
    std::sort(objects.begin(), objects.end(), [this, axis](Object* a, Object* b){return compare_boxes(a,b,axis);});
    auto middle = objects.size()/2;
    std::vector<Object*> left(objects.begin(), objects.begin()+middle);
    std::vector<Object*> right(objects.begin()+middle, objects.end());
    return {left, right};
}

std::pair<Object*, std::optional<double>> BVH::intersect(Node* n, const Ray& ray) const {
    // First handle the ray not intersection the box, then handle leaf nodes
    // Remember that boxes can overlap, so you must test both left and right boxes.
    // Given the results of hitting possible left or right or both, return the closest
    if (!n->box.intersect(ray)) {
        return {};
    }
    if (n->left == nullptr && n->right == nullptr) { //leaf
        auto time = n->object->intersect(ray);
        if (time) {
            return {n->object, time};
        }
        return {};
    }
    auto lhit = intersect(n->left, ray);
    auto rhit = intersect(n->right, ray);
    if (lhit.first || rhit.first) {
        if (lhit.first && rhit.first) {
            return (*lhit.second < *rhit.second) ? lhit : rhit;
        } else if (lhit.first) {
            return lhit;
        } else {
            return rhit;
        }
    }
    return {}; // no intersection
}

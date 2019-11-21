#ifndef VULKANLAB_NODE_H
#define VULKANLAB_NODE_H

#include <vector>

struct Node {
    Node() :
        parent(nullptr),
        meshes({})
    {
    }

    ~Node() {
    }

    Node* parent;
    std::vector<unsigned int> meshes;
};

#endif //VULKANLAB_NODE_H

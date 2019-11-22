#ifndef VULKANLAB_NODE_H
#define VULKANLAB_NODE_H

#include <vector>
#include "../Maths/Transform.h"
#include "../Geometry/Mesh.h"

struct Node {
    Node() :
        name(nullptr),
        parent(nullptr),
        meshes({}),
        children({}),
        transform(new Transform())
    {
    }

    ~Node() {
        delete transform;
    }

    const char* name;
    Node* parent;
    std::vector<Mesh*> meshes;
    std::vector<Node*> children;
    Transform* transform;
};

#endif //VULKANLAB_NODE_H

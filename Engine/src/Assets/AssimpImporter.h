#ifndef VULKANLAB_ASSIMP_IMPORTER_H
#define VULKANLAB_ASSIMP_IMPORTER_H

#include "../Geometry/Mesh.h"
#include "../Scene/Node.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/ProgressHandler.hpp>

class Scene;
class Shader;

class AssimpImporter {
public:
    AssimpImporter();

    ~AssimpImporter();

    void import(const char *filename, Scene *scene);

    void processNode(std::vector<Mesh *> &meshes, aiNode *node, Node *parent, Node *newNode);

    Mesh *processMesh(const aiScene *scene, aiMesh *object);

private:
};

#endif //VULKANLAB_ASSIMP_IMPORTER_H

#ifndef VULKANLAB_ASSET_MANAGER_H
#define VULKANLAB_ASSET_MANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <filesystem>
#include "Font.h"
#include "../Shaders/Shader.h"
#include "../Texturing/Texture.h"
#include "../Materials/Material.h"
#include "../Scene/Node.h"

#include "AssimpImporter.h"
#include "FontImporter.h"

namespace fs = std::filesystem;

class Asset;

class AssetManager {
public:
    AssetManager(const char *bin_path);

    ~AssetManager();

    enum AssetType {
        SHADER,
        TEXTURE,
        MATERIAL,
        AUDIO,
        MESH,
        FONT
    };

    /**
     * Asset Container helper
     * @tparam T - The type of asset to store.
     */
    template<typename T>
    struct AssetContainer {
        typedef std::unordered_map<const char *, std::pair<AssetType, T *>> data;
    };

    /**
     * Load a an asset given its path.
     *
     * This method can load Shaders, Textures, Audio files, Models & Materials.
     * @tparam T - The type of asset to load
     * @param filepath - The path of the asset
     * @param name - The string used to rename the asset.
     * @return T
     */
    template<class T>
    inline T *load(const char *filepath, const char *name, Scene *scene = nullptr) {
        // Shaders loading
        if constexpr (std::is_same<T, Shader>::value) {
            std::fstream vertex, fragment;
            std::string vs_data, fs_data, line_v, line_f;
            auto path = fs::path(this->root_dir) / fs::path(std::string(filepath));

            vertex.open((fs::path(path).string() + ".vert"));
            fragment.open((fs::path(path).string() + ".frag"));

            if (vertex.is_open())
                while (getline(vertex, line_v))
                    vs_data += line_v + "\n";

            if (fragment.is_open())
                while (getline(fragment, line_f))
                    fs_data += line_f + "\n";

            vertex.close();
            fragment.close();

            Shader *asset = new Shader(name, vs_data, fs_data);
            this->shaders[name] = std::make_pair(AssetType::SHADER, asset);

            return asset;
        }
            // Textures loading
        else if constexpr (std::is_same<T, Texture>::value) {
            Texture *texture = new Texture(name, filepath);
            std::cout << "Loaded texture \"" << texture->getName() << "\"" << std::endl;

            this->textures[name] = std::make_pair(AssetType::TEXTURE, texture);

            return texture;
        }
            // Materials loading
        else if constexpr (std::is_same<T, Material>::value) {
            Material *material = new Material(filepath);
            std::cout << "Loaded material \"" << material->getName() << "\"" << std::endl;

            this->materials[name] = std::make_pair(AssetType::MATERIAL, material);
            return material;
        }
            // Mesh loading
        else if constexpr (std::is_same<T, Mesh>::value) {
            if (scene == nullptr)
                std::cout << "Can't import the mesh: \"" << filepath << "\","
                          << "the scene to import to was missing."
                          << "Please provide a ptr to the desired scene." << std::endl;
            else {
                AssimpImporter *importer = new AssimpImporter();
                importer->import(filepath, scene);
                Mesh* m = new Mesh();
                return m;
            }
        }
            // Font loading
        else if constexpr (std::is_same<T, Font>::value) {
            FontImporter *fontImporter = new FontImporter();
            fontImporter->import(filepath);
        }
    }

private:
    std::string root_dir;
    AssetContainer<Shader>::data shaders;
    AssetContainer<Texture>::data textures;
    AssetContainer<Material>::data materials;
};

#endif //VULKANLAB_ASSET_MANAGER_H

#ifndef VULKANLAB_ASSET_MANAGER_H
#define VULKANLAB_ASSET_MANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <filesystem>
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

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
        MODEL
    };

    /**
     * Asset Container helper
     */
    template<typename T>
    struct AssetContainer {
        typedef std::unordered_map<const char *, std::pair<AssetType, T *>> data;
    };

    /**
     * Load a an asset given its path.
     * This method can load Shaders, Textures, Audio files, Models & Materials.
     * @tparam T
     * @param filepath
     * @param name
     * @return
     */
    template<class T>
    inline T *load(const char *filepath, const char *name) {
        // Shaders loading
        if constexpr (std::is_same<T, Shader>::value) {
            std::fstream vertex, fragment;
            std::string vs_data, fs_data;
            std::string line_v, line_f;

            vertex.open(fs::path(fs::path(this->root_dir) / fs::path(std::string(filepath) + ".vert")).string());
            fragment.open(fs::path(fs::path(this->root_dir) / fs::path(std::string(filepath) + ".frag")).string());

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
            Texture *texture = new Texture(filepath);
            std::cout << "Loaded texture \"" << texture->getName() << "\"" << std::endl;

            this->textures[name] = std::make_pair(AssetType::TEXTURE, texture);

            return texture;
        }
        // Materials loading
        else if constexpr (std::is_same<T, Material>::value) {
            Material *material = new Material(name);
            std::cout << "Loaded material \"" << material->getName() << "\"" << std::endl;

            this->materials[name] = std::make_pair(AssetType::MATERIAL, material);
            return material;
        }
    }

private:
    std::string root_dir;
    AssetContainer<Shader>::data shaders;
    AssetContainer<Texture>::data textures;
    AssetContainer<Material>::data materials;
};

#endif //VULKANLAB_ASSET_MANAGER_H

#include <iostream>
#include <filesystem>
#include "AssetManager.h"
#include "../Shaders/Shader.h"

namespace fs = std::filesystem;

AssetManager::AssetManager(const char* bin_path) {
    this->root_dir = fs::canonical(fs::path(fs::current_path() / fs::path("../shaders/"))).string();
    std::cout << "Shaders directory: " << this->root_dir << std::endl;
}

AssetManager::~AssetManager() {

}

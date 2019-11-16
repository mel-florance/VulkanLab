#include <iostream>
#include "Shader.h"
#include "../Assets/Asset.h"

Shader::Shader(
        const std::string &name,
        const std::string &vs_src,
        const std::string &fs_src
) : Asset() {
    this->name = name;

    // Create vertex shader
    ShaderData vs_data;
    vs_data.id = glCreateShader(GL_VERTEX_SHADER);
    vs_data.source = vs_src;
    this->data[ShaderType::VERTEX] = vs_data;
    const char *vs_files = {vs_data.source.c_str()};
    glShaderSource(vs_data.id, 1, &vs_files, 0);

    // Create fragment shader
    ShaderData fs_data;
    fs_data.id = glCreateShader(GL_FRAGMENT_SHADER);
    fs_data.source = fs_src;
    this->data[ShaderType::FRAGMENT] = fs_data;
    const char *fs_files = {fs_data.source.c_str()};
    glShaderSource(fs_data.id, 1, &fs_files, 0);

    std::cout << "Loaded shader: \"" << name << "\"" << std::endl;

    // Compile shaders
    this->compile(VERTEX);
    this->compile(FRAGMENT);

    // Link shaders
    this->program = glCreateProgram();
    glAttachShader(this->program, vs_data.id);
    glAttachShader(this->program, fs_data.id);
    glLinkProgram(this->program);

    int link_status;
    char info_log[512];
    glGetProgramiv(this->program, GL_LINK_STATUS, &link_status);

    if (!link_status) {
        glGetProgramInfoLog(this->program, 512, NULL, info_log);
        std::cout << "Linking shader \"" << this->name << "\" failed. " << info_log << std::endl;
    } else {
        std::cout << "Linked shader \"" << this->name << "\" without errors." << std::endl;
    }
}

/**
 * Compile a shader type, could be any of Shader::ShaderType.
 * @param type
 */
void Shader::compile(Shader::ShaderType type) {
    auto type_name = this->shaderTypeToString(type);
    auto it = this->data.find(type);

    if (it != this->data.end()) {

        glCompileShader(it->second.id);
        glGetShaderiv(it->second.id, GL_COMPILE_STATUS, &it->second.compile_status);

        if (it->second.compile_status == GL_FALSE) {
            GLenum error;

            while ((error = glGetError()) != GL_NO_ERROR) {
                std::cout << this->errorToString((ShaderError) error) << std::endl;
            }

            std::cout << "Can't compile shader \"" << this->name << "\"" << std::endl;
        } else {
            std::cout << "Compiled " << type_name << " shader \"" << this->name << "\" without errors." << std::endl;
        }
    }
}

Shader::~Shader() {

}

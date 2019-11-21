#include "Shader.h"
#include <glad/glad.h>

Shader::Shader(
    const std::string &name,
    const std::string &vs_src,
    const std::string &fs_src
) : Asset(), name(name), vs_src(vs_src), fs_src(fs_src) {
    load();
    compile();
    link();
}

bool Shader::load() {
    status &= ~(ShaderStatus::Loaded);

    ShaderData vs_data{status, 0, vs_src};
    ShaderData fs_data{status, 1, fs_src};
    data[ShaderType::VERTEX] = vs_data;
    data[ShaderType::FRAGMENT] = fs_data;

    return status & ShaderStatus::Loaded;
}

bool Shader::compile() {
    status &= ~(ShaderStatus::Compiled);

    std::unordered_map<ShaderType, ShaderData>::iterator it = data.begin();

    for (; it != data.end(); it++) {
        int shader = glCreateShader((GLenum) it->first);
        shaders[it->first] = shader;

        const char *str = it->second.source.c_str();
        glShaderSource(shader, 1, &str, NULL);

        glCompileShader(shader);

        int status;
        char error[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (!status) {
            glGetShaderInfoLog(shader, 512, NULL, error);
            std::cout << "Shader compilation failed: " << error << std::endl;
        } else {
            std::string type;
            switch (it->first) {
                case ShaderType::VERTEX:
                    type = "Vertex";
                    break;
                case ShaderType::FRAGMENT:
                    type = "Fragment";
                    break;
                case GEOMETRY:
                    type = "Geometry";
                    break;
                case COMPUTE:
                    type = "Compute";
                    break;
                case TESS_EVAL:
                    type = "Tesselation evaluation";
                    break;
                case TESS_CTRL:
                    type = "Tesselation control";
                    break;
            }
            std::cout << "Compiled \"" << type.c_str() << "\" shader: " << name.c_str() << std::endl;
            status |= ShaderStatus::Compiled;
        }
    }

    return status & ShaderStatus::Compiled;
}

bool Shader::link() {
    status &= ~(ShaderStatus::Linked);

    program = glCreateProgram();
    std::unordered_map<ShaderType, int>::iterator it = shaders.begin();

    for (; it != shaders.end(); it++)
        glAttachShader(program, it->second);

    glLinkProgram(program);

    int status;
    char error[512];
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status) {
        glGetProgramInfoLog(program, 512, NULL, error);
        std::cout << "Shader program linking failed: " << error << std::endl;
    } else {
        std::cout << "Linked shader: " << name.c_str() << std::endl;
        status |= ShaderStatus::Linked;
    }

    for (; it != shaders.end(); it++)
        glDeleteShader(it->second);

    return status & ShaderStatus::Linked;
}

void Shader::bind() {
    glUseProgram(program);
}

void Shader::setUniform1i(const std::string &name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string &name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform2f(const std::string &name, float x, float y) {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setUniform2f(const std::string &name, const glm::vec2 &value) {
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform3f(const std::string &name, const glm::vec3 &value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform3f(const std::string &name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setUniform4f(const std::string &name, const glm::vec4 &value) {
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform4f(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::getUniformLocation(const std::string &uniform_name) {

    int location = glGetUniformLocation(program, uniform_name.c_str());

    if (location == -1)
        std::cout << "Shader \"" << name << "\" Invalid uniform location: " << uniform_name << std::endl;

    return location;
}

Shader::~Shader() {

}
#include "Shader.h"

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
    }
    else {
        std::cout << "Linked shader: " << name.c_str() << std::endl;
        status |= ShaderStatus::Linked;
    }

    for (; it != shaders.end(); it++)
        glDeleteShader(it->second);

    return status & ShaderStatus::Linked;
}

Shader::~Shader() {

}
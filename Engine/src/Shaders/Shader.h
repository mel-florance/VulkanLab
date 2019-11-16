#ifndef VULKANLAB_SHADER_H
#define VULKANLAB_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "../Assets/Asset.h"

class Shader : public Asset {
public:
    /**
     * Shader constructor
     */
    Shader(
            const std::string &name,
            const std::string &vs_src,
            const std::string &fs_src
    );

    /**
     * Shader destructor
     */
    ~Shader();

    enum ShaderType {
        VERTEX = 0x8B31,
        FRAGMENT = 0x8B30,
        GEOMETRY = 0x8DD9,
        COMPUTE = 0x91B9,
        TESS_EVAL = 0x8E87,
        TESS_CTRL = 0x8E88
    };

    enum ShaderError {
        INVALID_ENUM = 0x0500,
        INVALID_VALUE = 0x0501,
        INVALID_OPERATION = 0x0502,
        STACK_OVERFLOW = 0x0503,
        STACK_UNDERFLOW = 0x0504,
        OUT_OF_MEMORY = 0x0505,
        INVALID_FRAMEBUFFER_OPERATION = 0x0506,
        CONTEXT_LOST = 0x0507,
        TABLE_TOO_LARGE = 0x8031
    };

    enum ShaderStatus {
        Loaded = 1 << 0,
        Compiled = 1 << 1,
        Linked = 1 << 2
    };

    struct ShaderData {
        int compile_status;
        unsigned int id;
        std::string source;
    };

    /**
     * Convert a enum Shader::ShaderType to string.
     */
    inline static const char *shaderTypeToString(ShaderType type) {
        switch (type) {
            default:
                return "Undefined";
            case VERTEX:
                return "VERTEX";
            case FRAGMENT:
                return "FRAGMENT";
            case GEOMETRY:
                return "GEOMETRY";
        }
    }

    /**
     * Convert OpenGL error to string.
     * @param error
     * @return
     */
    static inline const char *errorToString(ShaderError error) {
        switch (error) {
            default:
                return "Undefined";
            case INVALID_ENUM:
                return "The enumeration parameter is not a legal value for that function.";
            case INVALID_VALUE:
                return "The value parameter is not a legal value for that function.";
            case INVALID_OPERATION:
                return "The set of state for that command doesn't match the parameters of that command.";
            case STACK_OVERFLOW:
                return "The stack limit has been reacher, can't execute the operation.";
            case STACK_UNDERFLOW:
                return "The stack popping cannot be done because the stack is already at its lowest point.";
            case OUT_OF_MEMORY:
                return "Cannot allocate more memory for the function.";
            case INVALID_FRAMEBUFFER_OPERATION:
                return "The framebuffer isn't complete, cannot read / write.";
            case CONTEXT_LOST:
                return "The OpenGL has been lost due to a graphics card reset.";
            case TABLE_TOO_LARGE:
                return "Part of the ARB_imaging extension. (See doc).";
        }
    }

    /**
     * Load the shader sources.
     */
    bool load();

    /**
     * Compile the shader given its type.
     */
    bool compile();

    /**
     * Link the shader given its type.
     * @param type
     */
    bool link();

    /**
     * Return the OpenGL shader id.
     * @return
     */
    inline unsigned int getProgram() {
        return program;
    }

    /**
     * Return the shader name.
     * @return
     */
    inline std::string getName() {
        return name;
    }

    /**
     * Return the source data of the shader.
     * @return
     */
    inline std::unordered_map<ShaderType, ShaderData> getData() {
        return data;
    }

    /*
     * Bind this shader to the gpu.
     */
    inline void bind() {
        glUseProgram(program);
    }

    /**
     * Set uniform integer.
     */
    inline void setUniform1i(const std::string &name, int value) {
        glUniform1i(getUniformLocation(name), value);
    }

    /*
     * Set uniform float.
     */
    inline void setUniform1f(const std::string &name, float value) {
        glUniform1f(getUniformLocation(name), value);
    }

    /**
     * Set uniform of 2 floats.
     */
    inline void setUniform2f(const std::string &name, float x, float y) {
        glUniform2f(getUniformLocation(name), x, y);
    }

    /**
     * Set uniform of a vector 2D.
     * @param name
     * @param value
     */
    inline void setUniform2f(const std::string &name, const glm::vec2 &value) {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    /**
     * Set uniform of a vector 3D.
     * @param name
     * @param value
     */
    inline void setUniform3f(const std::string &name, const glm::vec3 &value) {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    /**
     * Set uniform of 3 floats.
     */
    inline void setUniform3f(const std::string &name, float x, float y, float z) {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    /**
     * Set uniform vector 4D.
     * @param name
     * @param value
     */
    inline void setUniform4f(const std::string &name, const glm::vec4 &value) {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    /**
     * Set uniform 4 floats.
     * @param name
     * @param x
     * @param y
     * @param z
     * @param w
     */
    inline void setUniform4f(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }

    /**
     * Set uniform matrix 4x4.
     */
    inline void setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    unsigned int getUniformLocation(const std::string &uniform_name) {

        int location = glGetUniformLocation(program, uniform_name.c_str());

        if (location == -1)
            std::cout << "Shader \"" << name << "\" Invalid uniform location: " << uniform_name << std::endl;

        return location;
    }

private:
    char status;
    unsigned int program;
    std::string name;
    std::string vs_src;
    std::string fs_src;
    std::unordered_map<ShaderType, int> shaders;
    std::unordered_map<ShaderType, ShaderData> data;
};

#endif //VULKANLAB_SHADER_H

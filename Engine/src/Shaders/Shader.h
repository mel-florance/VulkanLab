#ifndef VULKANLAB_SHADER_H
#define VULKANLAB_SHADER_H

#include <glad/glad.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include "Assets/Asset.h"

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
        VERTEX,
        FRAGMENT,
        GEOMETRY
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
     * Compile the shader given a the type of shader.
     */
    void compile(ShaderType type);

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

private:
    unsigned int program;
    std::string name;
    std::unordered_map<ShaderType, ShaderData> data;
};

#endif //VULKANLAB_SHADER_H

#ifndef VULKANLAB_MATERIAL_H
#define VULKANLAB_MATERIAL_H

#include "../Assets/Asset.h"

class Shader;

class Material : public Asset {
public:
    /**
     * Material constructor.
     * @param name
     */
    Material(const char *name);

    /**
     * Material destructor.
     */
    ~Material();

    /**
     * Return the name of the material.
     * @return
     */
    inline const char *getName() {
        return name;
    }

    /**
     * Set the name of the material.
     * @param value
     */
    inline void setName(const char *value) {
        this->name = value;
    }

    /**
     * Return the material shader.
     * @return
     */
    inline Shader *getShader() const {
        return this->shader;
    }

    /**
     * Set the material shader.
     * @param shader
     */
    inline void setShader(Shader *shader) {
        this->shader = shader;
    }

private:
    const char *name;
    Shader* shader;
};

#endif //VULKANLAB_MATERIAL_H

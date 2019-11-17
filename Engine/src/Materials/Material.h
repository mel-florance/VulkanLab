#ifndef VULKANLAB_MATERIAL_H
#define VULKANLAB_MATERIAL_H

#include "../Assets/Asset.h"

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

private:
    const char *name;
};

#endif //VULKANLAB_MATERIAL_H

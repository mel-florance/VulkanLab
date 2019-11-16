#ifndef VULKANLAB_TEXTURE_H
#define VULKANLAB_TEXTURE_H

#include "Assets/Asset.h"

class Texture : public Asset {
public:
    /**
     * Texture constructor.
     * @param name
     */
    Texture(const char* name);

    /**
     * Texture destructor.
     */
    ~Texture();

    /**
     * Return the name of the texture.
     * @return
     */
    inline const char* getName() { return name; }

private:
    const char* name;
};

#endif //VULKANLAB_TEXTURE_H

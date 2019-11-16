#ifndef VULKANLAB_TEXTURE_H
#define VULKANLAB_TEXTURE_H

#include <glad/glad.h>
#include "../Assets/Asset.h"

class Texture : public Asset {
public:
    /**
     * Texture constructor.
     * @param name
     */
    Texture(const char *name, const char *path);

    /**
     * Texture destructor.
     */
    ~Texture();

    /**
     * Return the OpenGL texture id.
     * @return
     */
    inline unsigned int getId() {
        return id;
    }

    /**
     * Return the name of the texture.
     * @return
     */
    inline const char *getName() {
        return name;
    }

    /**
     * Bind the texture for the next draw call.
     */
    void bind(unsigned int slot = 0);

    /**
     * Return the width of the texture.
     */
    inline int getWidth() {
        return width;
    }

    /**
     * Return the height of the texture.
     */
    inline int getHeight() {
        return height;
    }

    /**
     * Return the number of channels in the texture.
     */
    inline int getChannels() {
        return channels;
    }

    /**
     * Return the raw data of the texture.
     */
    inline unsigned char *getData() {
        return data;
    }

    /**
     * Set the id of the texture.
     * @param id
     */
    void setId(unsigned int id) {
        this->id = id;
    }

    /**
     * Set the name of the texture.
     * @param name
     */
    void setName(const char *name) {
        this->name = name;
    }

    /**
     * Set the width of the texture.
     * @param width
     */
    void setWidth(int width) {
        this->width = width;
    }

    /**
     * Set the height of the texture.
     * @param height
     */
    void setHeight(int height) {
        this->height = height;
    }

    /**
     * Set the numbers of channels of the texture.
     */
    void setChannels(int channels) {
        this->channels = channels;
    }

    /**
     * Set the data of the texture.
     * @param data
     */
    void setData(unsigned char *data) {
        this->data = data;
    }

private:
    unsigned int id;
    const char *name;
    int width;
    int height;
    int channels;
    unsigned char *data;
};

#endif //VULKANLAB_TEXTURE_H

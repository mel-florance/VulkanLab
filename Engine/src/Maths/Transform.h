#ifndef VULKANLAB_TRANSFORM_H
#define VULKANLAB_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
    Transform() :
        position(glm::vec3(0.0f)),
        rotation(glm::vec3(0.0f)),
        scale(glm::vec3(1.0f)),
        matrix(glm::mat4(1.0f))
    {

    }
    ~Transform() {}

    /**
     * Return the position component of the transformation.
     */
    inline const glm::vec3 &getPosition() const {
        return this->position;
    }

    /**
     * Set the position component of the transformation.
     */
    inline void setPosition(const glm::vec3 &position) {
        this->position = position;
    }

    /**
     * Return the rotation component of the transformation.
     */
    inline const glm::vec3 &getRotation() const {
        return this->rotation;
    }

    /**
     * Set the rotation component of the transformation.
     */
    inline void setRotation(const glm::vec3 &rotation) {
        this->rotation = rotation;
    }

    /**
     * Return the scale component of the transformation.
     */
    inline const glm::vec3 &getScale() const {
        return this->scale;
    }

    /**
     * Set the scale component of the transformation.
     */
    inline void setScale(const glm::vec3 &scale) {
        this->scale = scale;
    }

    /**
     * Return the matrix of the transformation.
     */
    glm::mat4 getMatrix();

    /**
     * Set the matrix of the transformation.
     */
    inline void setMatrix(const glm::mat4 &matrix) {
        this->matrix = matrix;
    }

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 matrix;
};

#endif //VULKANLAB_TRANSFORM_H

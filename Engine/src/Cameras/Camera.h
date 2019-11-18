#ifndef VULKANLAB_CAMERA_H
#define VULKANLAB_CAMERA_H

#include <glm/glm.hpp>

class Viewport;

class Camera {
public:
    /**
     * Camera constructor
     * @param viewport
     */
    Camera(Viewport *viewport);

    /**
     * Camera destructor
     */
    virtual ~Camera();

    /**
     * Return the camera position;
     * @return
     */
    inline glm::vec3 &getPosition() {
        return this->position;
    }

    /**
     * Set the camera position.
     */
    inline void setPosition(const glm::vec3 &position) {
        this->position = position;
    }

    /**
     * Return the viewport associated to the camera.
     * @return
     */
    inline Viewport *getViewport() {
        return this->viewport;
    }

    /**
     * Set the camera viewport to use.
     */
    inline void setViewport(Viewport *viewport) {
        this->viewport = viewport;
    }

    /**
     * Return the direction of the camera.
     */
    inline const glm::vec3 &getDirection() const {
        return direction;
    }

    /**
     * Set the direction of the camera.
     * @param direction
     */
    inline void setDirection(const glm::vec3 &direction) {
        Camera::direction = direction;
    }

    /**
     * Return the camera up vector.
     * @return
     */
    inline const glm::vec3 &getUp() const {
        return up;
    }

    /**
     * Set the camera up vector.
     * @param up
     */
    inline void setUp(const glm::vec3 &up) {
        Camera::up = up;
    }

    /**
     * Return the camera right vector.
     * @return
     */
    inline const glm::vec3 &getRight() const {
        return right;
    }

    /**
     * Set the camera right vector.
     * @param right
     */
    inline void setRight(const glm::vec3 &right) {
        Camera::right = right;
    }

    /**
     * Return the camera projection.
     * @return
     */
    inline const glm::mat4 &getProjection() const {
        return projection;
    }

    /**
     * Set the camera projection
     */
    inline void setProjection(const glm::mat4 &projection) {
        Camera::projection = projection;
    }

private:
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;
    Viewport *viewport;
};

#endif //VULKANLAB_CAMERA_H

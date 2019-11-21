#ifndef VULKANLAB_CAMERA_H
#define VULKANLAB_CAMERA_H

#include <glm/glm.hpp>
#include "../Events/Event.h"

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
     * Update the camera.
     */
    virtual void update(float delta) {}

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
        return this->direction;
    }

    /**
     * Set the direction of the camera.
     * @param direction
     */
    inline void setDirection(const glm::vec3 &direction) {
        this->direction = direction;
    }

    /**
     * Return the camera up vector.
     * @return
     */
    inline const glm::vec3 &getUp() const {
        return this->up;
    }

    /**
     * Set the camera up vector.
     * @param up
     */
    inline void setUp(const glm::vec3 &up) {
        this->up = up;
    }

    /**
     * Return the camera right vector.
     * @return
     */
    inline const glm::vec3 &getRight() const {
        return this->right;
    }

    /**
     * Set the camera right vector.
     * @param right
     */
    inline void setRight(const glm::vec3 &right) {
        this->right = right;
    }

    /**
     * Return the camera projection.
     * @return
     */
    inline const glm::mat4 &getProjection() const {
        return this->projection;
    }

    /**
     * Set the camera projection
     */
    inline void setProjection(const glm::mat4 &projection) {
        this->projection = projection;
    }

    /**
     * Return the camera field of view.
     * @return
     */
    inline float getFov() {
        return this->fov;
    }

    /**
     * Set the camera field of view.
     * @param fov
     */
    inline void setFov(float fov) {
        this->fov = fov;
    }

    /*
     * Return the camera aspect ratio.
     * viewport.width / viewport.height
     */
    inline float getAspectRatio() {
        return this->aspectRatio;
    }

    /**
     * Set the camera aspect ratio.
     * Must the width / height.
     * @param ratio
     */
    inline void setAspectRatio(float ratio) {
        this->aspectRatio = ratio;
    }

    /**
     * Return the camera far clipping plane.
     * @return
     */
    inline float getFar() {
        return this->clipping.y;
    }

    /*
     * Set the camera far clipping plane.
     */
    inline void setFar(float far) {
        this->clipping.y = far;
    }

    /*
     * Return the camera near clipping plane.
     */
    inline float getNear() {
        return this->clipping.x;
    }

    /*
     * Set the camera near clipping plane.
     */
    inline void setNear(float near) {
        this->clipping.x = near;
    }

    /**
     * Return the world up vector.
     * @return
     */
    inline const glm::vec3 &getWorldUp() const {
        return this->worldUp;
    }

    /**
     * Set the world up vector.
     */
    inline void setWorldUp(const glm::vec3 &worldUp) {
        this->worldUp = worldUp;
    }

    /**
     * Return the camera view matrix.
     * @return
     */
    inline const glm::mat4 &getView() const {
        return this->view;
    }

    /**
     * Set the camera view matrix.
     */
    inline void setView(const glm::mat4 &view) {
        this->view = view;
    }

protected:
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float fov;
    float aspectRatio;
    glm::vec2 clipping;

    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 position;
    Viewport *viewport;
};

#endif //VULKANLAB_CAMERA_H

#ifndef VULKANLAB_FPS_CAMERA_H
#define VULKANLAB_FPS_CAMERA_H

#include "Camera.h"

class FPSCamera : public Camera {
public:
    /**
     * FPS Camera constructor
     * @param viewport
     */
    FPSCamera(Viewport *viewport);

    /**
     * FPS Camera destructor
     */
    ~FPSCamera();

    /**
     * Compute camera axis vectors.
     */
    void compute();

    /**
     * Update the camera.
     */
    void update(float delta) override;

    /**
     * OnMouseMove event
     */
    void onMouseMove(Event* data) override;

    /**
     * OnMouseButton event
     */
    void onMouseButton(Event* data) override;

    /**
     * OnKeyboardInput event
     */
    void onKeyboardInput(Event* data) override;

    /**
     * OnMouseScroll event
     */
    void onMouseScroll(Event* data) override;

    /**
     * OnWindowResize event
     */
    void onWindowResize(Event* data) override;

    /**
     * Return the camera yaw axis value.
     * @return
     */
    inline float getYaw() const {
        return this->yaw;
    }

    /**
     * Set the camera yaw axis value.
     */
    inline void setYaw(float yaw) {
        this->yaw = yaw;
    }

    /**
     * Return the camera pitch axis value.
     */
    inline float getPitch() const {
        return this->pitch;
    }

    /**
     * Set the camera pitch axis value.
     */
    inline void setPitch(float pitch) {
        this->pitch = pitch;
    }

    /**
     * Return the camera roll axis value.
     */
    inline float getRoll() const {
        return this->roll;
    }

    /**
     * Set the camera roll axis value.
     */
    inline void setRoll(float roll) {
        this->roll = roll;
    }

    /**
     * Return the velocity of the camera.
     * @return
     */
    inline const glm::vec3 &getVelocity() const {
        return this->velocity;
    }

    /**
     * Set the velocity of the camera.
     * @param velocity
     */
    inline void setVelocity(const glm::vec3 &velocity) {
        this->velocity = velocity;
    }

private:
    float yaw, pitch, roll;
    glm::vec3 velocity;
    float speed;
    float delta;
    float friction;

    float sensitivity;
    glm::vec2 mouseOffset;
    glm::vec2 lastPosition;
    bool isFirstTimeMoving;
    bool constrainAxis;
public:

};

#endif //VULKANLAB_FPS_CAMERA_H

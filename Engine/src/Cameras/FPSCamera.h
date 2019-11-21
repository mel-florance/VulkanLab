#ifndef VULKANLAB_FPS_CAMERA_H
#define VULKANLAB_FPS_CAMERA_H

#include "Camera.h"

class FPSCamera :
    public Camera,
    public MouseEvents,
    public KeyboardEvents,
    public WindowEvents {
public:

    enum Direction {
        FORWARD  = 1 << 0,
        BACKWARD = 1 << 1,
        LEFT     = 1 << 2,
        RIGHT    = 1 << 3,
        UP       = 1 << 4,
        DOWN     = 1 << 5
    };

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
    void update(float delta);

    /**
     * OnMouseMove event
     */
    void onMouseMove(Event *data) override;

    /**
     * OnMouseButton event
     */
    void onMouseButton(Event *data) override;

    /**
     * OnKeyboardInput event
     */
    void onKeyboardInput(Event *data) override;

    /**
     * OnMouseScroll event
     */
    void onMouseScroll(Event *data) override;

    /**
     * OnWindowResize event
     */
    void onWindowResize(Event *data) override;


    /**
     * Return the camera yaw axis value.
     * @return
     */
    float getYaw() const {
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

    /**
     * Return the speed multiplier.
     * @return
     */
    inline float getSpeedMultiplier() const {
        return this->speedMultiplier;
    }

    /**
     * Set the speed multiplier.
     */
    inline void setSpeedMultiplier(float speedMultiplier) {
        this->speedMultiplier = speedMultiplier;
    }

    /**
     * Return the camera minimum speed limit.
     */
    inline float getMinSpeed() const {
        return this->minSpeed;
    }

    /**
     * Set the camera minimum speed limit.
     */
    inline void setMinSpeed(float minSpeed) {
        this->minSpeed = minSpeed;
    }

    /**
     * Return the camera max speed limit.
     */
    inline float getMaxSpeed() const {
        return this->maxSpeed;
    }

    /**
     * Set the camera max speed limit.
     */
    inline void setMaxSpeed(float maxSpeed) {
        this->maxSpeed = maxSpeed;
    }

    /**
     * Return the camera speed.
     * @return
     */
    inline float getSpeed() const {
        return this->speed;
    }

    /**
     * Set the camera speed.
     */
    inline void setSpeed(float speed) {
        this->speed = speed;
    }

    /**
     * Return the delta attached to the camera.
     */
    inline float getDelta() const {
        return this->delta;
    }

    /**
     * Set the camera delta.
     */
    inline void setDelta(float delta) {
        this->delta = delta;
    }

    /**
     * Return the camera movement friction.
     */
    inline float getFriction() const {
        return this->friction;
    }

    /**
     * Set the camera movement friction.
     */
    inline void setFriction(float friction) {
        this->friction = friction;
    }

    /**
     * Return the camera view sensitivity.
     */
    inline float getSensitivity() const {
        return this->sensitivity;
    }

    /**
     * Set the camera view sensitivity.
     */
    inline void setSensitivity(float sensitivity) {
        this->sensitivity = sensitivity;
    }

    /**
     * Return the mouse delta position.
     */
    inline const glm::vec2 &getMouseOffset() const {
        return this->mouseOffset;
    }

    /**
     * Set the mouse delta position.
     */
    inline void setMouseOffset(const glm::vec2 &mouseOffset) {
        this->mouseOffset = mouseOffset;
    }

    /**
     * Return the mouse last position.
     */
    inline const glm::vec2 &getLastPosition() const {
        return this->lastPosition;
    }

    /**
     * Set the time mouse position.
     */
    inline void setLastPosition(const glm::vec2 &lastPosition) {
        this->lastPosition = lastPosition;
    }

    /**
     * Check if the mouse moved for the first time.
     */
    inline bool isFirstTimeMoving1() const {
        return this->isFirstTimeMoving;
    }

    /**
     * Set a flag for saving the mouse first time movement.
     */
    inline void setIsFirstTimeMoving(bool isFirstTimeMoving) {
        this->isFirstTimeMoving = isFirstTimeMoving;
    }

    /**
     * Check if pitch & yaw constraints axis are enabled.
     */
    inline bool isConstrainAxis() const {
        return this->constrainAxis;
    }

    /**
     * Active the yaw & pitch constraints axis.
     */
    inline void setConstrainAxis(bool constrainAxis) {
        this->constrainAxis = constrainAxis;
    }

private:
    float delta;
    float yaw, pitch, roll;

    float friction;

    float sensitivity;
    glm::vec2 mouseOffset;
    glm::vec2 lastPosition;
    bool isFirstTimeMoving;
    bool constrainAxis;

    glm::vec3 velocity;
    float speed;
    float speedMultiplier;
    float minSpeed;
    float maxSpeed;

    char movementDirection;
};

#endif //VULKANLAB_FPS_CAMERA_H

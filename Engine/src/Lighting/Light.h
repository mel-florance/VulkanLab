#ifndef VULKANLAB_LIGHT_H
#define VULKANLAB_LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    enum Type {
        DIRECTIONAL = 0,
        POINT = 1,
        AREA = 2,
        SPOT = 3
    };

    Light(Light::Type type = Light::Type::POINT) : type(type) {}

    ~Light() {}

    /**
     * Return the light intensity.
     */
    inline float getIntensity() const {
        return intensity;
    }

    /**
     * Set the light intensity.
     */
    inline void setIntensity(float intensity) {
        this->intensity = intensity;
    }

    /**
     * Return the light color.
     */
    inline glm::vec3 &getColor() {
        return this->color;
    }

    /**
     * Set the light color.
     */
    inline void setColor(const glm::vec3 &color) {
        this->color = color;
    }

    /**
     * Return the light position.
     */
    inline glm::vec3 &getPosition() {
        return this->position;
    }

    /**
     * Set the light position.
     */
    inline void setPosition(const glm::vec3 &position) {
        this->position = position;
    }

    /**
     * Change the light type.
     */
    inline void setType(Type type) {
        this->type = type;
    }

    /**
     * Return the light type.
     */
    inline Type getType() {
        return this->type;
    }

    /**
     * Return the linear attenuation part of the light.
     * This is used for an attenuation model, typically
     * for Point lights.
     */
    inline float getLinear() const {
        return linear;
    }

    /**
     * Set the linear attenuation part of the light.
     * This is used for an attenuation model, typically
     * for Point lights or Spot lights.
     */
    inline void setLinear(float linear) {
        this->linear = linear;
    }

    /**
     * Return the constant attenuation part of the light.
     */
    inline float getConstant() const {
        return this->constant;
    }

    /**
     * Set the constant attenuation part of the light.
     * This is used for an attenuation model, typically
     * for Point lights or Spot lights.
     */
    inline void setConstant(float constant) {
        this->constant = constant;
    }

    /**
     * Return the quadratic attenuation part of the light.
     * This is used for an attenuation model, typically
     * for Point lights or Spot lights.
     */
    inline float getQuadratic() const {
        return this->quadratic;
    }

    /**
     * Set the quadratic attenuation part of the light.
     * This is used for an attenuation model, typically
     * for Point lights or Spot lights.
     */
    inline void setQuadratic(float quadratic) {
        this->quadratic = quadratic;
    }

    /**
     * Return the inner cutoff cone of the light.
     * This is reserved for spot lights.
     */
    inline float getInnerCutoff() const {
        return this->innerCutoff;
    }

    /**
     * Set the inner cutoff cone of the light.
     * This is reserved for the cone of the light.
     */
    inline void setInnerCutoff(float innerCutoff) {
        this->innerCutoff = innerCutoff;
    }

    /**
     * Return the outer cutoff cone of the light.
     * This is reserved for spot lights.
     */
    inline float getOuterCutoff() const {
        return this->outerCutoff;
    }

    /**
     * Set the outer cutoff cone of the light.
     * This is reserved for spot lights.
     */
    inline void setOuterCutoff(float outerCutoff) {
        this->outerCutoff = outerCutoff;
    }

private:
    // Common parameters
    Type type;
    float intensity;
    glm::vec3 color;
    glm::vec3 position;

    // Attenuation parameters
    float linear;
    float constant;
    float quadratic;

    // Cone parameters
    float innerCutoff;
    float outerCutoff;
};

#endif //VULKANLAB_LIGHT_H

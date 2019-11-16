#include "Viewport.h"

Viewport::Viewport(
        const glm::vec4 &color,
        const glm::vec2 &position,
        const glm::vec2 &size
)
        :
        clearColor(color),
        position(position),
        size(size) {

}

Viewport::~Viewport() {

}
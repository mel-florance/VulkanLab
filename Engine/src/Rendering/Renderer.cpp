#include "Renderer.h"
#include "../Display/Viewport.h"

Renderer::Renderer(Viewport* viewport) :
    viewport(viewport) {
}

Renderer::~Renderer() {

}

void Renderer::render() {
    this->viewport->clear();
}
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Display/Window.h"
#include "Display/Viewport.h"
#include "Assets/AssetManager.h"
#include "Shaders/Shader.h"
#include "Texturing/Texture.h"
#include "Geometry/Mesh.h"
#include "Materials/Material.h"
#include "Buffers/ArrayBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"

int main(int argc, char **argv) {

    // Initialize engine classes.
    const char *self_path = argv[0];
    Window *window = new Window();
    Viewport *viewport = new Viewport();
    AssetManager *am = new AssetManager(self_path);

    // Load some stuff.
    Texture *texture = am->load<Texture>("/home/mel/Projects/VulkanLab/Resources/omg.jpg", "omg");
    am->load<Material>("material_path", "material_path");
    Shader *defaultShader = am->load<Shader>("default", "default");

    Mesh *triangle = new Mesh();

    // Create mesh vertices of a plane
    std::vector vertices = {
        // First triangle
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.5f,
        // Second triangle
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f
    };

    // Create mesh uv coordinates of a plane
    std::vector uvs = {
        // First triangle
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        // Second triangle
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    triangle->setVertices(vertices);
    triangle->setUvs(uvs);

    // Bind the new shader.
    defaultShader->bind();

    // Create the main array buffer.
    ArrayBuffer *vao = new ArrayBuffer();
    vao->bind();

    // Create a vertex buffer for the vertices to be store.
    VertexBuffer *vbo_position = new VertexBuffer();
    vbo_position->bind();
    vbo_position->setData(vertices.data(), vertices.size() * sizeof(float));

    // Create a position attribute for the vertices.
    VertexBuffer::AttributeData *position_attribute = new VertexBuffer::AttributeData();
    position_attribute->index = 0;
    position_attribute->size = 3;
    vbo_position->setAttribute(position_attribute);

    // Create a vertex buffer for the uvs to be store.
    VertexBuffer *vbo_uvs = new VertexBuffer();
    vbo_uvs->bind();
    vbo_uvs->setData(uvs.data(), uvs.size() * sizeof(float));

    // Create a uv coordinate attribute for the uvs.
    VertexBuffer::AttributeData *texture_attribute = new VertexBuffer::AttributeData();
    texture_attribute->index = 1;
    texture_attribute->size = 2;
    vbo_uvs->setAttribute(texture_attribute);

//    // Index buffer
//    IndexBuffer *indexBuffer = new IndexBuffer();
//    indexBuffer->setData(indices, sizeof(indices));

    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);

    // Main render loop
    window->update([=](glm::ivec2 &size) {
        viewport->setSize(size);
        viewport->apply();
        viewport->clear();

        texture->bind();
        vao->bind();
        triangle->draw();
    });

    delete window;

    return 0;
}

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

    const char *self_path = argv[0];
    Window *window = new Window();
    Viewport *viewport = new Viewport();
    AssetManager *am = new AssetManager(self_path);

    Texture *texture = am->load<Texture>("/home/mel/Projects/VulkanLab/Resources/omg.jpg", "omg");
    am->load<Material>("material_path", "material_path");
    Shader *defaultShader = am->load<Shader>("default", "default");
    Mesh *triangle = new Mesh();

    std::vector vertices = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };


    triangle->setVertices(vertices);

    defaultShader->bind();


    ArrayBuffer *vao = new ArrayBuffer();
    vao->bind();

    VertexBuffer *vbo = new VertexBuffer();
    vbo->bind();
    vbo->setData(&vertices[0], vertices.size() * sizeof(float));

    // Index buffer
    IndexBuffer *indexBuffer = new IndexBuffer();
    indexBuffer->setData(indices, sizeof(indices));

    // Position buffer
    VertexBuffer::AttributeData *position_attribute = new VertexBuffer::AttributeData();
    position_attribute->index = 0;
    position_attribute->size = 3;
    position_attribute->stride = 3 * sizeof(float);
    vbo->setAttribute(position_attribute);
    vao->enableAttribute(0);

    // Color buffer
    VertexBuffer::AttributeData *color_attribute = new VertexBuffer::AttributeData();
    color_attribute->index = 1;
    color_attribute->size = 3;
    color_attribute->stride = 6 * sizeof(float);
    color_attribute->pointer = (void *) (3 * sizeof(float));
    vbo->setAttribute(color_attribute);
    vao->enableAttribute(1);

    // Texture coordinates
    VertexBuffer::AttributeData *texture_attribute = new VertexBuffer::AttributeData();
    texture_attribute->index = 2;
    texture_attribute->size = 2;
    texture_attribute->stride = 8 * sizeof(float);
    texture_attribute->pointer = (void *) (6 * sizeof(float));
    vbo->setAttribute(texture_attribute);
    vao->enableAttribute(2);

    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);

    window->update([=](glm::ivec2 &size)
    {
        viewport->setSize(size);
        viewport->apply();
        viewport->clear();

        vao->bind();
        indexBuffer->bind();
        texture->bind();
        triangle->draw();
    });

    delete window;

    return 0;
}

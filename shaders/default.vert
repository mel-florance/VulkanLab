#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUvs;

out vec2 uvs;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    uvs = aUvs;
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
}
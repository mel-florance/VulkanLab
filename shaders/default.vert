#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUvs;

out vec2 uvs;

void main() {
    uvs = aUvs;
    gl_Position = vec4(aPos, 1.0);
}